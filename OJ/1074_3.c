#include <stdio.h>
//AC
#define MaxLen 1000
#define Wr_dir 10
int row,col;
char map[100][100];
int dir[2][100][100];
//dir: 0 up 1 right 2 down 3 left
//考虑重复路径，因此需要将start到key和key到end两个分离
struct point{
    int row;
    int col;
};
struct point start,end,key;
int ShortestPath(struct point from,struct point to,int path); //path 0:start->key 1:key->end
void printPath(struct point from,struct point to,int path);
int main(){
    scanf("%d %d\n",&row,&col);
    char c;
    for(int i=1;i<=row;i++){
        for(int j=1;j<=col;j++){
            map[i][j]=getchar();
            if(map[i][j]=='R')
            {
                start.row=i;
                start.col=j;
            }
            else if(map[i][j]=='Y')
            {
                key.row=i;
                key.col=j;
            }
            else if(map[i][j]=='C')
            {
                end.row=i;
                end.col=j;
            }
        }            
            c=getchar();
    }
    ShortestPath(start,key,0);
    ShortestPath(key,end,1);
    printPath(start,key,0);
    printPath(key,end,1);
    // for(int i=1;i<=row;i++){
    //     for(int j=1;j<=col;j++)
    //         printf("%c",map[i][j]);
    //         printf("\n");
    // }
    return 0;
}
int ShortestPath(struct point from,struct point to,int path){
    if(from.row == to.row && from.col == to.col)
        return 0;
    char Temp = map[from.row][from.col];
    map[from.row][from.col]='1';
    
    struct point mid[4];
    mid[0].row = from.row-1;
    mid[0].col = from.col;
    mid[1].row = from.row;
    mid[1].col = from.col+1;
    mid[2].row = from.row+1;
    mid[2].col = from.col;
    mid[3].row = from.row;
    mid[3].col = from.col-1;

    int len=MaxLen;
    int dirtmp=Wr_dir;
    int lentmp;
    for(int i=0;i<=3;i++){
        if(mid[i].row>=1 && mid[i].row<=row && mid[i].col>=1 && mid[i].col<=col && map[mid[i].row][mid[i].col]!='1'){
            lentmp=ShortestPath(mid[i],to,path)+1;
            if(lentmp<len){
                len=lentmp;
                dirtmp=i;
            }
        }
    }
    
    map[from.row][from.col]=Temp;
    dir[path][from.row][from.col]=dirtmp;
    return len;
}
void printPath(struct point from,struct point to,int path){
    if(from.row == to.row && from.col == to.col){
        if(path==0)
            return;
        else 
        {
            printf("%d %d\n",to.row,to.col);
            return;
        }
    }
    printf("%d %d\n",from.row,from.col);
    struct point mid;
    switch (dir[path][from.row][from.col])
    {
    case 0:
        mid.row = from.row-1;
        mid.col = from.col;
        break;
    case 1:
        mid.row = from.row;
        mid.col = from.col+1;
        break;
    case 2:
        mid.row = from.row+1;
        mid.col = from.col;
        break;
    case 3:
        mid.row = from.row;
        mid.col = from.col-1;
        break;
    }
    printPath(mid,to,path);
}
