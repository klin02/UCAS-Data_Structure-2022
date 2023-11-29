#include <stdio.h>
//AC
int set[100010]={0};    //set[i] means i belong to set which root is set[i],init state are themselves
int dif[100010]={0};    //dif[i] means i and dif[i] belong to different set,init state are themselves
void InitSet(int n);  //init n set which all have only one item
int Find(int x);        //find which set x belongs to
void Merge(int r1,int r2); //when r1 and r2 disjoint, merge r2 to r1

int result[100010]={0};
int resulttop=0;
int main(){
        int T;
        int n,m;
        char c;
        char type;
        int x,y;
        scanf("%d",&T);
        while(T--){//execute time: T
                scanf("%d %d%c",&n,&m,&c);
                InitSet(n);
                while(m--){
                        scanf("%c %d %d%c",&type,&x,&y,&c);
                        int rx,ry;      //root of x,y
                        rx = Find(x);
                        ry = Find(y);
                        if(type=='D')
                        {
                                if(dif[x]==x) //init state
                                        dif[x]=y;
                                else
                                        Merge(Find(dif[x]),ry);

                                if(dif[y]==y)
                                        dif[y]=x;
                                else    
                                        Merge(Find(dif[y]),rx);

                        }
                        if(type=='A')
                        {
                                if(rx==ry)
                                        result[resulttop++]=1;  
                                else if(Find(dif[x])==ry)
                                        result[resulttop++]=2;  
                                else 
                                        result[resulttop++]=0;  
                        }
                }
        }
        for(int i=0;i<resulttop;i++){
                if(result[i]==1)
                        printf("是同一个团伙所为\n");
                else if(result[i]==2)
                        printf("不是同一个团伙所为\n");
                else
                        printf("不确定\n");
        }
        return 0;
}

void InitSet(int n){
        for(int i=0;i<n;i++){
                set[i]=i;
                dif[i]=i;
        }
        return ;
}

int Find(int x){
        if(x!=set[x])
                return Find(set[x]);
        else
                return x;
}

void Merge(int r1,int r2){
        if(r1!=r2)
                set[r2]=r1;
        return ;
}