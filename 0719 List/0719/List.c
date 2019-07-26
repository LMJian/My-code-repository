#include"List.h"

void ListInit(List* plist)
{
	plist->_head = (ListNode*)malloc(sizeof(ListNode));
	plist->_head->_next = plist->_head;
	plist->_head->_prev = plist->_head;
}
void ListDestory(List* plist)
{
	ListNode* pt = plist->_head->_next;
	while (pt != plist->_head)
	{
		pt = pt->_next;
		free(pt->_prev);
	}
	plist->_head->_next = plist->_head;
	plist->_head->_prev = plist->_head;
}
void ListPushBack(List* plist, LTDataType x)//Î²²å
{
	ListNode* pt = (ListNode*)malloc(sizeof(ListNode));
	if (pt == NULL)
	{
		printf("Î²²åÊ§°Ü");
		return;
	}
	pt->_data = x;
	plist->_head->_prev->_next = pt;
	pt->_prev = plist->_head->_prev;
	pt->_next = plist->_head;
	plist->_head->_prev = pt;
}
void ListPopBack(List* plist)//Î²É¾
{
	ListNode* pt = plist->_head->_prev;
	pt->_prev->_next = pt->_next;
	pt->_next->_prev = pt->_prev;
	free(pt);
}
void ListPushFront(List* plist, LTDataType x)//Í·²å
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	if (node == NULL)
	{
		printf("Í·²åÊ§°Ü\n");
		return;
	}
	node->_data = x;
	node->_next = plist->_head->_next;
	plist->_head->_next->_prev = node;
	plist->_head->_next = node;
	node->_prev = plist->_head;
}
void ListPopFront(List* plist)//Í·É¾
{
	ListNode* pt = plist->_head->_next;
	plist->_head->_next = pt->_next;
	pt->_next->_prev = plist->_head;
	free(pt);
}
ListNode* ListFind(List* plist, LTDataType x)//²éÕÒ
{
	ListNode* pt = plist->_head->_next;
	while (pt != plist->_head)
	{
		if (pt->_data == x)
			return pt;
		pt = pt->_next;
	}
	return NULL;
}

void ListInsertFront(ListNode* pos, LTDataType x)//Ç°²åÈë
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	if (node == NULL)
	{
		printf("Ç°²åÊ§°Ü\n");
		return;
	}
	node->_data = x;
	pos->_prev->_next = node;
	node->_prev = pos->_prev;
	node->_next = pos;
	pos->_prev = node;
}

void ListInsertBack(ListNode* pos, LTDataType x)//ºó²åÈë
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	if (node == NULL)
	{
		printf("Ç°²åÊ§°Ü\n");
		return;
	}
	node->_data = x;
	node->_next = pos->_next;
	pos->_next->_prev = node;
	pos->_next = node;
	node->_prev = pos;
}
void ListErase(ListNode* pos)//É¾³ı½Úµã
{
	pos->_prev->_next = pos->_next;
	pos->_next->_prev = pos->_prev;
	free(pos);
}
void ListRemove(List* plist, LTDataType x)//É¾³ıÖµÎªxµÄ½áµã
{
	ListNode* pt = plist->_head->_next;
	while (pt != plist->_head)
	{
		if (pt->_data == x)
		{
			pt->_prev->_next = pt->_next;
			pt->_next->_prev = pt->_prev;
			ListNode* node = pt;
			pt = pt->_next;
			free(node);
			continue;
		}
		pt = pt->_next;
	}
}
void ListPrint(List* plist)
{
	ListNode* pt = plist->_head->_next;
	while (pt != plist->_head)
	{
		printf("%d ", pt->_data);
		pt = pt->_next;
	}
	printf("\n");
}

void ListMerge(List* plist1, List* plist2)
{
	ListNode* p1 = plist1->_head->_next;
	ListNode* p2 = plist2->_head->_next;
	ListNode* pt2 = p2->_next;
	while (p2 != plist2->_head&&p1 != plist1->_head)
	{
		if (p1->_data > p2->_data)
		{
			p1->_prev->_next = p2;
			p2->_prev = p1->_prev;
			p2->_next = p1;
			p1->_prev = p2;
			p2 = pt2;
			pt2 = p2->_next;
		}
		else
		{
			p1 = p1->_next;
		}
	}
	if (p2 != plist2->_head)
	{
		plist1->_head->_prev->_next = p2;
		p2->_prev = plist1->_head->_prev;
		plist2->_head->_prev->_next = plist1->_head;
		plist1->_head->_prev = plist2->_head->_prev;
	}
}
List* ListPopDitto(List* plist)
{
	ListNode* pt = plist->_head->_next;
	while (pt->_next != plist->_head)
	{
		if (pt->_data == pt->_next->_data)
		{
			pt->_next = pt->_next->_next;
			pt->_next->_prev = pt;
			continue;
		}
		pt = pt->_next;
	}
	return plist;
}
