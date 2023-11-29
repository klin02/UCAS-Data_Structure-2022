#include <stdio.h>
//AC
//快排也可AC
//考虑到限制了整数均不大于10000，可使用桶排序 不需比较和移动
//注意考虑同一数字重复情形
int stack[10000]={0};
int main(){
    int n;
    for(int i=0;i<1000;i++){
        scanf("%d",&n);
        stack[n]++;
    }
    for(int i=0;i<10000;i++){
        if(stack[i]){
            for(int j=0;j<stack[i];j++)
            printf("%d ",i);
        }
            
    }
    return 0;
}