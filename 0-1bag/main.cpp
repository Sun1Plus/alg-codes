#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;

class Item
{
public:
	Item()
	{
		value = 0;
		weight = 100;
	}
	Item(int weight, int value) :value(value), weight(weight){}
	void show()
	{
		cout <<"weight:" << weight << ", value:" << value << endl;
	}
public:
	int weight;
	int value;
};

typedef struct qnode
{
public:
	int wt;
	int wvalue;
	int level;
	struct qnode* parent;
}qnode;


void MaxBag(vector<Item>& w, int c, int n)
{
	queue<qnode*> Q;
	qnode *p = new qnode;
	p->level = 0;
	p->wt = 0;
	p->wvalue = 0;
	p->parent = NULL;

	Q.push(p);
	int bestv = 0;
	qnode* bestp = p;
	while (!Q.empty())
	{
		p = Q.front();
		Q.pop();

		if (p->wt + w[p->level].weight <= c)
		{
			qnode* q = new qnode;
			q->wt = p->wt + w[p->level].weight;
			q->wvalue = p->wvalue + w[p->level].value;
			q->parent = p;
			q->level = p->level + 1;
			if (q->level < n)		//control the edge
			{
				Q.push(q);
			}
			if (bestv < q->wvalue)
			{
				bestv = q->wvalue;
				bestp = q;
			}
		}
		qnode* q = new qnode;
		q->wt = p->wt;
		q->wvalue = p->wvalue;
		q->level = p->level + 1;
		q->parent = p;
		if (q->level < n)		//control the edge
		{
			Q.push(q);
		}

	}

	//gain the result
	vector<int> x;
	x.clear();
	for (int i = 0; i < n; i++)
	{
		x.push_back(0);
	}
	p = bestp;
	while (p->parent != NULL)
	{
		int tempv = p->wvalue;
		p = p->parent;
		if (p->wvalue != tempv)
		{
			x[p->level] = 1;
			w[p->level].show();
		}
	}
}

int main()
{
	Item t1(15, 25);
	Item t2(20, 40);
	Item t3(15, 25);
	vector<Item> item_store;
	item_store.push_back(t1);
	item_store.push_back(t2);
	item_store.push_back(t3);

	MaxBag(item_store, 30, 3);

	system("pause");
	return 0;
}

