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
		//âûçûâàåì ôóíêöèþ
		piramid(a, i, 0);
	}
}
//!
// Ôóíêöèÿ äëÿ âûâîäà âðåìåíè â íóæíîì ôîðìàòå
void printDuration(microseconds duration) {
	milliseconds millisec = duration_cast<milliseconds>(duration); // Ïîëó÷àåì âðåìÿ â ìèëëèñåêóíäàõ
	int microsec = duration.count() % 1000; // Îñòàòîê âðåìåíè â ìèêðîñåêóíäàõ

	cout << millisec.count()
		<< setfill('0') << setw(3) << microsec
		<< " micorsec" << endl;
}

// Ôóíêöèÿ ñðàâíåíèÿ äëÿ qsort
int compare(const void* a, const void* b) {
	return (*(int*)a - *(int*)b);
}

//ôóíêöèÿ ðàíäîìíîãî ÷èñëà
int getRandomNumber(int min, int max) 
{
	return rand() % (max - min) + min;
}

//! 
int main()
{
	setlocale(LC_ALL, "ru");
	ifstream input("d16.txt");//÷òåíèå ôàéëà
	ofstream output("ar16.txt");//çàïèñü ôàéëà
	//ïðîâåðêà íàëè÷èÿ ôàéëîâ:
	if (!input)
	{
		cerr << "îøèáêà îòêðûòèÿ ñ÷èòûâàåìîãî ôàéëà" << endl;
		return 16;
	}
	if (!output)
	{
		cerr << "îøèáêà îòêðûòèÿ âïèñûâàåìîãî ôàéëà" << endl;
		return -16;
	}

	vector<int> a,aCopy;//razmer a.size(), ochistka a.clear()		//!
	int num;//ïåðåìåííàÿ äëÿ öèêëà

	while (input >> num)//äîáàâëåíèå ÷èñåë ôàéëà â âåêòîð
	{
		a.push_back(num);
	}
	//!
	aCopy = a;
	// Çàìåð âðåìåíè ñîðòèðîâêè ïèðàìèäàëüíîé
	high_resolution_clock::time_point startPiramid = high_resolution_clock::now();
	piramidSort(a);//ñîðòèðîâêà ïèðàìèäîé
	high_resolution_clock::time_point stopPiramid = high_resolution_clock::now();
	// Ïîäñ÷åò âðåìåíè âûïîëíåíèÿ ñîðòèðîâêè ïèðàìèäû
	microseconds durationPiramid = duration_cast<microseconds>(stopPiramid - startPiramid);
	cout << "Piramid sort time for " << a.size() << " elements: ";
	printDuration(durationPiramid);

	// Çàìåð âðåìåíè ñòàíäàðòíîé ôóíêöèè qsort
	high_resolution_clock::time_point startQSort = high_resolution_clock::now();
	qsort(aCopy.data(), aCopy.size(), sizeof(int), compare);
	high_resolution_clock::time_point stopQSort = high_resolution_clock::now();

	// Ïîäñ÷åò âðåìåíè âûïîëíåíèÿ qsort
	microseconds durationQSort = duration_cast<microseconds>(stopQSort - startQSort);
	cout << "qsort time for " << aCopy.size() << " elements: ";
	printDuration(durationQSort);
	//!
	for (const int& num : a)//öèêë äëÿ çàïèñè ñîðòèðîâàííûõ ÷èñåë
	{
		output << num << endl;
	}
	//çàêðûòèå ôàéëîâ+î÷èñòêà âåêòîðà
	input.close();
	output.close();
	a.clear();

	//îòêðûòèå íîâûõ ôàéëîâ
	/*Ïðèìå÷àíèå: äàëåå êîä áóäåò âûïîëíÿòü àíàëîãè÷íûå äåéñòâèÿ ñîðòèðîâêè, íóæíû äëÿ äðóãèõ òåêñòîâûõ ôàéëîâ!*/
	//äëÿ 100 ýëåìåíòîâ:
	input.open("d100.txt");
	output.open("ar100.txt");
	//ïðîâåðêà íàëè÷èÿ ôàéëîâ:
	if (!input)
	{
		cerr << "îøèáêà îòêðûòèÿ ñ÷èòûâàåìîãî ôàéëà" << endl;
		return 16;
	}
	if (!output)
	{
		cerr << "îøèáêà îòêðûòèÿ âïèñûâàåìîãî ôàéëà" << endl;
		return -16;
	}
	while (input >> num)//äîáàâëåíèå ÷èñåë ôàéëà â âåêòîð
	{
		a.push_back(num);
	}
	//!
	aCopy = a;
	// Çàìåð âðåìåíè ñîðòèðîâêè ïèðàìèäàëüíîé
	startPiramid = high_resolution_clock::now();
	piramidSort(a);//ñîðòèðîâêà ïèðàìèäîé
	stopPiramid = high_resolution_clock::now();
	// Ïîäñ÷åò âðåìåíè âûïîëíåíèÿ ñîðòèðîâêè ïèðàìèäàëüíîé
	durationPiramid = duration_cast<microseconds>(stopPiramid - startPiramid);
	cout << "Piramid sort time for " << a.size() << " elements: ";
	printDuration(durationPiramid);

	// Çàìåð âðåìåíè ñòàíäàðòíîé ôóíêöèè qsort
	startQSort = high_resolution_clock::now();
	qsort(aCopy.data(), aCopy.size(), sizeof(int), compare);
	stopQSort = high_resolution_clock::now();

	// Ïîäñ÷åò âðåìåíè âûïîëíåíèÿ qsort
	durationQSort = duration_cast<microseconds>(stopQSort - startQSort);
	cout << "qsort time for " << aCopy.size() << " elements: ";
	printDuration(durationQSort);
	//!
	for (const int& num : a)//öèêë äëÿ çàïèñè ñîðòèðîâàííûõ ÷èñåë
	{
		output << num << endl;
	}
	//çàêðûòèå ôàéëîâ+î÷èñòêà âåêòîðà
	input.close();
	output.close();
	a.clear();

	//äëÿ 500 ýëåìåíòîâ:
	input.open("d500.txt");
	output.open("ar500.txt");
	//ïðîâåðêà íàëè÷èÿ ôàéëîâ:
	if (!input)
	{
		cerr << "îøèáêà îòêðûòèÿ ñ÷èòûâàåìîãî ôàéëà" << endl;
		return 16;
	}
	if (!output)
	{
		cerr << "îøèáêà îòêðûòèÿ âïèñûâàåìîãî ôàéëà" << endl;
		return -16;
	}
	while (input >> num)//äîáàâëåíèå ÷èñåë ôàéëà â âåêòîð
	{
		a.push_back(num);
	}
	//!
	aCopy = a;
	// Çàìåð âðåìåíè ñîðòèðîâêè ïèðàìèäàëüíîé
	startPiramid = high_resolution_clock::now();
	piramidSort(a);//ñîðòèðîâêà ïèðàìèäîé
	stopPiramid = high_resolution_clock::now();
	// Ïîäñ÷åò âðåìåíè âûïîëíåíèÿ ñîðòèðîâêè ïèðàìèäîé
	durationPiramid = duration_cast<microseconds>(stopPiramid - startPiramid);
	cout << "Piramid sort time for " << a.size() << " elements: ";
	printDuration(durationPiramid);

	// Çàìåð âðåìåíè ñòàíäàðòíîé ôóíêöèè qsort
	startQSort = high_resolution_clock::now();
	qsort(aCopy.data(), aCopy.size(), sizeof(int), compare);
	stopQSort = high_resolution_clock::now();

	// Ïîäñ÷åò âðåìåíè âûïîëíåíèÿ qsort
	durationQSort = duration_cast<microseconds>(stopQSort - startQSort);
	cout << "qsort time for " << aCopy.size() << " elements: ";
	printDuration(durationQSort);
	//!
	for (const int& num : a)//öèêë äëÿ çàïèñè ñîðòèðîâàííûõ ÷èñåë
	{
		output << num << endl;
	}
	//çàêðûòèå ôàéëîâ+î÷èñòêà âåêòîðà
	input.close();
	output.close();
	a.clear();

	//äëÿ 1000 ýëåìåíòîâ:
	input.open("d1000.txt");
	output.open("ar1000.txt");
	//ïðîâåðêà íàëè÷èÿ ôàéëîâ:
	if (!input)
	{
		cerr << "îøèáêà îòêðûòèÿ ñ÷èòûâàåìîãî ôàéëà" << endl;
		return 16;
	}
	if (!output)
	{
		cerr << "îøèáêà îòêðûòèÿ âïèñûâàåìîãî ôàéëà" << endl;
		return -16;
	}
	while (input >> num)//äîáàâëåíèå ÷èñåë ôàéëà â âåêòîð
	{
		a.push_back(num);
	}
	//!
	aCopy = a;
	// Çàìåð âðåìåíè ñîðòèðîâêè ïèðàìèäàëüíîé
	startPiramid = high_resolution_clock::now();
	piramidSort(a);//ñîðòèðîâêà ïèðàìèäàëüíàÿ
	stopPiramid = high_resolution_clock::now();
	// Ïîäñ÷åò âðåìåíè âûïîëíåíèÿ ïèðàìèäàëüíîé ñîðòèðîâêè
	durationPiramid = duration_cast<microseconds>(stopPiramid - startPiramid);
	cout << "Piramid sort time for " << a.size() << " elements: ";
	printDuration(durationPiramid);

	// Çàìåð âðåìåíè ñòàíäàðòíîé ôóíêöèè qsort
	startQSort = high_resolution_clock::now();
	qsort(aCopy.data(), aCopy.size(), sizeof(int), compare);
	stopQSort = high_resolution_clock::now();

	// Ïîäñ÷åò âðåìåíè âûïîëíåíèÿ qsort
	durationQSort = duration_cast<microseconds>(stopQSort - startQSort);
	cout << "qsort time for " << aCopy.size() << " elements: ";
	printDuration(durationQSort);
	//!
	for (const int& num : a)//öèêë äëÿ çàïèñè ñîðòèðîâàííûõ ÷èñåë
	{
		output << num << endl;
	}
	//çàêðûòèå ôàéëîâ+î÷èñòêà âåêòîðà
	input.close();
	output.close();
	a.clear();

	//äëÿ 5000 ýëåìåíòîâ:
	input.open("d5000.txt");
	output.open("ar5000.txt");
	//ïðîâåðêà íàëè÷èÿ ôàéëîâ:
	if (!input)
	{
		cerr << "îøèáêà îòêðûòèÿ ñ÷èòûâàåìîãî ôàéëà" << endl;
		return 16;
	}
	if (!output)
	{
		cerr << "îøèáêà îòêðûòèÿ âïèñûâàåìîãî ôàéëà" << endl;
		return -16;
	}
	while (input >> num)//äîáàâëåíèå ÷èñåë ôàéëà â âåêòîð
	{
		a.push_back(num);
	}
	//!
	aCopy = a;
	// Çàìåð âðåìåíè ñîðòèðîâêè ïèðàìèäàëüíîé
	startPiramid = high_resolution_clock::now();
	piramidSort(a);//ñîðòèðîâêà ïèðàìèäàëüíàÿ
	stopPiramid = high_resolution_clock::now();
	// Ïîäñ÷åò âðåìåíè ïèðàìèäàëüíîé ñîðòèðîâêè
	durationPiramid = duration_cast<microseconds>(stopPiramid - startPiramid);
	cout << "Piramid sort time for " << a.size() << " elements: ";
	printDuration(durationPiramid);

	// Çàìåð âðåìåíè ñòàíäàðòíîé ôóíêöèè qsort
	startQSort = high_resolution_clock::now();
	qsort(aCopy.data(), aCopy.size(), sizeof(int), compare);
	stopQSort = high_resolution_clock::now();

	// Ïîäñ÷åò âðåìåíè âûïîëíåíèÿ qsort
	durationQSort = duration_cast<microseconds>(stopQSort - startQSort);
	cout << "qsort time for " << aCopy.size() << " elements: ";
	printDuration(durationQSort);
	//!
	for (const int& num : a)//öèêë äëÿ çàïèñè ñîðòèðîâàííûõ ÷èñåë
	{
		output << num << endl;
	}
	//çàêðûòèå ôàéëîâ+î÷èñòêà âåêòîðà
	input.close();
	output.close();
	a.clear();
	//îêîí÷àíèå ïðîãðàììû:
	cout << "ïðîãðàììà âûïîëíåíà" << endl;
	cout << "õîòèòå åùå ïîèãðàòüñÿ? 1-ñîðòèðîâêà ñ ïðîèçâîëüíûìè ðàíäîìíûìè ÷èñëàìè" << endl;
	cin >> num;
	while (num == 1)
	{
		int k,min,max;//êîëè÷åñòâî ÷èñåë,ìèíèìàëüíîå è ìàêñèìàëüíîå ÷èñëî
		cout << "ââåäèòå êîëè÷åñòâî, ìèíèìàëüíîå è ìàêñèìàëüíîå ÷èñëî" << endl;
		cin >> k >> min >> max;
		for (int i = 0; i < k; i++) 
		{
			a.push_back(getRandomNumber(min,max));// äèàïàçîí [min, max]
		}
		output.open("any.txt");
		//ïðîâåðêà íàëè÷èÿ ôàéëîâ:
		if (!output)
		{
			cerr << "îøèáêà îòêðûòèÿ âïèñûâàåìîãî ôàéëà" << endl;
			return -16;
		}
		//!
		aCopy = a;
		// Çàìåð âðåìåíè ñîðòèðîâêè ïèðàìèäàëüíîé
		startPiramid = high_resolution_clock::now();
		piramidSort(a);//ñîðòèðîâêà ïèðàìèäîé
		stopPiramid = high_resolution_clock::now();
		// Ïîäñ÷åò âðåìåíè âûïîëíåíèÿ ñîðòèðîâêè ïèðàìèäàëüíîé
		durationPiramid = duration_cast<microseconds>(stopPiramid - startPiramid);
		cout << "Piramid sort time for " << a.size() << " elements: ";
		printDuration(durationPiramid);

		// Çàìåð âðåìåíè ñòàíäàðòíîé ôóíêöèè qsort
		startQSort = high_resolution_clock::now();
		qsort(aCopy.data(), aCopy.size(), sizeof(int), compare);
		stopQSort = high_resolution_clock::now();

		// Ïîäñ÷åò âðåìåíè âûïîëíåíèÿ qsort
		durationQSort = duration_cast<microseconds>(stopQSort - startQSort);
		cout << "qsort time for " << aCopy.size() << " elements: ";
		printDuration(durationQSort);
		//!
		for (const int& num : a)//öèêë äëÿ çàïèñè ñîðòèðîâàííûõ ÷èñåë
		{
			output << num << endl;
		}

		input.close();
		output.close();
		a.clear();
		cout << "ïîâòîðèòü 1?" << endl; cin >> num;
	}
	return 0;
}
