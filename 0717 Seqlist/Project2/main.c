#include"seqlist.h"

int main()
{
	SeqList test;
	SeqListInit(&test, 10);
	SeqListPushBack(&test, 1);
	SeqListPushBack(&test, 2);
	SeqListPushBack(&test, 3);
	SeqListPushBack(&test, 4);
	SeqListPushBack(&test, 5);
	SeqListPushFront(&test, 6);
	SeqListPushFront(&test, 5);
	SeqListPushFront(&test, 7);
	SeqListPushFront(&test, 8);
	SeqListPushBack(&test, 5);
	SeqListPushFront(&test, 5);
	SeqListPrint(&test);
	SeqListRemoveAll(&test, 5);
	SeqListPrint(&test);
	SeqListDestory(&test);
	SeqListPrint(&test);

	system("pause");
	return 0;
}