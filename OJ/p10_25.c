#include <stdio.h>
#include <stdlib.h>
//AC
typedef struct linknode{
    int data;
    struct linknode *next;
}node;
node * Insert(node *head,int data);
int main(){
    int n;
    scanf("%d",&n);
    int data;
    node *head=NULL;
    for(int i=0;i<n;i++){
        scanf("%d",&data);
        head=Insert(head,data);
    }
    while(head){
        printf("%d ",head->data);
        head=head->next;
    }
    return 0;
}
node * Insert(node *head,int data){
    node *p=(node *)malloc(sizeof(node));
    p->data=data;
    p->next=NULL;
    if(!head)
        return p;
    if(data<head->data){
        p->next=head;
        return p;
    }
    else{
        node *t=head;
        while(t->next && t->next->data < data)
            t=t->next;
        p->next=t->next;
        t->next=p;
        return head;
    }
}