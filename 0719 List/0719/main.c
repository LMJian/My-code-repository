#include"List.h"

int main()
{
	List test2;
	ListInit(&test2);
	ListPushBack(&test2, 0);
	ListPushBack(&test2, 1);
	ListPushBack(&test2, 1);
	ListPushBack(&test2, 2);
	ListPushBack(&test2, 2);
	ListPushBack(&test2, 2);
	ListPushBack(&test2, 3);
	ListPushBack(&test2, 3);
	ListPushBack(&test2, 3);
	ListPushBack(&test2, 3);
	ListPopDitto(&test2);
	ListPrint(&test2);

	system("pause");
	return 0;
}