#include<iostream>
#include<algorithm>
#include<vector>
#include<ctime>
#include<cmath>
#include"point.h"


#define N 1000

using namespace std;

vector<Point> pointVec;

//生成点集
void gen_pointSet()
{
	pointVec.clear();

	pointVec.push_back(Point(7, 7));
	pointVec.push_back(Point(9, 8));
	pointVec.push_back(Point(11, 10));
	pointVec.push_back(Point(14, 11));
	pointVec.push_back(Point(1, 1));
	pointVec.push_back(Point(2, 4));
	pointVec.push_back(Point(2, 6));
	pointVec.push_back(Point(3, 10));
	pointVec.push_back(Point(5, 6));
	pointVec.push_back(Point(22, 20));
	pointVec.push_back(Point(3, 7));

	pointVec.push_back(Point(1, 1));
	pointVec.push_back(Point(4, 4));
	pointVec.push_back(Point(9, 9));
	pointVec.push_back(Point(15, 1));
	pointVec.push_back(Point(22, 14));
	pointVec.push_back(Point(25, 6));
	pointVec.push_back(Point(13, 21));
	pointVec.push_back(Point(2, 4));
	pointVec.push_back(Point(2, 9));

	cout << "generate Set:" << endl;
	for (auto it = pointVec.begin(); it != pointVec.end(); it++)
	{
		it->show();
	}
}

//随机数组生成
void gen_random_set()
{
	int i;
	int x[N], y[N];
	srand(time(0));
	for (i = 0; i<N; i++)
	{
		x[i] = rand() % N;
		cout << x[i] << ' ';
	}
	cout << endl;
	for (i = 0; i<N; i++)
	{
		y[i] = rand() % N;
		cout << y[i] << ' ';
	}

	pointVec.clear();
	for (i = 0; i < N; i++)
	{
		pointVec.push_back(Point(x[i], y[i]));
	}

	cout << "generate Set:" << endl;
	for (auto it = pointVec.begin(); it != pointVec.end(); it++)
	{
		it->show();
	}
}

//exchange point index in vec
void pointSwap(Point & a, Point & b)
{
	Point temp = a;
	a = b;
	b = temp;
}

int xSquare(int x)
{
	return x*x;
}

//the distance of Points
double pairDistance(Point a, Point b)
{
	return sqrt(xSquare(a.x - b.x) + xSquare(a.y - b.y));
}

double doublemin(double a, double b)
{
	if (a >= b)
		return b;
	else
		return a;
}

bool compx(const Point& a, const Point&b)
{
	return a.x < b.x;
}

bool compy(const Point& a, const Point&b)
{
	return a.y < b.y;
}

//sort the pointVec
void vecsort()
{
	sort(pointVec.begin(), pointVec.end(), compx);

	cout << "排序后的元素数组：" << endl;
	for (auto it = pointVec.begin(); it != pointVec.end(); it++)
		it->show();
	cout << endl;
}

//穷举法
double Point_exhaustion()
{
	double  min_distance = 10000;
	double temp_distance;
	Point a, b;
	for (vector<Point>::iterator it = pointVec.begin(); it != pointVec.end(); it++)
	{
		for (vector<Point>::iterator jt = it + 1; jt != pointVec.end(); jt++)
		{
			temp_distance = pairDistance(*it, *jt);
			if (temp_distance < min_distance)
			{
				min_distance = temp_distance;
				a = *it;
				b = *jt;
			}
		}
	}
	cout << "The min distance is: " << min_distance << endl;
	cout << "Two Point are" << endl;
	a.show();
	b.show();

	return min_distance;
}


//分治法
//divide and mergt
Result area_Divide(int left, int right)
{
	int mid;
	Result lmin_Distance(1000), rmin_Distance(1000);
	Result min_Distance(10000);
	
	if (left==right)	//如果只有一个点，返回无限大
	{
		return Result(10000);
	}
	else if ((right - left) == 1)		//如果两个点，返回其距离
	{
		Point A = pointVec[left];
		Point B = pointVec[right];
		double temp_length = pairDistance(pointVec[left], pointVec[right]);
		return Result(A, B, temp_length);
	}
	else				//子区域大于两个点
	{
		mid = left + (right - left) / 2;
		
		//Divide
		lmin_Distance = area_Divide(left, mid);
		rmin_Distance = area_Divide(mid + 1, right);
		
		//Merge
		if (lmin_Distance.min_pair_distance < rmin_Distance.min_pair_distance)
			min_Distance = lmin_Distance;
		else
			min_Distance = rmin_Distance;
			
		double midAreaLeft = (double)pointVec[mid].x - min_Distance.min_pair_distance;
		double midAreaRight = (double)pointVec[mid].x + min_Distance.min_pair_distance;

		vector<Point> tempPointLeft;
		vector<Point> tempPointRight;

		//收集左边区域满足的点
		for (int i = left; i <= mid; i++)
		{
			if (pointVec[i].x > midAreaLeft)
			{
				tempPointLeft.push_back(pointVec[i]);
			}
		}
		sort(tempPointLeft.begin(), tempPointLeft.end(), compy);

		//收集右边区域满足的点
		for (int j = mid + 1; j <= right; j++)
		{
			if (pointVec[j].x < midAreaRight)
			{
				tempPointRight.push_back(pointVec[j]);
			}
		}
		sort(tempPointRight.begin(), tempPointRight.end(), compy);

		//计算两个数组内所有点的距离
		for (auto it = tempPointLeft.begin(); it != tempPointLeft.end(); it++)
		{
			for (auto jt = tempPointRight.begin(); jt != tempPointRight.end(); jt++)
			{
				double tempDistance = pairDistance(*it, *jt);
				if (tempDistance < min_Distance.min_pair_distance)
				{
					min_Distance.min_pair_distance = tempDistance;
					min_Distance.A = *it;
					min_Distance.B = *jt;
				}
			}
		}
		return min_Distance;
	}
}




int main()
{
	Result result(1000);
	pointVec.clear();
	gen_pointSet();
	//gen_random_set();

	cout << "------------------------遍历法------------------------" << endl;
	Point_exhaustion();
	cout << endl;

	cout << "************************分治法************************" << endl;
	vecsort();
	result = area_Divide(0, pointVec.size() - 1);
	cout << "元素组中最短距离为：" << result.min_pair_distance << endl;
	result.A.show();
	result.B.show();

	system("pause");
	return 0;
}