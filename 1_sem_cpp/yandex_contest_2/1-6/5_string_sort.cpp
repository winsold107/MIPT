#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
const int k = 256;

void CountingSort(string* a, int n, int* c, int byte) {
	for (int i = 0; i < k; ++i)
		c[i] = 0;
	for (int i = 0; i < n; ++i)
		++c[a[i][byte]];
	//int pos = 0;
	int sum = 0;
	for (int i = 0; i < k; i++) {
		int tmp = c[i];
		c[i] = sum;
		sum += tmp;
	}
	//for (int i = 0; i < k; ++i) {
	//for (int j = 0; j < c[i]; ++j) {
	//	c[pos++] = i;
	//	}
	//}
	string* arr = new string[n];
	for (int i = 0; i < n; i++)
		arr[c[a[i][byte]]++] = a[i];
	for (int i = 0; i < n; i++)
		a[i] = arr[i];
	delete[] arr;
}
// Поразрядная сортировка по одному конкретному байту.
// Заполняет массив c[0..k-1] – начала групп.
void MSDSort(string* a, int n, int byte) {
	if (n <= 1)
		return;
	int* c = new int[k];
	CountingSort(a, n, c, byte);
	for (int i = 1; i < k; ++i)
		if (i == k - 1) { MSDSort(a + c[i], n - 1 - c[i], byte + 1); }
		else { MSDSort(a + c[i], c[i + 1] - c[i], byte + 1); }
		delete[] c;
}

int run5_string_sort() {
	fstream in("input.txt", ios_base::in);
	string a[100000];

	int n = 0;

	while (!in.eof()) {
		in >> a[n++];
	}

	MSDSort(a, n - 1, 0);
	for (int i = 0; i < n - 1; i++) {
		cout << a[i] << endl;
	}
	return 0;
}

