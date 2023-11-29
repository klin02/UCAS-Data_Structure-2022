#include <stdio.h>
//AC
void swap(int *a,int *b);
int main(){
    int x,y,z;
    scanf("%d %d %d",&x,&y,&z);
    if(x<y) swap(&x,&y);
    if(y<z){
        swap(&y,&z);
        if(x<y)
            swap(&x,&y);
    } 
    printf("%d %d %d",x,y,z);
    return 0;
}
void swap(int *a,int *b){
    int tmp=*a;
    *a=*b;
    *b=tmp;
}