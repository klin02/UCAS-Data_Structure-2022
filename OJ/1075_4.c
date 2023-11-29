#include <stdio.h>
//AC
char stack[10000];
int top=0;
int state=0;
// state: 0 code 1 string 2 annotation
char anno_tmp='0';
int main(){
    char c;
    while((c=getchar())!=EOF){
        switch(state){
            case 0:
                stack[top++]=c;
                if(stack[top-1]=='\"' && ((stack[top-2]!='\\' && top>1) || top==1))
                    state=1;
                else if(top>1 && stack[top-1]=='*' && stack[top-2]=='/'){
                    state=2;
                    anno_tmp='0';//reset
                    stack[--top]='\0';
                    stack[--top]='\0';
                }
                else 
                    state=0;
                break;
            case 1:
                stack[top++]=c;
                if(top>1 && stack[top-1]=='\"' && stack[top-2]!='\\')
                    state=0;
                else    
                    state=1;
                break;
            case 2:
                if(c=='/' && anno_tmp=='*')
                    state=0;
                else
                    state=2;
                anno_tmp=c;
                break;
            default:
                state=0;
                break;
        }    
    }
    for(int i=0;i<top;i++){
        printf("%c",stack[i]);
    }
}  