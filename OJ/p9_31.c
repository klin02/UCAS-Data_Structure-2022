#include <stdio.h>
#include <stdlib.h>
//AC
typedef struct binode{
    int data;
    int left,right;
    struct binode *lchild,*rchild;
}Binode,*Bitree;
Bitree stack[100];
int top=0;
int checkTree(Bitree T);
int main(){
    int n,left,right;
    while(scanf("%d%d%d",&n,&left,&right)==3){
        Binode * p=(Binode *)malloc(sizeof(Binode));
        p->data=n;
        p->left=left;
        p->right=right;
        stack[top++]=p;
    }
    for(int i=0;i<top;i++){
        if(stack[i]->left!=-1)
            stack[i]->lchild=stack[stack[i]->left];
        else     
            stack[i]->lchild=NULL;
        if(stack[i]->right!=-1)
            stack[i]->rchild=stack[stack[i]->right];
        else     
            stack[i]->rchild=NULL;
    }

    printf("%d",checkTree(stack[0]));
    return 0;
}
int checkTree(Bitree T){
    if(!T)
        return 1;
    
    if(T->lchild && T->lchild->data >= T->data)
        return 0;
    else if(T->rchild && T->rchild->data <= T->data)
        return 0;
    else
        return checkTree(T->lchild) & checkTree(T->rchild);
    
}