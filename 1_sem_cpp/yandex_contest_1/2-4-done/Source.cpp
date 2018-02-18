
#include <iostream>

using namespace std;

struct turm { int n;
turm *next, *prev;
} *first, *put, *ad;

int m, n;

void addturm(int v) {
	turm *put;
	if (ad == nullptr && first == nullptr) {
		ad = new turm;
		ad->n = v;
		ad->next = nullptr;
		ad->prev = nullptr;
		first = ad;
	}
	else { put = new turm;
		   put->n = v;
		   put->next = nullptr;
		   put->prev = ad;
		   ad->next = put;
		   ad = put;
	}
	return;
}
int main() {
	int i;
	cin >> n;
	cin >> m;
	for (i = 0; i < n; i++)
	{addturm(i + 1);}
	ad->next = first;
	first->prev = ad;
	put = first;
	for (i = 0; i < n; i++) { put = put->next;
	}
	ad = first;
	while (n > 1) { put = ad;
					for (i = 1; i < m; i++) { put = put->next; }
					put->next->prev = put->prev;
					put->prev->next = put->next;
					ad = put->next;
					delete put;
					n--;
	}
	cout << ad->n;

	return 0;
}