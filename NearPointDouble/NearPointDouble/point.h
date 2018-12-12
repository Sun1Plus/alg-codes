#include<iostream>
using namespace std;

class Point
{
public:
	Point() :x(-1), y(-1){}
	Point(double x, double y) :x(x), y(y){}
	void show()
	{
		cout << "(" << x << ", " << y << ")" << endl;
	}
public:
	double x;
	double y;
};

class Result
{
public:
	Result(Point A, Point B, double length) :A(A), B(B), min_pair_distance(length){}
	Result(double length) :min_pair_distance(length){}
public:
	Point A;
	Point B;
	double min_pair_distance;
};