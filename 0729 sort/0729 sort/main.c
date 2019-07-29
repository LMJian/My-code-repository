#include"sort.h"

int main()
{
	int arr[] = { 1, 4, 0, 2, 9, 7, 8, 6, 3, 5 };
	//mergeSort(arr, 10);
	QSort(arr, 10);
	for (int i = 0; i < 10; i++)
		printf("%d ", arr[i]);
	system("pause");
	return 0;
}