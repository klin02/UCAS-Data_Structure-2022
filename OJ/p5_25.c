#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define swap(a,b) {if(a!=b) a=b-a,b=b-a,a=a+b;}
//AC
int a[2][100][100]={0};
int data[2][100][3]={0};
int r[100][100]={0};
int main()
{
    int m, n;
    char c;
    scanf("%d %d%c", &m, &n, &c); //吸收换行符
    //注意没有非零元素为空行
    //B矩阵指A矩阵非零元用1代替
    //读取B之后用三元组进行存储
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
    //如果想简单起见，可以先根据两个表得到结果矩阵，再搜索得到对应的V,B矩阵，但时间复杂度稍高
    //两个data表合并,然后再排序
    //注意到两个data表均已经有序 可以考虑使用两个指针按序扫描

    int v[100][3]={0};
    int lv=0;
    int p1=0,p2=0;
    int f1,f2;//用于比较先后
    int num;
    //两个均在范围内操作
    while(p1<len[0] && p2<len[1]){
        f1=data[0][p1][0]*n+data[0][p1][1];
        f2=data[1][p2][0]*n+data[1][p2][1];
        if(f1<f2){
            for(int t=0;t<3;t++)
                v[lv][t]=data[0][p1][t];
            lv++;
            p1++;
        }
        else if(f1>f2){
            for(int t=0;t<3;t++)
                v[lv][t]=data[1][p2][t];
            lv++;
            p2++;
        }
        else{
            num=data[0][p1][2]+data[1][p2][2];
            if(num!=0){
                for(int t=0;t<2;t++)
                    v[lv][t]=data[0][p1][t];
                v[lv][2]=num;
                lv++;
            }
            p1++,p2++;
        }
    }
    //接上其余部分
    if(p1<len[0]){
        for(int i=p1;i<len[0];i++)
            {for(int t=0;t<3;t++)
                v[lv][t]=data[0][p1][t];
            lv++;}
    }
    if(p2<len[1]){
        for(int i=p2;i<len[1];i++)
            {for(int t=0;t<3;t++)
                v[lv][t]=data[1][i][t];
            lv++;}
    }

    if(lv!=0){
         printf("%d",v[0][2]);
         r[v[0][0]][v[0][1]]=1;
        for(int i=1;i<lv;i++){
            printf(" %d",v[i][2]);
            r[v[i][0]][v[i][1]]=1;
        }
    }
    //printf("\n");
        
    for (int i=0;i<m;i++){
        printf("\n");
         printf("%d",r[i][0]);
        for (int j=1;j<n;j++)
            printf(" %d",r[i][j]);
    }
        
    return 0;
}