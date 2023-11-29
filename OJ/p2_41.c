#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
//AC
struct data
{
    int base;
    int pow;
} da[100]; //用于读取数据
struct node
{
    int base;
    int pow;
    struct node *prior;
    struct node *next;
}; //用于合并、求导、以及反向输出
struct node *newnode();
void printlist(struct node *plist);
void daup(int bas, int po); //增加da数组
int dalen = 0;
int cmp(const void *, const void *);

int main()
{
    char c;
    int bas = 0, po = 0;
    int state = 0; //0读取系数，1读取指数
    char s[10];
    int j = 0; //s[j]
    //atoi不可包含空格,但读取时可以跳过空格。

    while ((c = getchar()) != '\n')
    {
        if (c == '+' || c == '-')
        {
            if (state == 0)
            {
                if (j == 0)
                    bas = 0;
                else if (j == 1 && s[0] == '+')
                    bas = 1;
                else if (j == 1 && s[0] == '-')
                    bas = -1;
                else
                    bas = atoi(s);
                memset(s, 0, sizeof(s));
                j = 0;
                po = 0;
            }
            else if (state == 1)
            {
                if (j != 0)
                    po = atoi(s);
                memset(s, 0, sizeof(s));
                j = 0;
            }
            daup(bas, po);
            state = 0;
            bas = po = 0;
            s[j++] = c;
        }
        if (isdigit(c))
            s[j++] = c;
        if (c == 'x')
        {
            //考虑省略1的情形
            if (j == 0 || (j == 1 && s[0] == '+'))
                bas = 1;
            else if (j == 1 && s[0] == '-')
                bas = -1;
            else
                bas = atoi(s);
            memset(s, 0, sizeof(s));
            j = 0;
            if ((c = getchar()) == '^') //由于输入每项后均有空格，不需考虑将+-号读取情形
                state = 1;
            else
            {
                po = 1;
                state = 1;
                if (c == '\n')
                    break;
            }
        }
    }
    if (state == 0)
    {
        if (j == 0)
            bas = 0;
        else if (j == 1 && s[0] == '+')
            bas = 1;
        else if (j == 1 && s[0] == '-')
            bas = -1;
        else
            bas = atoi(s);
        memset(s, 0, sizeof(s));
        j = 0;
        po = 0;
    }
    else if (state == 1)
    {
        if (j != 0)
            po = atoi(s);
        memset(s, 0, sizeof(s));
        j = 0;
    }
    daup(bas, po);

    qsort(da, dalen, sizeof(struct data), cmp);

    // for (int i = 0; i < dalen; i++)
    //     printf("%d,%d ", da[i].base, da[i].pow);

    //事实上此处直接使用排好序的数组稍作处理输出即可通过OJ，但以下特地使用循环链表进行
    struct node *plist, *plast, *p;
    plist = newnode();
    plist->base = da[0].base;
    plist->pow = da[0].pow;
    plist->prior = plist->next = NULL;
    plast = plist;
    for (int i = 1; i < dalen; i++)
    {
        p = newnode();
        p->base = da[i].base;
        p->pow = da[i].pow;
        p->prior = plast;
        p->next = NULL;
        plast->next = p;
        plast = plast->next;
    }

    //printlist(plist);
    //合并
    struct node *pre = plist;
    while (pre != NULL && pre->next != NULL)
    {
        if (pre->pow == pre->next->pow)
        {
            struct node *p = pre->next;
            pre->base +=p->base;
            if(p==plast)
            {
                pre->next=NULL;
            }
            else{
                pre->next=p->next;
                p->next->prior=pre;
            }
        }
        pre=pre->next;
    }
    //printlist(plist);
    //暂缓去零 直接求导后再去零，在输出处稍作调整即可。
    pre=plist;
    while(pre!=NULL){
        pre->base=pre->base*pre->pow;
        pre->pow--;
        pre=pre->next;
    }
    pre=plist;
    while(pre!=NULL){
        if(pre->base==0){
            if(pre==plist){
                if(pre->next==NULL)
                    plist=NULL;
                else{
                    pre->next->prior=NULL;
                    plist=pre->next;
                }
            }
            else{
                if(pre->next==NULL)
                pre->prior->next=NULL;
                else {
                    pre->prior->next=pre->next;
                    pre->next->prior=pre->prior;
                }
            }
        }
        pre=pre->next;
    }
    printlist(plist);
}
void daup(int bas, int po)
{
    da[dalen].base = bas;
    da[dalen].pow = po;
    dalen++;
}

int cmp(const void *a, const void *b)
{
    return (*(struct data *)b).pow - (*(struct data *)a).pow;
}
struct node *newnode()
{
    return (struct node *)malloc(sizeof(struct node));
}
void printlist(struct node *plist)
{
    struct node *pnode;
    pnode = plist;
    if(pnode==NULL){
        printf("0");
        return;
    }
    while (pnode != NULL)
    {
        if (pnode->base == 0)
            ;//printf("0");
        else if (pnode->base > 0)
        {
            if (pnode != plist)
                printf("+ ");
            printf("%d", pnode->base);
        }
        else if (pnode->base < 0)
        {
            printf("- %d", -pnode->base);
        }
        if (pnode->pow == 0)
            printf(" ");
        else if (pnode->pow == 1)
            printf("x ");
        else
            printf("x^%d ", pnode->pow);
        pnode = pnode->next;
    }
    printf("\n");
}