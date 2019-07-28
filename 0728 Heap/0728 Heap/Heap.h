#ifndef _HEAP_H_
#define _HEAP_H_
#define MAXSIZE 100
#define ARRSIZE(a) (sizeof(a)/sizeof(a[0]))

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef int HPDataType;
typedef struct Heap 
{ 
	HPDataType* _a;
	int _size;    
	int _capacity; 
}Heap;
void DownAdjust(Heap *hp, int n);
void HeapInit(Heap *hp, HPDataType *a, int n); 
void HeapDestory(Heap *hp); 
void HeapPush(Heap *hp, HPDataType x); 
void HeapPop(Heap *hp); 
HPDataType HeapTop(Heap *hp); 
int HeapSize(Heap *hp); 
int HeapEmpty(Heap *hp);
void HeapPrint(Heap *hp);
// ∂—≈≈–Ú 
void HeapSort(Heap *hp);

#endif/*_HEAP_H_*/