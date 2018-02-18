/*#include <iostream>
#include <vector>
using namespace std;

int Partition(int* a, int begin_index, int end_index) {
	if (end_index == begin_index) {
		return 0;
	}
	int index = rand() % (end_index - begin_index + 1) + begin_index;
	int pivot = a[index];
	swap(a[index], a[end_index]);

	int i = begin_index;
	int j = begin_index;
	while (i <= end_index - 1 && a[i] <= pivot) {
		i++;
	}
	j = i + 1;
	while (j < end_index) {
		while (a[j] > pivot) {
			j++;
		}
		if (j < end_index) {
			swap(a[i], a[j]);
			i++;
			j++;
		}
	}
	swap(a[end_index], a[i]);
	return i;
}
void QuickSortOptimization(int* a, int n) {
	int part = Partition(a, n);
	if (part > 0) QuickSortOptimization(a, part);
	if (part + 1 < n) QuickSortOptimization(a + part + 1, n -(part + 1));
}
int run6_try() {
	int n;
	cin >> n;
	vector <int> numerus(n);
	for (int i = 0; i < n; i++)
		cin >> numerus[i];
	QuickSortOptimization(numerus.data(), n);
	for (int i = 0; i < n; i++)
		if (i % 10 == 0)
			cout << numerus[i];
	system("pause");
	return 0;
}*/