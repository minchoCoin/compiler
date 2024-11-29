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


void printTree(Node *node, int indent) {
    if (node == NULL) return;

    
    for (int i = 0; i < indent; i++) printf("    ");

    switch (node->type) {
        case INT_NODE:
            printf("Int(%d)\n", node->data.ival);
            break;
        case SYM_NODE:
            printf("Sym('%s')\n", node->data.sval);
            break;
        case BINOP_NODE:
            printf("Op(%s)\n", node->data.opNode.op);
            printTree(node->data.opNode.left, indent + 1);
            printTree(node->data.opNode.right, indent + 1);
            break;
        case UNOP_NODE:
            printf("Uop(%s)\n", node->data.opNode.op);
            printTree(node->data.opNode.left, indent + 1);
            break;
    }
}
