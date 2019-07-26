#include"SList.h"

void SListInit(SList* plist)
{
	plist->_head = NULL;
}
void SListDestory(SList* plist)//销毁
{
	if (plist->_head != NULL)
	{
		SListNode* pt = plist->_head;
		while (pt != NULL)
		{
			SListNode* t = pt;
			pt = pt->_next;
			free(t);
		}
		plist->_head = NULL;
	}
}
SListNode* BuySListNode(SLTDataType x)//创建结点
{
	SListNode* pt;
	pt = (SListNode*)malloc(sizeof(SListNode));
	if (pt == NULL)
	{
		printf("创建结点失败\n");
		return NULL;
	}
	pt->_data = x;
	pt->_next = NULL;
	return pt;
}
void SListPushFront(SList* plist, SLTDataType x)//头插
{
	SListNode* node = BuySListNode(x);
	if (node != NULL)
	{
		node->_next = plist->_head;
		plist->_head = node;
	}
}
void SListPopFront(SList* plist)//头删
{
	if (plist->_head != NULL)
	{
		SListNode* pt = plist->_head;
		plist->_head = pt->_next;
		free(pt);
	}
}
SListNode* SListFind(SList* plist, SLTDataType x)//查询指定值
{
	SListNode* pt = plist->_head;
	while (pt != NULL)
	{
		if (pt->_data == x)
			return pt;
		else
			pt = pt->_next;
	}
	return NULL;
}

void SListInsertAfter(SListNode* pos, SLTDataType x)//后插
{
	SListNode* node = BuySListNode(x);
	node->_next = pos->_next;
	pos->_next = node;
}

void SListEraseAfter(SListNode* pos)//删除pos+1位置结点
{
	SListNode* pt = pos->_next;
	pos->_next = pos->_next->_next;
	free(pt);
}

void SListRemove(SList* plist, SLTDataType x)//删除值为x的结点
{
	while (plist->_head != NULL&&plist->_head->_data == x)
	{
		SListPopFront(plist);
	}
	if (plist->_head == NULL)
		return;

	SListNode* ph = plist->_head;
	SListNode* pt = ph->_next;
	while (pt != NULL)
	{
		if (pt->_data == x)
		{
			pt = pt->_next;
			SListEraseAfter(ph);
			ph->_next = pt;
			continue;
		}
		pt = pt->_next;
		ph = ph->_next;
	}
}

void SListPrint(SList* plist)
{
	SListNode* pt = plist->_head;
	while (pt != NULL)
	{
		printf("%d ", pt->_data);
		pt = pt->_next;
	}
	printf("\n");
}

void SListReverse(SList* plist)
{
	SListNode* head = plist->_head;
	SListNode* ph = plist->_head;
	SListNode* pt = ph->_next;
	while (pt != NULL)
	{
		ph->_next = pt->_next;
		pt->_next = head;
		head = pt;
		pt = ph->_next;
	}
	plist->_head = head;
}

SListNode* FindCommonNode(SListNode* p1, SListNode* p2)
{
	int len1 = 0, len2 = 0;
	SListNode *pt1 = p1, *pt2 = p2;
	int i;
	while (pt1 != NULL)
	{
		len1++;
		pt1 = pt1->_next;
	}
	while (pt2 != NULL)
	{
		len2++;
		pt2 = pt2->_next;
	}
	if (len1 > len2)
	{
		for (i = 0; i < len1 - len2; i++)
			p1 = p1->_next;
	}
	else
	{
		for (i = 0; i < len2 - len1; i++)
			p2 = p2->_next;
	}
	do
	{
		if (p1 == p2)
			return p1;
		p1 = p1->_next;
		p2 = p2->_next;
	} while (p1 != NULL);
	return NULL;
}
int judgeLoop(SList* list)
{
	SListNode *p1 = list->_head;
	SListNode *p2 = list->_head->_next;
	while (p1 != NULL&&p2 != NULL)
	{
		if (p1 == p2)
			return 1;
		p1 = p1->_next;
		if (p2->_next == NULL)
			return 0;
		p2 = p2->_next->_next;
	}
	return 0;
}

SListNode *FindEntrance(SList *phead)
{
	SListNode *slow = phead->_head;
	SListNode *fast = phead->_head;
	while (slow != NULL&&fast != NULL)
	{
		slow = slow->_next;
		if (fast->_next == NULL)
			return NULL;
		fast = fast->_next->_next;
		if (slow == fast)
		{
			fast = phead->_head;
			while (slow != fast)
			{
				slow = slow->_next;
				fast = fast->_next;
			}
			return slow;
		}
	}
	return NULL;
}