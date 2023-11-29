#include <stdio.h>
#include <stdlib.h>
//AC 
typedef struct word{
    int tag;//1 allocated 0 free
    int addr;
    int kval;
    struct word *llink,*rlink;
}WORD;
WORD *FreeList[32];
void Insert(int addr,int kval);
void Del(WORD *p);
void Recycle();
void printFreeList();
int main(){
    int addr,kval;
    int n;
    char c;
    int mode=0;// 0读取k，1读取地址
    while(scanf("%d%c",&n,&c)==2){
        if(mode==0){
            kval=n;
            mode=1;
        }
        else{
            addr=n;
            Insert(addr,kval);
        }
        if(c=='\n')
            mode=0;
    }
    Recycle();
    printFreeList();
    return 0;
}
void Insert(int addr,int kval){
    WORD *p=(WORD *)malloc(sizeof(WORD));
    p->addr=addr;
    p->kval=kval;
    p->llink=p->rlink=NULL;
    if(!FreeList[kval])
    {   FreeList[kval]=p;
        return ;}
    else{
        WORD *head=FreeList[kval];
        if(head->addr > p->addr){
            head->llink=p;
            p->rlink=head;
            FreeList[kval]=p;
            return;
        }
        else{
            for(;head->rlink&&head->rlink->addr < p->addr; head=head->rlink)
            ;
            p->rlink=head->rlink;
            head->rlink=p;
            p->llink=head;
            if(p->rlink)
                p->rlink->llink=p;
            return ;
        }    
    }

}
void Del(WORD *p){
    //此操作考虑左节点为空，即头结点情形
    if(p==FreeList[p->kval])
        FreeList[p->kval]=p->rlink;
    else
        p->llink->rlink=p->rlink;
    if(p->rlink)
        p->rlink->llink=p->llink;
    return ;
}
void Recycle(){
    for(int i=0;i<32;i++){
        if(FreeList[i]){
            WORD *head =FreeList[i];
            while(head&&head->rlink){
                if(head->addr%(2<<head->kval)==0 && head->rlink->addr==head->addr+(1<<head->kval)){
                    Insert(head->addr,head->kval+1);
                    WORD *next=head->rlink->rlink;
                    Del(head->rlink);
                    Del(head);
                    head=next;
                }
                else    
                    head=head->rlink;
            }
        }
    }
}
void printFreeList(){
    for(int k=0;k<32;k++)
    if(FreeList[k]){
        printf("%d",k);
        WORD *p=FreeList[k];
        while(p){
            printf(" %d",p->addr);
            p=p->rlink;
        }
        printf("\n");
    }
    return ;
}