 %{  #include <stdio.h>
#include <stdio.h>
#include "ast.h"
int yyerror(const char *msg), yylex();
Node *Root;
%}

%union {
char *sval;
int ival;
Node *pval;
}
%token <ival> NUM
%token <sval> ID '+' '-' '*' '/'
%type <pval> Exp

%%
Prg : Exp { Root = $1; }
    ;

Exp : NUM { $$ = mkIntNode($1); }
    | ID {$$ = mkSymNode($1);}
    | '-' Exp    { $$ = mkUopNode("-", $2); }
    | '+' Exp    { $$ = mkUopNode("+", $2);; }
    | '(' '+' Exp Exp ')' { $$ = mkBopNode("+", $3, $4); }
    | '(' '-' Exp Exp ')' { $$ = mkBopNode("-", $3, $4); }
    | '(' '*' Exp Exp ')' { $$ = mkBopNode("*", $3, $4); }
    | '(' '/' Exp Exp ')' { $$ = mkBopNode("/", $3, $4); }
    ;

%%
int main() { yyparse(); printTree(Root, 0);}
int yyerror(const char *msg) { fputs(msg, stderr); return -1; }
