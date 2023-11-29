#include <stdio.h>
#include <string.h>
//AC
void reverse(char[],int left,int right);
int main(){
    char s[100];
    memset(s,0,100);
    char c;
    int len=0;
    while((c=getchar())!='\n'&&c!=EOF)
    s[len++]=c;
    //这里不用scanf主要是因为不确定输入的最后一位是什么，如果是EOF的话长度可能有问题
    reverse (s,0,len-1);
    printf("%s\n",s);
    return 0;
}
void reverse(char s[],int left,int right){
    char c;
    if(left>=right)
        return ;
    else{
        c=s[left];
        s[left]=s[right];
        s[right]=c;
        reverse(s,left+1,right-1);
        return;
    }
    
}
