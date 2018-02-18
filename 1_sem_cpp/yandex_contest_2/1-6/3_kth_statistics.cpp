/*#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

#include <cassert>
#include <cstdlib>
#include <ctime>

template <typename Data>
int getRandomPivot(Data* array, int left, int right) {
assert(left < right);
int mod = right - left + 1;
return left + (std::rand() % mod);
}

/*template <typename Data/*, typename Comparator>*/
/*int Partition(int* array, int left, int right/*, Comparator less_) {
int pivotIdx = getRandomPivot(array, left, right);
int pivotElem = array[pivotIdx];

// Just giving array another name. Nothing special.
int* a = array;

swap(a[left], a[pivotIdx]);

int i = left, j = i + 1;
while (j <= right) {
while (j <= right && /*less_(pivotElem, a[j]) pivotElem < a[j]) {
j++;
}
if (j <= right) {
swap(a[i++], a[j++]);
}
}

return i;
}*/



/*int KStatistics (int* arr, int arr_size, int start_index, int finish_index, int k_index) {
int pivot_index = -1;
while (pivot_index != k_index) {
if (pivot_index < k_index) {
start_index = pivot_index + 1;
pivot_index = Partition(arr, start_index, finish_index);
}
else if (pivot_index > k_index) {
finish_index = pivot_index - 1;
pivot_index = Partition(arr, start_index, finish_index);
}
}
return arr[pivot_index];
}

int task3() {
int n;
int kth;
cin >> n >> kth;
vector <int> array(n);
for (int i = 0; i < n; i++) {
cin >> array[i];
}
cout << KStatistics(array.data(), n - 1, 0, n - 1, kth);
system("pause");
return 0;
}*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cassert>
using namespace std;

int GetRandomPivot1(int* array, int left, int right) {
	assert(left < right);
	int value = right - left + 1;
	return left + (rand() % value);
}

int Partition1(int* a, int begin_index, int end_index) {
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
	//if (i >= end_index - begin_index + 1) {
		//return end_index;
	//}
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

/*int Partition1(int* array, int left, int right) {
	int pivotIdx = GetRandomPivot1(array, left, right);
	int pivotElem = array[pivotIdx];
	int* a = array;
	swap(a[left], a[pivotIdx]);
	int i = left, j = i + left;
	while (j <= right) {
		while (j <= right && pivotElem < a[j]) {
			j++;
		}
		if (j <= right) {
			swap(a[i++], a[j++]);
		}
	}
	return i;
}*/

int KStatistics1(int* arr, int arr_size, int start_index, int finish_index, int k_index) {
	int pivot_index = -1;
	while (pivot_index != k_index) {
		if (pivot_index < k_index) {
			start_index = pivot_index + 1;
			pivot_index = Partition1(arr, start_index, finish_index);
		}
		else if (pivot_index > k_index) {
			finish_index = pivot_index - 1;
			pivot_index = Partition1(arr, start_index, finish_index);
		}
	}
	return arr[pivot_index];
}

int run3_kth_statistics() {
	int n;
	int kth;
	cin >> n >> kth;
	vector <int> array(n);
	for (int i = 0; i < n; i++) {
		cin >> array[i];
	}
	cout << KStatistics1(array.data(), n - 1, 0, n - 1, kth);
	system("pause");
	return 0;
}