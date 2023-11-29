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
struct node *buildlist();
int main(){
    struct node *la,*lb,*lc;
    la=buildlist();
    lb=buildlist();
    lc=buildlist();
    
    struct node *pre;
    pre=la;
    while(pre!=NULL){
        int flag1=0,flag2=0;
        while(lb!=NULL){
            if(lb->data==pre->data){
                flag1=1;
                break;
            }
            else if(lb->data>pre->data){
                break;
            }
            else{
                lb=lb->next;
            }
        }
        while(lc!=NULL){
            if(lc->data==pre->data){
                flag2=1;
                break;
            }
            else if(lc->data>pre->data){
                break;
            }
            else{
                lc=lc->next;
            }
        }
        if(flag1*flag2==1){
            if(pre==la)
                la=la->next;
            else{
                struct node *cur=la;
                while(cur->next!=pre)
                    cur=cur->next;
                cur->next=pre->next;
            }
        }
        pre=pre->next;
    }
    printlist(la);
    return 0;
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
struct node *buildlist(){
    char c;
    int flag=0;
    struct node *plist,*plast,*p;
    while((c=getchar())!='\n'){
        if(c!=','){
            p=newnode();
            p->data=c;
            p->next=NULL;
            if(flag==0){
                flag=1;
                plist=plast=p;
            }
            else{
                plast->next=p;
                plast=plast->next;
            }
        }
    }
    return plist;
}
