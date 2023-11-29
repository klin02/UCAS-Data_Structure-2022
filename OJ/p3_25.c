#include <stdio.h>
//AC
int main(){
    int n;
    scanf("%d",&n);
    int f=1;
    while(n!=0){
        f*=n;
        n/=2;
    }
    printf("%d",f);
    return 0;
}