#include"SList.h"

int main()
{
	SList test;
	SListNode *pt;
	SListInit(&test);
	SListPushFront(&test, 6);
	SListPushFront(&test, 5);
	SListPushFront(&test, 4);
	SListPushFront(&test, 3);
	SListPushFront(&test, 2);
	SListPushFront(&test, 1);
	SListPrint(&test);
	pt = test._head;
	while (pt->_next != NULL)
		pt = pt->_next;
	pt->_next = test._head->_next;

	printf("%d\n", FindEntrance(&test)->_data);
	system("pause");
	return 0;
}