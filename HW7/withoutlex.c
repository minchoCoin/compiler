#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define INPUT_LEN 100
char input[INPUT_LEN];
int pos = 0;

int word_count = 0;
int symbol_count = 0;
int custom_gets()
{
    if (!fgets(input, sizeof(input), stdin))
    {
        return 0;
    }
    return strlen(input);
}

int yywrap()
{
    return 1;
}

int issymbol(char ch)
{
    return (ch == '(' || ch == ')' || ch == '-' || ch == '_' || ch == '+' || ch == '=' ||
            ch == '|' || ch == '\\' || ch == '/' || ch == '<' || ch == '>' || ch == ':' || ch == ';' ||
            ch == '\"' || ch == '\'' || ch == '`' || ch == '~' || ch == '{' || ch == '}' || ch == '[' || ch == ']' || ch == '.' || ch == ',');
}

void yylex()
{
    while (custom_gets() > 1)
    {
        pos = 0;
        word_count=0;
        symbol_count=0;
        while (input[pos] != '\0')
        {
            while (input[pos] == ' ')
                pos++;

            char ch = input[pos];

            if (isalpha(ch))
            {
                while (isalpha(input[pos]))
                {
                    pos++;
                }
                word_count++;
            }

            else if (issymbol(ch))
            {
                pos++;
                symbol_count++;
            }
            else{
                pos++;
            }
        }
        printf("%d %d\n", word_count, symbol_count);
    }
    yywrap();
    return;
}

int main()
{
    yylex();
    return 0;
}
