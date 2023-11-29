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
int main(){
    int n,m;//node edge
    scanf("%d,%d",&n,&m);
    int start=1;
    int end=n;
    //检测节点序号连续，考虑可能0起始
    for(int i=0;i<m;i++){
        int u,v;
        char c;
        scanf("%d-%d%c",&u,&v,&c);
        if(u==0 || v==0)
        {
            start=0;
            end=n-1;
        }
        Adjlist[u]=InsertAL(Adjlist[u],v);
    }
    for(int i=start;i<=end;i++){
        printf("%d",i);
        if(Adjlist[i]){
            printf(" %d",Adjlist[i]->adj);
            Arcnode *p=Adjlist[i]->next;
            while(p){
                printf(",%d",p->adj);
                p=p->next;
            }
        }
        printf("\n");
    }
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