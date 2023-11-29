#include <stdio.h>
//AC
int main(){
    char s[100],t[100],v[100],r[100];
    //定义main函数中的不会自动清空，为省略清零过程，在打印时不用%s,只打印自己填充部分。
    int ls,lt,lv,lr;
    ls=lt=lv=lr=0;
    char c;
    while((c=getchar())!=' ' &&c!='\n'&&c!=EOF)
        s[ls++]=c;
    while((c=getchar())!=' ' &&c!='\n'&&c!=EOF)
        t[lt++]=c;
    while((c=getchar())!=' ' &&c!='\n'&&c!=EOF)
        v[lv++]=c;
    
    int p1,p2,bef;
    int flag=0;
    for(int i=0;i<ls;i++){
        p1=i,p2=0;
        while(s[p1]==t[p2]&& p1<ls && p2<lt)
            p1++,p2++;
        if(p2==lt){
            flag=1;
            bef=i;
            break;
        }
    }
    if(flag==0){
        for(int i=0;i<ls;i++)
        printf("%c",s[i]);
    } 
    else{
        for(int i=0;i<bef;i++)
            r[lr++]=s[i];
        for(int j=0;j<lv;j++)
            r[lr++]=v[j];
        for(int k=p1;k<ls;k++)
            r[lr++]=s[k];
        for(int i=0;i<lr;i++)
            printf("%c",r[i]);
    }
    return 0;
}