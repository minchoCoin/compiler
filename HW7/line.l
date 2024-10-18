%{
#include <stdio.h>
int word_count = 0;
int symbol_count = 0;
%}

word [a-zA-Z]+
symbol [\!\@\#\$\%\^\&\*\(\)\-\_\+\=\|\\\/\<\>\:\;\"\'\~\{\}\[\]\.\,\`] 
space [ ]
newline [\n]
%%

{word} { word_count++; } 
{symbol} { symbol_count++; }  
{space} {}
{newline} {printf("%d %d\n",word_count,symbol_count);}
%%
int yywrap() {
    return 1;
}
