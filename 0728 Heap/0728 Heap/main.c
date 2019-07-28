#include"Heap.h"

int main()
{
	HPDataType a[] = { 1, 6, 3, 7, 9, 8 };
	Heap hp;
	HeapInit(&hp, a, ARRSIZE(a));
	HeapSort(&hp);
	HeapPrint(&hp);
	HeapDestory(&hp);
	system("pause");
	return 0;
}