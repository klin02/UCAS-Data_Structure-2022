#include <stdio.h>
#include <string.h>
//AC
/***Input Format
 * Event Sex School Score
 * Event:1 bit
 * Sex:  M or F
 * School:A,B,C,D,E
 ***/
void myfflush();
int sumM[5] = {0}, sumF[5] = {0};
int main()
{
    char eve, sex, school;
    int score;
    //printf("Input Format:Event,sex,school,score\nInput:");
    while (scanf("%c %c %c %d", &eve, &sex, &school, &score)==4)
    { //scanf返回成功读入的数据项数,注意Event只有一位
    //  ！！！注意，循环读取时，换行符将被当做上一个的首字母,因此需清空缓冲区
        if (school < 'A' || school > 'E')
        {
            //printf("Error: School\n");
            break;
        }
        if (sex != 'F' && sex != 'M')
        {
            //printf("Error: Sex\n");
            break;
        }
        switch (sex)
        {
        case 'M':
            sumM[school - 'A'] += score;
            break;
        case 'F':
            sumF[school - 'A'] += score;
            break;
        default:
            break;
        }
        //printf("Input:");
        myfflush();
    }
    //printf("Output Format:School,Malescore,Femalescore,Totalscore\n");
    for(int i=0;i<5;i++){
        if(sumM[i]!=0)
            printf("%c M %d\n", 'A'+i,sumM[i]);
        if(sumF[i]!=0)
            printf("%c F %d\n", 'A'+i,sumF[i]);
        if(sumM[i]+sumF[i]!=0)
            printf("%c %d\n", 'A'+i,sumM[i] + sumF[i]);
    }
    return 0;
}
void myfflush(void)//针对多行输入 清空本行换行符即停止
{
	char c;
	while ((c = getchar()) != '\n'&&c != EOF)
		;
}