#include <stdio.h>
#include <stdlib.h>
#define max(a,b) ((a)>(b))?(a):(b)
//AC
typedef struct arcnode{
    int adj;
    struct arcnode *next;
}Arcnode;
//不需额外设置头结点
Arcnode * Adjlist[100];
Arcnode * InsertAL(Arcnode *head,int data);
int pathlen(int u);//dfs
int main(){
    int n;//node
    char c;
    scanf("%d%c",&n,&c);
    //检测节点序号连续，考虑可能0起始
    while(1){
        int u,v;
        scanf("%d-%d%c",&u,&v,&c);
        Adjlist[u]=InsertAL(Adjlist[u],v);
        if(c!=',')
            break;
    }
    printf("%d",pathlen(1));
    for(int i=2;i<=n;i++)
    printf(",%d",pathlen(i));

    return 0;
}
Arcnode * InsertAL(Arcnode *head,int data){
    Arcnode *p=(Arcnode *)malloc(sizeof(Arcnode));
    p->adj=data;
    p->next=NULL;
    if(!head)
        head=p;
    else if(head->adj<p->adj)
    {
        p->next=head;
        head=p;
    }
    else{
        Arcnode *t=head;
        while(t->next && t->next->adj>data){
            t=t->next;
        }
        p->next=t->next;
        t->next=p;
    }   
    return head;
}
int pathlen(int u){
    Arcnode *p= Adjlist[u];
    if(!p)
        return 0;
    else{
        int top=0;
        while(p){
            top=max(top,pathlen(p->adj)+1);
            p=p->next;
        }
        return top;
    }
}