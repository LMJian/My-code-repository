#define _CRT_SECURE_NO_WARNINGS 1
#include"contact.h"

void Menu()
{
	printf("####################################\n");
	printf("###   1 Add   2 Del   3 Search   ###\n");
	printf("###   4 Mod   5 Show  6 Clear    ###\n");
	printf("###   7 Sort  8 Exit             ###\n");
	printf("####################################\n");
	printf("Please Select:");
}

int main()
{
	int key = 1;
	int num;
	contact test;
	contactInit(&test);//初始化头结点
	while (key)
	{
		Menu();
		scanf("%d", &num);
		switch (num)
		{
		case 1:
			Add(&test);
			break;
		case 2:
			Del(&test);
			break;
		case 3:
			Search(&test);
			break;
		case 4:
			Mod(&test);
			break;
		case 5:
			Show(&test);
			break;
		case 6:
			Clear(&test);
			break;
		case 7:
			Sort(&test);
			break;
		case 8:
			key = 0;
			break;
		default:
			printf("Incorrect input\n");
			break;
		}
	}
	system("pause");
	return 0;
}