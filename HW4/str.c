#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum _Tag
{
    TINT,
    TSTR,
    TSYM
} Tag;
typedef char *str;
typedef struct _Data
{
    Tag tag;
    union
    {
        int ival;
        str sval;
    };
} Data;

Data mkint(int i);
Data mkstr(str s);
Data mksym(str s);

char buf[200];

Data datarray[1000];
int sz = 0;

int custom_gets() {
    if (!fgets(buf, sizeof(buf), stdin)) {
        return 0; // Handle EOF or error
    }
    return strlen(buf);
}

str substr(str s, int start, int end){
    str tmp = (str)malloc(sizeof(char)*(end-start+2));
    strncpy(tmp,s+start,end-start+1);
    tmp[end-start] = '\0';
    return tmp;
}
int isDigit(char a) {
    return a >= '0' && a <= '9';
}
int main()
{
    Data d;
    while(custom_gets()>1){
        buf[strcspn(buf, "\n")] = '\0'; 
        int i=0;
        while(i<strlen(buf)){
            if(buf[i] == ' '){
                i++;
            }
            else if(isDigit(buf[i])){
                int start = i;
                while(isDigit(buf[i])){
                    i++;
                }
                str tmp;
                tmp = substr(buf,start,i);
                d = mkint(atoi(tmp));
                datarray[sz++] = d;
                free(tmp);
            }
            else if(buf[i]=='\"'){
                i++;
                int start=i;
                while(buf[i]!='\"' || (buf[i]=='\"' && buf[i-1]=='\\')){
                    i++;
                }
                str tmp;
                tmp = substr(buf,start,i);
                d = mkstr(tmp);

                int j=0;
                int len = strlen(d.sval);
                while(d.sval[j]!='\0'){
                    if(d.sval[j]=='\\' && d.sval[j+1]=='\"'){
                        for(int k=j;k<len-1;++k){
                            d.sval[k] = d.sval[k+1];
                        }
                        len=len-1;
                        d.sval[len] = '\0';
                        i++;
                    }
                    j++;
                }

                datarray[sz++] = d;
                free(tmp);
            }
            else{
                int start = i;
                while (buf[i] != '\0') {
                    i++;
                }

                str tmp;
                tmp = substr(buf,start,i);
                d = mksym(tmp);
                datarray[sz++] = d;
                free(tmp);
            }
        }
    }
    for (int i = 0; i < sz; i++)
    {
        switch (datarray[i].tag)
        {
        case TINT:
            printf("(INT, %d)\n", datarray[i].ival);
            break;
        case TSTR:
            
            printf("(STR, '%s')\n", datarray[i].sval);
            free(datarray[i].sval);
            break;
        case TSYM:
            printf("(SYM, %s)\n", datarray[i].sval);
            free(datarray[i].sval);
            break;
        default:
            fputs("Error:unknown data type", stderr);
            break;
        }
    }
    return 0;
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