#include <stdio.h>
#include <stdlib.h>
#define max(a,b) ((a)>(b))?(a):(b)
//AC
typedef struct binode{
    char data;
    int left,right;
    struct binode *lchild,*rchild;
}Binode,*Bitree;
Bitree stack[100];
int flag[100]={0};
//非零表示为孩子，只有一棵树，为0则是根结点
int top=0;
void printTree(Bitree T);
int main(){
    char c;
    //使用EOF时出现runtimeError，故换用考虑需要几行
    int num=1;
    while(top<num){
        Bitree p=(Bitree)malloc(sizeof(Binode));
        scanf("%c%c",&p->data,&c);
        scanf("%d%c",&p->left,&c);
        scanf("%d%c",&p->right,&c);
        num=max(num,p->left);
        num=max(num,p->right);
        stack[top++]=p;
        if(c==EOF)
            break;
    }
    Bitree t;
    for(int i=0;i<top;i++){
        t=stack[i];
        if(t->left==-1){
            t->lchild=NULL;
        }
        else{
            t->lchild=stack[t->left-1];
            flag[t->left]++;//该节点为孩子
        }
        if(t->right==-1){
            t->rchild=NULL;
        }
        else{
            t->rchild=stack[t->right-1];
            flag[t->right]++;//该节点为孩子
        }
    }
    for(int i=0;i<top;i++)
    if(flag[i]==0){
        t=stack[i];//找到根结点
        break;
    }
    printTree(t);
    return 0;
}
void printTree(Bitree T){
    if(!T)
        return;
    else{
        printf("%c ",T->data);
        printTree(T->lchild);
        printTree(T->rchild);
    }
}