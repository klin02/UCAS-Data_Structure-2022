#include <stdio.h>
#include <stdlib.h>
#define min(a, b) ((a) < (b)) ? (a) : (b)
#define INF 99999
//AC
//注意为无向图
typedef struct arcnode
{
    int adj;
    int weight;
    struct arcnode *next;
} Arcnode;
Arcnode *Adjlist[100];
Arcnode *InsertAL(Arcnode *head, int data,int wt);
int D[100]={0};
int flag[100]={0};
int shortpath(int u,int v);
void Dijkstra(int n,int begin);
int main()
{
    int n,begin; //node
    char c;
    scanf("%d %d%c", &n, &begin, &c);
    int u,v,wt;
    while(scanf("%d-%d %d%c",&u,&v,&wt,&c)==4)
    {
        Adjlist[u]=InsertAL(Adjlist[u],v,wt);
        Adjlist[v]=InsertAL(Adjlist[v],u,wt);
        if(c!='\n')
            break;
    }
    Dijkstra(n,begin);
    int first=1;
    for(int i=1;i<=n;i++)
    {
        if(i==begin)
        continue;
        else if(first)
        {
            printf("%d",D[i]);
            first=0;
        }
        else
            printf(",%d",D[i]);
    }

    
    return 0;
}
Arcnode * InsertAL(Arcnode *head,int data,int wt){
    Arcnode *p=(Arcnode *)malloc(sizeof(Arcnode));
    p->adj=data;
    p->weight=wt;
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
void Dijkstra(int n,int begin){
    //Init D[]
    Arcnode *p=Adjlist[begin];
    while(p){
        flag[p->adj]=p->weight;
        p=p->next;
    }
    for(int i=1;i<=n;i++)
        if(i==begin)
            D[i]=-1;
        else if(flag[i]==0)
            D[i]=INF;
        else 
            D[i]=flag[i];
    
    //长度最长为n-1,初始化下一步长度为2
    for(int dep=2;dep<n;dep++){
        for(int i=1;i<=n;i++)
        {
            if(D[i]==-1)
            ;//自身
            else{
                Arcnode *t=Adjlist[i];
                if(t){
                    while(t){
                        if(t->adj!=begin)
                            D[i]=min(D[i],t->weight+D[t->adj]);
                        t=t->next;
                    }
                }
            }
        }
    }
}