#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

class Node
{
public:
	Node()
	{
		ch = ' ';
		left = NULL;
		right = NULL;
		next = NULL;
	}
	Node(char ch, float fre) :ch(ch), fre(fre)
	{
		left = NULL;
		right = NULL;
		next = NULL;
	}
	Node(const Node& n)
	{
		ch = n.ch;
		fre = n.fre;
		left = n.left;
		right = n.right;
		next = NULL;
	}
public:
	char ch;
	float fre;
	Node *left, *right;
	Node *next;
};

bool comp(const Node& n1, const Node& n2)
{
	if (n1.fre < n2.fre)
		return true;
	else
		return false;
}

void print(Node * root, string prefixs)
{
	if (root->ch == ' ')
	{
		print(root->left, prefixs + '0');
		print(root->right, prefixs + '1');
	}
	else
	{
		cout << root->ch << ":" << prefixs << endl;
	}
}

//int main()
//{
//	vector<Node> nodevec = { Node('a', 45), Node('b', 13), Node('c', 12), Node('d', 16), Node('e', 9), Node('f', 5) };
//
//	Node * root = NULL;
//
//	while (nodevec.size() != 1)
//	{
//		sort(nodevec.begin(), nodevec.end(), comp);
//
//		Node *a = new Node(nodevec[0]);
//		Node *b = new Node(nodevec[1]);
//
//		//删除前两个
//		nodevec.erase(nodevec.begin());
//		nodevec.erase(nodevec.begin());
//
//		Node * parent = new Node();
//		parent->fre = a->fre + b->fre;
//		parent->ch = ' ';
//		parent->left = a;
//		parent->right = b;
//
//		nodevec.push_back(*parent);
//		root = parent;
//	}
//	print(root, "");
//
//	system("pause");
//	return 0;
//}

int main()
{
	vector<Node> nodevec = { Node('a', 45), Node('b', 13), Node('c', 12), Node('d', 16), Node('e', 9), Node('f', 1) };
	Node * root = NULL, *head = NULL;
	sort(nodevec.begin(), nodevec.end(), comp);

	head = &nodevec[0];
	for (auto it = nodevec.begin(); it != nodevec.end()-1; it++)
	{
		it->next = &(*(it + 1));
	}

	while (head->next != NULL)
	{
		Node * parent = new Node();
		parent->fre = head->fre + head->next->fre;
		parent->left = head;
		parent->right = head->next;
		root = parent;
		head = head->next->next;
		if (head == NULL)
			break;

		Node * temp = head, *record = head;
		int flag = 0;

		while (parent->fre > temp->fre)
		{
			flag = 1;
			record = temp;
			temp = temp->next;
			if (temp == NULL)
				break;
		}
		//特殊情况，parent的频率小于所有的
		if (record == head && flag == 0)
		{
			parent->next = record;
			head = parent;

			continue;
		}

		parent->next = record->next;
		record->next = parent;
	}
	
	print(root, "");
	
	system("pause");
	return 0;
}