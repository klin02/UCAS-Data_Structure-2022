#include <stdio.h>
#include <stdlib.h>
//AC
typedef struct binode{
    int data;
    struct binode *lchild,*rchild;
}Binode, * Bitree;
Bitree Insert(Bitree T,int data);
Bitree Merge(Bitree T,Bitree Q);
void printBitree(Bitree T);
int main(){
    int n;
    char c;
    Bitree T,Q;
    T=Q=NULL;
    while(1){
        scanf("%d%c",&n,&c);
        T=Insert(T,n);
        if(c!=' ')
            break;
    }
    while(1){
        scanf("%d%c",&n,&c);
        Q=Insert(Q,n);
        if(c!=' ')
            break;
    }
    T=Merge(T,Q);
    printBitree(T);
    return 0;
}
Bitree Insert(Bitree T,int data){
    Binode *p=(Binode *)malloc(sizeof(Binode));
    p->data=data;
    p->lchild=p->rchild=NULL;
    if(data==-1)
        return T;
    else if(!T)
        return p;
    
    if(T->data==data)
        ;
    else if(data<T->data)
        T->lchild=Insert(T->lchild,data);
    else 
        T->rchild=Insert(T->rchild,data);
    return T;
}
Bitree Merge(Bitree T,Bitree Q){
    if(!Q)
        return T;
    else{
        T=Insert(T,Q->data);
        T=Merge(T,Q->lchild);
        T=Merge(T,Q->rchild);
        return T;
    }
}
void printBitree(Bitree T){
    //In order
    if(!T)
        return ;
    else{
        printBitree(T->lchild);
        printf("%d ",T->data);
        printBitree(T->rchild);
        return ;
    }
}