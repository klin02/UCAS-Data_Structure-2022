#include <stdio.h>
//AC
int a[100][100]={0};
int main(){
    int m,n;
    scanf("%d %d",&m,&n);
    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
        scanf("%d",&a[i][j]);

    int flag=0;//第一项前不需加号
    for(int i=m-1;i>=0;i--)
        for(int j=n-1;j>=0;j--)
        if(a[i][j]!=0){
            if(flag==0){
                flag=1;
            }
            else
                printf("+");
            if(a[i][j]!=1)
                printf("%d",a[i][j]);
            if(i!=0)
                printf("xE%d",i);
            if(j!=0)
                printf("yE%d",j);
        }
    return 0;
}