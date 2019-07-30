#include"sort.h"

void dealMergeSort(int *arr, int *tmp, int start, int end)
{
	if (start >= end)
		return;
	int mid = (start + end) / 2;
	dealMergeSort(arr, tmp, start, mid);
	dealMergeSort(arr, tmp, mid+1, end);

	int a = start;
	int b = mid + 1;
	int c = a;
	for (; a <= mid&&b <= end; c++)
	{
		if (arr[a] < arr[b])
		{
			tmp[c] = arr[a];
			a++;
		}
		else
		{
			tmp[c] = arr[b];
			b++;
		}
	}
	for (; a <= mid; a++, c++)
		tmp[c] = arr[a];
	for (; b <= end; b++, c++)
		tmp[c] = arr[b];
	for (int i = start; i <= end; i++)
		arr[i] = tmp[i];
}
void mergeSort(int *arr, int n)
{
	int *tmp = (int*)malloc(sizeof(int)*n);
	dealMergeSort(arr, tmp, 0, n - 1);
	free(tmp);
}
void dealQSort(int *arr, int left, int right)
{
	if (left >= right)
		return;
	int i = left, j = right;
	int flag = 1;
	while (i < j)
	{
		if (arr[i] > arr[j])
		{
			int t = arr[i];
			arr[i] = arr[j];
			arr[j] = t;
			flag = !flag;
		}
		flag ? i++ : j--;
	}
	dealQSort(arr, left, i - 1);
	dealQSort(arr, i + 1, right);
	/*int mid = left;
	int a = left, b = right;
	while (left < right)
	{
		while (left < right)
		{
			if (arr[right] < arr[mid])
			{
				int t = arr[right];
				arr[right] = arr[mid];
				arr[mid] = t;
				mid = right;
				break;
			}
			right--;
		}
		while (left < right)
		{
			if (arr[left] > arr[mid])
			{
				int t = arr[left];
				arr[left] = arr[mid];
				arr[mid] = t;
				mid = left;
				break;
			}
			left++;
		}
	}
	if (a < left - 1)
		dealQSort(arr, a, left - 1);
	if (left + 1 < b)
		dealQSort(arr, left + 1, b);*/
}
void QSort(int *arr, int n)
{
	dealQSort(arr, 0, n - 1);
}

void directInsertionSort(int *arr, int n)
{
	int i, j, t;
	for (i = 1; i < n; i++)
	{
		j = i;
		while (j>0 && arr[j] < arr[j - 1])
		{
			t = arr[j];
			arr[j] = arr[j - 1];
			arr[j - 1] = t;
			j--;
		}
	}
}
void sellSort(int *arr, int n)
{
	int gap = n / 2;
	while (gap >= 1)
	{
		int i, j, t;
		for (i = gap; i < n; i++)
		{
			j = i;
			while (j>0 && arr[j] < arr[j - gap])
			{
				t = arr[j];
				arr[j] = arr[j - gap];
				arr[j - gap] = t;
				j = j - gap;
			}
		}
		gap = gap / 2;
	}
}
