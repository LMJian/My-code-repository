#include"BTree.h"

int main()
{
	BTNode *test = BinaryTreeCreate("ABDF####CE#GH##I#J###");
	printf("%d\n", BinaryTreeSize(test));
	printf("%d\n", BinaryTreeLeafSize(test));
	//printf("%d\n", BinaryTreeLeve1KSize(test,5));
	printf("%p\n", BinaryTreeFind(test, 'D'));
	BinaryTreePrevOrder(test);
	printf("\n");
	BinaryTreePrevOrderNonR(test);
	printf("\n");
	BinaryTreeInOrder(test);
	printf("\n");
	BinaryTreeInOrderNonR(test);
	printf("\n");
	BinaryTreePostOrder(test);
	printf("\n");
	BinaryTreePostOrderNonR(test);
	printf("\n");
	BinaryTreeLevelOrder(test);
	printf("%d\n", BinaryTreeComplete(test));
	printf("%d\n", BinaryTreeLevelKSize(test, 7));
	BinaryTreeDestory(&test);
	return 0;
}