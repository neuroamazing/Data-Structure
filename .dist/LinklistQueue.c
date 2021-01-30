#include<stdio.h>
#include <stdlib.h>
#include<string.h>
typedef char String[30];
typedef struct QNode{//链表队列
    String data;
    struct QNode *next;
}Qnode,* LinkQueueNode;

typedef struct{
    LinkQueueNode front;
    LinkQueueNode rear;
}QFrontAndRear;

//节点域 ->队头
//节点域 ->队尾

int initLinkQueue(QFrontAndRear *LQ){
    LQ->front=LQ->rear=(LinkQueueNode)malloc(sizeof(Qnode));
    if(LQ->front == NULL)return 0;
    LQ->front->next=NULL;
    return 1;
}

int LinkQueueEmpty(QFrontAndRear LQ){
    if(LQ.front == LQ.rear)return 1;
    else return 0;
}

int LinkQueueLength(QFrontAndRear Q){
    LinkQueueNode p;
    int n=0;
    if(Q.front == Q.rear)return 0;
    p = Q.front->next;//进入数据链表区域
    while(p){
        n++;
        p=p->next;
    }
    return n;
}

int LinkQueueGetHead(QFrontAndRear Q,String e){
    if(Q.front == Q.rear)return 0;
    strcpy(e,Q.front->next->data);
    return 1;
}
// 节点域 -> 队头数据域 -> 数据
int LinkQueueEnter(QFrontAndRear *Q,String e){//入链队
    LinkQueueNode p =(LinkQueueNode)malloc(sizeof(Qnode));
    if(p==NULL)return 0;
    strcpy(p->data,e);
    p->next = NULL;
    Q->rear->next = p;
    Q->rear = p;
    return 1;
}

int LinkQueueOut(QFrontAndRear *Q,String e){//出链队
    LinkQueueNode p;
    if(Q->rear == Q->front)return 0;
    strcpy(e,Q->front->next->data);
    p = Q->front->next;
    Q->front->next = p->next;
    if(Q->rear == p){
        Q->rear = Q->front;
    }
    free(p);
    return 1;
}
// 头链队 front|空| -> |数据A| -> |数据B|
//          e             p
//                      front -> |数据B|

void LinkQueueTravers(QFrontAndRear *Q){
    LinkQueueNode p = Q->front->next;
    while(p){
        printf("%s\n",p->data);
        p = p->next;
    }
}

main(){
QFrontAndRear Q;
String a = "dsadsadwdasadw";
String b = "||";
initLinkQueue(&Q);
if(LinkQueueEmpty(Q))printf("Empty\n");
LinkQueueEnter(&Q,a);
LinkQueueEnter(&Q,b);
printf("%d\n",LinkQueueLength(Q));
LinkQueueTravers(&Q);
LinkQueueOut(&Q,a);
printf("%d\n",LinkQueueLength(Q));
LinkQueueTravers(&Q);

}