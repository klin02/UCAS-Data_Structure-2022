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
struct node *del(struct node *plist,int k); //注意delete为保留字
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
    int x;
    scanf("%d",&x);
    //printlist(plist);
    if(plist==plast && x==0)
        printf("NULL\n");
    else{
        plist=del(plist,x);
        printlist(plist);
    }
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
struct node *del(struct node *plist,int k){
    struct node *pre=plist;
    if(k==0){
        plist=plist->next;
        return plist;
    }
    for(int i=0;i<k-1;i++){
        pre=pre->next;
    }
    struct node *t=pre->next;
    pre->next=t->next;
    free(t);
    return plist;
}
/***
 * OJ测试并未测试删除首元素出现的问题，但规范起见，del中应当加入特判,由于改变头指针，也应当改变函数类型
 * 说明runtime error问题：
 * 当链表只有一个元素的时候，t为空指针，t->next异常
*/