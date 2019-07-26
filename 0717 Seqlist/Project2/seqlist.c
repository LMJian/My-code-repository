#include"seqlist.h"

// 基本增删查改接口
void SeqListInit(SeqList* psl, size_t capacity)
{
	psl->array = (SLDataType*)(calloc(capacity, sizeof(SLDataType)));
	psl->size = 0;
	psl->capacity = capacity;
}
void SeqListDestory(SeqList* psl)//销毁
{
	if (psl->array != NULL)
	{
		free(psl->array);
		psl->array = NULL;
		psl->capacity = 0;
		psl->size = 0;
	}
}
void CheckCapacity(SeqList* psl)//检查满
{
	if (psl->size == psl->capacity)
	{
		psl->capacity *= 2;
		psl->array = (SLDataType*)(realloc(psl->array,psl->capacity*sizeof(SLDataType)));
	}
}
void SeqListPushBack(SeqList* psl, SLDataType x)//尾插
{
	CheckCapacity(psl);
	psl->array[psl->size] = x;
	psl->size++;
}
void SeqListPopBack(SeqList* psl)//尾删
{
	psl->size--;
}
void SeqListPushFront(SeqList* psl, SLDataType x)//头插
{
	CheckCapacity(psl);
	int i;
	for (i = psl->size - 1; i >= 0; i--)
	{
		psl->array[i + 1] = psl->array[i];
	}
	psl->array[0] = x;
	psl->size++;
}
void SeqListPopFront(SeqList* psl)//头删
{
	int i;
	for (i = 1; i < psl->size; i++)
	{
		psl->array[i - 1] = psl->array[i];
	}
	psl->size--;
}
int SeqListFind(SeqList* psl, SLDataType x)//查找X
{
	int i;
	for (i = 0; i < psl->size; i++)
	{ 
		if (psl->array[i] == x)
			return i;
	}
	return -1;

}
void SeqListInsert(SeqList* psl, int pos, SLDataType x)//插入
{
	if (pos<0 || pos>psl->size)
		return;
	CheckCapacity(psl);
	int i;
	for (i = psl->size - 1; i >= pos; i--)
	{
		psl->array[i + 1] = psl->array[i];
	}
	psl->array[pos] = x;
	psl->size++;
}
void SeqListErase(SeqList* psl, int pos)//删除指定位置的值
{
	if (pos < 0 || pos >= psl->size)
		return;
	int i;
	for (i = pos; i < psl->size-1; i++)
	{
		psl->array[i] = psl->array[i+1];
	}
	psl->size--;
}
void SeqListRemoveFirst(SeqList* psl, SLDataType x)//删除指定值（第一个）
{
	if (SeqListFind(psl, x)!=-1)
		SeqListErase(psl, SeqListFind(psl, x));
}
// 本题要求：时间复杂度：O(N) 空间复杂度 O(1)
void SeqListRemoveAll(SeqList* psl, SLDataType x)//删除指定值（所有）
{
	int top = 0;
	int i;
	for (i = 0; i < psl->size; i++)
	{
		if (psl->array[i] == x)
			top++;
		else
			psl->array[i - top] = psl->array[i];
	}
	psl->size -= top;
}
void SeqListModify(SeqList* psl, int pos, SLDataType x)//修改指定值
{
	if (pos>=0&&pos<psl->size)
		psl->array[pos] = x;
}
void SeqListPrint(SeqList* psl)
{
	int i;
	for (i = 0; i < psl->size; i++)
	{
		printf("%d ", psl->array[i]);
	}
	printf("\n");
}
// 扩展面试题实现
void SeqListBubbleSort(SeqList* psl)
{
	int i, j;
	SLDataType t;
	for (i = 1; i < psl->size; i++)
	{
		j = i;
		while (j>0 && psl->array[j] < psl->array[j - 1])
		{
			t = psl->array[j];
			psl->array[j] = psl->array[j - 1];
			psl->array[j - 1] = t;
			j--;
		}
	}
}
int SeqListBinaryFind(SeqList* psl, SLDataType x)//二分查找
{
	int left = 0;
	int right = psl->size - 1;
	int mid;
	while (left<=right)
	{
		mid = (left + right) / 2;
		if (psl->array[mid] < x)
		{
			left = mid + 1;
		}
		else if (psl->array[mid] > x)
		{
			right = mid - 1;
		}
		else
			return mid;
	}
	return - 1;
}
