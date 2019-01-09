#include<iostream>
#include<vector>
#include<cstdlib>
#include<time.h>
#define random(x) (rand()%x)
#define k 50

using namespace std;



void Input_array(vector<int>& a, int size)
{
	for (int i = 0; i < size; i++)
	{
		int num=random(size);
		a.push_back(num);
	}
}

int Partition(vector<int> &A, int p, int r)	//p是左端，r是右端
{
	int base_x = A[r];
	int i = p - 1, j;
	for (j = p; j < r; j++)
	{
		if (A[j] <= base_x)
		{
			i++;
			int temp = A[i];
			A[i] = A[j];
			A[j] = temp;
		}
	}
	int temp = A[i + 1];
	A[i + 1] = A[r];
	A[r] = temp;
	return (i + 1);
}

void QuickSort(vector<int> &A, int p, int r)	//p是左端，r是右端
{
	//当划分小于k时，数组执行插入排序。
	if ((r - p) < k)
	{
		for (int j = p; j <= r; j++)
		{
			int key = A[j];
			int i = j - 1;
			while (i >= p && A[i] > key)
			{
				A[i + 1] = A[i];
				i = i - 1;
			}
			A[i + 1] = key;
		}
	}
	else if (p < r)
	{
		int q;			//划分点
		q = Partition(A, p, r);
		QuickSort(A, p, q - 1);
		QuickSort(A, q + 1, r);
	}
	else
		;
}

int main()
{
	clock_t start,end;
	double spendtime;
	vector<int> vec;
	//数组赋值
	Input_array(vec,50000);
	start=clock();
	cout<<"the size:"<<vec.size()<<endl;
	int a = 0;
	int size = vec.size();
	//快速排序
	QuickSort(vec, a, (size-1));

	end=clock();

	//for (auto it = vec.begin(); it != vec.end(); it++)
	//{
	//	cout << *it << " " << endl;
	//}

	spendtime=double(end-start)/CLOCKS_PER_SEC;
	cout<<endl<<spendtime<<"ms"<<endl;
	system("pause");
	return 0;
}
