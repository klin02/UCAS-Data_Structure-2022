#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//AC
//大无语。。。好几次WA的原因是多写了free(q),
//通过十字链表存储之后还要以V，B形式输出比较冗余
typedef struct olnode{
    int x,y,data;
    struct olnode *right,*down;
}OLnode;
typedef OLnode * OLink;
typedef struct {
    OLink *rhead,*chead;
    int mu,nu,tu;
}Crosslist;
//mu,nu,tu 行数，列数，非零元数
Crosslist * creMatr(int mu,int nu);
void Insert(Crosslist *M,int px,int py,int d);
void Del(Crosslist *M,int px,int py);
void AddMatr(Crosslist *M,Crosslist *T);
void printMatr(Crosslist *M);
int data[2][100][3]={0};
int main(){
    int m,n;
    char c;
    scanf("%d %d%c",&m,&n,&c);
    Crosslist *A,*B;
    A=creMatr(m,n);
    B=creMatr(m,n);
    
    //仍先用三元组记录，再将其插入链表
    int len[4] = {0};
    //len0,1 表V数组 2,3表前面坐标 0=2,1=3
    char s[10];
    int ptr = 0;
    int tmp;
    int flag = 0; //判断有无非零元
    for (int k = 0; k < 2; k++)
    {
        //V array 包括考虑没有非零元
        flag = 0;
        memset(s, 0, sizeof(s));
        while ((c = getchar()) != '\n' && c!=EOF)
        {
            flag = 1;
            if (c != ' ')
                s[ptr++] = c;
            else
            {
                data[k][len[k]++][2] = atoi(s);
                memset(s, 0, sizeof(s));
                ptr = 0;
            }
        }
        if (flag == 1)
            data[k][len[k]++][2] = atoi(s);
        memset(s, 0, sizeof(s));
        ptr = 0;

        //B matrix
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                scanf("%d%c", &tmp, &c); //用于吸收第一个B矩阵输入完后的换行符
                if (tmp == 1)
                {
                    data[k][len[k + 2]][0] = i;
                    data[k][len[k + 2]][1] = j;
                    len[k + 2]++;
                }
            }
    }

    for(int i=0;i<len[0];i++)
        Insert(A,data[0][i][0],data[0][i][1],data[0][i][2]);
    for(int i=0;i<len[1];i++)
        Insert(B,data[1][i][0],data[1][i][1],data[1][i][2]);

    AddMatr(A,B);
    printMatr(A);
    return 0;
}
Crosslist * creMatr(int mu,int nu){
    Crosslist *M = (Crosslist *)malloc(sizeof(Crosslist));
    M->rhead=(OLink *)malloc((mu+1)*sizeof(OLink));
    M->chead=(OLink *)malloc((nu+1)*sizeof(OLink));
    memset(M->rhead,0,(mu+1)*sizeof(OLink));
    memset(M->chead,0,(nu+1)*sizeof(OLink));
    //此时M->rhead[i]为空指针
    M->mu=mu;
    M->nu=nu;
    M->tu=0;
    return M;
}
void Insert(Crosslist *M,int px,int py,int d){
    if(d==0)
        return;
    OLnode *p,*q;
    p=(OLnode *)malloc(sizeof(OLnode));
    p->down=p->right=NULL;
    p->x=px,p->y=py,p->data=d;
    //行插入
    if( M->rhead[px]==NULL || M->rhead[px]->y > py){
        p->right=M->rhead[px];
        M->rhead[px]=p;
    }
    else{
        q=M->rhead[px];
        while(q->right!=NULL && q->right->y<py)
            q=q->right;
        p->right=q->right;
        q->right=p;
    }
    //列插入
    if( M->chead[py]==NULL || M->chead[py]->x > px){
        p->down=M->chead[py];
        M->chead[py]=p;
    }
    else{
        q=M->chead[py];
        while(q->down!=NULL && q->down->x < px)
            q=q->down;
        p->down=q->down;
        q->down=p;
    }
    M->tu++;
    return ;
}
void Del(Crosslist *M,int px,int py){
    OLnode *p,*q;
    if(M->rhead[px]->y==py){
        q=M->rhead[px];
        M->rhead[px]=q->right;
    }
    else{
        for(p=M->rhead[px];p&&p->right&&p->right->y<py;p=p->right)
        ;
        q=p->right;
        p->right=q->right;
    }
    if(M->chead[py]->x==px){
        q=M->chead[py];
        M->chead[py]=q->down;
    }
    else{
        for(p=M->chead[py];p&&p->down&&p->down->x<px;p=p->down)
        ;
        q=p->down;
        p->down=q->down;
    }
    //free(q);
    return;
}
void AddMatr(Crosslist *M,Crosslist *T){
    OLnode *p,*q;
    for(int i=0;i<T->mu;i++)
    {
        if(T->rhead[i]==NULL)
            continue;
        q=M->rhead[i];
        //设置在while循环外，同时将for循环条件改为<可以避免每次扫描全部
        for(p=T->rhead[i];p;p=p->right){
            for(;q&&q->right&&q->y<p->y;q=q->right)
            ;
            if(q&&q->y==p->y){
                q->data += p->data;
                if(q->data==0)
                    Del(M,i,q->y);
            }
            else
                Insert(M,i,p->y,p->data);
        }
    }
    return ;
}
void printMatr(Crosslist *M){
    int a[100][100]={0};
    OLnode *p;
    int flag=0;
    for(int i=0;i<M->mu;i++)
        for(p=M->rhead[i];p;p=p->right){
            if(flag==0){
                flag=1;
                printf("%d",p->data);
            }
            else
                printf(" %d",p->data);
            
            a[i][p->y]=1;
        }
    for(int i=0;i<M->mu;i++){
        printf("\n%d",a[i][0]);
        for(int j=1;j<M->nu;j++)
            printf(" %d",a[i][j]);
    }
    return ;
}