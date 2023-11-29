#include <stdio.h>
#include <stdlib.h>
#define max(a,b) ((a)>(b))?(a):(b)
//AC
typedef struct csnode{
    int data;
    int first,next;
    struct csnode *fchild,*nsib;
}CSnode,*CSTree;
CSTree stack[100];
int sontag[100]={0};
//非零表示为孩子，只有一棵树，为0则是根结点
int top=0;
void printCSTree(CSTree T,int dep);
int main(){
    char c;
    //使用EOF时出现runtimeError，故换用考虑需要几行
    int num=1;
    while(top<num){
        CSTree p=(CSTree)malloc(sizeof(CSnode));
        scanf("%c%c",&p->data,&c);
        scanf("%d%c",&p->first,&c);
        scanf("%d%c",&p->next,&c);
        num=max(num,p->first);
        num=max(num,p->next);
        stack[top++]=p;
        if(c==EOF)
            break;
    }
    CSTree t;
    for(int i=0;i<top;i++){
        t=stack[i];
        if(t->first==-1){
            t->fchild=NULL;
        }
        else{
            t->fchild=stack[t->first-1];
            sontag[t->first]++;//该节点为孩子
        }
        if(t->next==-1){
            t->nsib=NULL;
        }
        else{
            t->nsib=stack[t->next-1];
            sontag[t->next]++;//该节点为孩子
        }
    }
    for(int i=0;i<top;i++)
    if(sontag[i]==0){
        t=stack[i];//找到根结点
        break;
    }
    
    printCSTree(t,0);
    return 0;
}
void printCSTree(CSTree T,int dep){
    //根结点0层,先孩子后兄弟
    if(!T)
        return;
    else{
        for(int i=0;i<dep;i++)
        printf("-");
        printf("%c\n",T->data);
        printCSTree(T->fchild,dep+1);
        printCSTree(T->nsib,dep);
    }
    return ;
}