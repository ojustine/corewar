#include <logger.h>
#include "mem.h"
#include "ft_regex.h"

#define OKPAT		1
#define NOPAT		0

t_byte			automaton[MAXNFA];
t_byte *mp;
t_byte *lp;
t_byte *sp;

static int		status = NOPAT;
static int		tagstk[MAXTAG];
static t_byte	bittab[BITBLK];
static t_byte	bitarr[] = {1, 2, 4, 8, 16, 32, 64, 128};


static inline void	chset(t_byte c)
{
	bittab[(c & BLKIND) >> 3] |= bitarr[c & BITIND];
}
static inline int	badpat(char *err)
{
	*automaton = END;
	log_error(__func__, "Regex compilation failed: %s", err);
	return (0);
}
#define store(x)    *mp++ = x


static inline int	re_comp_class(char *p)
{
	const t_byte	mask = (*++p == '^' && ++p) ? 0377 : 0;
	register t_byte	c;
	register int	n;

	store(CCL);
	if (*p == ']')
		chset(*p++);
	while (*p && *p != ']')
		if (*(p + 1) && *(p + 1) == '-' && *(p + 2) && *(p + 2) != ']')
		{
			c = *p;
			while (c <= *(p + 2))
				chset((t_byte)c++);
			p += 3;
		}
		else
			chset(*p++);
	if (!*p)
		return badpat("Missing ]");
	n = 0;
	while (n < BITBLK)
	{
		store(mask ^ bittab[n]);
		bittab[n++] = (char)0;
	}
	return (0);
}

int		re_comp(char *pat)
{
	register char *p;

	register int tagi = 0;
	register int tagc = 1;

	register int n;
	register t_byte mask;
	int c1, c2;

	mp = automaton;
	sp = automaton;
	if (!pat || !*pat)
	{
		if (status == OKPAT)
			return 0;
		else
			return badpat("No previous regular expression");
	}
	status = NOPAT;

	p = pat;
	while (*p)
	{
		lp = mp;
		switch (*p)
		{
			case '.':               /* match any char..  */
				store(ANY);
				break;

			case '^':               /* match beginning.. */
				if (p == pat)
					store(BOL);
				else
				{
					store(CHR);
					store(*p);
				}
				break;

			case '$':               /* match endofline.. */
				if (!*(p + 1))
					store(EOL);
				else
				{
					store(CHR);
					store(*p);
				}
				break;

			case '[':
				re_comp_class(p);
				break;

			case '*':
			case '+':
				if (p == pat)
					return badpat("Empty closure");
				lp = sp;//last op
				if (*lp == CLO)
					break;
				if (*lp == BOL || *lp == BOT || *lp == EOT
				|| *lp == BOW || *lp == EOW || *lp == REF)
					return badpat("Illegal closure");
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

			case '\\':
				switch (*++p)
				{

					case '(':
						if (tagc < MAXTAG)
						{
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
						if (tagi > 0)
						{
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
						n = *p - '0';
						if (tagi > 0 && tagstk[tagi] == n)
							return badpat("Cyclical reference");
						if (tagc > n)
						{
							store(REF);
							store(n);
						}
						else
							return badpat("Undetermined reference");
						break;
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
		p++;
	}
	if (tagi > 0)
		return badpat("Unmatched \\(");
	store(END);
	status = OKPAT;
	return (1);
}

