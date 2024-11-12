%{
  #include  <stdio.h>
  #define   ILITERAL  301
  #define   SYMBOL    302
%}
iliteral    [-+]?[0-9]+
symbol      [a-zA-Z\+\*\-\/]
space       [ \t\n]+
comment     ;[^\n]*\n
%%
{iliteral}  { return ILITERAL;  }
{symbol}    { return SYMBOL;    }
"("         { return '(';    }
")"         { return ')';    }
{space}     ;
{comment}   ;
%%
int yywrap() {
    return 1;
}