#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#pragma warning (disable : 4996)
// Куча целых чисел, реализованная с помощью массива.
class CArray
{
public:
	CArray(int size);
	~CArray() { delete Mas; };
	int Amount() { return Number; };
	int GetFirst();
	void SiftUp(int);
	void SiftDown(int);
	void AddElement(int);		//Добавление элемента
private:
	int* Mas;	//Массив данных
	int SizeMas;	//Размер кучи
	int Number;	//Количество уже заполненных элементов
	void Swap(int, int);		//Смена мест элементов с заданными индексами
};

int CArray::GetFirst()
{
	int temp = Mas[0];
	Swap(0, --Number);
	SiftDown(0);
	return temp;
}

// Проталкивание элемента вниз.
void CArray::SiftDown(int i)
{
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	// Ищем меньшего сына, если такой есть.
	int largest = i;
	if (left < Number && Mas[left] < Mas[i])
		largest = left;
	if (right < Number && Mas[right] < Mas[largest])
		largest = right;
	// Если меньший сын есть, то проталкиваем корень в него.
	if (largest != i)
	{
		Swap(i, largest);
		this->SiftDown(largest);
	}
}


// Проталкивание элемента наверх.
void CArray::SiftUp(int i)
{
	int parent;
	while (i > 0)
	{
		parent = (i - 1) / 2;
		if (Mas[i] <= Mas[parent])
			Swap(i, parent);
		i = parent;
	}
}

void CArray::Swap(int i, int j)
{
	Mas[i] = Mas[i] ^ Mas[j];
	Mas[j] = Mas[i] ^ Mas[j];
	Mas[i] = Mas[i] ^ Mas[j];
}

CArray::CArray(int size) : SizeMas(size), Number(0)
{
	Mas = new int[SizeMas]; // Создаем буфер.
}

void CArray::AddElement(int Data)
{
	Mas[Number] = Data;
	SiftUp(Number);
	Number++;
}

//Расчет времени
int CalculateTime(CArray* IntMas)
{
	int time = 0;
	int Sum = 0;
	while (IntMas->Amount() > 1)
	{
		Sum = IntMas->GetFirst();
		Sum += IntMas->GetFirst();
		IntMas->AddElement(Sum);
		time += Sum;
	}
	return time;
}

int main()
{
	//Получение количства слагаемых
	int Number = 0;
	if (scanf("%d\n", &Number) != 1)
		return 0;
	assert(Number >= 0);

	CArray IntMas(Number);

	int num;
	for (int i = 0; i < Number; ++i)
	{
		scanf("%d", &num);
		IntMas.AddElement(num);
	}

	printf("%d\n", CalculateTime(&IntMas));
	return 0;
}




