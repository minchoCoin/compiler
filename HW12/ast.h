#ifndef AST_H
#define AST_H


typedef enum {
    INT_NODE,
    SYM_NODE,
    BINOP_NODE,
    UNOP_NODE
} NodeType;


typedef struct Node {
    NodeType type;
    union {
        int ival;               
        char *sval;             
        struct {
            char *op;           
            struct Node *left;  
            struct Node *right;
            
        } opNode;
    } data;
} Node;


Node *mkIntNode(int n);
Node *mkSymNode(char *s);
Node *mkBopNode(char *op, Node *left, Node *right);
Node *mkUopNode(char *op, Node *son);


void printTree(Node *node, int indent);

#endif