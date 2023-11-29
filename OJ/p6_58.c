#include <stdio.h>
#include <stdlib.h>
//AC
typedef enum ptag{Link, Thread} PointerTag ;
typedef struct binode{
    int data;
    struct binode *lchild,*rchild;
    PointerTag Ltag,Rtag;
}Binode,*Bitree;
int L[100]={0};
int R[100]={0};
Bitree pre;
Bitree createTree(int v,int o);
Bitree InOrderThreading(Bitree T);
Bitree InThreading(Bitree p);
Bitree findLoc(Bitree T,int loc);
void printTree(Bitree T);
int main(){
    int d;
    char c;
    int ls,rs;
    ls=rs=0;
    while(1){
        scanf("%d%c",&L[ls++],&c);
        if(c=='\n')
            break;
    }
    while(1){
        scanf("%d%c",&R[rs++],&c);
        if(c=='\n')
            break;
    }
    pre=(Bitree)malloc(sizeof(Binode));
    Bitree T=(Bitree)malloc(sizeof(Binode));
    T=createTree(1,0);
    Bitree Thrt=(Bitree)malloc(sizeof(Binode));
    Thrt=InOrderThreading(T);
    //printTree(Thrt);

    int loc;
    scanf("%d%c",&loc,&c);
    
    ls=rs=0;
    while(1){
        scanf("%d%c",&L[ls++],&c);
        if(c=='\n')
            break;
    }
    while(1){
        scanf("%d%c",&R[rs++],&c);
        if(c=='\n'|| c==EOF)
            break;
    }

    Bitree N=(Bitree)malloc(sizeof(Binode));
    N=createTree(L[0],L[0]-1);
    
    Bitree p=findLoc(Thrt,loc);
    if(!p->lchild || p->Ltag==Thread)
    {
        //注意由于进行过线索化，判空条件改变
        p->Ltag=Link;
        p->lchild=N;
    }
    else{
        N->Rtag=Link;
        N->rchild=p->lchild;
        p->Ltag=Link;
        p->lchild=N;
    }
    Thrt=InOrderThreading(T);
    printTree(Thrt);
    return 0;
}
Bitree createTree(int v,int o){
    if(v-o==0)
        return NULL;
    else{
        Bitree T=(Bitree)malloc(sizeof(Binode));
        T->data=v;
        if(L[v-o]!=0){
            T->Ltag=Link;
            T->lchild=createTree(L[v-o],o);            
        }
        else
            T->lchild=NULL;
        if(R[v-o]!=0){
            T->Rtag=Link;
            T->rchild=createTree(R[v-o],o);            
        }
        else   
            T->rchild=NULL;
        return T;
    }
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
void printTree(Bitree T){
    Bitree p=T->lchild;
    while (p!=T)
    {
        while(p->Ltag==Link) p=p->lchild;
        printf("%d ",p->data);
        while(p->Rtag==Thread && p->rchild!=T){
            p=p->rchild;
            printf("%d ",p->data);
        }
        p=p->rchild;
    }
    return ;
}
Bitree findLoc(Bitree T,int loc){
    Bitree p=T->lchild;
    while (p!=T)
    {
        while(p->Ltag==Link) p=p->lchild;
        //printf("%d ",p->data);
        if(p->data==loc)
            return p;
        while(p->Rtag==Thread && p->rchild!=T){
            p=p->rchild;
            if(p->data==loc)
            return p;
        }
        p=p->rchild;
    }
    return NULL;
}