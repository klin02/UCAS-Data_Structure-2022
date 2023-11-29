#include <stdio.h>
//AC
struct read
{
    char ch;
    int loc;
}re[100];
int lr=0;
//如果为了减少时间复杂度，可以用hash表存储是否读取过该元素
int main(){
    char s[100],t[100];
    int ls,lt;
    ls=lt=0;
    char c;
    while((c=getchar())!=' ')
        s[ls++]=c;
    while((c=getchar())!=' ' &&c!='\n'&&c!=EOF)
        t[lt++]=c;
    
    int flg1,flg2;
    for(int i=0;i<ls;i++){
        flg1=flg2=1;
        for(int j=0;j<lr;j++)
            if(re[j].ch==s[i])
            {
                flg1=0;
                break;
            }
        for(int k=0;k<lt;k++)
            if(t[k]==s[i])
            {
                flg2=0;
                break;
            }
        if(flg1*flg2==1){
            re[lr].ch=s[i];
            re[lr].loc=i;
            lr++;
        }
    }

    if(lr==0){
        printf("-1");
        return 0;
    }
    for(int i=0;i<lr;i++)
        printf("%c",re[i].ch);
    printf(" ");
    for(int i=0;i<lr;i++)
        printf("%d",re[i].loc);
    return 0;
}