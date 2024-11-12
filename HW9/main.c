#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define   ILITERAL  301
#define   SYMBOL    302

extern int yylex();
extern char *yytext;

typedef enum _Tag {
    TNIL,
    TINT,
    TSTR,
    TSYM,
    TDUO
} Tag;
typedef char *str;
typedef struct _Pair *duo;
typedef struct _Data {
    Tag tag;
    union {
        int ival;

        str sval;
        duo pval;
    };
} Data;

typedef struct _Pair {
    Data d[2];
} Pair;

Data cons(Data a, Data b) {
    Data d;
    d.tag = TDUO;
    d.pval = (duo)malloc(sizeof(Pair));
    d.pval->d[0] = a;
    d.pval->d[1] = b;
    return d;
}

static const Data nil = { .tag = TNIL, .pval = NULL };

int LA = -1;

void print_data(Data d) {
    if (d.tag == TINT) {
        printf("%d", d.ival);
    } else if (d.tag == TSTR || d.tag == TSYM) {
        printf("%s", d.sval);
    } else if (d.tag == TDUO) {
        printf("(");
        print_data(d.pval->d[0]);
        printf(" . ");
        print_data(d.pval->d[1]);
        printf(")");
    } else {
        printf("NIL");
    }
}

Data mkint(int i) {
    Data d;
    d.tag = TINT;
    d.ival = i;
    return d;
}

Data mkstr(str s) {
    Data d;
    d.tag = TSTR;
    d.sval = s;
    return d;
}

Data D() {
    switch (LA) {
        case ILITERAL: {
            Data result = mkint(atoi(strdup(yytext)));
            return result;
            break;
        }
        case SYMBOL: {
            Data result = mkstr(strdup(yytext));
            return result;
            break;
        }
        case '(': {
            LA = yylex();
            if (LA == ')') {
                LA = yylex();

                return nil;
            }

            Data first = D();
            Data rest = cons(first, nil);
            Data *current = &rest;

            LA = yylex();
            while (LA != ')') {
                Data next = D();
                LA = yylex();
                if ((*current).pval->d[1].tag == TNIL) {
                    (*current).pval->d[1] = cons(next, nil);
                }
                current = &((*current).pval->d[1]);
            }
            return rest;
            break;
        }
        default:
            return nil;
            break;
    }
}
int calculate_data(Data result){
	if(result.tag==TINT){
		return result.ival;
	}
	else if(result.tag==TDUO){
		int a = result.pval->d[1].pval->d[0].ival;
		int b = result.pval->d[1].pval->d[1].pval->d[0].ival;
		if(result.pval->d[0].tag == TSTR &&result.pval->d[0].sval[0]=='+'){
			return a+b;
		}
		else if(result.pval->d[0].tag == TSTR &&result.pval->d[0].sval[0]=='-'){
			return a-b;
		}
		else if(result.pval->d[0].tag == TSTR &&result.pval->d[0].sval[0]=='*'){
			return a*b;
		}
		else if(result.pval->d[0].tag == TSTR &&result.pval->d[0].sval[0]=='/'){
			return (int)a/b;
		}
	}
	
}
int main() {
    LA = yylex();
    while (LA != 0) {
        Data result = D();
        //print_data(result);
		int a = calculate_data(result);
		printf("%d",a);
        printf("\n");
        LA = yylex();
    }
    return 0;
}