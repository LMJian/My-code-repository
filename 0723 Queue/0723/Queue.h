#ifndef _QUEUE_H_
#define _QUEUE_H_
#define QueueMax 10
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef int QUDataType;
typedef struct Queue 
{
	QUDataType _data[QueueMax];
	QUDataType* _front; // ∂”Õ∑    
	QUDataType* _rear;  // ∂”Œ≤
	size_t size;
}Queue;
void QueueInit(Queue* pq); 
void QueueDestory(Queue* pq);
Queue* BuyQueueNode(QUDataType x); 
void QueuePush(Queue* pq, QUDataType x); 
void QueuePop(Queue* pq); 
QUDataType QueueFront(Queue* pq); 
QUDataType QueueBack(Queue* pq); 
int QueueEmpty(Queue* pq); 
int QueueSize(Queue* pq);
void TestQueue();

#endif /*_QUEUE_H_*/