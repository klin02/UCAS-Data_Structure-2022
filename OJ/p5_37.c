#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ATOM 0
#define LIST 1
//AC
typedef struct glnode{
    int tag;//Atom 0 List 1
    union{
        char atom;
        struct{struct glnode *hp,*tp;}ptr;
    };
} *GList,GLnode;
typedef struct servestr{
    char *head;
    char *tail;
} Server;
GList creGList(char *s);
void printGList(GList L,int mode);
GList DelAtom(GList L,char data);
void serve(Server *tmpsev,char *s);
char s[100];
char emp[]="()";
int main(){
    int ls=0;
    char c;
    while((c=getchar())!=EOF && c!='\n' && c!=' ')
    s[ls++]=c;
    s[ls]='\0';
    GList L=(GList)malloc(sizeof(GLnode));
    L=creGList(s);
    c=getchar();
    L=DelAtom(L,c);
    if(L==NULL)
        printf("-1");
    else 
    printGList(L,1);
    return 0;

}
GList creGList(char *s){
    if(!s||!*s) //!s 表示s不是NULL， !*s 表示s[0]不是\0
        return NULL;
    if(strcmp(s,emp)==0)
        return NULL;
    
    GList L=(GList)malloc(sizeof(GLnode));
    if(strlen(s)==1){
        L->tag=ATOM;
        L->atom=*s;
    }
    else{
        L->tag=LIST;
        Server *tmpsev=(Server *)malloc(sizeof(Server));
        serve(tmpsev,s);
        L->ptr.hp=creGList(tmpsev->head);
        L->ptr.tp=creGList(tmpsev->tail);
    }
    return L;
}

void serve(Server *tmpsev,char *s){
    char *h,*t;
    char *s0=s;
    int len=strlen(s);
    h=(char *)malloc(len*sizeof(char));
    t=(char *)malloc(len*sizeof(char));
    strcpy(h,s);
    strcpy(t,s);
    int k=0;//统计未配对左括号
    while(*s){
        if(*s=='(')
            k++;
        else if(*s==')')
            k--;
        else if(*s==',' && k==1)
            break;
        s++;
    }
    if(*s){
        //eg. (A,(b,c)) or (A,B,C)
        *(h+(s-s0))=0;
        h++;
        tmpsev->head=h;
        t+=(s-s0);
        *t='(';
        tmpsev->tail=t;
    }
    else{
        //eg. ((A)) 此时tail空，head只需脱括号
        *(h+len-1)=0;
        h++;
        tmpsev->head=h;
        tmpsev->tail=NULL;
    }
    return ;
}

void printGList(GList L,int mode){
    //e.g (a,b,c) head->a tail->(b,c)  ->b (c)
    //e.g (a,(b),c) ((b),c) head:(b) tail(c) 需要区分
    //因此设置mode区分头尾情形 尾部在创建过程中多添一对括号
    if(!L)
        return;
    if(L->tag==ATOM)
        printf("%c",L->atom);
    else {
        if(mode){
            printf("(");
        }
        printGList(L->ptr.hp,1);
        if(L->ptr.tp){
            if(L->ptr.hp)
                printf(",");
            printGList(L->ptr.tp,0);
        }
        if(mode){
            printf(")");
        }
    }
    return ;
}
GList DelAtom(GList L,char data){
    //传入形参，在函数中将其置空无效，因此应当在外层执行, 但改变类型后可以
    //由于(a,b) 尾部为b 因此原子节点必定是头结点
    if(!L)
        return NULL;
    if(L->tag==ATOM && L->atom==data)
        L=NULL;
    else if(L->tag==LIST){
        L->ptr.hp=DelAtom(L->ptr.hp,data);
        L->ptr.tp=DelAtom(L->ptr.tp,data);
        if(L->ptr.hp==NULL && L->ptr.tp==NULL)
            L=NULL;
    }
    return L;
}