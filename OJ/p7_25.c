#include <stdio.h>
#include <stdlib.h>
//AC
int s[1000],fst[1000],lst[1000];
int top=0;
int findpath(int u,int v);
int main(){
    int n;
    char c;
    scanf("%d%c",&n,&c);
    while(1){
        scanf("%d%c",&s[top++],&c);
        if(c!=' ')
        break;
    }
    for(int i=0;i<=n;i++)
        scanf("%d",&fst[i]);
    for(int i=0;i<=n;i++)
        scanf("%d",&lst[i]);

    int res=0;
    for(int i=0;i<=n;i++)
        if(findpath(i,i)==1)
        {
            res=1;
            break;
        }

    if(res==1)
        printf("yes");
    else    
        printf("no");
    
    return 0;
}
int findpath(int u,int v){
    for(int i=fst[u];i<lst[u];i++)
        if(s[i]==v)
            return 1;
        else if(findpath(s[i],v)==1)
            return 1;
    
    return 0;
}