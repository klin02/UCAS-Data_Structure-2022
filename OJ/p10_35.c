#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define swap(a,b) {if(a!=b) a=b-a,b=b-a,a=a+b;}
//AC
//三叉堆排序
//调整过程制造大顶堆，然后移到最后产生递增序列
typedef struct{
    int r[10000];
    int len;
}Heap;
//依据书中算法，记录数据为1...len
Heap * Heapsort(Heap *H);
Heap * HeapAdjust(Heap *H,int s,int m);
int main(){
    Heap *H=(Heap *)malloc(sizeof(Heap));
    memset(H,0,sizeof(Heap));
    H->len=0;
    int n;
    char c;
    while(1){
        scanf("%d%c",&n,&c);
        H->r[++H->len]=n;
        if(c!=' ')
            break;
    }
    H=Heapsort(H);
    for(int j=1;j<=H->len;j++){
        printf("%d ",H->r[j]);
    }
    return 0;

} 
Heap * Heapsort(Heap *H){
    //len= 3i-1,3i,3i+1
    for(int i=(H->len+1)/3;i>0;i--)
        H=HeapAdjust(H,i,H->len);
    for(int i=H->len;i>1;i--){
        swap(H->r[1],H->r[i]);
        H=HeapAdjust(H,1,i-1);
    }
    return H;
}
Heap * HeapAdjust(Heap *H,int s,int m){
    int rc=H->r[s];
    int j,tmp;
    for(j=3*s-1;j<=m;j=3*j-1){
        tmp=j;
        if(tmp<m && H->r[tmp]< H->r[tmp+1] ) ++tmp;//tmp记录前两个中较大者的下标
        if(j+2<=m && H->r[tmp] < H->r[j+2])
            j+=2;
        else
            j=tmp;//返回前三者中较大的坐标
        if(rc >=H->r[j])
            break;
        else{
            H->r[s]=H->r[j];
            s=j;
        }
    }
    H->r[s]=rc;
    return H;
}
