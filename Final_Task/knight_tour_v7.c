//存储路径以方便回溯
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <windows.h>

#define SIZE 8
#define TRUE 1
#define FALSE 0
#define maxchess SIZE*SIZE      
#define MAXHISTORY 100000
#define MAXDIFSTEP 1*maxchess   //允许和上一次成功路径不同的最多步数
#define MAXTB 5                 //允许演示的最多路径数
#define isIn(x) ((x)>=0 && (x)<SIZE)
#define MIN(x,y) (((x)<(y)) ? (x) : (y))
#define ToEdge(x) MIN(x,SIZE-x)

typedef struct chess{
        int x;                 //行，为节省空间，使用char类型
        int y;
        int dir;               //下一步行动方向 0-7,对应nextseq中数据
        int nextcnt;           //下一步最佳行动方向（下下步可移动数最少）
        int nextseq[8];        //排序后的下一步可行动点序列
}Chess;
Chess cur;
typedef struct stack{
        int sp;         //栈顶位置，栈顶指针可用 base[sp+1] 确定
        Chess * base;   //栈底指针
}Stack;
Stack *S;
typedef unsigned char Board[SIZE][SIZE]; //当前棋盘和历史棋盘的类型定义
Board board, history[MAXHISTORY];


int curstep = 0;         //当前移动步数
int historycnt =0;      //历史路径数
int TBpath=0 ;          //有回溯的路径数
int TBprint=0;          //允许演示的回溯路径数
int TBlist[MAXTB];      //允许演示的路径列表，控制数量以GUI友好
int TBflag=0;           //本条路径是否回溯标志
int TBdir[MAXTB][MAXDIFSTEP];   
int TBdirtop[MAXTB];    //记录dirtop
int TBdiffpt[MAXTB];
int curdir[100*maxchess];
int maxdirtop=0;
int dirtop=0;
int diffpoint=0; //和上一次成功遍历的分歧点
/*
*本次遍历路径序列的维护：
*只记录上一个分歧点之后的路径，DFS中通过成功回溯到下一次开始的最小步数确定分歧点，
*成功回溯无需修改dir数组，失败回溯需要。
*/
const int dir_x[8] = {-2,-1,1,2,2,1,-1,-2};
const int dir_y[8] = {1,2,2,1,-1,-2,-2,-1};

void PrintBoard(int no);
void Move(Stack *S);
void TrackBack(Stack *S,int flag);
void RenewTop(Stack *S);
void DFS(Stack *S);
void Init(Stack *S);//初始化函数，以供重新开始
int SortNext();
void PrintNow(Board plat,int upp,int pathno,int tbstep);
void ShowTraces(int no);

//适配系统的相关函数
void clear_screen();
void halt();

int main(){
        int x,y;
        char c;
        int no;
        clock_t clockstart, clockend;
        S = (Stack *)malloc(sizeof(Stack));
        S->base = (Chess*)malloc(100000*sizeof(Chess));
        printf("Welcome to Knight's Tour!\nAuthor: KL\n");
        while(1){
                Init(S);
                PrintBoard(-1);
                printf("Please input the start position as (0~%d 0~%d)\nExample:0 0\n",SIZE-1,SIZE-1);
                scanf("%d %d%c",&x,&y,&c);      // remove \n
                if(isIn(x)&& isIn(y)){
                        cur.x=x;
                        cur.y=y;
                        cur.dir=0;
                        board[cur.x][cur.y]=++curstep;
                        //Move(S);  
                        clockstart = clock();
                        DFS(S);
                        clockend = clock();
                        char func;
                        while(1){
                                printf("%d Path Found! Trackback Path:%d. TIME:%.2fs\n",historycnt,TBpath,(double)(clockend - clockstart) / CLOCKS_PER_SEC);
                                //printf("maxdirtop=%d\n",maxdirtop);
                                printf("Function Press as follows:\n");
                                printf("'c': show result directly   (All path)\n");
                                printf("'d': show trackback process (First %d Path)\n",TBprint);
                                printf("'r': rechoose initial postion\n");
                                printf("'q': quit\n");
                                printf("Please input function:");
                                scanf("%c%c",&func,&c);
                                if(func == 'c'){
                                        while(1){
                                        printf("Trackback disabled. Input 0~%d to view, -1 to rechoose func:",historycnt-1);
                                        scanf("%d%c",&no,&c);
                                        if(no==-1)
                                                break;
                                        else{
                                                clear_screen();
                                                printf("--------Path: %d--------\n",no);
                                                PrintBoard(no);
                                        }
                                        }
                                        
                                }
                                else if(func == 'd'){
                                        while(1){
                                                printf("Trackback enabled. List as follows:\n");
                                                for(int i=0;i<TBprint;i++)
                                                printf("%d: Path %d, DiffPoint %d, Traces %d\n",i,TBlist[i],TBdiffpt[i],TBdirtop[i]);
                                                printf("Please input 0~%d to view process, -1 to rechoose func\n",TBprint-1);
                                                scanf("%d%c",&no,&c);
                                                if(no==-1)
                                                break;
                                                else
                                                        ShowTraces(no); 
                                        }                           
                                }
                                else if(func == 'r'){
                                        clear_screen();
                                        break;  //到大循环中
                                }
                                else if(func =='q')
                                        return 0;
                                else{
                                        clear_screen();
                                        printf("Invalid func! Please input again!\n\n");
                                }
                                        
                        }
                        
                        // int no;
                        
                }
                else{
                        clear_screen();
                         printf("Invalid input! Please Input again!\n");
                } 
        }
}

void Init(Stack *S){
        S->sp=0;
        memset(board,0,sizeof(board));
        curstep=0;
        historycnt=0;
        TBpath=0;
        TBprint=0;
        TBflag=0;
        dirtop=0;
        diffpoint=0;
        maxdirtop=0;
        //重置所有全局变量
}
void Move(Stack *S){ //新一个点落子，原子压栈
        //原子压栈
        Chess backup = cur;
        backup.dir++;
        S->base[S->sp++]=backup;   //保护栈，防止其随cur而更改 
        
        //记录本步行进方向
        curdir[dirtop++]=cur.nextseq[cur.dir];
        int tmp=cur.nextseq[cur.dir];
        //新点落子,转换工作点
        cur.x += dir_x[cur.nextseq[cur.dir]];
        cur.y += dir_y[cur.nextseq[cur.dir]];
        cur.dir =0;
        board[cur.x][cur.y]=++curstep;

        //PrintNow();
}
void TrackBack(Stack *S,int flag){
        //flag: 0 表示成功回溯，1表示失败回溯
        curstep--;
        board[cur.x][cur.y]=0;
        cur = S->base[--S->sp]; 
        if(flag)
                curdir[dirtop++]=-1;
}
void RenewTop(Stack *S){
        Chess backup = cur;
        S->base[S->sp-1] = backup;
}
void DFS(Stack *S){
        int first=1; // 标记第一次回到分歧点
        while(1){
                int stop;
                if(cur.dir == 0 && SortNext()==0) //本次遍历未经历过,第一条件不成立则第二个不再执行
                {
                        
                        if(curstep == maxchess){
                                if(TBflag==1){
                                        if(dirtop < MAXDIFSTEP && TBprint < MAXTB){
                                                TBlist[TBprint] = historycnt;
                                                memcpy(TBdir[TBprint],curdir,dirtop*sizeof(int));
                                                TBdirtop[TBprint] = dirtop;
                                                TBdiffpt[TBprint] = diffpoint;
                                                TBprint++;
                                                maxdirtop = dirtop;
                                        }
                                        TBpath++;
                                }
                                //PrintNow();
                                memcpy(history[historycnt++],board,sizeof(Board));
                                if(historycnt == 89)
                                        stop=1;
                                first=1;
                                dirtop=0;
                                diffpoint=maxchess;
                                TBflag=0; //清零
                                if(historycnt == MAXHISTORY)
                                        return;
                        }
                        else TBflag=1;  //失败
                        TrackBack(S,TBflag);
                        //PrintNow();
                        continue;
                }
                else if(cur.dir == cur.nextcnt){
                        if(curstep==1)
                                break; //起始值，遍历结束
                        else {
                                TrackBack(S,TBflag);
                                continue;
                        }
                        
                }
                if(TBflag ==0 &&first==1){
                        diffpoint = curstep; //成功后第一次回到岔路，即分歧点
                        first=0;
                }
                Move(S);
        }
}

int SortNext(){//返回值表示有无下下步可行动点
        int num[8]={0};
        int edge[8]={0};
        int nx,ny;
        int nnextx,nnexty;
        cur.nextcnt=0;//清零以统计最优走法数
        int flag=0;     //统计有无可走点
        for(int i=0;i<8;i++){
                nx=cur.x+dir_x[i];
                ny=cur.y+dir_y[i];
                if(!isIn(nx) || !isIn(ny) || board[nx][ny]!=0){
                        num[i]=9;       //由于需要将先取较小可能，将其改为越界非法值，方便排序
                }
                else{
                        for(int j=0;j<8;j++){
                                nnextx = nx + dir_x[j];
                                nnexty = ny + dir_y[j];
                                if(isIn(nnextx) && isIn(nnexty) && board[nnextx][nnexty]==0)
                                        num[i]++;
                        }
                        if(!num[i] && curstep < maxchess-1) 
                                num[i]=9; //对于非最后一步，num[i]=0表示下下步不可走
                        else{
                                flag++;
                                edge[i]=ToEdge(nx)+ToEdge(ny); //边缘优先，只有下下步可走才计算
                        } 
                               
                }
        }

        if(flag==0)
                return 0; //之后无可行动点，直接不排序
        else{
                int min,mintmp,dis,distmp;
                int tar;
                for(int i=0;i<8;i++){
                        mintmp=9;
                        distmp=SIZE+1;
                        for(int j=0;j<8;j++){
                                if(num[j]<mintmp|| (num[j]==mintmp && edge[j] < distmp))
                                {
                                        mintmp = num[j];
                                        distmp = edge[j];
                                        tar=j;
                                }
                        }
                        if(!i){
                                min=mintmp;
                                dis=distmp;
                        }
                        if(mintmp==min) //只要均最少可走即可选择，但是排序还是边缘优先
                        {
                                cur.nextseq[cur.nextcnt++]=tar;
                                num[tar]=10;      //不再最优
                        }
                        else 
                                break;
                }
                return 1;
        }
        
}

void PrintBoard(int no){
        for(int i=0;i<SIZE;i++)
        {
                for(int j=0;j<SIZE;j++){
                        if(SIZE < 10)
                        {
                                if(no==-1)
                                        printf("__ ");
                                else 
                                        printf("%02d ",history[no][i][j]);
                        }
                        else
                        {
                                if(no==-1)
                                        printf("___ ");
                                else 
                                        printf("%03d ",history[no][i][j]);
                        }
                }
                printf("\n");
        }
}

void PrintNow(Board plat,int upp,int pathno,int tbstep){//只打印1~upp的数据
printf("--------Path: %d   TBstep: %d  Total step: %d---------\n",TBlist[pathno],tbstep,TBdirtop[pathno]);
        for(int i=0;i<SIZE;i++)
        {
                for(int j=0;j<SIZE;j++){
                        if(plat[i][j]>0 && plat[i][j]<=upp){
                                if(SIZE<10)
                                        printf("%02d ",plat[i][j]);
                                else 
                                        printf("%03d ",plat[i][j]);
                        }
                        else{
                                if(SIZE<10)
                                        printf("__ ");
                                else
                                        printf("___ ");
                        }

                }
                printf("\n");
        }
        //printf("-----------historcnt = %d  curstep = %d--------\n",historycnt, curstep);
}

void ShowTraces(int no){
        int path = TBlist[no];
        int upp = TBdiffpt[no]; //当前有效位置数
        int tmp;
        Board plat;
        struct pos{
                int x;
                int y;
        };
        struct pos showlist[maxchess];
        struct pos new;
        for(int i=0;i<SIZE;i++){
                for(int j=0;j<SIZE;j++){
                        tmp=history[path-1][i][j];
                        if(tmp>0 && tmp<=upp){
                                plat[i][j]=tmp;
                                showlist[tmp-1].x = i;
                                showlist[tmp-1].y = j;
                        }
                        else
                                plat[i][j]=0;
                }
        }
        clear_screen();
        PrintNow(plat,upp,no,0);
        for(int k=0;k<TBdirtop[no];k++){
                if(TBdir[no][k]== -1){
                        upp--;
                        plat[showlist[upp].x][showlist[upp].y]=0;
                }
                else{
                        new.x=showlist[upp-1].x + dir_x[TBdir[no][k]];
                        new.y=showlist[upp-1].y + dir_y[TBdir[no][k]];
                        showlist[upp++]=new;
                        plat[new.x][new.y]=upp;
                }
                halt();
                clear_screen();
                PrintNow(plat,upp,no,k+1);
        }
        printf("Path %d trackback Over!\n\n",path);
}

void clear_screen()
{
#ifdef linux
    system("clear");
#elif __WINDOWS_
    system("cls");
#elif _WIN32
    system("cls");
#endif
}

void halt(){
#ifdef linux
    sleep(1);
#elif __WINDOWS_
    Sleep(1000);
#elif _WIN32
    Sleep(1000);
#endif
}