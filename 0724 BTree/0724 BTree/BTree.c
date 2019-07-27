#include"BTree.h"

// 通过前序遍历的数组"ABD##E#H##CF##G##"构建二叉树 
BTNode* BinaryTreeCreate(BTDataType* a)
{
	static int i = 0;
	if (a[i] == '#')
	{
		i++;
		return NULL;
	}
	else
	{
		BTNode *node = (BTNode*)malloc(sizeof(BTNode));
		node->_Bdata = a[i];
		i++;
		node->_left = BinaryTreeCreate(a);
		node->_right = BinaryTreeCreate(a);
		return node;
	}
}
void BinaryTreeDestory(BTNode** root)
{
	if ((*root)->_left != NULL)
		BinaryTreeDestory(&(*root)->_left);
	if ((*root)->_right != NULL)
		BinaryTreeDestory(&(*root)->_right);
	free(*root);
}
int BinaryTreeSize(BTNode* root)
{
	int count = 0;
	if (root == NULL)
		count = 0;
	else
		count = 1 + BinaryTreeSize(root->_left) + BinaryTreeSize(root->_right);
	return count;
}
int BinaryTreeLeafSize(BTNode* root)
{
	int count = 0;
	if (root == NULL)
		count = 0;
	else if (root->_left == NULL&&root->_right == NULL)
		count = 1;
	else
		count = BinaryTreeLeafSize(root->_left) + BinaryTreeLeafSize(root->_right);
	return count;
}
int BinaryTreeLevelKSize(BTNode* root, int k)//计算第k层结点的个数
{
	int count = 0;
	if (root == NULL)
		count = 0;
	else if (k == 1)
		count = 1;
	else
		count = BinaryTreeLevelKSize(root->_left, k - 1) + BinaryTreeLevelKSize(root->_right, k - 1);
	return count;
}
BTNode* BinaryTreeFind(BTNode* root, BTDataType x)
{
	static BTNode* bn = NULL;
	if (root->_Bdata == x)
	{
		bn = root;
		return root;
	}
	if (root->_left != NULL)
		BinaryTreeFind(root->_left, x);
	if (root->_right != NULL)
		BinaryTreeFind(root->_right, x);
	return bn;
}
// 遍历 
void BinaryTreePrevOrder(BTNode* root)
{
	if (root != NULL)
	{
		printf("%c", root->_Bdata);
		BinaryTreePrevOrder(root->_left);
		BinaryTreePrevOrder(root->_right);
	}
}
void BinaryTreeInOrder(BTNode* root)
{
	if (root != NULL)
	{
		BinaryTreeInOrder(root->_left);
		printf("%c", root->_Bdata);
		BinaryTreeInOrder(root->_right);
	}
}
void BinaryTreePostOrder(BTNode* root)
{
	if (root != NULL)
	{
		BinaryTreePostOrder(root->_left);
		BinaryTreePostOrder(root->_right);
		printf("%c", root->_Bdata);
	}
}
void QueueInit(Queue *que, BTNode *test)
{
	QueueNode *node = (QueueNode*)malloc(sizeof(QueueNode));
	node->_Qdata = test;
	node->_next = NULL;
	que->_front = que->_rear = node;
}
void QueuePush(Queue *pq, BTNode *node)
{
	QueueNode *Qnode = (QueueNode*)malloc(sizeof(QueueNode));
	pq->_rear->_next = Qnode;
	Qnode->_next = NULL;
	Qnode->_Qdata = node;
	pq->_rear = pq->_rear->_next;
}
// 层序遍历 
void BinaryTreeLevelOrder(BTNode* root)
{
	Queue *pq = (Queue*)malloc(sizeof(Queue));
	QueueInit(pq, root);
	while (pq->_front != NULL)
	{
		if (pq->_front->_Qdata->_left != NULL)
			QueuePush(pq, pq->_front->_Qdata->_left);
		if (pq->_front->_Qdata->_right != NULL)
			QueuePush(pq, pq->_front->_Qdata->_right);
		printf("%c", pq->_front->_Qdata->_Bdata);
		QueueNode *pt = pq->_front;
		pq->_front = pq->_front->_next;
		free(pt);
	}
	printf("\n");
}
// 判断二叉树是否是完全二叉树 
int BinaryTreeComplete(BTNode* root)
{
	Queue *pq = (Queue*)malloc(sizeof(Queue));
	QueueInit(pq, root);
	int key = 0;
	while (pq->_front != NULL)
	{
		if (pq->_front->_Qdata->_left == NULL&&pq->_front->_Qdata->_right != NULL)
			return 0;
		if (key && (pq->_front->_Qdata->_left != NULL || pq->_front->_Qdata->_right != NULL))
			return 0;
		if (pq->_front->_Qdata->_right == NULL)
			key = 1;

		if (pq->_front->_Qdata->_left != NULL)
			QueuePush(pq, pq->_front->_Qdata->_left);
		if (pq->_front->_Qdata->_right != NULL)
			QueuePush(pq, pq->_front->_Qdata->_right);
		QueueNode *pt = pq->_front;
		pq->_front = pq->_front->_next;
		free(pt);
	}
	return 1;
}
void BinaryTreePrevOrderNonR(BTNode* root)
{
	Stack test;
	StackInit(&test, root);
	while (!StackEmpty(&test) || root != NULL)
	{
		printf("%c", root->_Bdata);
		if (root->_right != NULL)
			StackPush(&test, root->_right);
		if (root->_left != NULL)
			root = root->_left;
		else
		{
			root = StackTop(&test);
			StackPop(&test);
		}
	}
	StackDestory(&test);
}
void BinaryTreeInOrderNonR(BTNode* root)
{
	Stack test;
	StackInit(&test, root);
	while (!StackEmpty(&test) || root != NULL)
	{
		while (root != NULL)
		{
			StackPush(&test, root);
			root = root->_left;
		}
		root = StackTop(&test);
		StackPop(&test);
		putchar(root->_Bdata);
		root = root->_right;
	}
	StackDestory(&test);
}
void BinaryTreePostOrderNonR(BTNode* root)
{
	int bool[26] = { 0 };
	Stack test;
	StackInit(&test, root);
	while (!StackEmpty(&test) || root != NULL)
	{
		while (root != NULL)
		{
			if (bool[root->_Bdata - 'A'] == 0)
			{
				StackPush(&test, root);
				bool[root->_Bdata - 'A'] = 1;
			}
			if (root->_right != NULL)
			{
				if (bool[root->_right->_Bdata - 'A'] == 0)
				{
					StackPush(&test, root->_right);
					bool[root->_right->_Bdata - 'A'] = 1;
				}
			}
			if (root->_left != NULL&&bool[root->_left->_Bdata - 'A'] == 1)
				break;
			root = root->_left;
		}
		root = StackTop(&test);
		if (root->_left != NULL&&bool[root->_left->_Bdata - 'A'] == 0)
			continue;
		if (root->_right == NULL||bool[root->_right->_Bdata - 'A'] == 1)
		{
			StackPop(&test);
			putchar(root->_Bdata);
			root = StackTop(&test);
		}
		if (root != NULL&&root->_right != NULL&&bool[root->_right->_Bdata - 'A'] == 0)
		{
			root = root->_right;
		}
	}
	StackDestory(&test);
}
void StackInit(Stack* ps, BTNode *test)
{
	int size = BinaryTreeSize(test);
	ps->_a = (STDataType*)malloc(size*sizeof(STDataType));
	ps->_capacity = size;
	ps->_top = -1;
}
void StackDestory(Stack* ps)
{
	free(ps->_a);
	ps->_capacity = 0;
	ps->_top = -1;
}
void StackPush(Stack* ps, STDataType x)
{
	ps->_top++;
	ps->_a[ps->_top] = x;
}
void StackPop(Stack* ps)
{
	if (ps->_top > -1)
		ps->_top--;
}
STDataType StackTop(Stack* ps)
{
	if (ps->_top == -1)
		return NULL;
	return ps->_a[ps->_top];
}
int StackEmpty(Stack* ps)
{
	if (ps->_top == -1)
		return 1;
	return 0;
}
int StackSize(Stack* ps)
{
	return ps->_top + 1;
}
