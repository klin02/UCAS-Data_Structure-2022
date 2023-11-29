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
int main(){
    char c,s[10];
    int j=0;
    struct node *plist,*plast,*p;
    int flag=0;//标记第一个有效数据
    while((c=getchar())!='\n')
    {
        if(c!=' '){
            s[j++]=c;
        }
        else{// change to new item
            p=newnode();
            p->next=NULL;
            p->data=atoi(s);
            memset(s,0,sizeof(s));
            j=0;
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
    p=newnode();
    p->next=NULL;
    p->data=atoi(s);
    if(flag==0){
        flag=1;
        plist=plast=p;
    }
    else{
        plast->next=p;
        plast=plast->next;
    }

    int min,max;
    scanf("%d %d",&min,&max);

    //采用tmp指针，只考虑合法元素，且最后在考虑头结点
    //now在合法元素上移动
    struct node *now,*tmp,*nowlist;
    nowlist=now=tmp=plist;
    tmp=tmp->next;
    while(tmp!=NULL){
        if(tmp->data<= min || tmp->data>=max){
            now->next=tmp;
            now=now->next;
        }
        tmp=tmp->next;
    }
    now->next=NULL;
    
    //检查头结点
    if(nowlist->data >min && nowlist->data<max)
        nowlist=nowlist->next;
    printlist(nowlist);
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