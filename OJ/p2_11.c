#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//AC
int main(){
    int a[100]={0};
    int x;
    int len=0,j=0;//s[j] note the lenth is len but last one is a[len-1]
    char c,s[10];
    while((c=getchar())!='\n')
    {
        if(c!=' '){
            s[j++]=c;
        }
        else{// change to new item
            a[len]=atoi(s);
            memset(s,0,sizeof(s));
            j=0;
            len++;
        }
    }
    a[len]=atoi(s);
    len++;//note the last one
    scanf ("%d",&x);
    int k;
    for(k=0;k<len;k++){
        if(a[k]>x)
        break;
    }
    if(k==len){
        a[len]=x;
        len++;
    }
    else{
        for(int j=len-1;j>=k;j--){
            a[j+1]=a[j];
        }
        a[k]=x;
        len++;
    }

    for(int i=0;i<len;i++)
        printf("%d ",a[i]);
    return 0;
}