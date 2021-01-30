#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct LNode{
    int data;
    struct LNode *next;
}LNode,*LinkList;
int Pop(LinkList L){
if(L->next == NULL){
    return 0;
}
LinkList tem = L->next;
printf("%d",tem->data);
L->next = tem->next;
free(tem);
return 1 ;
}
int Push(LinkList L,int e){
LinkList newNode = (LinkList)malloc(sizeof(LinkList));
newNode -> data = e;
newNode -> next = L->next;
L->next = newNode;
return 1;
}