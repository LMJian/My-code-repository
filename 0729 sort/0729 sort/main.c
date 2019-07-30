#include"sort.h"

int main()
{
	int arr[] = { 6, 25, 24, 9, 12, 55, 56 };
	directInsertionSort(arr, 7);
	//sellSort(arr, 7);
	for (int i = 0; i < 7; i++)
		printf("%d ", arr[i]);
	printf("\n");
	/*int arr[] = { 1, 4, 0, 2, 9, 7, 8, 6, 3, 5 };
	//mergeSort(arr, 10);
	QSort(arr, 10);
	for (int i = 0; i < 10; i++)
		printf("%d ", arr[i]);*/
	system("pause");
	return 0;
}