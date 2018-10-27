#include<stdio.h>
#include<stdlib.h>
#include"tree_struct.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//这里的指针更改都是要成对出现的，改完孩子节点的指向，要记得更改孩子节点的父指针指向。
//在左旋时，x在y的左上方。
void LeftRotate(RBnode** root, RBnode* nodex)
{
	if (nodex->right != nil)
	{
		//step1
		RBnode *nodey = nodex->right;

		//step2
		nodex->right = nodey->left;
		if (nodex->left != nil)
			nodey->left->parent = nodex;

		//step3
		nodey->parent = nodex->parent;
		if (nodex->parent == nil)		//x is root
		{
			*root = nodey;
		}
		else if (nodex == (nodex->parent)->left)
		{
			nodex->parent->left = nodey;
		}
		else
		{
			nodex->parent->right = nodey;
		}

		//step4
		nodey->left = nodex;
		nodex->parent = nodey;
	}
	else
	{
		printf("在左旋时，x节点的右孩子为空，失败！");
		system("pause");
	}
}


//右旋时，y在x的右上方，见PPT14。
void RightRotate(RBnode** root, RBnode* nodey)
{
	if (nodey->left != nil)
	{
		//step1
		RBnode* nodex = nodey->left;

		//step2
		nodey->left = nodex->right;
		if (nodex->right != nil)
			nodex->right->parent = nodey;

		//step3
		nodex->parent = nodey->parent;
		if (nodey->parent == nil)
		{
			*root = nodex;
		}
		else if (nodey->parent == nodey->parent->left)
		{
			nodey->parent->left = nodex;
		}
		else
		{
			nodey->parent->right = nodex;
		}

		//step4
		nodex->right = nodey;
		nodey->parent = nodex;
	}
	else
	{
		printf("在右旋时，x节点的右孩子为空，失败！");
		system("pause");
	}
}
//end rotation.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//插入算法
//step1：将z节点按BST规则插入；
//step2：将z涂红；
//step3：调整使其满足红黑树性质

//插入时你自己考虑一下什么时候创建节点并分配内存单元
void RBInsert(RBnode** root, RBnode* nodez)
{
	RBnode* nodey = nil;		//y用于记录：当前扫描节点的父节点
	RBnode* nodex = *root;		//从root开始扫描

	while (nodex != nil)		//查找插入位置
	{
		nodey = nodex;
		if (nodez->key < nodex->key)
			nodex = nodex->left;
		else
			nodex = nodex->right;
	}

	nodez->parent = nodey;		//y是z的父节点
	if (nodey == nil)			//z是根
		*root = nodez;	
	else
	{
		if (nodez->key < nodey->key)	//左子插入
			nodey->left = nodez;
		else							//右子插入
			nodey->right = nodez;
	}

	nodez->left = nil;
	nodez->right = nil;
	nodez->color = RED;

	RBInsertFixup(root, nodez);
}


//插入调整算法
void RBInsertFixup(RBnode** root, RBnode* nodez)
{
	while (1)
	{
		if (*root == nodez)		//nodez为根节点，直接涂黑
		{
			nodez->color = BLACK;
			break;
		}
		else if ((nodez->parent->color) == BLACK)
		{
			//若父节点为黑，无需调整
			break;
		}
		else
		{
			//父节点为红，违反性质4
			if (nodez->parent == ((nodez->parent)->parent)->left)		//case1,2,3
			{
				RBnode* nodey = ((nodez->parent)->parent)->right;		//y是z的叔叔
				if (nodey->color == RED)			//case1
				{
					nodey->color = BLACK;
					nodez->parent->color = BLACK;
					((nodez->parent)->parent)->color = RED;
					nodez = ((nodez->parent)->parent);					//通过循环将矛盾上移
				}
				else								//case2 or case3
				{
					if (nodez == nodez->parent->right)	//case2
					{
						nodez = nodez->parent;
						LeftRotate(root, nodez);
					}
					//case3
					nodez->parent->color = BLACK;
					((nodez->parent)->parent)->color = RED;
					RightRotate(root, ((nodez->parent)->parent));		//z的父节点为黑，将退出循环
				}
			}
			else														//case4,5,6
			{	//if (nodez->parent = ((nodez->parent)->parent)->right)
				RBnode* nodey = ((nodez->parent)->parent)->left;		//y是z的叔叔

				if (nodey->color == RED)			//case4
				{
					nodey->color = BLACK;
					nodez->parent->color = BLACK;
					((nodez->parent)->parent)->color = RED;
					nodez = ((nodez->parent)->parent);					//通过循环将矛盾上移
				}
				else								//case5 or case6	
				{
					if (nodez == nodez->parent->left)	//case5
					{
						nodez = nodez->parent;
						RightRotate(root, nodez);
					}
					//case6
					nodez->parent->color = BLACK;
					((nodez->parent)->parent)->color = RED;
					LeftRotate(root, ((nodez->parent)->parent));		//z的父节点为黑，将退出循环
				}
			}
		}
	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
RBnode* TreeSuccessor(RBnode* root)
{
	RBnode* leftfirst = root;
	while (leftfirst->left != nil)
	{
		leftfirst = leftfirst->left;
	}
	return leftfirst;
}


//删除算法
//记得删除后，将返回的指针释放内存。
RBnode* RBDelete(RBnode** root, RBnode* nodez)
{
	RBnode *nodex = nil, *nodey = nil;			//x是连接点，y是真正物理删除节点，z是指向删除
	if (nodez->left == nil || nodez->right == nil)	//case1,2
		nodey = nodez;
	else												//case3
		nodey = TreeSuccessor(nodez);		//y是z的中序后继
	//此时，y统一地是x的父节点且是要删除的节点
	//x是待连接到y->parent的节点，一下要确定x
	if (nodey->left != nil)
		nodex = nodey->left;
	else
		nodex = nodey->right;

	//一下处理：用x取代y与y的双亲连接
	nodex->parent = nodey->parent;
	if (nodey->parent == nil)
		*root = nodex;
	else
	{
		if (nodey == nodey->parent->left)
			nodey->parent->left = nodex;
		else
			nodey->parent->right = nodex;
	}
	if (nodey != nodez)
		nodez->key = nodey->key;
	if (nodey->color == BLACK)	//如果删除的节点是红色节点，则无需调整
		RBDeleteFixup(*root, nodex);
	return nodey;
}

//删除调整
//仔细考虑特殊临界情况，比如nil的父指针，函数传值修改无效等。
void  RBDeleteFixup(RBnode** root, RBnode* nodex)
{
	while (1)		//x始终作为矛盾的存在。
	{
		if (nodex == *root)				//x是根节点，直接移去一层黑色，空操作
			break;
		else if (nodex->color == RED)	//x节点为红，涂黑即终止
		{
			nodex->color = BLACK;
			break;
		}
		else							//x节点非根，且为黑色，则通过变色、旋转解决问题。
		{								//x是双黑节点。
			if (nodex == nodex->parent->left)		//case1,2,3,4
			{
				RBnode* nodew = nodex->parent->right;	//w是x的兄弟节点
				if (nodew->color == RED)			//case1
				{
					nodew->color = BLACK;
					nodex->parent->color = RED;
					LeftRotate(root, nodex->parent);
					//这里的w节点不用赋值，while结束它自动消失，在下一次循环自动指到兄弟节点
				}
				else								//case2,3,4,兄弟节点w是黑
				{
					if (nodew->left->color == BLACK && nodew->right->color == BLACK)	//case2
					{
						nodew->color = RED;
						nodex = nodex->parent;
					}
					else
					{
						if (nodew->right->color == BLACK)	//case3转化成case4处理
						{
							nodew->left->color = BLACK;
							nodew->color = RED;
							RightRotate(root, nodew);
							nodew = nodex->parent->right;	//w指向新的兄弟
						}
						//throw problem
						if (nodew->right->color != RED)		
						{
							printf("删除时case3转化case4出问题");
							system("pause");
						}
						//case4
						//这里小心nil的父指针，肯定会报错。
						nodew->color = nodex->parent->color;
						nodex->parent->color = BLACK;
						nodew->right->color = BLACK;
						LeftRotate(root, nodex->parent);

						break;
					}
				}
			}

			else									//case5,6,7,8
			{

			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////