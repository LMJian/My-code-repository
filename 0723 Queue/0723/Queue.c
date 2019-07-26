#include"Queue.h"

void QueueInit(Queue* pq)
{
	pq->_front = pq->_rear = pq->_data;
	pq->size = 0;
}
void QueueDestory(Queue* pq)
{
	pq->_front = pq->_rear = pq->_data;
	pq->size = 0;
}
void QueuePush(Queue* pq, QUDataType x)
{
	if (pq->size == QueueMax)
	{
		printf("Õ»ÒÑÂú\n");
		return;
	}
	if (pq->_rear - pq->_data == QueueMax - 1)
	{
		*pq->_rear = x;
		pq->_rear=pq->_data;
	}
	else
	{
		*pq->_rear = x;
		pq->_rear++;
	}
	pq->size++;
}
void QueuePop(Queue* pq)
{
	if (pq->size == 0)
	{
		printf("Õ»¿Õ\n");
		return;
	}
	if (pq->_front - pq->_data == QueueMax - 1)
	{
		printf("%d ", *pq->_front);
		pq->_front=pq->_data;
	}
	else
	{
		printf("%d ", *pq->_front);
		pq->_front++;
	}
	pq->size--;
}
QUDataType QueueFront(Queue* pq)
{
	if (pq->size!=0)
		return *pq->_front;
	return -1;
}
QUDataType QueueBack(Queue* pq)
{
	if (pq->size == 0)
		return 0;
	if (pq->_rear == pq->_data)
		return *(pq->_rear + QueueMax - 1);
	return *(pq->_rear-1);
}