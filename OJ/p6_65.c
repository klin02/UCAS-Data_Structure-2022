#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//AC 
typedef struct binode{
    char data;
    struct binode *lchild,*rchild;
}Binode,*Bitree;
Bitree creatTree(char *s1,char *s2);
void printTree(Bitree T);
int main(){
    char s1[100],s2[100];
    memset(s1,0,sizeof(s1));
    memset(s2,0,sizeof(s2));
    int len=0;
    char c;
    while((c=getchar())!='\n'&& c!=EOF){
        s1[len++]=c;
    }
    s1[len]='\0';
    len=0;
    while((c=getchar())!='\n'&& c!=EOF){
        s2[len++]=c;
    }
    s2[len]='\0';

    Bitree T=creatTree(s1,s2);
    printTree(T);
}
Bitree creatTree(char *s1,char *s2){
    //strlen不计算\0
    if(!s1||!*s1)
        return NULL;
    
    Bitree T=(Bitree)malloc(sizeof(Binode));
    T->data=s1[0];
    char l1[100],l2[100],r1[100],r2[100];
    int len1=0,len2=0;
    //pre l1 r1 in l2 r2
    memset(l1,0,sizeof(l1));
    memset(l2,0,sizeof(l2));
    memset(r1,0,sizeof(r1));
    memset(r2,0,sizeof(r2));
    for(int i=0;i<strlen(s2);i++)
    {
        if(s2[i]==s1[0])
            break;
        else
            l2[len1++]=s2[i];
    }
    for(int i=len1+1;i<strlen(s2);i++)
        r2[len2++]=s2[i];
    
    int len3=0;
    for(int i=1;i<=len1;i++)
    l1[len3++]=s1[i];
    len3=0;
    for(int i=len1+1;i<strlen(s1);i++)
    r1[len3++]=s1[i];

    T->lchild=creatTree(l1,l2);
    T->rchild=creatTree(r1,r2);
    return T;
}
void printTree(Bitree T){
    //post order
    if(!T)
        return;
    printTree(T->lchild);
    printTree(T->rchild);
    printf("%c",T->data);
    return ;
}