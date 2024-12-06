#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"


Node *mkIntNode(int n) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->type = INT_NODE;
    node->data.ival = n;
    return node;
}


Node *mkSymNode(char *s) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->type = SYM_NODE;
    node->data.sval = strdup(s);
    return node;
}


Node *mkBopNode(char *op, Node *left, Node *right) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->type = BINOP_NODE;
    node->data.opNode.op = strdup(op);
    node->data.opNode.left = left;
    node->data.opNode.right = right;
    return node;
}

Node *mkUopNode(char *op, Node *son) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->type = UNOP_NODE;
    node->data.opNode.op = strdup(op);
    node->data.opNode.left = son;
    return node;
}


void generateCode(Node *node, int indent) {
    if (node == NULL) return;

    switch (node->type) {
        case INT_NODE:
            printf("ldc %d\n", node->data.ival);
            break;
        case SYM_NODE:
            printf("ldc %d\n", node->data.sval);
            break;
        case BINOP_NODE:
            generateCode(node->data.opNode.left, indent + 1);
            generateCode(node->data.opNode.right, indent + 1);
            switch (node->data.opNode.op[0]){
              case '+':
                printf("add\n");
                break;
              case '-':
                printf("sub\n");
                break;
              case '*':
                printf("mul\n");
                break;
              case '/':
                printf("div\n");
                break;
              default:
                printf("Unknown BINOP\n");
                break;
            }

            break;
        case UNOP_NODE:
            generateCode(node->data.opNode.left, indent + 1);
            switch (node->data.opNode.op[0]){
              /*
              case '+':
                printf("pos\n");
                break;
              */
              case '-':
                printf("neg\n");
                break;
              default:
                //printf("Unknown UNOP\n");
                break;
            }
            
            break;
    }
}