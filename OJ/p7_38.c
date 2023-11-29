#include <stdio.h>
#include <stdlib.h>
#define max(a, b) ((a) > (b)) ? (a) : (b)
//AC
typedef struct arcnode
{
    int adj;
    struct arcnode *next;
} Arcnode;
//额外设置头结点以存储标号
typedef struct vnode
{
    char data;
    Arcnode *fir;
} Vnode;
Vnode *Adjlist[100];
Vnode *InsertAL(Vnode *p, int adj);
void printGraph(Vnode *p);
int main()
{
    int n; //node
    char c;
    scanf("%d%c", &n, &c);
    for (int i = 0; i < n; i++)
    {
        Vnode *p = (Vnode *)malloc(sizeof(Vnode));
        p->fir = NULL;
        scanf("%c%c", &p->data, &c);
        if (c != ' ')
        {
            Adjlist[i] = p;
            continue;
        }

        int adj;
        while (1)
        {
            scanf("%d%c", &adj, &c);
            p = InsertAL(p, adj);
            if (c != ' ')
            {
                Adjlist[i] = p;
                break;
            }
        }
    }

    printGraph(Adjlist[0]);
    return 0;
}
Vnode *InsertAL(Vnode *p, int adj)
{
    //后标号先打印
    Arcnode *t = (Arcnode *)malloc(sizeof(Arcnode));
    t->adj = adj;
    if (!p->fir)
    {
        p->fir = t;
        p->fir->next = NULL;
    }
    else
    {
        t->next = p->fir;
        p->fir = t;
    }
    return p;
}
void printGraph(Vnode *p){
    Arcnode *t;
    if(p->fir)
        for(t=p->fir;t;t=t->next)
            printGraph(Adjlist[t->adj]);
    printf("%c",p->data);
    return ;
}
