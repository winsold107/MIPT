#include<iostream>
#include<vector>
using namespace std;

void merge(int* arr, int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	int*L = new int [n1];
	int*R = new int [n2];

	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	i = 0; // Initial index of first subarray
	j = 0; // Initial index of second subarray
	k = l; // Initial index of merged subarray
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}
	while (j < n2) 
	{
		arr[k] = R[j];
		j++;
		k++;
	}
	delete[]L;
	delete[]R;
}
void mergeSort(int* arr, int l, int r)
{
	if (l < r)
	{
		int m = l + (r - l) / 2;
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);
		merge(arr, l, m, r);
	}
}

int run4_merge_sort(){
	int n, k;
	cin >> n >> k;
	//vector<int> arr(n);
	//for (int i = 0; i < n; ++i) {
	//	cin >> arr[i];
	//}
	int* block = new int[2*k];

	if (n <= k) {
		for (int i = 0; i < n; ++i) {
			cin >> block[i];
		}
		mergeSort(block, 0, n - 1);
		for (int i = 0; i < n; ++i) {
			cout << block[i] << " ";
		}
	}

	for (int i = 0; i < k; ++i) {
		cin >> block[i];
	}
	
	int blocksEntered = 1;
	while (blocksEntered < n/k) {
		for (int i = 0; i < k; i++) {
			cin >> block[k+i];
		}
		mergeSort(block, k, 2*k - 1);
		merge(block, 0, k - 1, 2 * k - 1);

		for (int i = 0; i < k; ++i) {
			cout << block[i] << " ";
			block[i] = block[k + i];
		}
		blocksEntered++;
	}

	for (int i = 0; i < n % k; ++i) {
		cin >> block[k + i];
	}
	if (n%k > 0) {
		mergeSort(block, k, k + (n%k) - 1);
		merge(block, 0, k - 1, (n%k) - 1);
	}
	for (int i = 0; i < k + (n%k); ++i) {
		cout << block[i];
	}


	delete[] block;
	//for (int i = 0; i < n / k; ++i) {
	//	mergeSort(arr.data(), i*k, (i + 1)*k - 1);
	//}
	//mergeSort(arr.data(), (n / k - 1)*k, n - 1);

	//for (int i = 0; i < (n / k) - 1; ++i) {
	//	merge(arr.data(), i*k, (i + 1)*k - 1, (i + 2)*k - 1);
	//}
	//int i = n / k - 1;
	//merge(arr.data(), i, (i + 1)*k - 1, n - 1);
	//for (int i = 0; i < n; i++)
	//	cout << arr[i] << " ";
	system("pause");
	return 0;
}