#include <stdio.h>
#include <stdlib.h>
//AC 
typedef struct word{
    int tag;//1 allocated 0 free
    int addr;
    int size;
    struct word *llink,*rlink;
}WORD;
WORD * Insert(WORD *space,int addr,int size);
void printSpace(WORD *space);
int main(){
    int high,low,block;
    int n;
    char c;
    WORD * space =NULL;
    scanf("%d %d %d",&high,&low,&block);
    int total=(low-high)/block;
    int curaddr,cursize,state;
    curaddr=cursize=0;
    state=1;//前一个读取数字

    for(int i=0;i<total;i++){
        scanf("%d",&n);
        if(state==1&&n==0){
            curaddr=high+block*i;
            cursize+=block;
            state=0;
        }
        else if(state==0 && n==0){
            cursize+=block;
        }
        else if(state==0 && n==1){
            space=Insert(space,curaddr,cursize);
            curaddr=0;
            cursize=0;
            state=1;
        }
    }
    if(state==0)
    space=Insert(space,curaddr,cursize);
    if(space)
        printSpace(space);
    else
        printf("0 0 0\n");
    return 0;
}
WORD * Insert(WORD *space,int addr,int size){
    WORD *p=(WORD *)malloc(sizeof(WORD));
    p->addr=addr;
    p->size=size;
    p->llink=p->rlink=NULL;
    if(!space)
        return p;
    else{
        WORD *head=space;
        if(head->addr > p->addr){
            head->llink=p;
            p->rlink=head;
            return p;
        }
        else{
            for(;head->rlink&&head->rlink->addr < p->addr; head=head->rlink)
            ;
            p->rlink=head->rlink;
            head->rlink=p;
            p->llink=head;
            if(p->rlink)
                p->rlink->llink=p;
            return space;
        }    
    }

}
void printSpace(WORD *space){
    while(space){
        printf("0 %d %d\n",space->addr,space->size);
        space=space->rlink;
    }
    return ;
}