#include <stdio.h>
//AC
//只用L,R或 T足矣
int T[100]={0};
int L[100]={0};
int R[100]={0};
int isParent(int v,int u);
int main(){
    int d;
    char c;
    int lt,ls,rs;
    lt=ls=rs=0;
    while(1){
        scanf("%d%c",&T[lt++],&c);
        if(c=='\n')
            break;
    }
    while(1){
        scanf("%d%c",&L[ls++],&c);
        if(c=='\n')
            break;
    }
    while(1){
        scanf("%d%c",&R[rs++],&c);
        if(c=='\n')
            break;
    }
    int u,v;
    scanf("%d %d",&u,&v);
    printf("%d",isParent(v,u));
    return 0;
}
int isParent(int v,int u){
    if(T[u]==0)
        return 0;
    else if(T[u]==v)
        return 1;
    else 
        return isParent(v,T[u]);
}