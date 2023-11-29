#include <stdio.h>
#include <stdlib.h>
#define max(a,b) ((a)>(b))?(a):(b)
//AC
//此处完全二叉树定义！！ 与满二叉树在1-k完全对应，递归左右层数可能有差
typedef struct binode{
    char data;
    int No;
    int left,right;
    struct binode *lchild,*rchild;
}Binode,*Bitree;
Bitree stack[100];
int sontag[100]={0};
//非零表示为孩子，只有一棵树，为0则是根结点
int top=0;
int flag[1000]={0};//1表示对应标号有节点
int Nomax=1;
void markTree(Bitree T);
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
            sontag[t->left]++;//该节点为孩子
        }
        if(t->right==-1){
            t->rchild=NULL;
        }
        else{
            t->rchild=stack[t->right-1];
            sontag[t->right]++;//该节点为孩子
        }
    }
    for(int i=0;i<top;i++)
    if(sontag[i]==0){
        t=stack[i];//找到根结点
        break;
    }

    t->No=1;
    markTree(t);

    int res=1;
    int find;
    for(find=1;find<=Nomax;find++)
        if(flag[find]==0)//中间有缺失，并非完全
        {
            res=0;
            break;
        }
    
    if(res==1)
        printf("Yes");
    else
        printf("No");
    return 0;
}
void markTree(Bitree T){//按照满二叉数编号
    if(!T)
        return;
    else{
        flag[T->No]=1;
        Nomax=max(Nomax,T->No);
        if(T->lchild){
            T->lchild->No=2*T->No;
            markTree(T->lchild);
        }
        if(T->rchild){
            T->rchild->No=2*T->No+1;
            markTree(T->rchild);
        }
    }
    return;
}