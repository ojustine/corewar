#include <printf.h>

#define MAXNFA  1024
#define MAXTAG  10

#define OKP     1
#define NOP     0

#define CHR     1
#define ANY     2
#define CCL     3
#define BOL     4
#define EOL     5
#define BOT     6
#define EOT     7
#define BOW	8
#define EOW	9
#define REF     10
#define CLO     11

#define END     0

#define MAXCHR	128
#define CHRBIT	8
#define BITBLK	MAXCHR/CHRBIT
#define BLKIND	0170
#define BITIND	07

#if defined( DOS ) || defined( _WIN32 ) || defined(SUN)
typedef unsigned char CHAR;
#else /* DOS */
typedef /*unsigned*/ char CHAR;
#endif /* DOS */

static int  tagstk[MAXTAG];             /* subpat tag stack..*/
static CHAR nfa[MAXNFA];		/* automaton..       */
static int  sta = NOP;               	/* status of lastpat */

static CHAR bittab[BITBLK];		/* bit table for CCL */
					/* pre-set bits...   */
static CHAR bitarr[] = {1,2,4,8,16,32,64,128};

static void
chset(CHAR c)
{
	bittab[((c) & BLKIND) >> 3] |= bitarr[(c) & BITIND];
}

#define badpat(x)	(*nfa = END, x)
#define store(x)	*mp++ = x

char *re_comp( char *pat )
{
	register char *p;               /* pattern pointer   */
	register CHAR *mp=nfa;          /* nfa pointer       */
	register CHAR *lp;              /* saved pointer..   */
	register CHAR *sp=nfa;          /* another one..     */

	register int tagi = 0;          /* tag stack index   */
	register int tagc = 1;          /* actual tag count  */

	register int n;
	register CHAR mask;		/* xor mask -CCL/NCL */
	int c1, c2;

	if (!pat || !*pat)
		if (sta)
			return 0;
		else
			return badpat("No previous regular expression");
	sta = NOP;

	for (p = pat; *p; p++) {
		lp = mp;
		switch(*p) {

		case '.':               /* match any char..  */
			store(ANY);
			break;

		case '^':               /* match beginning.. */
			if (p == pat)
				store(BOL);
			else {
				store(CHR);
				store(*p);
			}
			break;

		case '$':               /* match endofline.. */
			if (!*(p+1))
				store(EOL);
			else {
				store(CHR);
				store(*p);
			}
			break;

		case '[':               /* match char class..*/
			store(CCL);

			if (*++p == '^') {
				mask = 0377;
				p++;
			}
			else
				mask = 0;

			if (*p == '-')		/* real dash */
				chset(*p++);
			if (*p == ']')		/* real brac */
				chset(*p++);
			while (*p && *p != ']') {
				if (*p == '-' && *(p+1) && *(p+1) != ']') {
					p++;
					c1 = *(p-2) + 1;
					c2 = *p++;
					while (c1 <= c2)
						chset((CHAR)c1++);
				}
#ifdef EXTEND
				else if (*p == '\\' && *(p+1)) {
					p++;
					chset(*p++);
				}
#endif
				else
					chset(*p++);
			}
			if (!*p)
				return badpat("Missing ]");

			for (n = 0; n < BITBLK; bittab[n++] = (char) 0)
				store(mask ^ bittab[n]);

			break;

		case '*':               /* match 0 or more.. */
		case '+':               /* match 1 or more.. */
			if (p == pat)
				return badpat("Empty closure");
			lp = sp;		/* previous opcode */
			if (*lp == CLO)		/* equivalence..   */
				break;
			switch(*lp) {

			case BOL:
			case BOT:
			case EOT:
			case BOW:
			case EOW:
			case REF:
				return badpat("Illegal closure");
			default:
				break;
			}

			if (*p == '+')
				for (sp = mp; lp < sp; lp++)
					store(*lp);

			store(END);
			store(END);
			sp = mp;
			while (--mp > lp)
				*mp = mp[-1];
			store(CLO);
			mp = sp;
			break;

		case '\\':              /* tags, backrefs .. */
			switch(*++p) {

			case '(':
				if (tagc < MAXTAG) {
					tagstk[++tagi] = tagc;
					store(BOT);
					store(tagc++);
				}
				else
					return badpat("Too many \\(\\) pairs");
				break;
			case ')':
				if (*sp == BOT)
					return badpat("Null pattern inside \\(\\)");
				if (tagi > 0) {
					store(EOT);
					store(tagstk[tagi--]);
				}
				else
					return badpat("Unmatched \\)");
				break;
			case '<':
				store(BOW);
				break;
			case '>':
				if (*sp == BOW)
					return badpat("Null pattern inside \\<\\>");
				store(EOW);
				break;
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				n = *p-'0';
				if (tagi > 0 && tagstk[tagi] == n)
					return badpat("Cyclical reference");
				if (tagc > n) {
					store(REF);
					store(n);
				}
				else
					return badpat("Undetermined reference");
				break;
#ifdef EXTEND
			case 'b':
				store(CHR);
				store('\b');
				break;
			case 'n':
				store(CHR);
				store('\n');
				break;
			case 'f':
				store(CHR);
				store('\f');
				break;
			case 'r':
				store(CHR);
				store('\r');
				break;
			case 't':
				store(CHR);
				store('\t');
				break;
#endif
			default:
				store(CHR);
				store(*p);
			}
			break;

		default :               /* an ordinary char  */
			store(CHR);
			store(*p);
			break;
		}
		sp = lp;
	}
	if (tagi > 0)
		return badpat("Unmatched \\(");
	store(END);
	sta = OKP;
	return 0;
}


static char *bol;
char *bopat[MAXTAG];
char *eopat[MAXTAG];
#ifdef NEEDPROTOS
static char *pmatch( char *lp, CHAR *ap );
#else /* NEEDPROTOS */
static char *pmatch();
#endif /* NEEDPROTOS */

int re_exec( char *lp )
{
	register char c;
	register char *ep = 0;
	register CHAR *ap = nfa;

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

	switch(*ap) {

	case BOL:			/* anchored: match from BOL only */
		ep = pmatch(lp,ap);
		break;
	case CHR:			/* ordinary char: locate it fast */
		c = *(ap+1);
		while (*lp && *lp != c)
			lp++;
		if (!*lp)		/* if EOS, fail, else fall thru. */
			return 0;
	default:			/* regular matching all the way. */
		do {
			if ((ep = pmatch(lp,ap)))
				break;
			lp++;
		} while (*lp);

		break;
	case END:			/* munged automaton. fail always */
		return 0;
	}
	if (!ep)
		return 0;

	bopat[0] = lp;
	eopat[0] = ep;
	return 1;
}

void re_fail(msg, op)
{
	printf(msg);
}

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

#define inascii(x)	(0177&(x))
#define iswordc(x) 	chrtyp[inascii(x)]
#define isinset(x,y) 	((x)[((y)&BLKIND)>>3] & bitarr[(y)&BITIND])

#define ANYSKIP	2 	/* [CLO] ANY END ...	     */
#define CHRSKIP	3	/* [CLO] CHR chr END ...     */
#define CCLSKIP 18	/* [CLO] CCL 16bytes END ... */

static char *pmatch( char *lp, CHAR *ap)
{
	register int op, c, n;
	register char *e;		/* extra pointer for CLO */
	register char *bp;		/* beginning of subpat.. */
	register char *ep;		/* ending of subpat..	 */
	char *are;			/* to save the line ptr. */

	while ((op = *ap++) != END)
		switch(op) {

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
			if (!isinset(ap,c))
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
			bopat[*ap++] = lp;
			break;
		case EOT:
			eopat[*ap++] = lp;
			break;
 		case BOW:
			if (lp!=bol && iswordc(lp[-1]) || !iswordc(*lp))
				return 0;
			break;
		case EOW:
			if (lp==bol || !iswordc(lp[-1]) || iswordc(*lp))
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
			switch(*ap) {

			case ANY:
				while (*lp)
					lp++;
				n = ANYSKIP;
				break;
			case CHR:
				c = *(ap+1);
				while (*lp && c == *lp)
					lp++;
				n = CHRSKIP;
				break;
			case CCL:
				while ((c = *lp) && isinset(ap+1,c))
					lp++;
				n = CCLSKIP;
				break;
			default:
				re_fail("closure: bad nfa.", *ap);
				return 0;
			}

			ap += n;

			while (lp >= are) {
				if (e = pmatch(lp, ap))
					return e;
				--lp;
			}
			return 0;
		default:
			re_fail("re_exec: bad nfa.", op);
			return 0;
		}
	return lp;
}

static CHAR deftab[16] = {
	0, 0, 0, 0, 0, 0, 0377, 003, 0376, 0377, 0377, 0207,
	0376, 0377, 0377, 007
};

void re_modw( char *s )
{
	register int i;

	if (!s || !*s) {
		for (i = 0; i < MAXCHR; i++)
			if (!isinset(deftab,i))
				iswordc(i) = 0;
	}
	else
		while(*s)
			iswordc(*s++) = 1;
}

int re_subs( char *src, char *dst)
{
	register char c;
	register int  pin;
	register char *bp;
	register char *ep;

	if (!*src || !bopat[0])
		return 0;

	while (c = *src++) {
		switch(c) {

		case '&':
			pin = 0;
			break;

		case '\\':
			c = *src++;
			if (c >= '0' && c <= '9') {
				pin = c - '0';
				break;
			}

		default:
			*dst++ = c;
			continue;
		}

		if ((bp = bopat[pin]) && (ep = eopat[pin])) {
			while (*bp && bp < ep)
				*dst++ = *bp++;
			if (bp < ep)
				return 0;
		}
	}
	*dst = (char) 0;
	return 1;
}
