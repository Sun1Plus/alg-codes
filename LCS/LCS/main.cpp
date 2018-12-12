#include<iostream>
#include<vector>
#include<string>

using namespace std;

void LCS_Length(string X, string Y, vector<vector<char>>& b, vector<vector<int>>& c)	//b是箭头矩阵，c是数字矩阵
{
	int m = X.size()+1;
	int n = Y.size()+1;



	for (int i = 0; i < m; i++)
	{
		c[i][0] = 0;
	}

	for (int j = 0; j < n; j++)
	{
		c[0][j] = 0;
	}

	int index_i, index_j;

	for (int i = 1; i < m; i++)
	{
		index_i = i - 1;
		for (int j = 1; j < n; j++)
		{
			index_j = j - 1;
			if (X[index_i] == Y[index_j])
			{
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = '1';			//1代表左上
			}
			else
			{
				if (c[i - 1][j] >= c[i][j - 1])
				{
					c[i][j] = c[i - 1][j];
					b[i][j] = '2';		//2代表向上
				}
				else
				{
					c[i][j] = c[i][j - 1];
					b[i][j] = '3';		//3代表向左
				}
			}
		}
	}
}

void Print_LCS(vector<vector<char>>& b, string X, int i, int j)		//b是箭头矩阵
{
	if (i == 0 || j == 0)
		return;
	if (b[i][j] == '1')					//1代表左上
	{
		Print_LCS(b, X, i - 1, j - 1);
		cout << " " << X[i-1];
	}
	else
	{
		if (b[i][j] == '2')				//2代表向上
			Print_LCS(b, X, i - 1, j);
		else
			Print_LCS(b, X, i, j - 1);
	}
}


int main()
{
	string A = "ABCBDAB";
	string B = "BDCABA";
	

	vector<vector<char>> arrow(A.size() + 1, vector<char>(B.size() + 1));
	vector<vector<int>> subarray(A.size() + 1, vector<int>(B.size() + 1));

	LCS_Length(A, B, arrow, subarray);
	Print_LCS(arrow, A, A.size(), B.size());

	system("pause");
	return 0;
}