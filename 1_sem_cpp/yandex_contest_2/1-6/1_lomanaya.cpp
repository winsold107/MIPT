#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class CPoint {
public:
	int X;
	int Y;

	CPoint() : X(0), Y(0) {}
	CPoint(int x, int y) : X(x), Y(y) {}

	CPoint& operator=(const CPoint& point_probe) {
		//проверка на самоприсваивание
		if (this == &point_probe) {
			return *this;
		}
		X = point_probe.X;
		Y = point_probe.Y;
		return *this;
	}
};

ostream& operator<<(ostream& os, const CPoint& point)
{
	os << point.X << " " << point.Y;
	return os;
}

istream& operator>>(istream& is, CPoint& point)
{
	is >> point.X >> point.Y;
	return is;
}

bool operator<(const CPoint& point1, const CPoint& point2)
{
	if (point1.X != point2.X) {
		return point1.X < point2.X;
	}
	return point1.Y < point2.Y;
}

bool operator>(const CPoint& point1, const CPoint& point2)
{
	return point2 < point1;
}

template<class T>
void insertionSort_1(T* points, int n)
{

	int i, j;
	CPoint key;
	for (i = 1; i < n; i++)
	{
		key = points[i];
		j = i - 1;
		while (j >= 0 && points[j] > key)
		{
			points[j + 1] = points[j];
			j = j - 1;
		}
		points[j + 1] = key;
	}
}

int run1_lomanaya() {
	int n;
	cin >> n;

	CPoint* points = new CPoint[n];
	for (int i = 0; i < n; i++) {
		cin >> points[i];
	}

	insertionSort_1(points, n);
	for (int i = 0; i < n; ++i) {
		cout << points[i] << endl;
	}
	delete[]points;
	system("pause");
	return 0;
}