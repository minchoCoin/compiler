#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int isDigit(char a) {
    return a >= '0' && a <= '9';
}

typedef enum _Tag {
    TINT,
    TSTR
} Tag;

typedef char* str;

typedef struct _Data {
    Tag tag;
    union {
        int ival;
        str sval;
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
                while (isDigit(buf[i])) {
                    i++;
                }
                
                d.tag = TINT;
                str tmp = substr(buf,start,i);
                d.ival = atoi(tmp);
                datarray[datasz++] = d;
                free(tmp);
                
            } else if (buf[i] == ' ') {
                i++;
            } else {
                int start = i;
                while (buf[i] != ' ' && buf[i] != '\0') {
                    i++;
                }
                d.tag = TSTR;
                d.sval = substr(buf,start,i);
                datarray[datasz++] = d;
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