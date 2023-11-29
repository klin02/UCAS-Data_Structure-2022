#include <stdio.h>
#include <string.h>
//AC
int cnt[1000]={0};
void CountSort(int s[],int len);
int main(){
    int s[1000]={0};
    int len=0;
    char c;
    while(1){
        scanf("%d%c",&s[len++],&c);
        if(c!=' ')
            break;
    }
    CountSort(s,len);
    for(int i=0;i<len;i++)
        printf("%d ",cnt[i]);
    // for(int i=0;i<len;i++)
    //     printf("%d ",s[i]);
    return 0;
}
void CountSort(int s[],int len){
    int tmp[1000];
    memcpy(tmp,s,len*sizeof(int));
    //只考虑右边 节省一半时间
    for(int i=0;i<len;i++)
        for(int j=i+1;j<len;j++)
            if(s[i]>s[j])
                cnt[i]++;
            else    
                cnt[j]++;
    
    for(int i=0;i<len;i++)
        s[cnt[i]]=tmp[i];
}