#include "ft_regex.h"
#include "str.h"

re_node *tnode;
char *buf;
char g_quable = 0; // is the last node quantifiable
char temp;

unsigned idx = 0;

unsigned long val; // for parsing numbers in {m,n}
unsigned j = 0;    // index into tnode

static int	re_compile_slash(const char *pattern, re_node *node)
{
	g_quable = 1;
	if (*(++pattern) == '\0')
		return tre_err("Dangling \\");
	if (*pattern == RE_DIGIT)
		node[j].type = RE_DIGIT;
	else if (*pattern == RE_NDIGIT)
		node[j].type = RE_NDIGIT;
	else if (*pattern == RE_ALPHA)
		node[j].type = RE_ALPHA;
	else if (*pattern == RE_NALPHA)
		node[j].type = RE_NALPHA;
	else if (*pattern == RE_SPACE)
		node[j].type = RE_SPACE;
	else if (*pattern == RE_NSPACE)
		node[j].type = RE_NSPACE;
	else
	{
		node[j].type = RE_CHAR;
		node[j].u.ch = *pattern;
	}
	return (RE_SUCCESS);
}

int			re_compile(const char *pattern, tre_comp *regex)
{
	int	status;

	if (!regex || !pattern)
		return tre_err("NULL/empty string or tre_comp");

	tnode = regex->nodes;
	buf = regex->buffer;

	while (*pattern && (j + 1 < RE_MAX_NODES))
	{
		switch (*pattern)
		{
			case '^':
				g_quable = 0;
				tnode[j].type = RE_BEGIN;
				break;
			case '$':
				g_quable = 0;
				tnode[j].type = RE_END;
				break;
			case '.':
				g_quable = 1;
				tnode[j].type = RE_DOT;
				break;
			case '*':
				if (g_quable == 0)
					return tre_err("Non-quantifiable before *");
				g_quable = 0;
				if (*(pattern + 1) == '?' && ++pattern)
					tnode[j].type = RE_LSTAR;
				else
					tnode[j].type = RE_STAR;
				break;
			case '+':
				if (g_quable == 0)
					return tre_err("Non-quantifiable before +");
				g_quable = 0;
				if (*(pattern + 1) == '?' && ++pattern)
					tnode[j].type = RE_LPLUS;
				else
					tnode[j].type = RE_PLUS;
				break;
			case '?':
				if (g_quable == 0)
					return tre_err("Non-quantifiable before ?");
				g_quable = 0;
				if (*(pattern + 1) == '?' && ++pattern)
					tnode[j].type = RE_LQMARK;
				else
					tnode[j].type = RE_QMARK;
				break;

			case '\\':
			{
				status = re_compile_slash(pattern, tnode);
			}
				break;

			case '[':
			{
				g_quable = 1;
				if (*(pattern + 1) == '^' && ++pattern)
					tnode[j].type = RE_NCLASS;
				else
					tnode[j].type = RE_CLASS;
				tnode[j].u.cc = buf + idx;
				while (*(++pattern) != ']' && *pattern != '\0')
				{
					temp = 0;
					if (idx > RE_MAX_BUFLEN - 3)
						return tre_err("Buffer overflow in class");
					if (*pattern == '\\')
					{
						if (*(++pattern) == '\0')
							return tre_err("Dangling '\\' in class");
						if ((temp = RE_ISMETA(*pattern)) || *pattern == '\\')
							buf[idx++] = '\\';
					}
					buf[idx++] = *pattern;
					if (temp || *(pattern + 1) != '-' || *(pattern + 2) == '\0' ||
						*(pattern + 2) == ']')
						continue ;
					temp = (char)(*(pattern + 2) == '\\');
					if ((temp && *(pattern + 3) == '\0') || RE_ISMETA(*(pattern + 3)))
						continue ;
					temp = (char)(temp ? *(pattern + 3) : *(pattern + 2));
					if (temp < *pattern)
						return tre_err("Incorrect range in class");
				}
				if (*pattern != ']')
					return tre_err("Non terminated class");
				buf[idx++] = 0;
			}
				break;

			case '{':
			{
				if (g_quable == 0)
					return tre_err("Non-quantifiable before {m,n}");
				g_quable = 0;
				pattern++;
				val = 0;
				do
				{
					if (*pattern < '0' || *pattern > '9')
						return tre_err("Non-digit min value in quantifier");
					val = 10 * val + (unsigned)(*pattern++ - '0');
				} while (*pattern != ',' && *pattern != '}');

				if (val > RE_MAXQUANT)
					return tre_err("Min value too big in quantifier");
				tnode[j].u.mn[0] = val;

				if (*pattern == ',')
				{
					if (*(++pattern) == '\0')
						return tre_err("Dangling ',' in quantifier");
					if (*pattern == '}')
						val = RE_MAXQUANT;
					else
					{
						val = 0;
						while (*pattern != '}')
						{
							if (*pattern < '0' || *pattern > '9')
								return tre_err("Non-digit max value in quantifier");
							val = 10 * val + (unsigned)(*pattern++ - '0');
						}

						if (val > RE_MAXQUANT || val < tnode[j].u.mn[0])
							return tre_err("Max value too big or less than min value in quantifier");
					}
				}
				if (*(pattern + 1) == '?' && ++pattern)
					tnode[j].type = RE_LQUANT;
				else
					tnode[j].type = RE_QUANT;
				tnode[j].u.mn[1] = val;
			}
				break;

			default:
				g_quable = 1;
				tnode[j].type = RE_CHAR;
				tnode[j].u.ch = *pattern;
				break;
		}
		if (status == RE_FAIL)
			return (RE_FAIL);
		pattern++;
		j++;
	}
	tnode[j].type = RE_STOP;
	return (RE_SUCCESS);
}
