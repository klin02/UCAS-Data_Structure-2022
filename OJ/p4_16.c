#include <stdio.h>
//AC
int main(){
    char s[100],t[100];
    int ls,lt;
    ls=lt=0;
    char c;
    while((c=getchar())!=' ')
        s[ls++]=c;
    while((c=getchar())!=' ' &&c!='\n'&&c!=EOF)
        t[lt++]=c;
    //int res=0;
    for(int i=0;i<ls&& i<lt;i++){
        if(s[i]>t[i])
        {
            printf("1");
            return 0;
        }
        else if(s[i]<t[i]){
            printf("-1");
            return 0;
        }
    }
    if(ls>lt)
        printf("1");
    else if(ls<lt)
        printf("-1");
    else
        printf("0");
    return 0;
}