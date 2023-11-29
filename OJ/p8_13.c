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
void Del(WORD *p);
WORD * Recycle(WORD *space,int addr,int size);
void printSpace(WORD *space);
int main(){
    int tag,addr,size;
    char c;
    WORD * space =NULL;
    while(scanf("%d%d%d",&tag,&addr,&size)==3){
        if(tag==0)
            space=Insert(space,addr,size);
        else
            space=Recycle(space,addr,size);
    }
    printSpace(space);
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
void Del(WORD *p){
    //此操作未考虑左节点为空情形，因此在使用时避免删除左侧节点
    p->llink->rlink=p->rlink;
    if(p->rlink)
        p->rlink->llink=p->llink;
    return ;
}
WORD * Recycle(WORD *space,int addr,int size){
    space=Insert(space,addr,size);
    WORD *head =space;
    while(head && head->rlink){
        if(head->addr+head->size==head->rlink->addr){
            head->size += head->rlink->size;
            Del(head->rlink);
            //注意删除右侧点且head不移动
        }
        else
            head=head->rlink;
    }
    return space;
}
void printSpace(WORD *space){
    while(space){
        printf("0 %d %d\n",space->addr,space->size);
        space=space->rlink;
    }
    return ;
}