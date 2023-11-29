#include <stdio.h>
//AC
int main(){
    int n;
    float x;
    scanf("%f %d",&x,&n);
    float base=1,sum=0;
    float a;
    for(int i=0;i<=n;i++){
        scanf("%f",&a);
        sum += base*a;
        base *= x;
    }
    printf("%.f",sum);
    return 0;
}