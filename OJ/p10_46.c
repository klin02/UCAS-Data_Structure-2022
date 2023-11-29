#include <stdio.h>
#include <stdlib.h>
//AC
//纯链表可用冒泡等方式交换不同位置的对应结点
//为直接应用快排，以下使用结构体 内含标号和指针
typedef struct linknode{
    int data;
    struct linknode *next;
}node;
typedef struct index{
    int no;
    node *key;
}Index;
Index stack[100];
int cmp( const void *a ,const void *b) ;
int main(){
    int n;
    scanf("%d",&n);
    int data;
    for(int i=0;i<n;i++){
        scanf("%d",&data);
        stack[i].no=data;
        stack[i].key=(node *)malloc(sizeof(node));
        stack[i].key->data=data;
        stack[i].key->next=NULL;
    }
    qsort(stack,n,sizeof(stack[0]),cmp); 
    // for(int i=0;i<n;i++)
    //     printf("%d ",stack[i].no);
    for(int i=0;i<n-1;i++)
        stack[i].key->next=stack[i+1].key;
    node *h=stack[0].key;
    while(h){
        printf("%d ",h->data);
        h=h->next;
    }

    return 0;
}
int cmp( const void *a ,const void *b) 
{ 
  return (*(Index *)a).no > (*(Index *)b).no ? 1 : -1; 
} 

