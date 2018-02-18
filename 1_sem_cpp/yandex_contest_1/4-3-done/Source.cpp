#include <iostream>
#include <assert.h>
using namespace std;
class stack {
public:
	stack(int _buffersize);
	~stack();
	void draw();
	void pushback(int a);
	int popback();
	bool empty() const { return realSize == 0; }
	int size() const { return realSize; }
private:
	void expand();
	int* buffer;
	int bufferSize;
	int realSize;
	int front;
};
stack::stack(int _buffersize) :
	bufferSize(_buffersize),
	front(-1),
	realSize(0)
{
	buffer = new int[bufferSize];
}

stack::~stack()
{
	delete[] buffer;
}

void stack::expand() {
	int newBufferSize = bufferSize * 2;
	int *newBuffer = new int[newBufferSize];
	for (int i = 0; i < bufferSize; i++) {
		newBuffer[i] = buffer[i];
	}
	delete[] buffer;
	buffer = newBuffer;
	bufferSize = newBufferSize;
}

void stack::pushback(int a)
{
	if (realSize == bufferSize)
		expand();
	front++;
	buffer[front] = a;
	realSize++;
}
int stack::popback()
{
	realSize--;
	return buffer[front--];
}

void stack::draw() {
	cout << "front: " << front << endl;
	cout << "realSize:" << realSize << endl;
	for (int i = 0; i < bufferSize; i++) {
		cout << buffer[i] << " ";
	}
	cout << endl;

	cout << "-------------";
	cout << endl;
}

class queue {
public:
	queue();
	~queue();
	void pushback(int a);
	int popfront();
	bool empty();
private:
	void movefirtosec();
	stack *first;
	stack *second;
};

queue::queue() {
	first = new stack(2);
	second = new stack(2);
}

queue::~queue() {
	delete first;
	delete second;
}

void queue::movefirtosec() {
	while (!first->empty())
	{
		second->pushback(first->popback());
	}
}

bool queue::empty() {
	return first->empty() && second->empty();
}

void queue::pushback(int a) {
	first->pushback(a);
}

int queue::popfront() {
	if (second->empty())
	{
		movefirtosec();
	}
	//second->draw();

	return second->popback();

}

int main() {
	int n;
	int a;
	int b;
	bool possible = true;
	queue q;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int k = -1;
		cin >> a >> b;
		if (a == 2) {
			if (!q.empty()) { k = q.popfront(); }
			//cout << "K: " << k << "; B: "<<b<< endl;
			if (b != k) { 
				possible = false; 
			}
		}
		else
		{
			q.pushback(b);
		}
	}

	if (possible) { cout << "YES"; }
	else { cout << "NO"; }

	return 0;
}	