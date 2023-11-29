#include <stdio.h>
#include <stdlib.h>
//AC
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
    char c;
    int len1=0,len2=0;
    List * T1,*T2;
    T1=T2=NULL;
    while(1){
        scanf("%d%c",&n,&c);
        T1=Insert(T1,n);
        len1++;
        if(c!=' ')
            break;
    }
    while(1){
        scanf("%d%c",&n,&c);
        T2=Insert(T2,n);
        len2++;
        if(c!=' ')
            break;
    }
    if(len1>len2)
    {
        T1=Mergesort(T1,T2);
        printList(T1);
    }
    else{
        T2=Mergesort(T2,T1);
        printList(T2);
    }
    return 0;
}
List * Insert(List *T,int data){
    
    //mode 0 尾部插入 1 查找合适位置插入
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
    // }
    // else{
    //     if(T->head->data > data){
    //         p->next=T->head;
    //         T->head=p;
    //         return p;
    //     }
    //     else{
    //         node *head=T->head;
    //         while(head->next && head->next->data < data)
    //             head=head->next;
    //         p->next=head->next;
    //         head->next=p;
    //         if(!p->next)
    //             T->tail=p;
    //         return T;
    //     }
    // }
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