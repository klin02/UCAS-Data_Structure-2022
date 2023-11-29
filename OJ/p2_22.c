#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//AC
struct node{
    int data;
    struct node *next;  
};
struct node *newnode();
void printlist(struct node *plist);
//头插法即可
int main(){
    char c;
    struct node *plist,*p;
    int flag=0;
    while((c=getchar())!='\n'){
        if(c!=','){
            p=newnode();
            p->data=c;
            if(flag==0){
                flag=1;
                p->next=NULL;
                plist=p;
            }
            else{
                p->next=plist;
                plist=p; 
            }
        }
    }
    printlist(plist);
}

struct node *newnode(){
    return (struct node*)malloc(sizeof(struct node));
}
void printlist(struct node *plist){
    struct node *pnode;
    pnode=plist;
    while(pnode!=NULL){
        printf("%c",pnode->data);
        pnode=pnode->next;
        if(pnode!=NULL)
        printf(",");
    }
    printf("\n");
}