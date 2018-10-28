#include<iostream>
#include<vector>

using namespace std;


vector<int> Input_array(int size)
{
	vector<int> a;
	for (int i = 0; i < size; i++)
	{
		int num;
		cin >> num;
		a.push_back(num);
	}
	return a;
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
	if (p < r)
	{
		int q;			//划分点
		q = Partition(A, p, r);
		QuickSort(A, p, q - 1);
		QuickSort(A, q + 1, r);
	}
}

int main()
{
	vector<int> vec;
	int size = 8;
	//数组赋值
	vec = Input_array(size);
	int a = 0;
	//快速排序
	QuickSort(vec, a, (size-1));

	for (auto it = vec.begin(); it != vec.end(); it++)
	{
		cout << *it << " " << endl;
	}
	system("pause");
	return 0;
}