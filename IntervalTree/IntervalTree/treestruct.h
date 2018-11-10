#ifndef TREE_STRUCT_H
#define TREE_STRUCT_H

#include<stdio.h>
#include<stdlib.h>
#define RED 0
#define BLACK 1

typedef struct IB_node
{
	int int_low;
	int int_high;
	int max;
	int color;
	struct IB_node* left, *right;
	struct IB_node* parent;
}IBnode;

extern IBnode* nil;

void LeftRotate(IBnode** root, IBnode* nodex);
void RightRotate(IBnode** root, IBnode* nodey);
void IBInsert(IBnode** root, IBnode* nodez);
void IBInsertFixup(IBnode** root, IBnode* nodez);
IBnode* IBDelete(IBnode** root, IBnode* nodez);
void IBDeleteFixup(IBnode** root, IBnode* nodex);

#endif