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
%type <pval> Exp Term Factor

%%
Prg : Exp { Root = $1; }
    ;

Exp : Exp '+' Term { $$ = mkBopNode("+", $1, $3); }
    | Exp '-' Term { $$ = mkBopNode("-", $1, $3); }
    | Term         { $$ = $1; }
    ;

Term : Term '*' Factor { $$ = mkBopNode("*", $1, $3); }
     | Term '/' Factor { $$ = mkBopNode("/", $1, $3); }
     | Factor          { $$ = $1; }
     ;

Factor : '(' Exp ')'   { $$ = $2; }
       | '-' Factor    { $$ = mkUopNode("-", $2); }
       | '+' Factor    { $$ = mkUopNode("+", $2);; }
       | NUM           { $$ = mkIntNode($1); }
       | ID            { $$ = mkSymNode($1); }
       ;

%%
int main() { yyparse(); printTree(Root, 0);}
int yyerror(const char *msg) { fputs(msg, stderr); return -1; }
