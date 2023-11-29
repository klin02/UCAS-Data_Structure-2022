#include <stdio.h>
//AC
int main(){
    char a[100],b[100];
    char c;
    int lena=0,lenb=0;
    while((c=getchar())!='\n'){
        if(c!=','){
            a[lena]=c;
            lena++;
        }
    }
    while((c=getchar())!='\n'){
        if(c!=','){
            b[lenb]=c;
            lenb++;
        }
    }
    for(int i=0;i<lena && i<lenb;i++){
        if(a[i]<b[i]){
            printf("1");
            return 0;
        }
        else if(a[i]>b[i]){
            printf("2");
            return 0;
        }
    }
    int tmp=lena-lenb;
    if(tmp==0)
        printf("0");
    else if(tmp<0)
        printf("1");
    else 
        printf("2");
    return 0;

}