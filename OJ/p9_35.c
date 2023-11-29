#include <stdio.h>
#include <stdlib.h>
//AC
typedef enum ptag{Link, Thread} PointerTag ;
typedef struct binode{
    int data;
    struct binode *lchild,*rchild;
    PointerTag Ltag,Rtag;
}Binode,*Bitree;

Bitree pre;
Bitree Insert(Bitree T,int data);
Bitree InOrderThreading(Bitree T);
Bitree InThreading(Bitree p);

void printTree(Bitree T,int a,int b);
int main(){
    int n;
    char c;
    int top=0;
    int tmp[100]={0};
    while(1){
        scanf("%d%c",&n,&c);
        tmp[top++]=n;
        if(c=='\n')
            break;
    }
    pre=(Bitree)malloc(sizeof(Binode));
    Bitree T=NULL;
    for(int i=top/2;i>=0;i--)
        T=Insert(T,tmp[i]);
    for(int i=top/2+1;i<top;i++)
        T=Insert(T,tmp[i]);
    Bitree Thrt=(Bitree)malloc(sizeof(Binode));
    Thrt=InOrderThreading(T);
    //printTree(Thrt);

    int a,b;
    scanf("%d%d",&a,&b);
    
    printTree(Thrt,a,b);
    return 0;
}
Bitree Insert(Bitree T,int data){
    Binode *p=(Binode *)malloc(sizeof(Binode));
    p->data=data;
    p->lchild=p->rchild=NULL;
    p->Ltag=p->Rtag=Thread;
    if(!T)
        return p;
    
    if(T->data==data)
        ;
    else if(data<T->data){
        T->Ltag=Link;
        T->lchild=Insert(T->lchild,data);
    }
    else{
        T->Rtag=Link;
        T->rchild=Insert(T->rchild,data);
    }
        
    return T;
}
Bitree InOrderThreading(Bitree T){
    //Thrt指向头结点，最后一个节点指回Thrt   pre为公用变量
    Bitree Thrt=(Bitree)malloc(sizeof(Binode));
    Thrt->Ltag=Link;
    Thrt->Rtag=Thread;
    Thrt->rchild=Thrt;
    if(!T) Thrt->lchild=Thrt;
    else{
        Thrt->lchild=T;
        pre=Thrt;
        T=InThreading(T);
        pre->rchild=Thrt;
        pre->Rtag=Thread;
        Thrt->rchild=pre;
    }
    return Thrt;
}
Bitree InThreading(Bitree p){
    //实质上执行遍历过程，pre始终指向p的前驱
    if(p){
        //更新为初始态
        if(p->Ltag==Thread)
            p->lchild=NULL;
        if(p->Rtag==Thread)
            p->rchild=NULL;

        p->lchild=InThreading(p->lchild);
        if(!p->lchild){
            p->Ltag=Thread;
            p->lchild=pre;
        }
        if(!pre->rchild){
            pre->Rtag=Thread;
            pre->rchild=p;
        }
        pre=p;
        p->rchild=InThreading(p->rchild);
    }
    return p;
}
void printTree(Bitree T,int a,int b){
    Bitree p=T->lchild;
    while (p!=T)
    {
        while(p->Ltag==Link) p=p->lchild;
        if(p->data>a && p->data<b)
        printf("%d ",p->data);
        while(p->Rtag==Thread && p->rchild!=T){
            p=p->rchild;
            if(p->data>a && p->data<b)
            printf("%d ",p->data);
        }
        p=p->rchild;
    }
    return ;
}
