#include <stdio.h>
#include <stdlib.h>
//策略：考虑链表T1，将当前头指针作为归并段的头，从而取出一个最大升序子列，作为工作链表T2，并从原链表删除对应结点
//将取出工作链表与有序链表T3归并，直至原链表为空

typedef struct linknode{
        int data;
        struct linknode *next;
}node;
typedef struct linklist{
    node *head,*tail;
}List;
List * Insert(List *T,int data);
List * Mergesort(List *T,List *S);//target source
void printList(List *T);

int main(){
        int n;
        List *T1, *T2,*T3;
        T1=T2=T3=NULL;
        int data;
        int tmp;
        scanf("%d",&n);
        for(int i=0;i<n;i++){
                scanf("%d",&data);
                T1 = Insert(T1,data);
        }
        while(T1->head){
                
                T2=NULL;
                tmp=T1->head->data;
                T2=Insert(T2,tmp);
                
                node *p=T1->head;
                while(!p && p!=T1->tail){
                        if(p->next->data > tmp){
                                tmp = p->next->data;
                                T2=Insert(T2,tmp);
                                p->next = p->next->next;
                                if(!p->next)
                                        T1->tail=p;
                        }
                        p=p->next;
                }
                
                T1->head=T1->head->next;
                if(!T3)
                        T3=T2;
                else
                        T3=Mergesort(T3,T2);
        }
        printList(T3);
        return 0;
}


List * Insert(List *T,int data){
//直接在尾部插入
    node *p=(node *)malloc(sizeof(node));
    p->data=data;
    p->next=NULL;
    if(!T){
        T=(List *)malloc(sizeof(List));
        T->head=T->tail=p;
        return T;
    }
    else
    {
        T->tail->next=p;
        T->tail=p;
        return T;
    }
}
List * Mergesort(List *T,List *S){
    node *p=S->head;
    node *head=T->head;
    while(p){
        node *cur=(node *)malloc(sizeof(node));
        cur->data=p->data;
        if(T->head->data > cur->data){
            cur->next=T->head;
            T->head=cur;
            head=T->head;
        }
        else{
            while(head->next && head->next->data < cur->data)
                head=head->next;
            cur->next=head->next;
            head->next=cur;
            if(!cur->next)
                T->tail=p;
        }
        p=p->next;
    }
    return T;
}
void printList(List *T){
    node *p=T->head;
    while(p){
        printf("%d ",p->data);
        p=p->next;
    }
    return;
}