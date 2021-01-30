#include "mem.h"
#include "ft_regex.h"

extern t_byte	automaton[MAXNFA];
static t_byte	bitarr[] = {1, 2, 4, 8, 16, 32, 64, 128};


#define bopat    _ldap_bopat
#define eopat    _ldap_eopat

static char *bol;
char *bopat[MAXTAG];
char *eopat[MAXTAG];
#ifdef NEEDPROTOS
static char *pmatch( char *lp, t_byte *ap );
#else /* NEEDPROTOS */

static char *pmatch();

#endif /* NEEDPROTOS */

/*
 * re_exec:
 * 	execute automaton to find a match.
 *
 *	special cases: (automaton[0])
 *		BOL
 *			Match only once, starting from the
 *			beginning.
 *		CHR
 *			First locate the character without
 *			calling pmatch, and if found, call
 *			pmatch for the remaining string.
 *		END
 *			re_comp failed, poor luser did not
 *			check for it. Fail fast.
 *
 *	If a match is found, bopat[0] and eopat[0] are set
 *	to the beginning and the end of the matched fragment,
 *	respectively.
 *
 */

int
re_exec(char *lp)
{
	register char c;
	register char *ep = 0;
	register t_byte *ap = automaton;

	bol = lp;

	bopat[0] = 0;
	bopat[1] = 0;
	bopat[2] = 0;
	bopat[3] = 0;
	bopat[4] = 0;
	bopat[5] = 0;
	bopat[6] = 0;
	bopat[7] = 0;
	bopat[8] = 0;
	bopat[9] = 0;

	switch (*ap)
	{

		case BOL:            /* anchored: match from BOL only */
			ep = pmatch(lp, ap);
			break;
		case CHR:            /* ordinary char: locate it fast */
			c = *(ap + 1);
			while (*lp && *lp != c)
				lp++;
			if (!*lp)        /* if EOS, fail, else fall thru. */
				return 0;
		default:            /* regular matching all the way. */
			do
			{
				if ((ep = pmatch(lp, ap)))
					break;
				lp++;
			} while (*lp);

			break;
		case END:            /* munged automaton. fail always */
			return 0;
	}
	if (!ep)
		return 0;

	bopat[0] = lp;
	eopat[0] = ep;
	return 1;
}

/*
 * pmatch: internal routine for the hard part
 *
 * 	This code is partly snarfed from an early grep written by
 *	David Conroy. The backref and tag stuff, and various other
 *	innovations are by oz.
 *
 *	special case optimizations: (automaton[n], automaton[n+1])
 *		CLO ANY
 *			We KNOW .* will match everything upto the
 *			end of line. Thus, directly go to the end of
 *			line, without recursive pmatch calls. As in
 *			the other closure cases, the remaining pattern
 *			must be matched by moving backwards on the
 *			string recursively, to find a match for xy
 *			(x is ".*" and y is the remaining pattern)
 *			where the match satisfies the LONGEST match for
 *			x followed by a match for y.
 *		CLO CHR
 *			We can again scan the string forward for the
 *			single char and at the point of failure, we
 *			execute the remaining automaton recursively, same as
 *			above.
 *
 *	At the end of a successful match, bopat[n] and eopat[n]
 *	are set to the beginning and end of subpatterns matched
 *	by tagged expressions (n = 1 to 9).
 *
 */

#ifndef re_fail

extern void re_fail();

#endif /* re_fail */

/*
 * character classification table for word boundary operators BOW
 * and EOW. the reason for not using ctype macros is that we can
 * let the user add into our own table. see re_modw. This table
 * is not in the bitset form, since we may wish to extend it in the
 * future for other character classifications.
 *
 *	TRUE for 0-9 A-Z a-z _
 */
static char chrtyp[MAXCHR] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
		0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 0, 0, 0, 0, 0
};

#define inascii(x)    (0177&(x))
#define iswordc(x)    chrtyp[inascii(x)]
#define isinset(x, y)    ((x)[((y)&BLKIND)>>3] & bitarr[(y)&BITIND])

/*
 * skip values for CLO XXX to skip past the closure
 */

#define ANYSKIP    2    /* [CLO] ANY END ...	     */
#define CHRSKIP    3    /* [CLO] CHR chr END ...     */
#define CCLSKIP 18    /* [CLO] CCL 16bytes END ... */

static char *
pmatch(char *lp, t_byte *ap)
{
	register int op, c, n;
	register char *e;        /* extra pointer for CLO */
	register char *bp;        /* beginning of subpat.. */
	register char *ep;        /* ending of subpat..	 */
	char *are;            /* to save the line ptr. */

	while ((op = *ap++) != END)
		switch (op)
		{

			case CHR:
				if (*lp++ != *ap++)
					return 0;
				break;
			case ANY:
				if (!*lp++)
					return 0;
				break;
			case CCL:
				c = *lp++;
				if (!isinset(ap, c))
					return 0;
				ap += BITBLK;
				break;
			case BOL:
				if (lp != bol)
					return 0;
				break;
			case EOL:
				if (*lp)
					return 0;
				break;
			case BOT:
				bopat[(int)*ap++] = lp;
				break;
			case EOT:
				eopat[(int)*ap++] = lp;
				break;
			case BOW:
				if (((lp != bol) && (iswordc(lp[-1]) != 0)) ||
					(iswordc(*lp) == 0))
					return 0;
				break;
			case EOW:
				if ((lp == bol) || (iswordc(lp[-1]) == 0) ||
					(iswordc(*lp) != 0))
					return 0;
				break;
			case REF:
				n = *ap++;
				bp = bopat[n];
				ep = eopat[n];
				while (bp < ep)
					if (*bp++ != *lp++)
						return 0;
				break;
			case CLO:
				are = lp;
				switch (*ap)
				{

					case ANY:
						while (*lp)
							lp++;
						n = ANYSKIP;
						break;
					case CHR:
						c = *(ap + 1);
						while (*lp && c == *lp)
							lp++;
						n = CHRSKIP;
						break;
					case CCL:
						while ((c = *lp) && isinset(ap + 1, c))
							lp++;
						n = CCLSKIP;
						break;
					default:
						//re_fail("closure: bad automaton.", *ap);
						return 0;
				}

				ap += n;

				while (lp >= are)
				{
					if (NULL != (e = pmatch(lp, ap)))
						return e;
					--lp;
				}
				return 0;
			default:
				//re_fail("re_exec: bad automaton.", op);
				return 0;
		}
	return lp;
}

/*
 * re_modw:
 *	add new characters into the word table to change re_exec's
 *	understanding of what a word should look like. Note that we
 *	only accept additions into the word definition.
 *
 *	If the string parameter is 0 or null string, the table is
 *	reset back to the default containing A-Z a-z 0-9 _. [We use
 *	the compact bitset representation for the default table]
 */

static t_byte deftab[16] = {
		0, 0, 0, 0, 0, 0, 0377, 003, 0376, 0377, 0377, 0207,
		0376, 0377, 0377, 007
};

void
re_modw(char *s)
{
	register int i;

	if (!s || !*s)
	{
		for (i = 0; i < MAXCHR; i++)
			if (!isinset(deftab, i))
				iswordc(i) = 0;
	}
	else
		while (*s)
			iswordc(*s++) = 1;
}

/*
 * re_subs:
 *	substitute the matched portions of the src in dst.
 *
 *	&	substitute the entire matched pattern.
 *
 *	\digit	substitute a subpattern, with the given	tag number.
 *		Tags are numbered from 1 to 9. If the particular
 *		tagged subpattern does not exist, null is substituted.
 */
int
re_subs(char *src, char *dst)
{
	register char c;
	register int pin;
	register char *bp;
	register char *ep;

	if (!*src || !bopat[0])
		return 0;

	while (0 != (c = *src++))
	{
		switch (c)
		{

			case '&':
				pin = 0;
				break;

			case '\\':
				c = *src++;
				if (c >= '0' && c <= '9')
				{
					pin = c - '0';
					break;
				}

			default:
				*dst++ = c;
				continue;
		}

		if ((bp = bopat[pin]) && (ep = eopat[pin]))
		{
			while (*bp && bp < ep)
				*dst++ = *bp++;
			if (bp < ep)
				return 0;
		}
	}
	*dst = (char)0;
	return 1;
}

#ifdef DEBUG
/*
 * symbolic - produce a symbolic dump of the automaton
 */
symbolic( char *s )
{
	printf("pattern: %s\n", s);
	printf("nfacode:\n");
	nfadump(automaton);
}

static
nfadump( t_byte *ap)
{
	register int n;

	while (*ap != END)
		switch(*ap++) {
		case CLO:
			printf("CLOSURE");
			nfadump(ap);
			switch(*ap) {
			case CHR:
				n = CHRSKIP;
				break;
			case ANY:
				n = ANYSKIP;
				break;
			case CCL:
				n = CCLSKIP;
				break;
			}
			ap += n;
			break;
		case CHR:
			printf("\tCHR %c\n",*ap++);
			break;
		case ANY:
			printf("\tANY .\n");
			break;
		case BOL:
			printf("\tBOL -\n");
			break;
		case EOL:
			printf("\tEOL -\n");
			break;
		case BOT:
			printf("BOT: %d\n",*ap++);
			break;
		case EOT:
			printf("EOT: %d\n",*ap++);
			break;
		case BOW:
			printf("BOW\n");
			break;
		case EOW:
			printf("EOW\n");
			break;
		case REF:
			printf("REF: %d\n",*ap++);
			break;
		case CCL:
			printf("\tCCL [");
			for (n = 0; n < MAXCHR; n++)
				if (isinset(ap,(t_byte)n)) {
					if (n < ' ')
						printf("^%c", n ^ 0x040);
					else
						printf("%c", n);
				}
			printf("]\n");
			ap += BITBLK;
			break;
		default:
			printf("bad automaton. opcode %o\n", ap[-1]);
			exit(1);
			break;
		}
}
#endif

//#endif //_OS_NEXT_