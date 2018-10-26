#include<stdio.h>
#include"tree_struct.h"

RBnode* nil;

void InsertKey(RBnode** root, int key)
{
	RBnode* node_pointer = (RBnode*)malloc(sizeof(RBnode));
	node_pointer->key = key;
	node_pointer->parent = nil;
	node_pointer->left = nil;
	node_pointer->right = nil;
	node_pointer->color = RED;   //默认红色

	RBInsert(root, node_pointer); //调用插入
}

void print_tree(RBnode* root)
{
	if (root != nil)
	{
		print_tree(root->left);
		printf(" %d ", root->key);
		print_tree(root->right);
	}
}


int main()
{
	nil = (RBnode*)malloc(sizeof(RBnode));
	nil->color = BLACK;
	nil->parent = NULL;
	nil->left = NULL;
	nil->right = NULL;
	nil->key = -1;

	RBnode* root = nil;
	InsertKey(&root, 4);
	InsertKey(&root, 3);
	InsertKey(&root, 2);
	InsertKey(&root, 5);
	print_tree(root);

	InsertKey(&root, 6);
	InsertKey(&root, 9);
	InsertKey(&root, 1);
	print_tree(root);

	system("pause");
	return 0;
}
