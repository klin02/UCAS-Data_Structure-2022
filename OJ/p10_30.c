#include <stdio.h>
#define swap(a,b) {if(a!=b) a=b-a,b=b-a,a=a+b;}
//AC
//快排非递归
//简便起见，省略随机取标杆过程，选择排序使用冒泡排序
int buf[1000]={0};
int top=0;
int main(){
    int s[1000]={0};
    int len=0;
    char c;
    while(1){
        scanf("%d%c",&s[len++],&c);
        if(c!=' ')
            break;
    }

    int head,tail;
    buf[top++]=0;
    buf[top++]=len-1;
    while(top>0){
        tail=buf[--top];
        head=buf[--top];
        if(head>=tail)
            continue;
        if(tail-head<3){
            for(int i=head+1;i<=tail;i++)
                for(int j=i;j>head;j--){
                    if(s[j]<s[j-1])
                        swap(s[j],s[j-1])  //注意拓展，此处不可加;
                    else break;
                }
        }
        else{
            int last=head;// last指向小于标杆的最后一个元素
            for(int i=head+1;i<=tail;i++)
                if(s[i]<s[head]){
                    last++;
                    swap(s[last],s[i]) //注意拓展 用++的话会重复操作
                }
            swap(s[last],s[head])
            buf[top++]=head;
            buf[top++]=last-1;
            buf[top++]=last+1;
            buf[top++]=tail;
        }
    }

    for(int i=0;i<len;i++){
        printf("%d ",s[i]);
    }
    return 0;
}