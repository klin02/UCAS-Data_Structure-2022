#include <stdio.h>
#include <stdlib.h>
//AC
//求共同祖先可以考虑三叉链表
typedef struct tri{
    char data;
    struct tri *parent,*lchild,*rchild;
}Trinode, *Tritree;
Tritree createTree(Tritree T,char input);//父节点的赋值在上一步完成
Tritree findLoc(Tritree T,char c);
int main(){
    char c;
    Tritree T=(Tritree)malloc(sizeof(Trinode));
    T->parent=NULL;
    c=getchar();
    T=createTree(T,c);
    char u,v;
    getchar();
    scanf("%c %c",&u,&v);
    Tritree p,q,t;
    p=findLoc(T,u);
    q=findLoc(T,v);
    p=p->parent;
    char res='^';
    while(p){
        for(t=q->parent;t;t=t->parent)
            if(p->data==t->data){
                res=t->data;
                break;
            }
        if(res!='^')
            break;
        else 
            p=p->parent;
    }
    printf("%c",res);
    return 0;
}
Tritree createTree(Tritree T,char input){
    T->data=input;
    char c;
    if((c=getchar())=='^')
        T->lchild=NULL;
    else{
        Tritree p=(Tritree)malloc(sizeof(Trinode));
        p->parent=T;
        T->lchild=p;
        T->lchild=createTree(T->lchild,c);
    }
    if((c=getchar())=='^')
        T->rchild=NULL;
    else{
        Tritree q=(Tritree)malloc(sizeof(Trinode));
        T->rchild=q;
        q->parent=T;
        T->rchild=createTree(T->rchild,c);
    }
    return T;
}
Tritree findLoc(Tritree T,char c){
    if(!T)
        return NULL;
    else if(T->data==c)
        return T;
    else if(findLoc(T->lchild,c))
        return findLoc(T->lchild,c);
    else if(findLoc(T->rchild,c))
        return findLoc(T->rchild,c);
    else 
        return NULL;
}