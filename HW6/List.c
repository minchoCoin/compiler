#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*
input: ((1) 2 3)
output: ((1 . NIL) . (2 . (3 . NIL)))
*/

typedef enum
{
    TNIL,
    TINT,
    TSTR,
    TDUO
} Tag;
typedef char *str;
typedef struct _Pair *duo;

typedef struct _Data
{
    Tag tag;
    union
    {
        int ival;
        str sval;
        duo pval;
    };
} Data;

typedef struct _Pair
{
    Data d[2]; 
} Pair;

Data mkint(int i)
{
    Data data;
    data.tag = TINT;
    data.ival = i;
    return data;
}


Data mkstr(str s)
{
    Data data;
    data.tag = TSTR;
    data.sval = s;
    return data;
}


Data cons(Data a, Data b)
{
    Pair *pair = (Pair *)malloc(sizeof(Pair));
    pair->d[0] = a; // car
    pair->d[1] = b; // cdr
    Data data;
    data.tag = TDUO;
    data.pval = pair;
    return data;
}


const Data nil = {.tag = TNIL, .pval = NULL};


void print_data(Data data)
{
    switch (data.tag)
    {
    case TINT:
        printf("%d", data.ival);
        break;
    case TSTR:
        printf("%s", data.sval);
        break;
    case TDUO:
        printf("(");

        print_data(data.pval->d[0]); 
        printf(" . ");
        print_data(data.pval->d[1]); 
        
        printf(")");
        break;
    case TNIL:
        printf("NIL");
        break;
    }
}


typedef enum
{
    T_INT,
    T_SYM,
    T_LPAREN,
    T_RPAREN,
    T_EOF,
    T_ERROR
} TokenType;

typedef struct
{
    TokenType type;
    union
    {
        int ival;
        char sval[100];
    };
} Token;

char input[100];
int pos = 0;
Token current_token;


void yylex()
{
    while (input[pos] == ' ') pos++; 

    char ch = input[pos];

    
    if (ch == '\0')
    {
        current_token.type = T_EOF;
        return;
    }

    
    if (isdigit(ch))
    {
        int value = 0;
        
        while (isdigit(input[pos]))
        {
            value = value * 10 + (input[pos] - '0');
            pos++;
        }
        current_token.type = T_INT;
        current_token.ival = value;
        return;
    }

    
    if (isalpha(ch))
    {
        int symbol_pos = 0;
        
        while (isalpha(input[pos]) && symbol_pos < 100 - 1)
        {
            current_token.sval[symbol_pos++] = input[pos++];
        }
        current_token.sval[symbol_pos] = '\0'; 
        current_token.type = T_SYM;
        return;
    }

    
    if (ch == '(')
    {
        current_token.type = T_LPAREN;
        pos++;
        return;
    }

    if (ch == ')')
    {
        current_token.type = T_RPAREN;
        pos++;
        return;
    }

    
    current_token.type = T_ERROR;
    pos++;
}


Data parse_list();


Data parse_data()
{
    if (current_token.type == T_INT)
    {
        Data d = mkint(current_token.ival);
        yylex();
        return d;
    }
    else if (current_token.type == T_SYM)
    {
        char* sym = malloc(100*sizeof(char));
        strncpy(sym,current_token.sval,100);
        Data d = mkstr(sym);
        yylex();
        return d;
    }
    else if (current_token.type == T_LPAREN)
    {
        return parse_list();
    }
    else
    {
        printf("Syntax error: Unexpected token\n");
        exit(0);
        
    }
}


Data parse_list()
{
    
    if (current_token.type == T_LPAREN)
    { 
       
        yylex(); 
        
    }

    if (current_token.type == T_RPAREN)
    { 
        
        yylex();
        return nil;
    }

   
    Data first = parse_data();

    
    if (current_token.type == T_RPAREN)
    {
        yylex();  
        return cons(first, nil);  
    }

    
    Data rest = parse_list();  
    return cons(first, rest);  
}


void reset_parser()
{
    pos = 0;
}


int custom_gets()
{
    if (!fgets(input, sizeof(input), stdin))
    {
        return 0;
    }
    return strlen(input);
}

int main()
{
    

    while (custom_gets() > 1)
    {
        reset_parser();  
        yylex();    
        
        Data parsed_data;

        
        if (current_token.type == T_LPAREN)
        {
            parsed_data = parse_list(); 
        }
        else if (current_token.type == T_INT || current_token.type == T_SYM)
        {
            parsed_data = parse_data();  
        }
        else
        {
            printf("Syntax error: Unexpected input\n");
            continue;
        }

        print_data(parsed_data);  
        printf("\n");
    }

    return 0;
}
