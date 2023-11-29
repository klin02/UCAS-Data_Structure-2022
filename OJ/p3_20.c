#include <stdio.h>
//AC
//up down left right x raw y col
int dx[]={-1,1,0,0};
int dy[]={0,0,-1,1};

int a[30][30];
int row,col,x,y;
int dir;
int Inmap(int px,int py);
void dfs(int px,int py);
int main(){
    scanf("%d %d %d %d %d",&row,&col,&x,&y,&dir);
    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++)
            scanf("%d",&a[i][j]);
    dfs(x,y);
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++)
            printf("%d",a[i][j]);
        printf("\n");
    }
        return 0;

}
int Inmap(int px,int py){
    if(px>=0 && px<row && py>=0 && py<col)
        return 1;
    else return 0;
}
void dfs(int px,int py){
    a[px][py]=2;
    int curdir;
    int tx,ty;
    for(int i=0;i<4;i++){
        curdir=(dir+i)%4;
        tx=px+dx[curdir];
        ty=py+dy[curdir];
        if(Inmap(tx,ty) && a[tx][ty]==1)
            dfs(tx,ty);
    }
}