#include <stdio.h>
#include <stdlib.h>
#define swap(a,b) {if(a!=b) a=b-a,b=b-a,a=a+b;}
//AC
//简便起见，可以不交换结点，而是交换结点的数据
typedef struct linknode{
    int data;
    struct linknode *next;
}node;
node * Selectsort(node *head);
node * getmin(node *head);

int main(){
    int data;
    char c;
    node *head=NULL;
    node *ptr=NULL;
    int first=1;
    while(1){
        scanf("%d%c",&data,&c);
        node *p=(node *)malloc(sizeof(node));
        p->data=data;
        p->next=NULL;
        if(first){
            first=0;
            head=ptr=p;
        }
        else{
            ptr->next=p;
            ptr=p;
        }
        if(c!=' ')
            break;
    }
    head=Selectsort(head);
    while(head){
        printf("%d ",head->data);
        head=head->next;
    }
    return 0;
}
node * Selectsort(node *head){
    node *p=head;
    node *t;
    while(p){
        t=getmin(p);
        swap(p->data,t->data);
        p=p->next;
    }
    return head;
}
node * getmin(node *head){
    node *p=head;
    node *min=NULL;
    while(p){
        if(!min || p->data<min->data){
            min=p;
        }
        p=p->next;
    }
    return min;
}