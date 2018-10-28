#include<stdio.h>
#include<stdlib.h>

//����㷨��ǰ����һ����������Χ��1��ʼ�������������ʱҪ���Ǵ�0��ʼ�ĵ�����


//A��ԭ���飬B�Ƿ��ص�����õ�����,size��A��B�Ĵ�С��max_num�����Ԫ��ֵ��Ҳ��C��size��
void CountSort(int A[], int B[], int size, int max_num)	
{
	int *C = (int*)malloc(max_num * sizeof(int));
	for (int i = 0; i < max_num; i++)
	{
		C[i] = 0;
	}
	for (int j = 0; j < size; j++)
		C[A[j]]++;
	for (int i = 1; i < max_num; i++)		//�޸�C
	{
		C[i] = C[i] + C[i - 1];
	}
	for (int j = size - 1; j >= 0; j--)
	{
		B[(C[A[j]]-1)] = A[j];			//�����C[]-1��Ϊ��B��Ѱַ���Ժ����Ż���
		C[A[j]]--;
	}
}

int main()
{
	int vec[10] = { 5, 2, 2, 5, 7, 1, 3, 4, 9, 15 };
	int vec_sorted[10];
	CountSort(vec, vec_sorted, 10, 16);	//����������дһ�£����ֵ+1��Ϊ��C�������ġ�

	for (int i = 0; i < 10; i++)
		printf("%d ", vec_sorted[i]);
	
	system("pause");
	return 0;
}

