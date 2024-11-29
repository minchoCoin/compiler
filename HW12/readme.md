# union
{d = max(d,$4);} 에서 $4가 int, char*, Node * 일때 union으로 선언

union _Type{
    int ival;
    char* sval;
    Node* pval;
}