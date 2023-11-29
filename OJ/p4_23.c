#include <stdio.h>
#include <stdlib.h>
//AC
struct chunk{
    char ch;
    struct chunk *next;
    struct chunk *prior;
};
struct str{
    struct chunk *head;
    struct chunk *tail;
};
//头指针不存，尾指针存
struct str *Init();
struct chunk *newchunk();
void Insert(struct str *S,char c);
int main(){
    int n;
    char c;
    scanf("%d%c",&n,&c);//吸收换行符
    struct str *S=Init();
    while((c=getchar())!='\n'){
        Insert(S,c);
    }
    struct chunk *l,*r;
    l=S->head->next;
    r=S->tail;
    int flag=1;
    while(l!=NULL){
        if(l->ch==r->ch){
            l=l->next;
            r=r->prior;
        }
        else{
            flag=0;
            break;
        }
    }
    printf("%d",flag);
    return 0;
}

struct str *Init(){
    struct str *tmp;
    tmp=(struct str*)malloc(sizeof(struct str));
    struct chunk *p=newchunk();
    p->prior=p->next=NULL;
    tmp->head=tmp->tail=p;
    return tmp;
}
struct chunk *newchunk(){
    return (struct chunk*)malloc(sizeof(struct chunk));
}
void Insert(struct str *S,char c){
    struct chunk *p=newchunk();
    p->ch=c;
    p->next=NULL;
    p->prior=S->tail;
    S->tail->next=p;
    S->tail=p;
}