#include <stdio.h>
#define swap(a,b) {if(a!=b) a=b-a,b=b-a,a=a+b;}
//AC
//虽然但是，如果要AC甚至不用十行
int L[100]={0};
int R[100]={0};
void convert(int v);
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
    convert(1);
    //若从0开始，两次翻转
    printf("%d",L[0]);
    for(int i=1;i<ls;i++)
        printf(" %d",L[i]);
    printf("\n");
    printf("%d",R[0]);
    for(int i=1;i<rs;i++)
        printf(" %d",R[i]);
    return 0;
}
void convert(int v){
    if(L[v]==0 && R[v]==0)
        return;
    else{
        if(L[v]!=0)
            convert(L[v]);
        if(R[v]!=0)
            convert(R[v]);
        swap(L[v],R[v]);
    }
}