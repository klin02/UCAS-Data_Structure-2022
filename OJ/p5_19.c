#include <stdio.h>
//AC
int a[100][100];
int Saddle(int x,int y);
int row,col;
int main(){
    scanf("%d %d",&row,&col);
    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++)
        scanf("%d",&a[i][j]);
    
    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++)
        if(Saddle(i,j))
        printf("%d ",a[i][j]);
    
    return 0;
}
int Saddle(int x,int y){
    int tmp=a[x][y];
    int flag1=1,flag2=1;
    for(int j=0;j<col;j++)
        if(a[x][j]<tmp){
            flag1=0;
            break;
        }
    for (int i=0;i<row;i++)
        if(a[i][y]>tmp){
            flag2=0;
            break;
        }
    return flag1*flag2;
}