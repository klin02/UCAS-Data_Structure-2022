#include <stdio.h>
#include <string.h>
//AC
//简便起见偷懒。。没用递推.递推可以从字符串最后一位逐一拿到新串，也可以逐一缩小长度翻转
void reverse(char[],int len);
int main(){
    char s[100];
    char c;
    int len=0;
    while((c=getchar())!='\n'&&c!=EOF)
    s[len++]=c;
    //这里不用scanf主要是因为不确定输入的最后一位是什么，如果是EOF的话长度可能有问题
    reverse (s,len);
    printf("%s\n",s);
    return 0;
}
void reverse(char s[],int len){
    int c,i,j;
    for (i=0,j=len-1;i<j;i++,j--){
        c=s[i];
        s[i]=s[j];
        s[j]=c;
    }
}