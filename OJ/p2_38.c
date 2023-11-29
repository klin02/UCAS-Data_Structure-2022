#include <stdio.h>
#include <stdlib.h>
//AC
struct node{
    int data;
    int freq;
    int ord;
    struct node *prior;
    struct node *next;
};
struct node *newnode();
void printlist(struct node *plist);

//由于要求频次相同，先访问优先而非先达到频次优先
//若将访问和排序同时进行，无法处理4 5 5 4情形
//若将访问和排序分离，无法处理按访问次序，因此加上成员order
int main(){
    int n;
    scanf("%d",&n);
    struct node *plist,*plast,*p;
    plist=newnode();
    scanf("%d",&plist->data);
    plist->freq=0;
    plist->ord=-1;
    plist->next=plist->prior=NULL;
    plast=plist;
    for(int i=1;i<n;i++){
        p=newnode();
        scanf("%d",&p->data);
        p->freq=0;
        p->ord=-1;
        p->next=NULL;
        p->prior=plast;
        plast->next=p;
        plast=plast->next;
    }
    int tmp;
    char c;
    int order=n;//区别未访问元素，先访问元素order较大
    while(scanf("%d%c",&tmp,&c)==2){
        struct node *pre=plist;
        while(pre->data!=tmp){
            pre=pre->next;
        }
        pre->freq++;
        if(pre->ord==-1)//首次访问
            pre->ord=order--;
        if(c=='\n')
            break;
    }
    struct node *pre=plist;
    while(pre!=NULL){
        while(pre!=plist){
            struct node *pp;
            pp=pre->prior;
            if(pre->freq > pp->freq || (pre->freq==pp->freq && pre->ord > pp->ord))
            {
                if(pp==plist){
                    struct node *nt=pre->next;
                    pre->next=plist;
                    pre->prior=NULL;
                    plist->prior=pre;
                    plist->next=nt;
                    nt->prior=plist;
                    plist=pre;
                }
                else if(pre==plast){
                    struct node *ppre=pp->prior;
                    ppre->next=pre;
                    pre->prior=ppre;
                    pre->next=pp;
                    pp->prior=pre;
                    pp->next=NULL;
                    plast=pp;
                }
                else{
                    struct node *nt=pre->next;
                    struct node *ppre=pp->prior;
                    ppre->next=pre;
                    pre->prior=ppre;
                    pre->next=pp;
                    pp->prior=pre;
                    pp->next=nt;
                    nt->prior=pp;
                }
                //printlist(plist);
            }
            else
                break;
        }
        pre=pre->next;
    }
    printlist(plist);
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