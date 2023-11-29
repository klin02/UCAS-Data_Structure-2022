#include <stdio.h>
//AC
int main()
{
    int top = 0;
    char c;
    int cnt = 0;
    int res;
    //测试样例给出多行，但实际上测试为单行
    while ((c = getchar()) != '\n' && c != EOF)
    {
        if (c == '(')
            cnt++;
        else if (c == ')')
            cnt--;
    }
    if (c == '\n' || c == EOF)
    {
        if (cnt == 0)
            res = 1;
        else
            res = 0;
        cnt = 0;
    }

    printf("%d\n", res);
    return 0;
}
