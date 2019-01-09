#include<stdio.h>
#include<stdlib.h>
#define n 7
#define k 3

int machine_spendedtime[k];	//ÿ���������������Ҫ��ʱ��
int work_machine[n];		//ÿ�������Ӧ�Ļ���
int work_time[n];			//ÿ��������Ҫ��ʱ��
int longest_time;			//because every machine is equal.

int best_work_machine[n];		//��ѵ��ȷ���

int get_longest_time()
{
	int longtime = 0;
	for (int i = 0; i < k; i++)
	{
		if (machine_spendedtime[i] > longtime)
			longtime = machine_spendedtime[i];
	}
	return longtime;
}

//i refers to the i_th work, j refers to the j_th machine,
//up refers to the up_bound.
void dispatching(int i, int j, int up)	
{
	work_machine[i] = j;
	machine_spendedtime[j] += work_time[i];

	//��ֻֽ�ᷢ���ڻ�����������ʱ�����������ü�֦����
	if (machine_spendedtime[j] > longest_time)
		return;

	if (i == n-1)
	{
		//��ֹ����
		int result = get_longest_time();
		if (result < longest_time)
		{
			longest_time = result;
			for (int i = 0; i < n; i++)
				best_work_machine[i] = work_machine[i];
		}
	}
	else
	{
		//����Ҫ����up��k�Ĺ�ϵ��up <= k
		//ʹ��up���ڵĻ���
		for (int it = 0; it <= up; it++)
		{
			dispatching(i + 1, it, up);
			//����
			work_machine[i + 1] = -1;
			machine_spendedtime[it] -= work_time[i+1];
		}
		//ʹ��up+1�Ļ���
		if (up < k-1)
		{
			dispatching(i + 1, up + 1, up + 1);
			//����
			work_machine[i + 1] = -1;
			machine_spendedtime[up+1] -= work_time[i+1];
		}
	}
}

void input_work_time()
{
	work_time[0] = 1;
	work_time[1] = 1;
	work_time[2] = 2;
	work_time[3] = 3;
	work_time[4] = 5;
	work_time[5] = 4;
	work_time[6] = 2;
}

void show_result()
{
	printf("The best dispatch is :\n");
	for (int i = 0; i < n; i++)
	{
		printf("the %d work is dispatched to %d machine:\n", i, best_work_machine[i]);
	}
	printf("The result time is %d\n", longest_time);
}

int main()
{
	longest_time = 1;
	input_work_time();
	for (int i = 0; i < n; i++)
	{
		work_machine[i] = -1;
		longest_time += work_time[i];
	}
	for (int j = 0; j < k; j++)
	{
		machine_spendedtime[j] = 0;
	}

	dispatching(0, 0, 0);

	show_result();

	system("pause");
	return 0;
}