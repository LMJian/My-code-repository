#define _CRT_SECURE_NO_WARNINGS 1
#include"contact.h"

void contactInit(contact *list)//��ʼ��ͷ���
{
	list->head = (person*)malloc(sizeof(person));
	list->head->_next = list->head;
	list->head->_prev = list->head;
}

void Add(contact *list)//����
{
	person *pt = (person*)malloc(sizeof(person));
	printf("Please Enter name,sex,age,tel,addr\n");
	scanf("%s", pt->name);
	getchar();
	scanf("%c", &(pt->sex));
	scanf("%d", &(pt->age));
	scanf("%s", pt->telphone);
	scanf("%s", pt->address);
	list->head->_prev->_next = pt;
	pt->_prev = list->head->_prev;
	pt->_next = list->head;
	list->head->_prev = pt;
}

void Del(contact *list)//ɾ��
{
	person* pt = list->head->_next;
	char name[20] = "";
	printf("Please Enter Del name\n");
	scanf("%s", name);
	while (pt != list->head)
	{
		if (strcmp(pt->name, name) == 0)
		{
			pt->_prev->_next = pt->_next;
			pt->_next->_prev = pt->_prev;
			free(pt);
			return;
		}
		pt = pt->_next;
	}
	printf("ɾ��ʧ�ܣ�û�д���\n");
}
int FindSame(char *str1, char *str2)
{
	char *strt;
	while (*str1 != '\0')
	{
		while (*str1 != '\0'&&*str1 != *str2)
			str1++;
		strt = str2;
		while (*str1 != '\0'&&*strt != '\0')
		{
			if (*strt != *str1)
				break;
			strt++;
			str1++;
		}
		if (*strt == '\0')
			return 1;
	}
	return 0;
}
void Search(contact *list)//ģ������
{
	char name[20] = "";
	person *pt = list->head->_next;
	printf("Please Enter Search Keyword Name\n");
	scanf("%s", name);
	while (pt != list->head)
	{
		if (FindSame(pt->name, name) == 1)
		{
			printf("%-10s%-5c%-10d%-10s%-10s\n", pt->name, pt->sex, pt->age, pt->telphone, pt->address);
		}
		pt = pt->_next;
	}
}

void Mod(contact *list)//�޸�
{
	char name[20] = "";
	person *pt = list->head->_next;
	printf("Please Enter Mod name\n");
	scanf("%s", name);
	while (pt != list->head)
	{
		if (strcmp(pt->name, name) == 0)
		{
			printf("Please Enter New name, sex, age, tel, addr\n");
			scanf("%s", pt->name);
			getchar();
			scanf("%c", &(pt->sex));
			scanf("%d", &(pt->age));
			scanf("%s", pt->telphone);
			scanf("%s", pt->address);
			return;
		}
		pt = pt->_next;
	}
	printf("�޸�ʧ�ܣ�û�д���\n");
}

void Show(contact *list)//���
{
	person *pt = list->head->_next;
	while (pt != list->head)
	{
		printf("%-10s%-5c%-10d%-10s%-10s\n", pt->name, pt->sex, pt->age, pt->telphone, pt->address);
		pt = pt->_next;
	}
}

void Clear(contact *list)//���
{
	person *pt = list->head->_next;
	person *ptt;
	while (pt != list->head)
	{
		ptt = pt->_next;
		free(pt);
		pt = ptt;
	}
	list->head->_next = list->head;
	list->head->_prev = list->head;
}

void Sort(contact *list)//����
{
	person *p1 = list->head->_next->_next;//�ڶ������
	person *p2, *p3;
	while (p1 != list->head)
	{
		p2 = p1;
		while (p2 != list->head->_next&&strcmp(p2->_prev->name, p2->name) == 1)
		{
			p3 = p2->_prev;//p3��p2ǰ�棬���������Ҫ����λ��
			p3->_next = p2->_next;
			p2->_next->_prev = p3;
			p3->_prev->_next = p2;
			p2->_prev = p3->_prev;
			p2->_next = p3;
			p3->_prev = p2;
		}
		p1 = p1->_next;
	}
	Show(list);
}