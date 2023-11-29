#include <stdio.h>
#include <stdlib.h>
//AC
typedef struct linknode{
    int data;
    struct linknode *next;
}Linknode;
Linknode *h,*t;
void Insert(int data);
int Search(int data);
int main(){
    int n;
    char c;
    int res[100]={0};
    int top=0;
    while(1){
        scanf("%d%c",&n,&c);
        Insert(n);
        if(c!=' ')
            break;
    }
    while(1){
        scanf("%d%c",&n,&c);
        res[top++]=Search(n);
        if(c!=' ')
            break;
    }
    for(int i=0;i<top;i++)
        printf("%d ",res[i]);
    return 0;
}
void Insert(int data){
    //递增顺序插入
    Linknode *p=(Linknode *)malloc(sizeof(Linknode));
    p->data=data;
    if(!h){
        h=t=p;
    }
    else{
        t->next=p;
    }
    p->next=h;
    t=p;
    return ;
}
int Search(int data){
    if(data==t->data)
        return 1;
    else if(data<t->data)
        t=h;
    else
        t=t->next;
    while(data >= t->data){
        if(data==t->data)
            return 1;
        else
            t=t->next;
    }
    return 0;
}