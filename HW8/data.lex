%{
#include <string.h>

#define NUM	301
#define SYM	302
#define LPAREN 303
#define RPAREN 304
#define STR 305
char attr[256];
%}
ilit	[-+]?[0-9]+
id	[a-zA-Z]+
comment ";".*
str \"(\\.|[^\"\\])*\"
%%
[ \t]	{}
[\n] {}
"(" {return LPAREN;}
")" {return RPAREN;}
{comment} {}
{ilit}	{ strcpy(attr, yytext); return NUM; }
{id}	{ strcpy(attr, yytext); return SYM; }
{str} {strcpy(attr,yytext); return STR;}
.	{}
%%
int yywrap() {
    return 1;
}

