#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*
A ->EOF|L A
L-> S newline
S ->(S)S|e
*/
int LA = -1;

bool eof(){
    return LA==EOF;
}

int yylex();
void match(int c);

void A();
void L();
void S();
int yylex(){
    return getchar();
}

void match(int c){
    if (LA==c) LA=yylex();
    else{
        fprintf(stderr,"Syntax err");
        exit(-1);
    }
}
void A(){
    if (eof()){
        exit(0);
    }
    else{
        L();
        A();
    }
}
void L(){
    S(); match('\n');
}

void S(){
    if(LA=='('){
        match('(');S();match(')');S();
    }
}

int main(){
    LA=yylex();
    A();
}