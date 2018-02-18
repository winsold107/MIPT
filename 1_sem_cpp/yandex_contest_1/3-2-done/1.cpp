#include <iostream>
#include <vector>
using namespace std;
int rec (int*arr, int index, int arrsize) {
	cout << "recursion" << endl;
	if (arrsize <= 1) {
		cout << "arrsize <= 1 " << arrsize << endl;
		return index;
	}
	while ((index*2 <= arrsize) && (arr[index-1] < arr[index*2 - 1])) {
		cout << "looking through " << index - 1 << " and " << index * 2 - 1 << endl;
		index = index * 2;
	}

	if (index < arrsize) {
		if (arr[index] > arr[index - 1]) {
			return rec(arr, index-1, arrsize - index + 1);
		}
		else {
			return rec(arr, index, index - (index / 2) + 1);
		}
	} else if (index =  )

	cout << "running new recursion index = " << index << " arrsize =" << arrsize << " arrsize - index " << arrsize - index << endl;
	
}
int main() {
	int n; int t = 1; int l;
	cin >> n;
	int *a= new int[n];
	for (int i = 0; i < n; i++) { 
		cin >> a[i]; 
	}
	cout << rec(a, 1, n);
	system("pause");
	return 0;
}