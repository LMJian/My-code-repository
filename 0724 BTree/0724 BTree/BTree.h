#ifndef _BTREE_H_
#define _BTREE_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef char BTDataType;
typedef struct BinaryTreeNode 
{ 
	BTDataType _Bdata;    
	struct BinaryTreeNode* _left;    
	struct BinaryTreeNode* _right; 
}BTNode;
typedef BTNode* DataType;
typedef struct QueueNode
{
	DataType _Qdata;
	struct QueueNode* _next;
}QueueNode;
typedef struct Queue
{
	QueueNode* _front; // 队头
	QueueNode* _rear;  // 队尾
}Queue;
typedef BTNode* STDataType;
typedef struct Stack 
{
	STDataType* _a;
	int _top;       // 栈顶
	int _capacity;  // 容量 
}Stack;
void StackInit(Stack* ps, BTNode *test);
void StackDestory(Stack* ps);
void StackPush(Stack* ps, STDataType x); 
void StackPop(Stack* ps); 
STDataType StackTop(Stack* ps); 
int StackEmpty(Stack* ps); 
int StackSize(Stack* ps);

// 通过前序遍历的数组"ABD##E#H##CF##G##"构建二叉树 
BTNode* BinaryTreeCreate(BTDataType* a);
void BinaryTreeDestory(BTNode** root);

int BinaryTreeSize(BTNode* root); 
int BinaryTreeLeafSize(BTNode* root); 
int BinaryTreeLevelKSize(BTNode* root, int k);

BTNode* BinaryTreeFind(BTNode* root, BTDataType x);
// 遍历 
void BinaryTreePrevOrder(BTNode* root); 
void BinaryTreeInOrder(BTNode* root); 
void BinaryTreePostOrder(BTNode* root);

void QueueInit(Queue *que, BTNode *test);
void QueuePush(Queue *pq, BTNode *node);
void BinaryTreeLevelOrder(BTNode* root);
// 非递归遍历 
// 层序遍历 
void BinaryTreeLevelOrder(BTNode* root); 
// 判断二叉树是否是完全二叉树 
int BinaryTreeComplete(BTNode* root);

void BinaryTreePrevOrderNonR(BTNode* root); 
void BinaryTreeInOrderNonR(BTNode* root); 
void BinaryTreePostOrderNonR(BTNode* root);

#endif /*_BTREE_H_*/