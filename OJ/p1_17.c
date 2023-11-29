#include <stdio.h>
//AC
int Fibo(int k,int m);
//传值调用
int main(){
    int k,m;
    scanf("%d %d",&k,&m);
    printf("%d",Fibo(k,m));
    return 0;
}
int Fibo(int k,int m){
    int s[10000]={0};
    s[k-1]=1;
    for(int i=k;i<=m;i++)
        for(int j=1;j<=k;j++)
            s[i]+=s[i-j];
    return s[m];
}