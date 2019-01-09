#include<stdio.h>
#include<stdlib.h>
#define n 7
#define k 3

int machine_spendedtime[k];	//每个机器完成任务需要的时间
int work_machine[n];		//每个任务对应的机器
int work_time[n];			//每个任务需要的时间
int longest_time;			//because every machine is equal.

int best_work_machine[n];		//最佳调度方案

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

	//剪纸只会发生在机器增加任务时，在这里设置剪枝即可
	if (machine_spendedtime[j] > longest_time)
		return;

	if (i == n-1)
	{
		//终止条件
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
		//这里要考虑up与k的关系，up <= k
		//使用up限内的机器
		for (int it = 0; it <= up; it++)
		{
			dispatching(i + 1, it, up);
			//回溯
			work_machine[i + 1] = -1;
			machine_spendedtime[it] -= work_time[i+1];
		}
		//使用up+1的机器
		if (up < k-1)
		{
			dispatching(i + 1, up + 1, up + 1);
			//回溯
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