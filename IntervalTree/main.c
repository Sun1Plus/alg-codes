#include<stdio.h>
#include"treestruct.h"

IBnode* nil;

void InsertKey(IBnode** root, int interval_low, int interval_high)
{
	if (interval_low >= interval_high)
	{
		printf("InsertKey ERROR: This is not a interval,the low is larger than the high!");
	}
	else
	{
		IBnode* node_pointer = (IBnode*)malloc(sizeof(IBnode));
		node_pointer->int_low = interval_low;
		node_pointer->int_high = interval_high;
		node_pointer->max = interval_high;
		node_pointer->parent = nil;
		node_pointer->left = nil;
		node_pointer->right = nil;
		node_pointer->color = RED;

		IBInsert(root, node_pointer);
	}
}

//检测重叠
int IsOverride(int a1, int a2, int b1, int b2)	//a1,a2代表区间A的低端和高端；b1，b2代表B区间的低端和高端
{
	if (a2<b1 || a1>b2)
		return 0;		  //不重叠
	else
		return 1;         //重叠		
}

IBnode* IntervalSearch(IBnode* root, int low, int high)
{
	IBnode* x = root;
	while (x != nil && IsOverride(low, high, x->int_low, x->int_high) == 0)
	{
		printf("当前节点区间：%d - %d，未重叠\n", x->int_low, x->int_high);
		if (x->left != nil && x->left->max >= low)
			x = x->left;
		else
			x = x->right;
	}
	return x;
}


int main()
{
	nil = (IBnode*)malloc(sizeof(IBnode));
	nil->color = BLACK;
	nil->parent = NULL;
	nil->left = NULL;
	nil->right = NULL;
	nil->int_low = -1;
	nil->int_high = -1;
	nil->max = -1;

	IBnode* root = nil;
	InsertKey(&root, 4, 6);
	InsertKey(&root, 3, 5);
	InsertKey(&root, 2, 9);
	InsertKey(&root, 5, 9);

	InsertKey(&root, 6, 8);
	InsertKey(&root, 8, 9);
	InsertKey(&root, 1, 2);
	InsertKey(&root, 12, 13);
	InsertKey(&root, 19, 45);
	InsertKey(&root, 13, 32);
	InsertKey(&root, 7, 8);
	InsertKey(&root, 23, 24);
	InsertKey(&root, 8, 9);

	IBnode* result = IntervalSearch(root,11,12 );

	if (result != nil)
	{
		printf("找到的重叠区间： ");
		printf("%d - %d\n", result->int_low, result->int_high);
	}
	else
	{
		printf("未找到重叠区间\n");
	}

	system("pause");
	return 0;
}