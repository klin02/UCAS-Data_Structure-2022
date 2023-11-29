#include <stdio.h>
//AC
char stack[100];
char top=0;
int main(){
    char c;
    while((c=getchar())!='@')
    stack[top++]=c;
    int flag=1;
    for(int i=0;i<top;i++)
    if(stack[i]!=stack[top-1-i]){
        flag=0;
        break;
    }
    printf("%d",flag);
    return 0;
}