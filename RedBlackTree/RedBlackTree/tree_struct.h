#ifndef TREE_STRUCT_H
#define TREE_STRUCT_H

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

extern RBnode* nil;

void LeftRotate(RBnode** root, RBnode* nodex);
void RightRotate(RBnode** root, RBnode* nodey);
void RBInsert(RBnode** root, RBnode* nodez);
void RBInsertFixup(RBnode** root, RBnode* nodez);
RBnode* RBDelete(RBnode** root, RBnode* nodez);
void RBDeleteFixup(RBnode** root, RBnode* nodex);

#endif