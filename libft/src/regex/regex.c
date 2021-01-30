// Public Domain Tiny Regular Expressions Library
// Forked from https://github.com/kokke/tiny-regex-c
//
// Supports:
// ---------
//   '^'        Start anchor, matches start of string
//   '$'        End anchor, matches end of string
// ---------
//   '*'        Asterisk, match zero or more (greedy, *? lazy)
//   '+'        Plus, match one or more (greedy, +? lazy)
//   '{m,n}'    Quantifier, match min. 'm' and max. 'n' (greedy, {m,n}? lazy)
//   '{m}'                  exactly 'm'
//   '{m,}'                 match min 'm' and max. MAX_QUANT
//   '?'        Question, match zero or one (greedy, ?? lazy)
// ---------
//   '.'        Dot, matches any character except newline (\r, \n)
//   '[abc]'    Character class, match if one of {'a', 'b', 'c'}
//   '[^abc]'   Inverted class, match if NOT one of {'a', 'b', 'c'}
//   '[a-zA-Z]' Character ranges, the character set of the ranges { a-z | A-Z }
//   '\s'       Whitespace, \t \f \r \n \v and spaces
//   '\S'       Non-whitespace
//   '\w'       Alphanumeric, [a-zA-Z0-9_]
//   '\W'       Non-alphanumeric
//   '\d'       Digits, [0-9]
//   '\D'       Non-digits
//   '\X'       Character itself; X in [^sSwWdD] (e.g. '\\' is '\')
// ---------


//#define TRE_SILENT // disable inclusion of stdio and printing
//#define TRE_DOTANY // dot matches anything including newline

#include "ft_regex.h"
#include "string.h"

#ifndef TRE_SILENT

#include "stdio.h"
#include "stdarg.h"

#endif

int tre_err(const char *format, ...)
{
#ifdef TRE_SILENT
	(void) format;
#else
	fputs("Error: ", stderr);
	va_list args;
	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
	fputs("\n", stderr);
	fflush(stderr);
#endif
	return 0;
}

const char *
tre_compile_match(const char *pattern, const char *text, const char **end)
{
	tre_comp tregex = {0};
	if (!re_compile(pattern, &tregex))
	{
		tre_err("Compiling pattern failed");
		return 0;
	}

	return tre_match(&tregex, text, end);
}

static const char *
matchpattern(const re_node *nodes, const char *text, const char *tend);

const char *
tre_nmatch(const tre_comp *tregex, const char *text, unsigned tlen,
		   const char **end)
{
	if (!tregex || !text || !tlen)
	{
		tre_err("NULL text or tre_comp");
		return 0;
	}

	const char *tend = text + tlen;
	const char *mend;
	const re_node *nodes = tregex->nodes;

	if (nodes->type == RE_BEGIN)
	{
		mend = matchpattern(nodes + 1, text, tend);
		if (mend)
		{
			if (end)
				*end = mend;
			return text;
		}
		return 0;
	}

	do
	{
		mend = matchpattern(nodes, text, tend);
		if (mend)
		{
			//if (!*text) //Fixme: ???
			//    return 0;
			if (end)
				*end = mend;
			return text;
		}
	} while (tend > text++);

	return 0;
}

const char *
tre_match(const tre_comp *tregex, const char *text, const char **end)
{
	return tre_nmatch(tregex, text, strlen(text), end);
}




#define TRE_MATCHDIGIT(c) ((c >= '0') && (c <= '9'))
#define TRE_MATCHALPHA(c) ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'))
#define TRE_MATCHSPACE(c) ((c == ' ') || (c == '\t') || (c == '\n') || (c == '\r') || (c == '\f') || (c == '\v'))
#define TRE_MATCHALNUM(c) ((c == '_') || TRE_MATCHALPHA(c) || TRE_MATCHDIGIT(c))

static int matchmetachar(char c, char mc)
{
	switch (mc)
	{
		case 'd':
			return TRE_MATCHDIGIT(c);
		case 'D':
			return !TRE_MATCHDIGIT(c);
		case 'w':
			return TRE_MATCHALNUM(c);
		case 'W':
			return !TRE_MATCHALNUM(c);
		case 's':
			return TRE_MATCHSPACE(c);
		case 'S':
			return !TRE_MATCHSPACE(c);
		default:
			return (c == mc);
	}
}

static int matchcharclass(char c, const char *str)
{
	char rmax;
	while (*str != '\0')
	{
		if (str[0] == '\\')
		{
			if (matchmetachar(c, str[1]))
				return 1;
			str += 2;
			if (RE_ISMETA(*str))
				continue;
		}
		else
		{
			if (c == *str)
				return 1;
			str += 1;
		}

		if (*str != '-' || !str[1])
			continue;
		rmax = (str[1] == '\\');
		if (rmax && RE_ISMETA(str[2]))
			continue;

		rmax = rmax ? str[2] : str[1];
		if (c >= str[-1] && c <= rmax)
			return 1;
		str++;

	}

	return 0;
}


#ifndef TRE_DOTANY
#define TRE_MATCHDOT(c)   ((c != '\n') && (c != '\r'))
#else
#define TRE_MATCHDOT(c)   (1)
#endif

static int matchone(const re_node *tnode, char c)
{
	switch (tnode->type)
	{
		case RE_CHAR:
			return (tnode->u.ch == c);
		case RE_DOT:
			return TRE_MATCHDOT(c);
		case RE_CLASS:
			return matchcharclass(c, tnode->u.cc);
		case RE_NCLASS:
			return !matchcharclass(c, tnode->u.cc);
		case RE_DIGIT:
			return TRE_MATCHDIGIT(c);
		case RE_NDIGIT:
			return !TRE_MATCHDIGIT(c);
		case RE_ALPHA:
			return TRE_MATCHALNUM(c);
		case RE_NALPHA:
			return !TRE_MATCHALNUM(c);
		case RE_SPACE:
			return TRE_MATCHSPACE(c);
		case RE_NSPACE:
			return !TRE_MATCHSPACE(c);
		default:
			return 0;
	}
}

#undef TRE_MATCHDIGIT
#undef TRE_MATCHALPHA
#undef TRE_MATCHSPACE
#undef TRE_MATCHALNUM
#undef TRE_MATCHDOT

static const char *
matchquant_lazy(const re_node *nodes, const char *text, const char *tend,
				unsigned min, unsigned max)
{
	const char *end;
	max = max - min;
	while (min && text < tend && matchone(nodes, *text))
	{
		text++;
		min--;
	}

	if (min)
		return 0;

	if ((end = matchpattern(nodes + 2, text, tend)))
		return end;

	while (max && text < tend && matchone(nodes, *text))
	{
		text++;
		max--;
		if ((end = matchpattern(nodes + 2, text, tend)))
			return end;
	}

	return 0;
}

static const char *
matchquant(const re_node *nodes, const char *text, const char *tend,
		   unsigned min, unsigned max)
{
	const char *end, *start = text + min;
	while (max && text < tend && matchone(nodes, *text))
	{
		text++;
		max--;
	}

	while (text >= start)
	{
		if ((end = matchpattern(nodes + 2, text--, tend)))
			return end;
	}

	return 0;
}

static const char *
matchpattern(const re_node *nodes, const char *text, const char *tend)
{
	do
	{
		if (nodes[0].type == RE_STOP)
			return text;

		if ((nodes[0].type == RE_END) && nodes[1].type == RE_STOP)
			return (text == tend) ? text : 0;

		switch (nodes[1].type)
		{
			case RE_QMARK:
				return matchquant(nodes, text, tend, 0, 1);
			case RE_LQMARK:
				return matchquant_lazy(nodes, text, tend, 0, 1);
			case RE_QUANT:
				return matchquant(nodes, text, tend, nodes[1].u.mn[0],
								  nodes[1].u.mn[1]);
			case RE_LQUANT:
				return matchquant_lazy(nodes, text, tend, nodes[1].u.mn[0],
									   nodes[1].u.mn[1]);
			case RE_STAR:
				return matchquant(nodes, text, tend, 0, RE_MAXPLUS);
			case RE_LSTAR:
				return matchquant_lazy(nodes, text, tend, 0, RE_MAXPLUS);
			case RE_PLUS:
				return matchquant(nodes, text, tend, 1, RE_MAXPLUS);
			case RE_LPLUS:
				return matchquant_lazy(nodes, text, tend, 1, RE_MAXPLUS);
		}
	} while (text < tend && matchone(nodes++, *text++));

	return 0;
}
