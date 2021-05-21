#include <iostream>

using namespace std;

#define tab "\t"
#define delimiter "\n---------------------------------------------\n"

class Element
{
	int Data; // Значение элемента
	Element* pNext; // Указатель на следующий элемент
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

int Element::count = 0; // Инициализация статической переменной

class ForwardList
{
	Element* Head;
	int size;
public:
	ForwardList()
	{
		Head = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}

	// Adding elements

	void push_front(int Data)
	{
		Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;
		size++;
	}

	void push_back(int Data)
	{
		// Этот метод не умеет работать с пустым списком
		if (Head == nullptr)
		{
			push_front(Data);
			return;
		}

		Element* New = new Element(Data);
		Element* Temp = Head;
		while (Temp->pNext != nullptr)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = New;
		size++;
	}

	void insert(int Data, int index)
	{
		if (index == 0)
		{
			push_front(Data);
			return;
		}
		Element* New = new Element(Data);
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++, Temp = Temp->pNext)if (Temp == nullptr)return;
		New->pNext = Temp->pNext;
		Temp->pNext = New;
		size++;
	}

	// Erasing elements

	void pop_front()
	{
		// Прежде чем исключить элемент из списка, нужно запомнить его адрес, для того чтобы можно было шото там
		Element* Temp = Head;
		// Удаляем элемент из списка
		Head = Head->pNext;
		// Удаляем элемент из памяти
		delete Temp;
		size--;
	}

	void pop_back()
	{
		Element* Temp = Head;
		//Element* Temp2 = Head = Head->pNext;
		while (Temp->pNext != nullptr)
		{
			Temp = Temp->pNext;
			//Temp2 = Temp2->pNext;
			if (Temp->pNext->pNext == nullptr)
			{
				delete Temp->pNext;
				Temp->pNext = nullptr;
			}
		}
		size--;
	}

	// Methods

	void Print()
	{
		Element* Temp = Head;
		while (Temp != nullptr)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
		cout << "Кол-во элементов в списке: " << size << endl;
		cout << "Общее кол-во элементов: " << Element::count << endl;
	}
};

int main()
{
	setlocale(LC_ALL, "");
	system("color 0A");

	int n;
	cout << "Введите размер списка: "; cin >> n;

	ForwardList List;

	for (int i = 0; i < n; i++)
	{
		List.push_back(rand() % 100);
	}
	List.Print();
	/*cout << delimiter << endl;
	List.pop_front();
	List.Print();
	cout << delimiter << endl;
	List.pop_back();
	List.Print();*/
	int value;
	int index;
	cout << "Добавить: "; cin >> value;
	cout << "Индекс: "; cin >> index;
	List.insert(value, index);
	List.Print();

	cout << "Ещё 1 список:\n";

	ForwardList List2;
	List2.push_back(3);
	List2.push_back(2);
	List2.push_back(1);
	List2.Print();
}