#include <stdio.h>
#include <stdlib.h>
//AC
struct chunk{
    char ch;
    struct chunk *succ;
    struct chunk *next;
};
struct str{
    struct chunk *head;
    struct chunk *tail;
};
//头指针不存，尾指针存
struct str *Init();
struct chunk *newchunk();
void Insert(struct str *S,char c);
void getnext(struct str *T);
int KMP(struct str *S,struct str *T,int tlen);
int main(){
    struct str *S,*T;
    //S主串，T模式串 下简便起见，均用具有next的结构，但S无实际用途
    //设置尾结点后，长度无用
    S=Init();
    T=Init();
    int slen,tlen;
    char c;
    scanf("%d %d%c",&slen,&tlen,&c);
    while((c=getchar())!='\n'){
        Insert(S,c);
    }
    while((c=getchar())!='\n'){
        Insert(T,c);
    }
    getnext(T);
    int result=KMP(S,T,tlen);
    printf("%d",result);
    return 0;
}

struct str *Init(){
    struct str *tmp;
    tmp=(struct str*)malloc(sizeof(struct str));
    struct chunk *p=newchunk();
    p->succ=p->next=NULL;
    tmp->head=tmp->tail=p;
    return tmp;
}
struct chunk *newchunk(){
    return (struct chunk*)malloc(sizeof(struct chunk));
}
void Insert(struct str *S,char c){
    struct chunk *p=newchunk();
    p->ch=c;
    p->succ=NULL;
    S->tail->succ=p;
    S->tail=p;
}
void getnext(struct str *T){
    struct chunk *h,*ptr;
    h=T->head->succ;
    h->next=T->head;
    ptr=T->head;
    while(h!=T->tail){
        //注意判断条件并非h！=NULL 因为后续有h右移操作
        if(ptr==T->head || h->ch==ptr->ch){
            h=h->succ;
            ptr=ptr->succ;
            h->next=ptr;
        }
        else ptr=ptr->next;
    }

}
int KMP(struct str *S,struct str *T,int tlen){
    struct chunk *p1,*p2;
    p1=S->head->succ;
    p2=T->head->succ;
    while(p1!=NULL && p2!=NULL){
        if(p2==T->head || p1->ch==p2->ch){
            p1=p1->succ;
            p2=p2->succ;
        }
        else
            p2=p2->next;
    }
    if(p2==NULL){
        struct chunk *pre;
        pre=S->head->succ;
        //注意匹配成功后p1后移一位，最终位置在后一位
        int len=0;
        while(pre!=p1){
            len++;
            pre=pre->succ;
        }
        return len-tlen;
    }
    else return -1;
}