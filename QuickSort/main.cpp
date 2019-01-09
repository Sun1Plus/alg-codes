//#include<iostream>
//#include<vector>
//
//#define k 10
//
//
//using namespace std;
//
//
//vector<int> Input_array(int size)
//{
//	vector<int> a;
//	for (int i = 0; i < size; i++)
//	{
//		int num;
//		cin >> num;
//		a.push_back(num);
//	}
//	return a;
//}
//
//int Partition(vector<int> &A, int p, int r)	//p是左端，r是右端
//{
//	int base_x = A[r];
//	int i = p - 1, j;
//	for (j = p; j < r; j++)
//	{
//		if (A[j] <= base_x)
//		{
//			i++;
//			int temp = A[i];
//			A[i] = A[j];
//			A[j] = temp;
//		}
//	}
//	int temp = A[i + 1];
//	A[i + 1] = A[r];
//	A[r] = temp;
//	return (i + 1);
//}
//
//void QuickSort(vector<int> &A, int p, int r)	//p是左端，r是右端
//{
//	//当划分小于k时，数组执行插入排序。
//	if ((r - p) < k)
//	{
//		for (int j = p; j <= r; j++)
//		{
//			int key = A[j];
//			int i = j - 1;
//			while (i >= p && A[i] > key)
//			{
//				A[i + 1] = A[i];
//				i = i - 1;
//			}
//			A[i + 1] = key;
//		}
//	}
//	else if (p < r)
//	{
//		int q;			//划分点
//		q = Partition(A, p, r);
//		QuickSort(A, p, q - 1);
//		QuickSort(A, q + 1, r);
//	}
//	else
//		;
//}
//
//int main()
//{
//	vector<int> vec;
//
//	//数组赋值
////	vec = Input_array(size);
//	vec = { 18, 4, 6, 7, 8, 9, 4, 56, 34, 6, 78, 2, 3, 45, 67, 4, 3, 324, 67, 674, 467, 2, 45, 67, 5, 3, 43, 5, 674, 14, 78 };
//	int a = 0;
//	int size = vec.size();
//	//快速排序
//	QuickSort(vec, a, (size-1));
//
//	for (auto it = vec.begin(); it != vec.end(); it++)
//	{
//		cout << *it << " " << endl;
//	}
//	system("pause");
//	return 0;
//}