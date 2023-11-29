#include <stdio.h>
//AC
//insertvex deletevex v 新增/删除节点v(及对应弧)
//insertarc deletearc u v 新增/删除弧u-v
int gra[100][100]={0};
void IV();
void IA();
void DV();
void DA();
int n;//line
int main(){
    char c;
    int u,v;
    scanf("%d%c",&n,&c);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            scanf("%d%c",&gra[i][j],&c);
    
    while(1){
        c=getchar();
        if(c=='I'){
            c=getchar();
            if(c=='A'){
                getchar();
                scanf("%d %d",&u,&v);
                IA(u,v);
            }
            else if(c=='V'){
                getchar();
                scanf("%d",&v);
                IV(v);
            }
        }
        else if(c=='D'){
            c=getchar();
            if(c=='A'){
                getchar();
                scanf("%d %d",&u,&v);
                DA(u,v);
            }
            else if(c=='V'){
                getchar();
                scanf("%d",&v);
                DV(v);
            }
        }
        else break;
        if((c=getchar())==EOF)
            break;
    }

    for(int i=0;i<n;i++){
        printf("%d",gra[i][0]);
        for(int j=1;j<n;j++)
            printf(" %d",gra[i][j]);
        printf("\n");
    }
    
    return 0;
}
void IV(int v){
    if(v==n){
        for(int i=0;i<=n;i++)
            gra[n][i]=gra[i][n]=0;
            n++;
    }
    else if(v<n){
        for(int i=n-1;i>=v;i--)
            for(int j=0;j<n;j++)
            gra[i+1][j]=gra[i][j];
        
        for(int j=n-1;j>=v;j--)
            for(int i=0;i<=n;i++)
            gra[i][j+1]=gra[i][j];
        
        for(int i=0;i<=n;i++)
            gra[v][i]=gra[i][v]=0;
            n++;
    }
}
void DV(int v){
    for(int i=v+1;i<n;i++)
        for(int j=0;j<n;j++)
        gra[i-1][j]=gra[i][j];
    
    for(int j=v+1;j<n;j++)
        for(int i=0;i<n-1;i++)
        gra[i][j-1]=gra[i][j];
    
    for(int i=0;i<n;i++)
        gra[i][n-1]=gra[n-1][i]=0;
    
    n--;
}
void IA(int u,int v){
    gra[u][v]=gra[v][u]=1;
}
void DA(int u,int v){
    gra[u][v]=gra[v][u]=0;
}