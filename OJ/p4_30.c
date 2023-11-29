#include <stdio.h>
#include <string.h>
//AC
int main(){
    char s[100],t[100],r[100];
    int ls,lt,lr;
    ls=lt=lr=0;
    char c;
    while((c=getchar())!=' ' &&c!='\n'&&c!=EOF)
        s[ls++]=c;
    int loc;
    //考察不同起始位置的重复串
    for(int i=0;i<ls;i++)
        for(int j=i+1;j<ls;j++)
        {
            int p1=i,p2=j;
            lt=0;
            memset(t,0,sizeof(t));
            while(s[p1]==s[p2] && p2<ls){
                t[lt++]=s[p1];
                p1++,p2++;
            }
            if(lt>lr){
                lr=lt;
                strcpy(r,t);
                loc=i;
            }
        }

    if(lr==0)
        printf("-1");
    else{
        for(int l=0;l<lr;l++)
            printf("%c",r[l]);
        printf(" ");
        printf("%d",loc);
    }
    return 0;
}
