#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	long long q; 
    long long d; 
    long long n;
    bool isf;
	cin >> n;;
    isf = false;
    int p;
    p = trunc(sqrt(n)) + 1;
	for (long long q = 2; q <= p; q++)
     	{
			if (n % q == 0)
				{
				  d = n / q;
				  cout << d << ' ' << n - d;
    			  isf = true;
				  break;
				}
         }        
	if (n == 1) { cout << "0" << " " << "1"; }
	else if (!(isf))
	 {
		cout << 1 << ' ' << n - 1;
	 }
	return 0;
}