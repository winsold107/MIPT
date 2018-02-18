#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

long long min_val (int cubes)
{
	return (sqrt(8 * cubes + 1) - 1) / 2;
	//int cur = 0;
	//int current = 0;
	//while (current <= cubes)
	//{
	//	current+=cur++;
	//}
	//return cur-1;
}

vector <vector <long>> K;
long long wide_pyramid (int cubes, int pp)
{
	if ((cubes == 0))
	{
		return 1;
		//return amountPyr;
	}
	else 
	{
		/*auto start_ind = [](int n)
		{
			return n % 2 == 0 ? n / 2 - 1 : n / 2;
		};*/
		long long sum = 0;
		int prev = min_val(cubes);
		for (; prev <= cubes; prev++)
		{
			//cout << i;
			if ((pp > prev) && (K[cubes - prev][prev] == -1)) {
				long long value = wide_pyramid(cubes - prev, prev);
				sum += value;
				K[cubes - prev][prev] = value;
			}
			else if ((pp > prev) && (K[cubes - prev][prev] != -1))
			{
				sum += K[cubes - prev][prev];
			}
			//= wide_pyramid(cubes - i, amountPyr);
				//cout << "incr" << " ";
			//amountPyr = wide_pyramid(cubes - 1, amountPyr) + 1;
			//return amountPyr;
		}
		return sum;
		//return amountPyr;
	}
}

int main ()
{
	long long n;
	cin >> n;
	if (n == 0) { cout << "0"; }
	else {
		//int amountPyr = 0;
		K.resize(n+1, vector <long>(n+1, -1));
		cout << wide_pyramid(n, n+1);
	}
	system("pause");
}
