#include <stdio.h>
//AC
int L[100]={0};
int R[100]={0};
int isDescendant(int v,int u);
int main(){
    int d;
    char c;
    int ls,rs;
    ls=rs=0;
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
    printf("%d",isDescendant(v,u));
    return 0;
}
int isDescendant(int v,int u){
    if(L[v]==u || R[v]==u)
        return 1;
    else if(L[v]!=0 && isDescendant(L[v],u))
        return 1;
    else if(R[v]!=0 && isDescendant(R[v],u))
        return 1;
    else
        return 0; 
}