#include <stdio.h>
#define swap(a,b) {if(a!=b) a=b-a,b=b-a,a=a+b;}
//AC
//本质上是三分问题，用qsort的标杆思想即可
int main(){
    int s[1000]={0};
    int len=0;
    char c;
    while(1){
        scanf("%d%c",&s[len++],&c);
        if(c!=' ')
            break;
    }
    int last=-1,more=len;
    int ptr=0;
    while(ptr<more){
        //注意终止条件，否则会出现3位置在more右边情形
        if(s[ptr]==1){
            last++;
            swap(s[last],s[ptr]);
            ptr++;
        }
        else if(s[ptr]==3){
            //考虑交换1的情形
            more--;
            swap(s[more],s[ptr]);
        }
        else 
            ptr++;
    }
    for(int i=0;i<len;i++)
        printf("%d ",s[i]);

    return 0;
}