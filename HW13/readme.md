# how to activate + unary operator
- modify part of the generateCode function in ast.c:
```c
...
case UNOP_NODE:
            generateCode(node->data.opNode.left, indent + 1);
            switch (node->data.opNode.op[0]){
              
              case '+':
                printf("pos\n");
                break;
              
              case '-':
                printf("neg\n");
                break;
              default:
                printf("Unknown UNOP\n");
                break;
            }
...
```
# union
{d = max(d,$4);} 에서 $4가 int, char*, Node * 일때 union으로 선언

union _Type{
    int ival;
    char* sval;
    Node* pval;
}