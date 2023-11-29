#include <stdio.h>
#include <string.h>
//AC
char OP[100];
char NO[100][100];//将类似cd-当做整体处理
int OPtop=0;
int NOtop=0;
int cmpOP(char a,char b);
int isOP(char a);
char tmp[2];
int main(){
    char c;
    OP[OPtop++]='#';
    c=getchar();
    char optr;
    char op1[100],op2[100];
    while(c!='\n' || OP[OPtop-1]!='#'||OPtop==0){
        if(isOP(c)==0){
            tmp[0]=c;
            tmp[1]='\0';
            strcpy(NO[NOtop++],tmp);
            c=getchar();
        }
        else {
            switch (cmpOP(OP[OPtop-1],c))
            {
            case -1:
                OP[OPtop++]=c;
                c=getchar();
                break;
            case 0:
                OPtop--;
                c=getchar();
                break;
            default:
                 optr=OP[--OPtop];
                 memset(op1,0,sizeof(op1));
                 memset(op2,0,sizeof(op2));
                 strcpy(op2,NO[--NOtop]);
                 strcpy(op1,NO[--NOtop]);
                 strcat(op1,op2);
                 tmp[0]=optr;
                 tmp[1]='\0';
                 strcat(op1,tmp);
                 strcpy(NO[NOtop++],op1);
                break;
            }
        }
    }
    printf("%s",NO[NOtop-1]);
    return 0;
}

//refer to the table in page 53
int cmpOP(char a,char b){
    if(a=='+'||a=='-'){
        switch (b)
        {
        case '+':case'-':case')':case'#':case'\n':
            return 1;
            break;
        default:
            return -1;
            break;
        }
    }
    else if(a=='*'||a=='/'){
        switch (b)
        {
        case '+':case'-':case')':case'#':case'*':case'/':case'\n':
            return 1;
            break;
        default:
            return -1;
            break;
        }
    }
    else if(a=='('){
        if(b==')')
        return 0;
        else 
        return -1;
    }
    else if(a==')')
        return 1;
    else{
        if(b=='#'||b=='\n')
            return 0;
        else 
            return -1;
    }
}

//注意换行符与尾部#等效
int isOP(char a){
    switch (a)
    {
    case '+':case'-':case'*':case'/':case'(':case')':case'#':case'\n':
        return 1;
        break;
    default:
        return 0;
        break;
    }
}
