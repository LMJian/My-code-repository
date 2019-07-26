#ifndef _SEQLIST_H_
#define _SEQLIST_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef int SLDataType;
// 顺序表的动态存储
typedef struct SeqList
{
	SLDataType* array; // 指向动态开辟的数组
	int size; // 有效数据个数
	int capacity; // 容量空间的大小
}SeqList;
// 基本增删查改接口
void SeqListInit(SeqList* psl, size_t capacity);
void SeqListDestory(SeqList* psl);
void CheckCapacity(SeqList* psl);
void SeqListPushBack(SeqList* psl, SLDataType x);
void SeqListPopBack(SeqList* psl);
void SeqListPushFront(SeqList* psl, SLDataType x);
void SeqListPopFront(SeqList* psl);
int SeqListFind(SeqList* psl, SLDataType x);
void SeqListInsert(SeqList* psl, int pos, SLDataType x);
void SeqListErase(SeqList* psl, int pos);
void SeqListRemoveFirst(SeqList* psl, SLDataType x);
void SeqListModify(SeqList* psl, int pos, SLDataType x);
void SeqListPrint(SeqList* psl);
// 扩展面试题实现
void SeqListBubbleSort(SeqList* psl);
int SeqListBinaryFind(SeqList* psl, SLDataType x);
// 本题要求：时间复杂度：O(N) 空间复杂度 O(1)
void SeqListRemoveAll(SeqList* psl, SLDataType x);

#endif /*_SEQLIST_H_*/