#include <stdio.h>
#include <stdlib.h>
//AC
typedef struct arcnode{
    int adj;
    struct arcnode *next;
}Arcnode;
//不需额外设置头结点
Arcnode * Adjlist[100];
Arcnode * InsertAL(Arcnode *head,int data);
int findpath(int u,int v);//dfs
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
    int x,y;
    scanf("%d,%d",&x,&y);
    if(findpath(x,y)==1)
        printf("yes");
    else
        printf("no");
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
int findpath(int u,int v){
    Arcnode *p= Adjlist[u];
    while(p){
        if(p->adj==v)
            return 1;
        else if(findpath(p->adj,v)==1)
            return 1;
        p=p->next;
    }
    return 0;
}