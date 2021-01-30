#include<stdio.h>
#include <stdlib.h>
#define SIZE 20

typedef struct SQueue{
	char data[SIZE];
	int rear;
	int length;
	int size;
}QE , *Queue;

int initQueue(Queue Q){//初始化
	Q->rear = -1;
	Q->length= 0;
	Q->size = SIZE;
	return 1;
}

int QueueEmpty(Queue Q){//队列空？
	if(Q->length == 0)return 1;
	else return 0;
}

int QueueLength(Queue Q){//取得队列长
	return Q->length;
}

int QueueGetHead(Queue Q,char *e){//取得队列头
	int front = (Q->rear - Q->length +Q->size +1)% Q->size;
	if(Q->rear == front)return 0;
	* e = Q->data[front];
	return 1;
}

int QueueEnter(Queue Q, char e){//进队列
	if(Q->length == Q->size)return 0;
	Q->length++;
	Q->rear = (Q->rear+1) % Q->size;
	Q->data[Q->rear] = e;
	return 1;
}

int QueueOut(Queue Q,char *e){//出队列
	if(Q->length == 0)return 0;
	int front = (Q->rear - Q->length +Q->size +1)% Q->size;
	* e = Q->data[front];
	Q->length--;
	return 1;
}

void QueueTravers(Queue Q){//遍历队列
	int i = (Q->rear - Q->length +Q->size +1)% Q->size;
	for(; i < Q->length;i++)
	{
		printf("%c",Q->data[i]);
	}
		printf("%c\n",Q->data[i]);

}
main(){
	Queue Q;
	char ch;
	if(initQueue(Q))printf("initialization finished\n");
	if(QueueEmpty(Q))printf("Empty\n");
	else printf("not Empty\n");

	QueueEnter(Q,'a');
	QueueEnter(Q,'b');
	QueueEnter(Q,'c');
	QueueOut(Q,&ch);
	printf("%c\n",ch);
	QueueTravers(Q);
	printf("Length: %d",QueueLength(Q));

}
