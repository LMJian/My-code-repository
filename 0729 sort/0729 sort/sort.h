#ifndef _SORT_H_
#define _SORT_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void dealMergeSort(int *arr,int *tmp,int start,int end);
void mergeSort(int *arr,int n);
void dealQSort(int *arr, int left, int right);
void QSort(int *arr, int n);

void directInsertionSort(int *arr, int n);
void sellSort(int *arr, int n);




#endif/*_SORT_H_*/