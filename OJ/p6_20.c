#include <stdio.h>
#include <stdlib.h>
//AC
//考虑线索本质上就是遍历次序，考虑用双向链表进行存储即可
//森林和二叉树等价
//题意中要求先序只进行前驱线索化。。
typedef struct binode{
    int data;
    int left,right;
    struct binode *lchild,*rchild;
}Binode,*Bitree;
Bitree stack[100];
int sontag[100]={0};
//非零表示为孩子，森林根结点为0
Bitree root[100];
int top=0;
typedef struct linknode{
    int data;
    struct linknode *l,*r;
}node;
typedef struct linklist{
    node *head,*tail;
}list;

int L[3][100]={0};
int R[3][100]={0};

list * newlist();
list * Insert(list *li,int data);
list * Prethreading(list *l1,Bitree T);
list * Inthreading(list *l2,Bitree T);
list * Postthreading(list *l3,Bitree T);
//题意要求先序只需前驱，后序只需后继
//如有左右树，先行标记
int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        Bitree p=(Bitree)malloc(sizeof(Binode));
        scanf("%d %d %d",&p->data,&p->left,&p->right);
        stack[i]=p;
    }
    //在生成树的过程中，如有左右子树，先行标记
    Bitree t;
    for(int i=1;i<=n;i++){
        t=stack[i];
        if(t->left==0){
            t->lchild=NULL;
        }
        else{
            t->lchild=stack[t->left];
            sontag[t->left]++;//该节点为孩子
            for(int j=0;j<3;j++)
                L[j][t->data]=t->left;
        }
        if(t->right==0){
            t->rchild=NULL;
        }
        else{
            t->rchild=stack[t->right];
            sontag[t->right]++;//该节点为孩子
            for(int j=0;j<3;j++)
                R[j][t->data]=t->right;//=t->rchild->data
        }
    }
    //由于输入为森林，根结点并未连接

    for(int i=1;i<=n;i++)
    if(sontag[i]==0){
        root[top++]=stack[i];
    }
    Bitree T=root[0];//root
    for(int i=0;i<top-1;i++){
        root[i]->rchild=root[i+1];//森林化为二叉树
        for(int j=0;j<3;j++)
            R[j][root[i]->data]=root[i]->rchild->data;
    }
    
    for(int i=0;i<3;i++)
        L[i][0]=R[i][0]=1;
    
    //先序只需填充L数组非零部分。。。
    list *l1,*l2,*l3;
    l1=newlist();
    l2=newlist();
    l3=newlist();
    l1=Prethreading(l1,T);
    l2=Inthreading(l2,T);
    l3=Postthreading(l3,T);

    node *ptr;
    //pre
    for(int i=1;i<=n;i++)
        if(L[0][i]==0){
            for(ptr=l1->head;ptr;ptr=ptr->r)
                if(ptr->data==i && ptr!=l1->head){
                    L[0][i]=ptr->l->data;
                }
        }

    //in
    for(int i=1;i<=n;i++)
        if(L[1][i]==0){
            for(ptr=l2->head;ptr;ptr=ptr->r)
                if(ptr->data==i && ptr!=l2->head)
                    L[1][i]=ptr->l->data;
        }
    for(int i=1;i<=n;i++)
        if(R[1][i]==0){
            for(ptr=l2->head;ptr;ptr=ptr->r)
                if(ptr->data==i && ptr!=l2->tail)
                    R[1][i]=ptr->r->data;
        }
        
    //post
    for(int i=1;i<=n;i++)
        if(R[2][i]==0){
            for(ptr=l3->head;ptr;ptr=ptr->r)
                if(ptr->data==i && ptr!=l3->tail)
                    R[2][i]=ptr->r->data;
        }

    for(int k=0;k<3;k++){
        printf("1");
        for(int i=1;i<=n;i++)
            printf(" %d",L[k][i]);
        printf("\n");
        printf("1");
        for(int i=1;i<=n;i++)
            printf(" %d",R[k][i]);
        printf("\n");
    }
    return 0;

}
list * newlist(){
    list *li=(list *)malloc(sizeof(list));
    li->head=li->tail=NULL;
    return li;
}
list *Insert(list *li,int data){
    node *p=(node *)malloc(sizeof(node));
    p->data=data;
    p->r=NULL;
    if(li->head==NULL){
        p->l=NULL;
        li->head=li->tail=p;
    }
    else{
        li->tail->r=p;
        p->l=li->tail;
        li->tail=p;
    }
    return li;
}
list * Prethreading(list *l1,Bitree T){
    if(!T)
        return l1;
    else{
        l1=Insert(l1,T->data);
        if(T->lchild)
            l1=Prethreading(l1,T->lchild);
        if(T->rchild)
            l1=Prethreading(l1,T->rchild);
    }
    return l1;
}
list * Inthreading(list *l2,Bitree T){
    if(!T)
        return l2;
    else{
        if(T->lchild)
            l2=Inthreading(l2,T->lchild);
        l2=Insert(l2,T->data);
        if(T->rchild)
            l2=Inthreading(l2,T->rchild);
    }
    return l2;
}
list * Postthreading(list *l3,Bitree T){
    if(!T)
        return l3;
    else{
        if(T->lchild)
            l3=Postthreading(l3,T->lchild);
        if(T->rchild)
            l3=Postthreading(l3,T->rchild);
        l3=Insert(l3,T->data);   
    }
    return l3;
}