#include <stdio.h>
//AC
#define MAXINT 0xffffffff
//4294967295 2^32-1
//注意，假设MAXINT为计算机允许的最大整数，程序中避免使用>MAXINT进行判断，应当反转式子后用除法判断
int main(){
    int n,arrsize;
    float tmp;
    unsigned int a[30]={0};//注意 如果用int 最后一个可能为负
    float op1=(float)(MAXINT/2);
    //printf("Input n:");
    scanf("%d %d",&n, &arrsize);
    if(n<0 || n>arrsize)
    {
        printf("-1");
        return 0;
    }
    a[0]=1;
    for(int i=1;i<n;i++){
        a[i]=a[i-1]*i*2;
        //judge part
        float op2=i;
        tmp=op1/op2;// note that unsigned should be change to int and second () is necessary!
        if((float)a[i-1]>tmp)
        {
            printf("-1");
            //printf("%d,%d",i,tmp);
            return 0;
        }
    }
    for(int i=0;i<n;i++)
        printf("%d ",a[i]);
    return 0;
}