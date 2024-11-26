 %{  #include <stdio.h>
 #include <ctype.h>
 int yyerror(const char *msg), yylex();
 %}
 %token NUMBER
 %%
 Line    : Exp { printf("%d\n", $1); }
 ;
 Exp: '(' '+' Exp Exp ')' {$$ = $3 + $4;}
    | '(' '-' Exp Exp ')' {$$ = $3 - $4;}
    | '(' '*' Exp Exp ')' {$$ = $3 * $4;}
    | '(' '/' Exp Exp ')' {$$ = $3 / $4;}
    | NUMBER { $$ = $1;}
    ;
 %%
 int main() { yyparse(); return 0; }
 int yyerror(const char *msg) { fputs(msg, stderr); return -1; }
