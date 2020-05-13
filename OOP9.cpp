// OOP9.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <clocale>
#include <iomanip>
#include <ctime>
#include <Windows.h>

using namespace std;

struct List
{
	List() : Next(nullptr), Prev(nullptr) {}
	int info;
	List* Next, *Prev;
};

void SetColor(int text, int background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

//сортировка туть
void InsertionSort(List* head)
{
	List* curr = nullptr, *prev = nullptr;
	for (curr = head->Next; curr->Next; curr = curr->Next)
	{
		int tmp = curr->info;
		for (prev = curr->Prev; prev && prev->info > tmp; prev = prev->Prev)
		{
			prev->Next->info = prev->info;
		}
		prev->Next->info = tmp;
	}
}


//вставка элемента Ррр после элемента ласт
List* InsertElementIntoList(List* last, List* p)
{
	if (last != NULL || p != NULL)
	{
		p->Prev = last;
		p->Next = last->Next;
		last->Next = p;
		p->Next->Prev = p;
		return p;
	}
	else
		return NULL;
}

void DeleteElementFromList(List* head, int e) {
	if (head != NULL) {
		for (List* curr = head->Next; curr->Next; curr = curr->Next)
		{
			if (curr->info == e) {
				curr->Next->Prev = curr->Prev;
				curr->Prev->Next = curr->Next;
				delete curr;
				break;
			}
		}
	}
}

int SearchElement(List* head, int e) {
	int i = 0;
	if (head != NULL) {
		for (List* curr = head->Next; curr->Next; curr = curr->Next, ++i)
		{
			if (curr->info == e) {
				return i;
			}
		}
	}
	return -1;
}

//двусвязный список из Н элементов
//хед и тейл указатели
void CreateList(List*& head, List*& tail, int n)
{
	head = new List;
	tail = new List;

	head->Next = tail;
	tail->Prev = head;

	srand(time(NULL));

	List* last; //тут последний вставленный элемент в список
	last = head;

	for (int i = 0; i < n; i++)
	{
		List* p = new List;
		cout << "Введите  " << i + 1 << "-ый элемент:\t";
		SetColor(1, 15);
		cin >> p->info;
		SetColor(0, 15);
		last = InsertElementIntoList(last, p);
	}
}


// вывод на экран
void PrintList(List* head, List* tail)
{
	List* p = head->Next;
	while (p != tail)
	{
		cout << setw(6) << p->info;
		p = p->Next;
	}
	cout << endl;
}

int main()
{
	while (true) {
		setlocale(LC_CTYPE, "rus");
		int k;
		char q;
		cout << "Введите количество элементов:\t";
		SetColor(1, 15);
		cin >> k;
		if (!cin){
			cout << "Вы должны вводить лишь цифры\n";
			cin.clear();
			while (cin.get() != '\n'); {
				cout << "Бестолочь";
				break;
			}
		}

		SetColor(0, 15);

		List* head, *tail;
		CreateList(head, tail, k);
		cout << "Исходный список: ";
		SetColor(2, 15);
		PrintList(head, tail);
		SetColor(0, 15);

		InsertionSort(head);
		cout << "Отсортированный список: ";
		SetColor(4, 15);
		PrintList(head, tail);
		SetColor(0, 15);


		int delE;
		cout << "Удалить цифру: \t";
		cin >> delE;
		DeleteElementFromList(head, delE);

		cout << "Новый список:\t";
		PrintList(head, tail);

		cout << "Найти:\t";
		int searchE;
		cin >> searchE;
		searchE = SearchElement(head, searchE);
		if (searchE != -1) {
			cout << "Найден под индексом " << searchE << endl;
		}
		else
			cout << "Такого в списке нет" << endl;



		cout << "Желаете продолжить? Y/N\t";
		cin >> q;

		try
		{
			if (q == 'Y' || q == 'y') {
				continue;
			}
			else if (q == 'N' || q == 'n') {
				cout << "Завершение программы...";
				break;
			}
			else //if(q != 'N' && q != 'n' && q != 'N' && q != 'n')
			{
				throw 123;
			}

		}
		catch (int i)
		{
			cout << "Ошибка № " << i << "Требовалось ввести Y или N !!!!" << endl << "Начнём заново" << endl;
			cout << "Желаете продолжить? Y/N\t";
			cin >> q;
			if (q == 'Y' || q == 'y') {
				continue;
			}
			else if (q == 'N' || q == 'n') {
				cout << "Завершение программы...";
				break;
			}
			else // if(q != 'N' || q != 'n' || q != 'N' || q != 'n')
			{
				SetColor(4, 15);
				cout << "Ну тебе же по-русски сказали...\nЗавершаю программу, больше сюда не заходи...";
				SetColor(0, 15);
				break;
			}
		}
	}
	return 0;
}

