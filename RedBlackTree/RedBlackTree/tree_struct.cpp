#include<stdio.h>
#include<stdlib.h>
#include"tree_struct.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�����ָ����Ķ���Ҫ�ɶԳ��ֵģ����꺢�ӽڵ��ָ��Ҫ�ǵø��ĺ��ӽڵ�ĸ�ָ��ָ��
//������ʱ��x��y�����Ϸ���
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
		printf("������ʱ��x�ڵ���Һ���Ϊ�գ�ʧ�ܣ�");
		system("pause");
	}
}


//����ʱ��y��x�����Ϸ�����PPT14��
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
		printf("������ʱ��x�ڵ���Һ���Ϊ�գ�ʧ�ܣ�");
		system("pause");
	}
}
//end rotation.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�����㷨
//step1����z�ڵ㰴BST������룻
//step2����zͿ�죻
//step3������ʹ��������������

//����ʱ���Լ�����һ��ʲôʱ�򴴽��ڵ㲢�����ڴ浥Ԫ
void RBInsert(RBnode** root, RBnode* nodez)
{
	RBnode* nodey = nil;		//y���ڼ�¼����ǰɨ��ڵ�ĸ��ڵ�
	RBnode* nodex = *root;		//��root��ʼɨ��

	while (nodex != nil)		//���Ҳ���λ��
	{
		nodey = nodex;
		if (nodez->key < nodex->key)
			nodex = nodex->left;
		else
			nodex = nodex->right;
	}

	nodez->parent = nodey;		//y��z�ĸ��ڵ�
	if (nodey == nil)			//z�Ǹ�
		*root = nodez;	
	else
	{
		if (nodez->key < nodey->key)	//���Ӳ���
			nodey->left = nodez;
		else							//���Ӳ���
			nodey->right = nodez;
	}

	nodez->left = nil;
	nodez->right = nil;
	nodez->color = RED;

	RBInsertFixup(root, nodez);
}


//��������㷨
void RBInsertFixup(RBnode** root, RBnode* nodez)
{
	while (1)
	{
		if (*root == nodez)		//nodezΪ���ڵ㣬ֱ��Ϳ��
		{
			nodez->color = BLACK;
			break;
		}
		else if ((nodez->parent->color) == BLACK)
		{
			//�����ڵ�Ϊ�ڣ��������
			break;
		}
		else
		{
			//���ڵ�Ϊ�죬Υ������4
			if (nodez->parent == ((nodez->parent)->parent)->left)		//case1,2,3
			{
				RBnode* nodey = ((nodez->parent)->parent)->right;		//y��z������
				if (nodey->color == RED)			//case1
				{
					nodey->color = BLACK;
					nodez->parent->color = BLACK;
					((nodez->parent)->parent)->color = RED;
					nodez = ((nodez->parent)->parent);					//ͨ��ѭ����ì������
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
					RightRotate(root, ((nodez->parent)->parent));		//z�ĸ��ڵ�Ϊ�ڣ����˳�ѭ��
				}
			}
			else														//case4,5,6
			{	//if (nodez->parent = ((nodez->parent)->parent)->right)
				RBnode* nodey = ((nodez->parent)->parent)->left;		//y��z������

				if (nodey->color == RED)			//case4
				{
					nodey->color = BLACK;
					nodez->parent->color = BLACK;
					((nodez->parent)->parent)->color = RED;
					nodez = ((nodez->parent)->parent);					//ͨ��ѭ����ì������
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
					LeftRotate(root, ((nodez->parent)->parent));		//z�ĸ��ڵ�Ϊ�ڣ����˳�ѭ��
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


//ɾ���㷨
//�ǵ�ɾ���󣬽����ص�ָ���ͷ��ڴ档
RBnode* RBDelete(RBnode** root, RBnode* nodez)
{
	RBnode *nodex = nil, *nodey = nil;			//x�����ӵ㣬y����������ɾ���ڵ㣬z��ָ��ɾ��
	if (nodez->left == nil || nodez->right == nil)	//case1,2
		nodey = nodez;
	else												//case3
		nodey = TreeSuccessor(nodez);		//y��z��������
	//��ʱ��yͳһ����x�ĸ��ڵ�����Ҫɾ���Ľڵ�
	//x�Ǵ����ӵ�y->parent�Ľڵ㣬һ��Ҫȷ��x
	if (nodey->left != nil)
		nodex = nodey->left;
	else
		nodex = nodey->right;

	//һ�´�����xȡ��y��y��˫������
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
	if (nodey->color == BLACK)	//���ɾ���Ľڵ��Ǻ�ɫ�ڵ㣬���������
		RBDeleteFixup(*root, nodex);
	return nodey;
}

//ɾ������
//��ϸ���������ٽ����������nil�ĸ�ָ�룬������ֵ�޸���Ч�ȡ�
void  RBDeleteFixup(RBnode** root, RBnode* nodex)
{
	while (1)		//xʼ����Ϊì�ܵĴ��ڡ�
	{
		if (nodex == *root)				//x�Ǹ��ڵ㣬ֱ����ȥһ���ɫ���ղ���
			break;
		else if (nodex->color == RED)	//x�ڵ�Ϊ�죬Ϳ�ڼ���ֹ
		{
			nodex->color = BLACK;
			break;
		}
		else							//x�ڵ�Ǹ�����Ϊ��ɫ����ͨ����ɫ����ת������⡣
		{								//x��˫�ڽڵ㡣
			if (nodex == nodex->parent->left)		//case1,2,3,4
			{
				RBnode* nodew = nodex->parent->right;	//w��x���ֵܽڵ�
				if (nodew->color == RED)			//case1
				{
					nodew->color = BLACK;
					nodex->parent->color = RED;
					LeftRotate(root, nodex->parent);
					//�����w�ڵ㲻�ø�ֵ��while�������Զ���ʧ������һ��ѭ���Զ�ָ���ֵܽڵ�
				}
				else								//case2,3,4,�ֵܽڵ�w�Ǻ�
				{
					if (nodew->left->color == BLACK && nodew->right->color == BLACK)	//case2
					{
						nodew->color = RED;
						nodex = nodex->parent;
					}
					else
					{
						if (nodew->right->color == BLACK)	//case3ת����case4����
						{
							nodew->left->color = BLACK;
							nodew->color = RED;
							RightRotate(root, nodew);
							nodew = nodex->parent->right;	//wָ���µ��ֵ�
						}
						//throw problem
						if (nodew->right->color != RED)		
						{
							printf("ɾ��ʱcase3ת��case4������");
							system("pause");
						}
						//case4
						//����С��nil�ĸ�ָ�룬�϶��ᱨ��
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