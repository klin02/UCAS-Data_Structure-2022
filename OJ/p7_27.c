#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//AC
typedef struct arcnode{
    int adj;
    struct arcnode *next;
}Arcnode;
//不需额外设置头结点
//注意无向图，一条弧等价于有向图两条
Arcnode * Adjlist[100];
Arcnode * InsertAL(Arcnode *head,int data);
int simplepath(int u,int v,int dep,int s[],int len);//dfs len为路径长度，s[]为先前访问结点
int k;//depth
int main(){
    int n;//node
    char c;
    scanf("%d,%d%c",&n,&k,&c);
    int x,y;
    scanf("%d,%d%c",&x,&y,&c);
    while(1){
        int u,v;
        scanf("%d-%d%c",&u,&v,&c);
        Adjlist[u]=InsertAL(Adjlist[u],v);
        Adjlist[v]=InsertAL(Adjlist[v],u);
        if(c!=',')
            break;
    }
    int s[100]={0};
    int len=0;
    if(simplepath(x,y,1,s,len)==1)
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

int simplepath(int u,int v,int dep,int s[],int len){
    for(int i=0;i<len;i++)
        if(s[i]==u)
            return 0;

    s[len++]=u;
    Arcnode *p=Adjlist[u];
    while(p){
        if(dep==k && p->adj==v){
            int flag=1;
            for(int i=0;i<len;i++)
                if(s[i]==v){
                    flag=0;
                    break;
                }
            if(flag==1)
                return 1;
        }
        else if(simplepath(p->adj,v,dep+1,s,len)==1)
            return 1;
        p=p->next;
    }
    return 0;
}