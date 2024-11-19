%{
    #include <stdio.h>
    int yylex();
    int yyerror(char *s);
%}

%token NUMBER
%%
Exp : Exp '+' Term {printf("E -> E + T\n");}
    | Exp '-' Term {printf("E -> E - T\n");}
    | Term {printf("E -> T\n");}
    ;
Term : Term '*' Factor {printf("T -> T * F\n");}
    | Term '/' Factor {printf("T -> T / F\n");}
    | Factor {printf("T -> F\n");}
    ;
Factor : NUMBER {printf("F -> n\n");}
        | '(' List ')'  {printf("F -> (L)\n");}
        | '(' ')' {printf("F -> NIL\n");}
        ;
List: Factor {printf("L -> F\n");}
        | List '.' Factor {printf("L -> L . F\n");}
        ;
%%
int main(){
    yyparse();
}
int yyerror(char *s){
    printf("%s\n",s);
}