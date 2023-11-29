#include <stdio.h>
#include <stdlib.h>
//AC
struct node{
    int data;
    struct node *next;
};
struct queue{
    struct node *tail;
};//无头指针的循环链表作为队列
struct queue *Init();
struct queue *Inqueue(struct queue *Q,int x);
struct queue *Outqueue(struct queue *Q);
struct node *newnode();
int main(){
    int n;
    scanf("%d",&n);
    int tmp;
    char c;
    struct queue *Q;
    Q=(struct queue*)malloc(sizeof(struct queue));
    Q=Init();
    for(int i=0;i<n;i++){
        scanf("%d%c",&tmp,&c);//！！注意有几个占位符就需要有几个参数
        Q=Inqueue(Q,tmp);
    }
    for(int i=0;i<n;i++){
        Q=Outqueue(Q);
    }
    return 0;
    //printf("%d",tmp);
}
struct queue *Init(){
    struct queue *tmp;
    tmp=(struct queue*)malloc(sizeof(struct queue));
    struct node *p;
    p=newnode();
    tmp->tail=p;
    p->next=tmp->tail;
    return tmp;
}
struct node *newnode(){
    return (struct node*)malloc(sizeof(struct node));
}
struct queue *Inqueue(struct queue *Q,int x){
    struct node *p;
    p=newnode();
    p->data=x;
    p->next=Q->tail->next;
    Q->tail->next=p;
    Q->tail=p;
    return Q;
}
struct queue *Outqueue(struct queue *Q){
    if(Q->tail==Q->tail->next)
    ;//NULL
    else{
        struct node *h;
        h=Q->tail->next;
        if(h->next==Q->tail){
            printf("%d",Q->tail->data);
            h->next=h;
        }
        else{
            struct node *t;
            t=h->next;
            h->next=t->next;
            printf("%d,",t->data);
            //free(t);
        }
    }
    return Q;
}