#include <stdio.h>
#include <stdlib.h>
//AC
typedef struct binode{
    char data;
    struct binode *lchild,*rchild;
}Binode,*Bitree;
Bitree creatTree();
void printTree(Bitree T);
int main(){
    Bitree T;
    T=creatTree();
    printTree(T);
    return 0;
}
Bitree creatTree(){
    char c=getchar();
    if(c=='#')
        return NULL;
    else{
        Bitree T=(Bitree)malloc(sizeof(Binode));
        T->data=c;
        T->lchild=creatTree();
        T->rchild=creatTree();
        return T;
    }
    
}
void printTree(Bitree T){
    if(!T) 
        return ;
    if(T->lchild && (T->lchild->data=='+'||T->lchild->data=='-') && (T->data=='*'||T->data=='/'))
    {
        printf("(");
        printTree(T->lchild);
        printf(")");
    }
    else
        printTree(T->lchild);
    printf("%c",T->data);
    //同加减，中心为-加括号 同乘除，中心/加括号
    if(T->rchild && (T->rchild->data=='+'||T->rchild->data=='-') && (T->data=='*'||T->data=='/'||T->data=='-'))
    {
        printf("(");
        printTree(T->rchild);
        printf(")");
    }
    else if(T->rchild && (T->rchild->data=='*'||T->rchild->data=='/')&& T->data=='/'){
        printf("(");
        printTree(T->rchild);
        printf(")");
    }
    else
        printTree(T->rchild);
}