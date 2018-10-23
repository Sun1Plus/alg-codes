#include<stdio.h>
#include<stdlib.h>
#define RED 0
#define BLACK 1

typedef struct RB_node
{
	int key;
	int color;
	struct RB_node* left, *right;
	struct RB_node* parent;
}RBnode;




