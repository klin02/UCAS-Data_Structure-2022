#include <stdio.h>
#include <stdlib.h>
//AC
typedef struct binode{
    int data;
    struct binode *lchild,*rchild;
}Binode, * Bitree;
Bitree Insert(Bitree T,int data);
void printTree(Bitree T,int x);
int main(){
    int n;
    char c;
    Bitree T=NULL;
    while(1){
        scanf("%d%c",&n,&c);
        T=Insert(T,n);
        if(c!=' ')
            break;
    }
    int x;
    scanf("%d",&x);
    printTree(T,x);
    return 0;
}
Bitree Insert(Bitree T,int data){
    Binode *p=(Binode *)malloc(sizeof(Binode));
    p->data=data;
    p->lchild=p->rchild=NULL;
    if(!T)
        return p;
    
    if(T->data==data)
        ;
    else if(data<T->data)
        T->lchild=Insert(T->lchild,data);
    else 
        T->rchild=Insert(T->rchild,data);
    return T;
}
void printTree(Bitree T,int x){
    //遍历顺序 右 中 左
    if(!T)
        return ;
    else{
        printTree(T->rchild,x);
        if(T->data >= x)
        printf("%d ",T->data);
        printTree(T->lchild,x);
        return ;
    }
}