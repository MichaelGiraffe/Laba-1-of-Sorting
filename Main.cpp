#include <iostream>//cin;cout
#include <fstream>//open_close .txt files
#include <vector>//because never use it before
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;
using namespace chrono;
/*//тут сортировка выборкой, решил вспомнить ее заодно
void selectionSort(vector <int> &a)//сортировка выборкой
{
	int mn;//минимальный индекс
	int n = a.size();//размер вектора
	for (int i = 0; i < n-1; i++)//ищем мин. индекс
	{
		mn = i;
		for (int q = i + 1; q < n; q++)//цикл выбора индекса
		{
			if (a[mn] > a[q])
			{
				mn = q;
			}
		}
		if (mn != i)//заменяем значения двух индексов
		{
			swap(a[i], a[mn]);
		}
	}
}
*/

//функция для преобразования вектора в пирамиду
void piramid(vector<int>& a, int n, int i)
{
	int max = i;//наиб. элемент как корень
	int left = 2 * i + 1;//левый дочерний элемент
	int right = 2 * i + 2;//правый дочерний элемент

	//если левый дочерний элемент больше корня
	if (left<n && a[left]>a[max])
	{
		max = left;
	}
	//если правый дочерний элемент больше корня
	if (right<n && a[right]>a[max])
	{
		max = right;
	}

	//если наибольший элемент не является корнем
	if (max != i)
	{
		swap(a[i], a[max]);
		//рекурсивно преобразуем поддерево в кучу
		piramid(a, n, max);
	}
}

//основная функция пирамидальной сортировки
void piramidSort(vector<int>& a)
{
	int n = a.size();

	//построение кучи(пирамиды)
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		piramid(a, n, i);
	}
	//поочередно извлекаем элементы из кучи
	for (int i = n - 1; i > 0; i--)
	{
		//перемещаем текущий корень в конец массива
		swap(a[0], a[i]);
		//вызываем функцию
		piramid(a, i, 0);
	}
}
//!
// Функция для вывода времени в нужном формате
void printDuration(microseconds duration) {
	milliseconds millisec = duration_cast<milliseconds>(duration); // Получаем время в миллисекундах
	int microsec = duration.count() % 1000; // Остаток времени в микросекундах

	cout << millisec.count()
		<< setfill('0') << setw(3) << microsec
		<< " micorsec" << endl;
}

// Функция сравнения для qsort
int compare(const void* a, const void* b) {
	return (*(int*)a - *(int*)b);
}

//функция рандомного числа
int getRandomNumber(int min, int max) 
{
	return rand() % (max - min) + min;
}

//! 
int main()
{
	setlocale(LC_ALL, "ru");
	ifstream input("d16.txt");//чтение файла
	ofstream output("ar16.txt");//запись файла
	//проверка наличия файлов:
	if (!input)
	{
		cerr << "ошибка открытия считываемого файла" << endl;
		return 16;
	}
	if (!output)
	{
		cerr << "ошибка открытия вписываемого файла" << endl;
		return -16;
	}

	vector<int> a,aCopy;//razmer a.size(), ochistka a.clear()		//!
	int num;//переменная для цикла

	while (input >> num)//добавление чисел файла в вектор
	{
		a.push_back(num);
	}
	//!
	aCopy = a;
	// Замер времени сортировки пирамидальной
	high_resolution_clock::time_point startPiramid = high_resolution_clock::now();
	piramidSort(a);//сортировка пирамидой
	high_resolution_clock::time_point stopPiramid = high_resolution_clock::now();
	// Подсчет времени выполнения сортировки пирамиды
	microseconds durationPiramid = duration_cast<microseconds>(stopPiramid - startPiramid);
	cout << "Piramid sort time for " << a.size() << " elements: ";
	printDuration(durationPiramid);

	// Замер времени стандартной функции qsort
	high_resolution_clock::time_point startQSort = high_resolution_clock::now();
	qsort(aCopy.data(), aCopy.size(), sizeof(int), compare);
	high_resolution_clock::time_point stopQSort = high_resolution_clock::now();

	// Подсчет времени выполнения qsort
	microseconds durationQSort = duration_cast<microseconds>(stopQSort - startQSort);
	cout << "qsort time for " << aCopy.size() << " elements: ";
	printDuration(durationQSort);
	//!
	for (const int& num : a)//цикл для записи сортированных чисел
	{
		output << num << endl;
	}
	//закрытие файлов+очистка вектора
	input.close();
	output.close();
	a.clear();

	//открытие новых файлов
	/*Примечание: далее код будет выполнять аналогичные действия сортировки, нужны для других текстовых файлов!*/
	//для 100 элементов:
	input.open("d100.txt");
	output.open("ar100.txt");
	//проверка наличия файлов:
	if (!input)
	{
		cerr << "ошибка открытия считываемого файла" << endl;
		return 16;
	}
	if (!output)
	{
		cerr << "ошибка открытия вписываемого файла" << endl;
		return -16;
	}
	while (input >> num)//добавление чисел файла в вектор
	{
		a.push_back(num);
	}
	//!
	aCopy = a;
	// Замер времени сортировки пирамидальной
	startPiramid = high_resolution_clock::now();
	piramidSort(a);//сортировка пирамидой
	stopPiramid = high_resolution_clock::now();
	// Подсчет времени выполнения сортировки пирамидальной
	durationPiramid = duration_cast<microseconds>(stopPiramid - startPiramid);
	cout << "Piramid sort time for " << a.size() << " elements: ";
	printDuration(durationPiramid);

	// Замер времени стандартной функции qsort
	startQSort = high_resolution_clock::now();
	qsort(aCopy.data(), aCopy.size(), sizeof(int), compare);
	stopQSort = high_resolution_clock::now();

	// Подсчет времени выполнения qsort
	durationQSort = duration_cast<microseconds>(stopQSort - startQSort);
	cout << "qsort time for " << aCopy.size() << " elements: ";
	printDuration(durationQSort);
	//!
	for (const int& num : a)//цикл для записи сортированных чисел
	{
		output << num << endl;
	}
	//закрытие файлов+очистка вектора
	input.close();
	output.close();
	a.clear();

	//для 500 элементов:
	input.open("d500.txt");
	output.open("ar500.txt");
	//проверка наличия файлов:
	if (!input)
	{
		cerr << "ошибка открытия считываемого файла" << endl;
		return 16;
	}
	if (!output)
	{
		cerr << "ошибка открытия вписываемого файла" << endl;
		return -16;
	}
	while (input >> num)//добавление чисел файла в вектор
	{
		a.push_back(num);
	}
	//!
	aCopy = a;
	// Замер времени сортировки пирамидальной
	startPiramid = high_resolution_clock::now();
	piramidSort(a);//сортировка пирамидой
	stopPiramid = high_resolution_clock::now();
	// Подсчет времени выполнения сортировки пирамидой
	durationPiramid = duration_cast<microseconds>(stopPiramid - startPiramid);
	cout << "Piramid sort time for " << a.size() << " elements: ";
	printDuration(durationPiramid);

	// Замер времени стандартной функции qsort
	startQSort = high_resolution_clock::now();
	qsort(aCopy.data(), aCopy.size(), sizeof(int), compare);
	stopQSort = high_resolution_clock::now();

	// Подсчет времени выполнения qsort
	durationQSort = duration_cast<microseconds>(stopQSort - startQSort);
	cout << "qsort time for " << aCopy.size() << " elements: ";
	printDuration(durationQSort);
	//!
	for (const int& num : a)//цикл для записи сортированных чисел
	{
		output << num << endl;
	}
	//закрытие файлов+очистка вектора
	input.close();
	output.close();
	a.clear();

	//для 1000 элементов:
	input.open("d1000.txt");
	output.open("ar1000.txt");
	//проверка наличия файлов:
	if (!input)
	{
		cerr << "ошибка открытия считываемого файла" << endl;
		return 16;
	}
	if (!output)
	{
		cerr << "ошибка открытия вписываемого файла" << endl;
		return -16;
	}
	while (input >> num)//добавление чисел файла в вектор
	{
		a.push_back(num);
	}
	//!
	aCopy = a;
	// Замер времени сортировки пирамидальной
	startPiramid = high_resolution_clock::now();
	piramidSort(a);//сортировка пирамидальная
	stopPiramid = high_resolution_clock::now();
	// Подсчет времени выполнения пирамидальной сортировки
	durationPiramid = duration_cast<microseconds>(stopPiramid - startPiramid);
	cout << "Piramid sort time for " << a.size() << " elements: ";
	printDuration(durationPiramid);

	// Замер времени стандартной функции qsort
	startQSort = high_resolution_clock::now();
	qsort(aCopy.data(), aCopy.size(), sizeof(int), compare);
	stopQSort = high_resolution_clock::now();

	// Подсчет времени выполнения qsort
	durationQSort = duration_cast<microseconds>(stopQSort - startQSort);
	cout << "qsort time for " << aCopy.size() << " elements: ";
	printDuration(durationQSort);
	//!
	for (const int& num : a)//цикл для записи сортированных чисел
	{
		output << num << endl;
	}
	//закрытие файлов+очистка вектора
	input.close();
	output.close();
	a.clear();

	//для 5000 элементов:
	input.open("d5000.txt");
	output.open("ar5000.txt");
	//проверка наличия файлов:
	if (!input)
	{
		cerr << "ошибка открытия считываемого файла" << endl;
		return 16;
	}
	if (!output)
	{
		cerr << "ошибка открытия вписываемого файла" << endl;
		return -16;
	}
	while (input >> num)//добавление чисел файла в вектор
	{
		a.push_back(num);
	}
	//!
	aCopy = a;
	// Замер времени сортировки пирамидальной
	startPiramid = high_resolution_clock::now();
	piramidSort(a);//сортировка пирамидальная
	stopPiramid = high_resolution_clock::now();
	// Подсчет времени пирамидальной сортировки
	durationPiramid = duration_cast<microseconds>(stopPiramid - startPiramid);
	cout << "Piramid sort time for " << a.size() << " elements: ";
	printDuration(durationPiramid);

	// Замер времени стандартной функции qsort
	startQSort = high_resolution_clock::now();
	qsort(aCopy.data(), aCopy.size(), sizeof(int), compare);
	stopQSort = high_resolution_clock::now();

	// Подсчет времени выполнения qsort
	durationQSort = duration_cast<microseconds>(stopQSort - startQSort);
	cout << "qsort time for " << aCopy.size() << " elements: ";
	printDuration(durationQSort);
	//!
	for (const int& num : a)//цикл для записи сортированных чисел
	{
		output << num << endl;
	}
	//закрытие файлов+очистка вектора
	input.close();
	output.close();
	a.clear();
	//окончание программы:
	cout << "программа выполнена" << endl;
	cout << "хотите еще поиграться? 1-сортировка с произвольными рандомными числами" << endl;
	cin >> num;
	while (num == 1)
	{
		int k,min,max;//количество чисел,минимальное и максимальное число
		cout << "введите количество, минимальное и максимальное число" << endl;
		cin >> k >> min >> max;
		for (int i = 0; i < k; i++) 
		{
			a.push_back(getRandomNumber(min,max));// диапазон [min, max]
		}
		output.open("any.txt");
		//проверка наличия файлов:
		if (!output)
		{
			cerr << "ошибка открытия вписываемого файла" << endl;
			return -16;
		}
		//!
		aCopy = a;
		// Замер времени сортировки пирамидальной
		startPiramid = high_resolution_clock::now();
		piramidSort(a);//сортировка пирамидой
		stopPiramid = high_resolution_clock::now();
		// Подсчет времени выполнения сортировки пирамидальной
		durationPiramid = duration_cast<microseconds>(stopPiramid - startPiramid);
		cout << "Piramid sort time for " << a.size() << " elements: ";
		printDuration(durationPiramid);

		// Замер времени стандартной функции qsort
		startQSort = high_resolution_clock::now();
		qsort(aCopy.data(), aCopy.size(), sizeof(int), compare);
		stopQSort = high_resolution_clock::now();

		// Подсчет времени выполнения qsort
		durationQSort = duration_cast<microseconds>(stopQSort - startQSort);
		cout << "qsort time for " << aCopy.size() << " elements: ";
		printDuration(durationQSort);
		//!
		for (const int& num : a)//цикл для записи сортированных чисел
		{
			output << num << endl;
		}

		input.close();
		output.close();
		a.clear();
		cout << "повторить 1?" << endl; cin >> num;
	}
	return 0;
}