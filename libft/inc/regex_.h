#ifndef REGEX__H
#define REGEX__H

int re_subs( char *src, char *dst);
void re_modw( char *s );
int re_exec( char *lp );
char *re_comp( char *pat );

#endif
