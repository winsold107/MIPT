#include <iostream>
#include <vector>

using namespace std;

class CInterval {
public:
	int Left;
	int Right;

	CInterval() : Left(0), Right(0) {}
	CInterval(int x, int y) : Left(x), Right(y) {}
	int getLeft() {
		return Left;
	}
	int getRight() {
		return Right;
	}

	CInterval& operator=(const CInterval& Interval_probe) {
		if (this == &Interval_probe) {
			return *this;
		}
		Left = Interval_probe.Left;
		Right = Interval_probe.Right;
		return *this;
	}
};

ostream& operator<<(ostream& os, const CInterval& Interval)
{
	os << Interval.Left << " " << Interval.Right;
	return os;
}

istream& operator>>(istream& is, CInterval& Interval)
{
	is >> Interval.Left >> Interval.Right;
	return is;
}

bool operator<(const CInterval& Interval1, const CInterval& Interval2)
{
	if (Interval1.Left != Interval2.Left) {
		return Interval1.Left < Interval2.Left;
	}
	return Interval1.Right < Interval2.Right;
}

bool operator>(const CInterval& Interval1, const CInterval& Interval2)
{
	return Interval2 < Interval1;
}
template <class K>
void heapify(K* arr, int n, int i)
{
	int largest = i;  
	int l = 2 * i + 1; 
	int r = 2 * i + 2; 

	if (l < n && arr[l] > arr[largest])
		largest = l;

	if (r < n && arr[r] > arr[largest])
		largest = r;

	if (largest != i)
	{
		swap(arr[i], arr[largest]);
		heapify(arr, n, largest);
	}
}
template <class T>
void heapSort(T* arr, int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	for (int i = n - 1; i >= 0; i--)
	{
		swap(arr[0], arr[i]);
		
		heapify(arr, i, 0);
	}
}

int run2_paint_otrezok() {
	int n;
	cin >> n;

	CInterval* Intervals = new CInterval[n];
	for (int i = 0; i < n; i++) {
		cin >> Intervals[i];
	}

	heapSort(Intervals, n);
	
	int counter_line_section = 0;
	for (int i = 0; i < n; i++) {
		int expansionStart = Intervals[i].getLeft(),
			expansionEnd = Intervals[i].getRight();

		while (i < n - 1 && Intervals[i + 1].getLeft() < expansionEnd) {
			if (Intervals[i + 1].getRight() > expansionEnd) {
				expansionEnd = Intervals[i + 1].getRight();
			}
			i++;
		}
		counter_line_section += expansionEnd - expansionStart;
	}

	cout << counter_line_section << endl;
	system("pause");
	return 0;
}