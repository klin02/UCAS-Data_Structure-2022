#include <stdio.h>
#include <stdlib.h>
//AC
struct node{
    int data;
    struct node *next;  
};
struct node *newnode();
void printlist(struct node *plist);
int main(){
    int m,n;
    scanf("%d %d",&m,&n);
    struct node *la,*lb,*ra,*rb,*p;
    ra=newnode();
    ra->next=NULL;
    scanf("%d",&ra->data);
    la=ra;
    for(int i=1;i<m;i++){
        p=newnode();
        scanf("%d",&p->data);
        p->next=NULL;
        ra->next=p;
        ra=ra->next;
    }
    //printlist(la);
    rb=newnode();
    rb->next=NULL;
    scanf("%d",&rb->data);
    lb=rb;
    for(int i=1;i<n;i++){
        p=newnode();
        scanf("%d",&p->data);
        p->next=NULL;
        rb->next=p;
        rb=rb->next;
    }
    //printlist(lb);
    rb->next=la;
    printlist(lb);
    return 0;

}
struct node *newnode(){
    return (struct node*)malloc(sizeof(struct node));
}
void printlist(struct node *plist){
    struct node *pnode;
    pnode=plist;
    while(pnode!=NULL){
        printf("%d ",pnode->data);
        pnode=pnode->next;
    }
    printf("\n");
}