#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ord(s) s=='$'?0:s-'a'+1
//AC
//用多重链表表示的键树 trie树
//更改结构 注意到叶子节点对应$(序号0)即可
typedef enum{LEAF,BRANCH} Nodetype;
typedef struct trienode{
   int tag[27];
   struct trienode *child[27];
}Trienode, *Trietree;
Trietree Insert(Trietree T,char s[]);
int Search(Trietree T,char s[]);
Trietree Del(Trietree,char s[]);
int main(){
    int mode;
    char c;
    char s[100];
    int len=0;
    Trietree T=NULL;
    int res[100]={0};//输入输出分离
    int top=0;
    while(1){
        memset(s,0,sizeof(s));
        len=0;
        if(scanf("%d%c",&mode,&c)!=2)
            break;
        while((c=getchar())!='\n'&&c!=EOF){
            s[len++]=c;
        }
        s[len++]='$';
        s[len]='\0';
        
        switch (mode)
        {
        case 1: T=Insert(T,s);
            break;
        case 2: T=Del(T,s);
            break;
        default: res[top++]=Search(T,s);
            break;
        }
        if(c==EOF)
            break;

    }
    for(int i=0;i<top;i++){
        if(res[i]==0)
            printf("False\n");
        else
            printf("True\n");
    }
    return 0;
}
Trietree Insert(Trietree T,char s[]){
    char cur[100];
    strcpy(cur,s);
    if(!T){
        T=(Trietree)malloc(sizeof(Trienode));
        memset(T,0,sizeof(Trienode));
    }
    if(cur[0]=='$'){
        T->tag[0]++;
        return T;
    }
    else{
        int order=ord(cur[0]);
        T->tag[order]++;
        T->child[order]=Insert(T->child[order],cur+1);
        return T;
    }
}
int Search(Trietree T,char s[]){
    for(int i=0;s[i]!='$' && T;i++)
    T=T->child[ord(s[i])];
    // if(T->tag[0]==0)
    //     printf("False\n");
    // else 
    //     printf("True\n");
    if(!T)//字符串长于深度情形
        return 0;
    else
        return T->tag[0];
}
Trietree Del(Trietree T,char s[]){
    //存在才删除
    if(Search(T,s)==0)
        return T;
    Trietree head=T;
    for(int i=0;s[i]!='$';i++){
        T->tag[ord(s[i])]--;
        T=T->child[ord(s[i])];
    }
    T->tag[0]--;
    return head;
}