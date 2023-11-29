#include <stdio.h>
//AC
int main()
{
    char stack[100];
    int top = 0;
    char c;
    while ((c = getchar()) != '&')
    {
        stack[top++] = c;
    }
    while ((c = getchar()) != '@')
    {
        if (c != stack[--top])
        {
            printf("0");
            return 0;
        }
    }
    if (top == 0)
        printf("1");
    return 0;
}