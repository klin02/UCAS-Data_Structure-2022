//整理代码结构，根据manual顺序进行声明
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define Height(T) ((T) ? (T)->height : 0)

#define LH 1
#define EH 0
#define RH -1

#define MAXTRENUM 10 //当前允许树的最多数量

#define MAXWD 90
#define MAXHT 10

typedef struct bsnode
{
        int data;
        int height; //以该点为根的树高，可由子树树高确定平衡因子
        struct bsnode *parent, *lchild, *rchild;
} BsNode, *BsTree;

int old_cur_x, old_cur_y; //原有光标位置，用于打印接口

int process = 0;          //是否进行过程展示，默认关闭
int mask = 0;             //考虑到合并和分支的操作，对于不同子树操作的步数可能不同。因此不展示具体的重平衡过程，设置原子操作的演示掩码
int show = 0;             //打印条件在子函数中确定，但是相关指针在父函数中才修改，通过全局变量传递

int randnum[100] = {0}; //用于生成不重复随机数
int randtop = 0;
int seq = 0;              //全局定增序号，保证每次取随机数时为不同值

int ExistList[MAXTRENUM] = {0}; //标记树存在的列表，树可以为空
BsTree TreeList[MAXTRENUM];     //树列表

BsTree hit;      //指向搜索到的节点
int ShowTreeNum; //正在展示的树编号，方便打印。涉及到根的改变时应当在演示中提前更新TreeList[]

//基本操作函数
BsTree R_Rotate(BsNode *p);
BsTree L_Rotate(BsNode *p);
BsTree LR_Rotate(BsNode *p);
BsTree RL_Rotate(BsNode *p);
BsTree LeftBalance(BsTree T);
BsTree RightBalance(BsTree T);
int GetHeight(BsTree T);
int GetBf(BsTree T);
BsTree FindPre(BsTree T);                                                //找到中序遍历下的直接前驱结点
void Traverse_R(BsTree T, int treeDepth, int depth, int right, int tap); //打印子函数
void gotoxy(int x, int y);                                               //改变光标函数
void halt();                                                             //等待函数，用于演示

//功能函数
void manual();
int CreateBST(int no);                           //创建树，返回是否成功，
int GiveupBST(int no);                           //放弃树
int PrintBST(int no);
int SearchBST(BsTree T, int e);                  //查找
BsTree InsertBST(BsTree T, int e);               //插入
BsTree DelBST(BsTree T, int e);                  //删除
int MergeBST(int no1, int no2);                  //将T2合并到T1
int BranchBST(int no1, int no2, int no3, int e); //根据e将T1元素分别插入T2和T3，最后删除T1，T2和T3若不存在将提前创建

int main()
{
        memset(ExistList, 0, sizeof(ExistList));
        memset(TreeList, 0, sizeof(TreeList));
        printf("Welcome to Balanced Binary Search Tree!\nAuthor: KL\n");
        manual();
        char func;
        char c;
        int tmpdat;
        int e;
        int arg[100] = {0};
        int argtop = 0;
        while ((func = getchar()) != EOF && func != 'q')
        {
                argtop = 0;
                if (func == 'h')
                { //无需参数的单独考虑，否则会在scanf时停顿
                        manual();
                        printf("\n");
                        continue;
                }
                else if (func == 'l')
                {
                        printf("Treelist:");
                        for (int i = 0; i < MAXTRENUM; i++)
                        {
                                if (ExistList[i] == 1)
                                        printf(" %d", i);
                        }
                        printf("\n\n");
                        continue;
                }
                else if (func == 'y')
                {
                        process = 1;
                        printf("Processing mode is on!\n\n");
                        continue;
                }
                else if (func == 'n')
                {
                        process = 0;
                        printf("Processing mode is off\n\n");
                        continue;
                }
                while (scanf("%d%c", &tmpdat, &c) == 2)
                {
                        arg[argtop++] = tmpdat;
                        if (c == '\n')
                                break;
                }

                switch (func)
                {
                case 'c':
                        for (int i = 0; i < argtop; i++)
                                CreateBST(arg[i]);
                        break;
                case 'g':
                        for (int i = 0; i < argtop; i++)
                                GiveupBST(arg[i]);
                        break;
                case 'p':
                        for (int i = 0; i < argtop; i++)
                                PrintBST(arg[i]);
                        break;

                case 's':
                        if (ExistList[arg[0]] == 0)
                                printf("Fail! Tree %d does not exist\n", arg[0]);
                        else
                        {
                                for (int i = 1; i < argtop; i++)
                                        if (SearchBST(TreeList[arg[0]], arg[i]) == 1)
                                                printf("%d is in Tree %d\n", arg[i], arg[0]);
                                        else
                                                printf("%d is not in Tree %d\n", arg[i], arg[0]);
                        }
                        break;
                case 'i':
                        if (ExistList[arg[0]] == 0)
                                printf("Fail! Tree %d does not exist\n", arg[0]);
                        else
                        {
                                BsTree T = TreeList[arg[0]];
                                if (process)
                                {
                                        printf("Procsssing: Insertion of Tree %d------------------------------------------------\n", arg[0]);
                                        PrintBST(arg[0]);
                                        show = 0;
                                }
                                for (int i = 1; i < argtop; i++)
                                {
                                        e = arg[i];
                                        if (SearchBST(T, e) == 1)
                                                printf("Fail! %d is already in Tree %d\n", e, arg[0]);
                                        else
                                        {
                                                if (process)
                                                {
                                                        printf("Processing: Insert %d to Tree %d--------------\n", e, arg[0]);
                                                        ShowTreeNum = arg[0];
                                                        show = 0;
                                                }
                                                T = InsertBST(T, e);
                                        }
                                }
                                printf("Insertion of Tree %d is over!\n", arg[0]);
                                TreeList[arg[0]] = T;
                        }
                        break;
                case 'r':
                        if (ExistList[arg[0]] == 0)
                                printf("Fail! Tree %d does not exist\n", arg[0]);
                        else if (TreeList[arg[0]] != NULL)
                                printf("Fail! Tree %d exists and is not empty\n", arg[0]);
                        else if (argtop < 3)
                                printf("Fail! This func need 3 arg\n");
                        else
                        {
                                BsTree T = TreeList[arg[0]];
                                if (process)
                                {
                                        printf("Procsssing: Random Generation of Tree %d-----------------------------------------\n", arg[0]);
                                        PrintBST(arg[0]);
                                }
                                srand(time(0) + (seq++));
                                randtop = 0;
                                int used;
                                for (int i = 0; i < arg[1];)
                                {
                                        used = 0;
                                        e = rand() % arg[2];
                                        for (int j = 0; j < randtop; j++)
                                        {
                                                if (e == randnum[j])
                                                {
                                                        used = 1;
                                                        break;
                                                }
                                        }
                                        if (used == 0)
                                        {
                                                randnum[randtop++] = e;
                                                i++;
                                        }
                                }

                                for (int i = 0; i < arg[1]; i++)
                                {
                                        e = randnum[i];
                                        if (process)
                                        {
                                                printf("Processing: Randomly Insert %d to Tree %d-------------------------\n", e, arg[0]);
                                                ShowTreeNum = arg[0];
                                        }
                                        T = InsertBST(T, e);
                                }
                                printf("Random Generation of Tree %d is over!\n", arg[0]);
                                TreeList[arg[0]] = T;
                        }
                        break;
                case 'd':
                        if (ExistList[arg[0]] == 0)
                                printf("Fail! Tree %d does not exist\n", arg[0]);
                        else
                        {
                                if (process)
                                {
                                        printf("Processing: Deletion of Tree %d----------------------------------------------\n", arg[0]);
                                        PrintBST(arg[0]);
                                }
                                BsTree T = TreeList[arg[0]];
                                for (int i = 1; i < argtop; i++)
                                {
                                        e = arg[i];
                                        if (SearchBST(T, e) == 0)
                                                printf("Fail! %d is not in Tree %d\n", e, arg[0]);
                                        else
                                        {
                                                if (process)
                                                {
                                                        printf("Processing: Delete %d from Tree %d--------------\n", e, arg[0]);
                                                        ShowTreeNum = arg[0];
                                                }
                                                T = DelBST(T, e);
                                        }
                                }
                                printf("Deletion of Tree %d is over!\n", arg[0]);
                                TreeList[arg[0]] = T;
                        }
                        break;
                case 'm':
                        if (process)
                                printf("Processing: Merge from Tree %d to Tree %d--------------------------------------\n", arg[1], arg[0]);
                        MergeBST(arg[0], arg[1]);
                        break;
                case 'b':
                        if (process)
                                printf("Processing: Branch from Tree %d to Tree %d and Tree %d-------------------------\n", arg[0], arg[1], arg[2]);
                        BranchBST(arg[0], arg[1], arg[2], arg[3]);
                        break;

                default:
                        break; //清空无效缓冲区
                }
                printf("\n");
        }
        return 0;
}

BsTree R_Rotate(BsNode *p)
{ 
        BsTree lc;
        lc = p->lchild;
        lc->parent = p->parent;
        p->parent = lc;
        if (lc->rchild)
                lc->rchild->parent = p;
        p->lchild = lc->rchild;
        lc->rchild = p;
        p = lc;
        return p;
}

BsTree L_Rotate(BsNode *p)
{
        BsTree rc;
        rc = p->rchild;
        rc->parent = p->parent;
        p->parent = rc;
        if (rc->lchild)
                rc->lchild->parent = p;
        p->rchild = rc->lchild;
        rc->lchild = p;
        p = rc;
        return p;
}

BsTree LR_Rotate(BsNode *p)
{
        p->lchild = L_Rotate(p->lchild);
        p = R_Rotate(p);
        return p;
}

BsTree RL_Rotate(BsNode *p)
{
        p->rchild = R_Rotate(p->rchild);
        p = L_Rotate(p);
        return p;
}

BsTree LeftBalance(BsTree T)
{
        switch (GetBf(T->lchild))
        {
        case LH:
        case EH:                 //插入没有0情形，删除有
                T = R_Rotate(T); //右单旋转，左斜线变成平衡
                //注意T改变
                T->rchild->height = GetHeight(T->rchild);
                T->height = GetHeight(T);
                break;
        case RH:
                T = LR_Rotate(T);
                T->lchild->height = GetHeight(T->lchild);
                T->rchild->height = GetHeight(T->rchild);
                T->height = GetHeight(T);
                break;
        }
        return T;
}

BsTree RightBalance(BsTree T)
{
        switch (GetBf(T->rchild))
        {
        case RH:
        case EH: //插入没有0情形，删除有
                T = L_Rotate(T);
                T->lchild->height = GetHeight(T->lchild);
                T->height = GetHeight(T);
                break;
        case LH:
                T = RL_Rotate(T);
                T->lchild->height = GetHeight(T->lchild);
                T->rchild->height = GetHeight(T->rchild);
                T->height = GetHeight(T);
                break;
        }
        return T;
}

int GetHeight(BsTree T)
{
        return 1 + MAX(Height(T->lchild), Height(T->rchild));
}

int GetBf(BsTree T)
{
        return Height(T->lchild) - Height(T->rchild);
}

BsTree FindPre(BsTree T)
{
        if (!T)
                return NULL;
        BsTree pre = T->lchild;
        if (pre)
        {
                while (pre->rchild)
                        pre = pre->rchild;
        }
        else if (T->parent && T->parent->rchild == T)
                pre = T->parent;
        else
                pre = NULL;
        return pre;
}

void Traverse_R(BsTree T, int treeDepth, int depth, int right, int tap)
{
        // treeDepth为整棵树的高度，调用时不需改变，考虑作为参数传入即可
        if (T == NULL)
                return;

        // 记录当前光标位置，用于在递归中记录当前递归时树的位置
        int x, y;

        // 计算父树的偏移量
        int tap1 = tap * pow(2, treeDepth - depth);
        // 计算子树的偏移量
        int tap2 = right * (pow(2, treeDepth - depth));
        // 计算半偏移量
        int tap3 = pow(2, treeDepth - depth - 1);

        // 获取根的坐标
        // x 计算方法为：父偏移量 + 子偏移量 + 半偏移量 - 1
        // y 计算方法为：目前打印的层数 * 2
        x = tap1 + tap2 + tap3 - 1;
        y = depth * 2;

        // 打印根的位置
        gotoxy(x * 2 + 4, y); //美观需求，全部将其向右移动4格
        printf("%d", T->data);

        // 在打印子树时，当前层数+1
        depth++;
        // 计算子树的父偏移量
        tap = tap * 2 + (right == 1 ? 2 : 0);
        if (T->lchild == NULL && T->rchild == NULL)
                return;
        else if (T->rchild == NULL)
        {
                // 打印左子树的位置
                gotoxy(x * 2 - tap3 + 4, y + 1);
                printf("┏");
                for (int i = 0; i < tap3 - 1; i++)
                        printf("━");
                printf("┛");
                Traverse_R(T->lchild, treeDepth, depth, 0, tap);
        }
        else if (T->lchild == NULL)
        {
                // 打印右子树的位置
                gotoxy(x * 2 + 4, y + 1);
                printf("┗");
                for (int i = 0; i < tap3 - 1; i++)
                        printf("━");
                printf("┓");
                Traverse_R(T->rchild, treeDepth, depth, 1, tap);
        }
        else
        {
                // 打印左右子树的位置
                gotoxy(x * 2 - tap3 + 4, y + 1);
                printf("┏");
                for (int i = 0; i < tap3 - 1; i++)
                        printf("━");
                printf("┻");
                for (int i = 0; i < tap3 - 1; i++)
                        printf("━");
                printf("┓");
                Traverse_R(T->lchild, treeDepth, depth, 0, tap);
                Traverse_R(T->rchild, treeDepth, depth, 1, tap);
        }
        return;
}

void gotoxy(int x, int y)
{
        // 更新光标位置
        COORD pos;
        HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
        pos.X = x + old_cur_x;
        pos.Y = y + old_cur_y;
        SetConsoleCursorPosition(hOutput, pos);
}

void halt()
{
        Sleep(1000); // windows
}

void manual()
{
        printf("---------------------Help manual----------------------\n");
        printf("Function Press as follows:\n");

        printf("------basic operation------\n");
        printf("'h': check help manual\n");
        printf("'l': show tree list\n");
        printf("'q': quit\n");
        printf("'c': create trees in list   e.g: c 1 2 means creat Tree[1] and Tree[2]\n");
        printf("'g': give up trees in list  e.g: g 1 2 means give up Tree[1] and Tree[2]\n");
        printf("'p': print trees in list    e.g: p 1 2 means print Tree[1] and Tree[2]\n");

        printf("------modify operation------\n");
        printf("'s': search nodes to tree   e.g: s 1 2 3 means search 2 and 3 in Tree[1]\n");
        printf("'i': insert nodes to tree   e.g: i 1 2 3 means insert 2 and 3 in order to Tree[1]\n");
        printf("'r': generate random tree   e.g: r 1 3 5 means randomly generate Tree[1] with 3 nodes ranging 0~5\n");
        printf("'d': delete nodes from tree e.g: d 1 2 3 means delete 2 and 3 in order from Tree[1]\n");
        printf("'m': merge Trees together   e.g: m 1 2 means merge Tree[2] into Tree[1]\n");
        printf("'b': branch Trees by data   e.g: b 1 2 3 4 means branch Tree[1] to Tree[2] and Tree[3] by 4\n");

        printf("------processing operation------\n");
        printf("'y': turn on processing mode! Support List: 'i' 'r' 'd' 'm' 'b'\n");
        printf("'n': turn off processing mode\n\n");
}

int CreateBST(int no)
{ // no范围将统一判断
        if (ExistList[no] == 1)
        {
                printf("Fail! Tree %d has existed!\n", no);
                return 0;
        }
        else
        {
                TreeList[no] = NULL;
                ExistList[no] = 1;
                printf("Success! Tree %d is created!\n", no);
                return 1;
        }
}

int GiveupBST(int no)
{
        if (ExistList[no] == 0)
        {
                printf("Fail! Tree %d does not exist!\n", no);
                return 0;
        }
        else
        {
                TreeList[no] = NULL;
                ExistList[no] = 0;
                printf("Success! Tree %d is given up!\n", no);
                return 1;
        }
}

int PrintBST(int no)
{
        if (ExistList[no] == 0)
        {
                printf("Fail! Tree %d does not exist!\n", no);
                return 0;
        }
        else
        {
                printf("Tree %d:\n", no);
                HANDLE hStdout;
                CONSOLE_SCREEN_BUFFER_INFO pBuffer;
                hStdout = GetStdHandle(STD_OUTPUT_HANDLE); //获取句柄
                GetConsoleScreenBufferInfo(hStdout, &pBuffer);
                old_cur_x = pBuffer.dwCursorPosition.X;
                old_cur_y = pBuffer.dwCursorPosition.Y;
                if (!TreeList[no])
                        printf("    NULL\n");
                else
                {
                        Traverse_R(TreeList[no], TreeList[no]->height, 0, 0, 0); //打印接口
                        if (process)
                                gotoxy(0, 2 * TreeList[no]->height + 1); //考虑高度改变
                        else
                                gotoxy(0, 2 * TreeList[no]->height - 1); //适应接口，打印换行符以便光标更新于行首
                }
                return 1;
        }
}

int SearchBST(BsTree T, int e)
{
        if (!T)
                return 0;
        else
        {
                if (T->data == e)
                {
                        hit = T;
                        return 1;
                }
                else if (e < T->data)
                        return SearchBST(T->lchild, e);
                else
                        return SearchBST(T->rchild, e);
        }
}

BsTree InsertBST(BsTree T, int e)
{
        int root = T == TreeList[ShowTreeNum]; //展示时需要考虑根结点被重平衡改变
        //需要更新高度，方便左右平衡旋转
        if (!T)
        {
                T = (BsNode *)malloc(sizeof(BsNode));
                T->data = e;
                T->parent = T->lchild = T->rchild = NULL;
                T->height = 1;
                if (process && !mask) //除去合并和分支的演示模式
                {                     //如果插入到根结点，在内部进行打印
                        if (root)
                        {
                                TreeList[ShowTreeNum] = T;
                                halt();                //父函数，无上层
                                PrintBST(ShowTreeNum); //插入后打印一次
                        }
                        else
                                show = 1; //转移到上层函数打印
                }
        }
        else
        {
                if (T->data == e)
                        return T;
                else if (e < T->data)
                {
                        int old_bf = GetBf(T);
                        int old_lch = Height(T->lchild); //原左子树高度
                        // if(InsertBST(T->lchild,e)==0) return 0;
                        T->lchild = InsertBST(T->lchild, e);
                        T->lchild->parent = T;
                        if (process && !mask && show)
                        { //如果插入到子树，更新指针后在外部打印
                                halt();
                                PrintBST(ShowTreeNum);
                                show = 0;
                        }
                        int new_lch = Height(T->lchild);

                        if (new_lch > old_lch)
                        {
                                switch (old_bf)
                                {
                                case LH:
                                        T = LeftBalance(T);
                                        if (process && !mask)
                                        {
                                                if (root)
                                                {
                                                        TreeList[ShowTreeNum] = T; //考虑重平衡时根结点改变，无上层
                                                        halt();
                                                        PrintBST(ShowTreeNum);
                                                }
                                                else
                                                        show = 1;
                                        }
                                        break; //其中会更新高度
                                case EH:
                                        T->height++;
                                        break;
                                case RH:
                                        break;
                                }
                        }
                }
                else
                {
                        int old_bf = GetBf(T);
                        int old_rch = Height(T->rchild);
                        // if(InsertBST(T->rchild,e)) return 0;
                        T->rchild = InsertBST(T->rchild, e);
                        T->rchild->parent = T;
                        if (process && !mask && show)
                        { //如果插入到子树，更新指针后在外部打印
                                halt();
                                PrintBST(ShowTreeNum);
                                show = 0;
                        }
                        int new_rch = Height(T->rchild);

                        if (new_rch > old_rch)
                        {
                                switch (old_bf)
                                {
                                case RH:
                                        T = RightBalance(T);
                                        if (process && !mask)
                                        {
                                                if (root)
                                                {
                                                        TreeList[ShowTreeNum] = T; //考虑重平衡时根结点改变
                                                        halt();
                                                        PrintBST(ShowTreeNum);
                                                }
                                                else
                                                        show = 1;
                                        }
                                        break;
                                case EH:
                                        T->height++;
                                        break;
                                case LH:
                                        break;
                                }
                        }
                }
        }
        return T;
}

BsTree DelBST(BsTree T, int e)
{ //查找到时才启动这个函数，此时全局hit指向被删除的节点
        if (SearchBST(T, e) == 0)
        {
                printf(" %d Not Found!\n", e);
                return T;
        } //否则将把hit放置到搜索到的位置
        if (process && !mask)
        {
                PrintBST(ShowTreeNum); //第一个操作，无延迟
                show = 0;
        }

        if (!hit->lchild)
        {
                if (hit->rchild)
                        hit->rchild->parent = hit->parent;
                if (hit == T)
                {
                        if (process && !mask)
                        {
                                TreeList[ShowTreeNum] = hit->rchild;
                                halt();
                                PrintBST(ShowTreeNum);
                        }
                        return hit->rchild;
                }
                else if (hit->parent->rchild == hit)
                        hit->parent->rchild = hit->rchild;
                else if (hit->parent->lchild == hit)
                        hit->parent->lchild = hit->rchild;
                if (process && !mask)
                        show = 1;
        }
        else if (!hit->rchild)
        {
                if (hit->lchild)
                        hit->lchild->parent = hit->parent;
                if (hit == T)
                {
                        if (process && !mask)
                        {
                                TreeList[ShowTreeNum] = hit->lchild;
                                halt();
                                PrintBST(ShowTreeNum);
                        }
                        return hit->lchild;
                }
                else if (hit->parent->rchild == hit)
                        hit->parent->rchild = hit->lchild;
                else if (hit->parent->lchild == hit)
                        hit->parent->lchild = hit->lchild;
                if (process && !mask)
                        show = 1;
        }
        else
        { //有两个孩子，则替换数据，转向删除前驱结点
                BsTree hpre;
                hpre = FindPre(hit);
                hit->data = hpre->data;
                //由于hit有两个孩子，根据中序遍历过程，hpre一定有父节点，且无右孩子
                //除去是hit左节点的情形，hpre一定是右孩子
                if (hpre->lchild)
                        hpre->lchild->parent = hpre->parent;
                if (hpre == hit->lchild)
                        hit->lchild = hpre->lchild;
                else
                        hpre->parent->rchild = hpre->lchild;
                hit = hpre;
                if (process && !mask)
                        show = 1;
        }
        if (process && !mask && show)
        {
                halt();
                PrintBST(ShowTreeNum);
                show = 0;
        }
        // hit为已删除的节点，从其父节点开始遍历
        int shorter = 1; //删除时，开始应当启动向前搜索
        int root = 0;    //展示需要：如果重平衡是根结点，需要改变TreeList
        while (shorter)
        {
                if (!hit->parent)
                {
                        T = hit; //重新确定根节点
                        break;   //根结点重平衡结束后，高度改变无需再向上传递
                }

                hit = hit->parent;
                root = hit == TreeList[ShowTreeNum];
                int old_ht = hit->height;
                switch (GetBf(hit))
                {
                case LH:
                case EH:
                case RH:
                        hit->height = GetHeight(hit);
                        break; //不需旋转
                case 2 * LH:
                        hit = LeftBalance(hit);
                        if (process && !mask)
                        {
                                if (root)
                                        TreeList[ShowTreeNum] = hit;
                                halt();
                                PrintBST(ShowTreeNum);
                        }
                        break; //其中更新了hit的高度
                case 2 * RH:
                        hit = RightBalance(hit);
                        if (process && !mask)
                        {
                                if (root)
                                        TreeList[ShowTreeNum] = hit;
                                halt();
                                PrintBST(ShowTreeNum);
                        }
                        break;
                }
                if (hit->height == old_ht)
                        shorter = 0; //高度不变，则父节点平衡因子也不变
        }
        if (!hit->parent)
                T = hit; //涉及根结点重平衡，但是高度未改变的结束
        return T;
}

int MergeBST(int no1, int no2)
{ //需要实现判断T2是否为空
        int e;
        BsTree T1, T2;
        int rt_val = 1;
        if (ExistList[no1] == 0)
        {
                printf("Fail! Tree %d does not exist!\n", no1);
                rt_val = 0;
        }
        if (ExistList[no2] == 0)
        {
                printf("Fail! Tree %d does not exist!\n", no2);
                rt_val = 0;
        }
        if (rt_val == 0)
                return 0;

        mask = 1; //不必展示插入和删除的细节操作
        T1 = TreeList[no1];
        T2 = TreeList[no2];

        int showstep = 0;
        if (process)
        {
                printf("Processing: Merge step: %d-------------\n", showstep++);
                PrintBST(no1);
                PrintBST(no2);
        }

        while (T2)
        {
                e = T2->data;
                T1 = InsertBST(T1, e);
                T2 = DelBST(T2, e); //从最终效果上不需删除，此处为了进行逐步演示,或者考虑在演示时才删
                if (process)
                {
                        TreeList[no1] = T1;
                        TreeList[no2] = T2;
                        halt();
                        printf("Processing: Merge step: %d-------------\n", showstep++);
                        PrintBST(no1);
                        PrintBST(no2);
                }
        }
        mask = 0;
        TreeList[no1] = T1;
        TreeList[no2] = NULL;
        ExistList[no2] = 0;
        printf("Merge from Tree %d to Tree %d is over!\n", no2, no1);
        return 1; // success
}

int BranchBST(int no1, int no2, int no3, int e)
{
        int data;
        if (ExistList[no1] == 0)
        {
                printf("Fail! Tree %d does not exist!\n", no1);
                return 0;
        }
        if (no1 == no2 || no2 == no3)
        {
                printf("Fail! Tree %d should differ from Tree %d and Tree %d\n", no1, no2, no3);
                return 0;
        }
        if (ExistList[no2] == 0)
                CreateBST(no2);
        if (ExistList[no3] == 0)
                CreateBST(no3);
        BsTree T1, T2, T3;
        T1 = TreeList[no1];
        T2 = TreeList[no2];
        T3 = TreeList[no3];
        mask = 1; //掩盖具体操作
        int showstep = 0;
        if (process)
        {
                printf("Processing: Branch step: %d-----------------\n", showstep++);
                PrintBST(no1);
                PrintBST(no2);
                PrintBST(no3);
        }
        while (T1)
        {
                data = T1->data;
                T1 = DelBST(T1, data);
                if (data < e)
                        T2 = InsertBST(T2, data);
                else
                        T3 = InsertBST(T3, data);
                if (process)
                {

                        TreeList[no1] = T1;
                        TreeList[no2] = T2;
                        TreeList[no3] = T3;
                        halt();
                        printf("Processing: Branch step: %d-----------------\n", showstep++);
                        PrintBST(no1);
                        PrintBST(no2);
                        PrintBST(no3);
                }
        }
        mask = 0;
        TreeList[no1] = NULL;
        ExistList[no1] = 0;
        TreeList[no2] = T2;
        TreeList[no3] = T3;
        printf("Branch from Tree %d to Tree %d and Tree %d is over!\n", no1, no2, no3);
        return 1;
}