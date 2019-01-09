#include<stdio.h>
#include<stdlib.h>

//这个算法的前提有一个是整数范围从1开始，所以数组计算时要考虑从0开始的调整。


//A是原数组，B是返回的排序好的数组,size是A，B的大小，max_num是最大元素值，也是C的size。
void CountSort(int A[], int B[], int size, int max_num)	
{
	int *C = (int*)malloc(max_num * sizeof(int));
	for (int i = 0; i < max_num; i++)
	{
		C[i] = 0;
	}
	for (int j = 0; j < size; j++)
		C[A[j]]++;
	for (int i = 1; i < max_num; i++)		//修改C
	{
		C[i] = C[i] + C[i - 1];
	}
	for (int j = size - 1; j >= 0; j--)
	{
		B[(C[A[j]]-1)] = A[j];			//这里的C[]-1是为了B的寻址，以后再优化。
		C[A[j]]--;
	}
}

int main()
{
	int vec[10] = { 5, 2, 2, 5, 7, 1, 3, 4, 9, 15 };
	int vec_sorted[10];
	CountSort(vec, vec_sorted, 10, 16);	//这里先随意写一下，最大值+1是为了C数组做的。

	for (int i = 0; i < 10; i++)
		printf("%d ", vec_sorted[i]);
	
	system("pause");
	return 0;
}

