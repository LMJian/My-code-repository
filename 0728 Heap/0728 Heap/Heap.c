#include"Heap.h"
void DownAdjust(Heap *hp, int n)//向下调整的下标
{
	while (2 * n + 1 < hp->_size)
	{
		if (2 * n + 2 < hp->_size)//左右孩子都有
		{
			if (hp->_a[2 * n + 1] > hp->_a[2 * n + 2] && hp->_a[n] < hp->_a[2 * n + 1])//左孩子大，且比父节点大
			{
				HPDataType t;
				t = hp->_a[2 * n + 1];
				hp->_a[2 * n + 1] = hp->_a[n];
				hp->_a[n] = t;
				n = 2 * n + 1;
			}
			else if (hp->_a[2 * n + 1] < hp->_a[2 * n + 2] && hp->_a[n] < hp->_a[2 * n + 2])//右孩子大，且比父节点大
			{
				HPDataType t;
				t = hp->_a[2 * n + 2];
				hp->_a[2 * n + 2] = hp->_a[n];
				hp->_a[n] = t;
				n = 2 * n + 2;
			}
			else
				return;
		}
		else if (2 * n + 1 < hp->_size)//只有左孩子
		{
			if (hp->_a[n] < hp->_a[2 * n + 1])
			{
				HPDataType t;
				t = hp->_a[2 * n + 1];
				hp->_a[2 * n + 1] = hp->_a[n];
				hp->_a[n] = t;
				n = 2 * n + 1;
			}
			else
				return;
		}
	}
}
void HeapInit(Heap *hp, HPDataType *a, int n)
{	
	int i;
	hp->_capacity = MAXSIZE > n ? MAXSIZE : n;
	hp->_size = n;
	hp->_a = (HPDataType*)malloc(sizeof(HPDataType)*hp->_capacity);
	memcpy(hp->_a, a, sizeof(HPDataType)*n);
	for (i = n / 2 - 1; i >= 0; i--)
		DownAdjust(hp, i);
}
void HeapDestory(Heap *hp)
{
	if (hp->_a)
	{
		free(hp->_a);
		hp->_a = NULL;
		hp->_capacity = hp->_size = 0;
	}
}
void HeapPush(Heap *hp, HPDataType x)
{
	if (hp->_size == hp->_capacity)
	{
		HPDataType* node = (HPDataType*)malloc(sizeof(HPDataType)*hp->_capacity * 2);
		memcpy(node, hp->_a, sizeof(HPDataType)*hp->_capacity);
		hp->_a = node;
		hp->_capacity = 2 * hp->_capacity;
	}
	hp->_a[hp->_size] = x;
	hp->_size++;
	int n = hp->_size - 1;
	while (n>0)
	{
		if (hp->_a[n] > hp->_a[(n - 1) / 2])
		{
			HPDataType t;
			t = hp->_a[n];
			hp->_a[n] = hp->_a[(n - 1) / 2];
			hp->_a[(n - 1) / 2] = t;
			n = (n - 1) / 2;
		}
		else
			return;
	}
}
void HeapPop(Heap *hp)
{
	HPDataType t = hp->_a[0];
	hp->_a[0] = hp->_a[hp->_size - 1];
	hp->_a[hp->_size - 1] = t;
	hp->_size--;
	DownAdjust(hp, 0);
}
HPDataType HeapTop(Heap *hp)
{
	if (hp->_size > 0)
		return hp->_a[0];
	return (HPDataType)0;
}
int HeapSize(Heap *hp)
{
	return hp->_size;
}
int HeapEmpty(Heap *hp)
{
	if (hp->_size == 0)
		return 1;
	return 0;
}
void HeapPrint(Heap *hp)
{
	int i;
	int m = 1, n = 0;
	for (i = 0; i < hp->_size; i++)
	{
		printf("%d ", hp->_a[i]);
		if (i == n)
		{
			putchar('\n');
			m = m * 2;
			n += m;
		}
	}
}
// 堆排序 
void HeapSort(Heap *hp)
{
	int t = hp->_size;
	while (hp->_size != 0)
	{
		HeapPop(hp);
	}
	hp->_size = t;
}