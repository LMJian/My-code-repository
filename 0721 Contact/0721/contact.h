#ifndef _CONTACT_H_
#define _CONTACT_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NAME_SIZE 20
#define TEL_SIZE 20
#define ADDR_SIZE 30

typedef struct person {
	char name[NAME_SIZE];
	char sex;
	int age;
	char telphone[TEL_SIZE];
	char address[ADDR_SIZE];
	struct person *_next;
	struct person *_prev;
}person;

typedef struct contact {
	person *head;
}contact;

void contactInit(contact *list);
void Add(contact *list);
void Del(contact *list);
void Search(contact *list);
void Mod(contact *list);
void Show(contact *list);
void Clear(contact *list);
void Sort(contact *list);
int FindSame(char *str1, char *str2);
#endif