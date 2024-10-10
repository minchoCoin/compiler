#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _Pair *duo;

typedef enum _Tag
{
    TINT,
    TSTR,
    TSYM,
    TNIL,
    TDUO
} Tag;

typedef char *str;

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

Data cons(Data a, Data b);
const Data nill = {.tag = TNIL, .pval = NULL};
Data mkint(int i);
Data mkstr(str s);
Data mksym(str s);
Data parse_data(int *i);
char buf[200];
Data datarray[1000];
int sz = 0;

int custom_gets()
{
    if (!fgets(buf, sizeof(buf), stdin))
    {
        return 0;
    }
    return strlen(buf);
}

str substr(str s, int start, int end)
{
    str tmp = (str)malloc(sizeof(char) * (end - start + 2));
    strncpy(tmp, s + start, end - start + 1);
    tmp[end - start] = '\0';
    return tmp;
}

int isDigit(char a)
{
    return a >= '0' && a <= '9';
}

Data mkint(int i)
{
    Data d = {TINT, .ival = 0};
    d.ival = i;
    return d;
}

Data mkstr(str s)
{
    Data d = {TSTR, .sval = NULL};
    d.sval = malloc(strlen(s) + 1);
    strcpy(d.sval, s);
    return d;
}

Data mksym(str s)
{
    Data d = {TSYM, .sval = NULL};
    d.sval = malloc(strlen(s) + 1);
    strcpy(d.sval, s);
    return d;
}

Data cons(Data a, Data b)
{
    Data d = {.tag = TDUO, .pval = NULL};
    duo tmp = malloc(sizeof(Pair));
    tmp->d[0] = a;
    tmp->d[1] = b;
    d.pval = tmp;
    return d;
}

void print_data(Data d)
{
    switch (d.tag)
    {
    case TINT:
        printf("(INT, %d)", d.ival);
        break;
    case TSTR:
        printf("(STR, '%s')", d.sval);
        free(d.sval);
        break;
    case TSYM:
        printf("(SYM, %s)", d.sval);
        free(d.sval);
        break;
    case TNIL:
        printf("NIL");
        break;
    case TDUO:
        printf("(");
        print_data(d.pval->d[0]);
        printf(" . ");
        print_data(d.pval->d[1]);
        printf(")");
        break;
    default:
        fputs("Error: unknown data type\n", stderr);
        break;
    }
}

Data parse_pair(int *i)
{
    (*i)++;
    Data d1 = parse_data(i);
    while (buf[*i] == ' ')
        (*i)++;
    if (buf[*i] == '.')
    {
        (*i)++;
        while (buf[*i] == ' ')
            (*i)++;
        Data d2 = parse_data(i);
        while (buf[*i] == ' ')
            (*i)++;
        if (buf[*i] == ')')
        {
            (*i)++;
            return cons(d1, d2);
        }
        else
        {
            fputs("Error: expected )\n", stderr);
            exit(1);
        }
    }
    else
    {
        
        return nill;
    }
}

Data parse_data(int *i)
{
    while (buf[*i] == ' ')
        (*i)++;

    if (buf[*i] == '(')
    {
        return parse_pair(i);
    }
    else if (isDigit(buf[*i]))
    {
        int start = *i;
        while (isDigit(buf[*i]))
            (*i)++;
        str tmp = substr(buf, start, *i);
        Data d = mkint(atoi(tmp));
        free(tmp);
        return d;
    }
    else if (buf[*i] == '\"')
    {
        (*i)++;
        int start = *i;
        while (buf[*i] != '\"')
            (*i)++;
        str tmp = substr(buf, start, *i);
        (*i)++;
        Data d = mkstr(tmp);
        free(tmp);
        return d;
    }
    else
    {
        int start = *i;
        while (buf[*i] != ' ' && buf[*i] !=')' && buf[*i] != '\0')
            (*i)++;
        str tmp = substr(buf, start, *i);
        if (strcmp(tmp, "nil") == 0)
        {
            free(tmp);
            return nill;
        }
        else
        {
            Data d = mksym(tmp);
            free(tmp);
            return d;
        }
    }
}

int main(void)
{
    Data d;
    while (custom_gets() > 1)
    {
        buf[strcspn(buf, "\n")] = '\0';
        int i = 0;
        while (i < strlen(buf))
        {
            d = parse_data(&i);
            datarray[sz++] = d;
        }
    }

    for (int i = 0; i < sz; i++)
    {
        print_data(datarray[i]);
        printf("\n");
    }

    return 0;
}
