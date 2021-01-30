#ifndef FT_REGEX_H
#define FT_REGEX_H

#define MAXNFA  1024
#define MAXTAG  10

#define END		0
#define CHR		1
#define ANY		2
#define CCL		3
#define BOL		4
#define EOL		5
#define BOT		6
#define EOT		7
#define BOW		8
#define EOW		9
#define REF		10
#define CLO		11

#define MAXCHR	128
#define CHRBIT	8
#define BITBLK	MAXCHR/CHRBIT
#define BLKIND	0170
#define BITIND	07

int		re_comp(char *pat);
int		re_exec(char *lp);


//#define RE_MAX_NODES	64
//#define RE_MAX_BUFLEN	256
//#define RE_MAXQUANT		1024
//#define RE_MAXPLUS		40000
//#define RE_SUCCESS		1
//#define RE_FAIL			0
//
//#define RE_ISMETA(c) ((c=='s')||(c=='S')||(c=='w')||(c=='W')||(c=='d')||(c=='D'))
//
//enum
//{
//	RE_STOP,
//	RE_BEGIN = '^',
//	RE_END = '$',
//	RE_QUANT = '{',
//	RE_LQUANT,
//	RE_QMARK = '?',
//	RE_LQMARK,
//	RE_STAR = '*',
//	RE_LSTAR,
//	RE_PLUS = '+',
//	RE_LPLUS,
//	RE_DOT = '.',
//	RE_CHAR,
//	RE_CLASS = '[',
//	RE_NCLASS,
//	RE_DIGIT = 'd',
//	RE_NDIGIT = 'D',
//	RE_ALPHA = 'w',
//	RE_NALPHA = 'W',
//	RE_SPACE = 's',
//	RE_NSPACE = 'S'
//};
//
//typedef struct re_node re_node;
//typedef struct tre_comp tre_comp;
//
//struct re_node
//{
//	unsigned char type;
//	unsigned char lazy;
//	union
//	{
//		char ch;    // character
//		char *cc;    // character class buffer
//		unsigned short mn[2]; // {m,n} quantifier
//	} u;
//};
//
//struct tre_comp
//{
//	re_node nodes[RE_MAX_NODES];
//	char buffer[RE_MAX_BUFLEN];
//};
//
//int re_compile(const char *pattern, tre_comp *regex);
//
//const char *
//tre_match(const tre_comp *tregex, const char *text, const char **end);
//
//const char *
//tre_compile_match(const char *pattern, const char *text, const char **end);
//
//void tre_print(const tre_comp *tregex);
//
//int tre_err(const char *format, ...);

#endif
