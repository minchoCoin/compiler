#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
int isDigit(char a) {
    return a >= '0' && a <= '9';
}

typedef enum _Tag {
    TINT,
    TSTR,
    TFLOAT,
    TBOOL,

    TINTARR,
    TSTRARR,
    TFLOATARR,
    TBOOLARR
} Tag;

typedef char* str;

typedef enum _boolean{
    FALSE,
    TRUE
} boolean;


typedef struct _Data {
    Tag tag;
    union {
        int ival;
        str sval;
        float fval;
        boolean bval;
    };
} Data;

char buf[200];

Data datarray[1000];
int datasz = 0;

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

void processInput() {
    Data d;
    while (custom_gets() > 1) {
        buf[strcspn(buf, "\n")] = '\0'; // Remove newline character
        int i = 0;
        while (i < strlen(buf)) {
            if (isDigit(buf[i])) {
                int start = i;
                int isfloat=0;
                while (isDigit(buf[i]) || buf[i]=='.') {
                    i++;
                    if (buf[i]=='.') isfloat=1;
                }
                str tmp;
                if(!isfloat){
                    d.tag = TINT;
                    tmp = substr(buf,start,i);
                    d.ival = atoi(tmp);
                }
                else{
                    //float
                    d.tag=TFLOAT;
                    tmp = substr(buf,start,i);
                    d.fval = atof(tmp);
                }
                datarray[datasz++] = d;
                free(tmp);
            } else if (buf[i] == ' ') {
                i++;
            } else {
                int start = i;
                while (buf[i] != ' ' && buf[i] != '\0') {
                    i++;
                }

                str tmp;
                tmp = substr(buf,start,i);

                if(strlen(tmp) == 4 && (strncmp(tmp,"true",4) == 0 || strncmp(tmp,"True",4)==0)){
                    d.tag = TBOOL;
                    d.bval = TRUE;
                    datarray[datasz++] = d;
                    free(tmp);
                }
                else if(strlen(tmp)==5 && (strncmp(tmp,"false",5) == 0 || strncmp(tmp,"False",5)==0)){
                    d.tag = TBOOL;
                    d.bval = FALSE;
                    datarray[datasz++] = d;
                    free(tmp);
                }
                else{
                    d.tag = TSTR;
                    d.sval = substr(buf,start,i);
                    datarray[datasz++] = d;
                   
                }
                
            }
        }
    }
}

void printDataArray(){
for (int i = 0; i < datasz; i++)
    {
        switch (datarray[i].tag)
        {
        case TINT:
            printf("(INT, %d)\n", datarray[i].ival);
            break;
        case TSTR:
            printf("(SYM, %s)\n", datarray[i].sval);
            free(datarray[i].sval);
            break;
        case TFLOAT:
            printf("(FLO, %f)\n",datarray[i].fval);
            break;
        case TBOOL:
            if(datarray[i].bval == FALSE){
                printf("(BOO, %s)\n","False");
            }
            else{
                printf("(BOO, %s)\n","True");
            }
            break;
        default:
            fprintf(stderr,"Error: unknown data type");
            break;
        }
    }
}

int main() {
    processInput();
    printDataArray();
    return 0;
}
//https://dojang.io/mod/page/view.php?id=745
