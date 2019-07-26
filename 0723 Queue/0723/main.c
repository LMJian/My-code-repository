#include"Queue.h"

int main()
{
	Queue pq;
	QueueInit(&pq);
	QueuePush(&pq, 1);
	QueuePush(&pq, 2);
	QueuePush(&pq, 3);
	QueuePush(&pq, 4);
	QueuePush(&pq, 5);
	QueuePush(&pq, 6);
	QueuePush(&pq, 7);
	QueuePush(&pq, 8);
	QueuePush(&pq, 9);
	QueuePush(&pq, 10);
	QueuePop(&pq);
	QueuePop(&pq);
	QueuePush(&pq, 11);
	QueuePush(&pq, 12);

	QueuePop(&pq);
	printf("%d ", QueueFront(&pq));
	QueuePop(&pq);
	printf("%d ", QueueFront(&pq));
	QueuePop(&pq);
	printf("%d ", QueueFront(&pq));
	QueuePop(&pq);
	printf("%d ", QueueFront(&pq));
	system("pause");
	return 0;
}