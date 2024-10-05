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
/*//��� ���������� ��������, ����� ��������� �� ������
void selectionSort(vector <int> &a)//���������� ��������
{
	int mn;//����������� ������
	int n = a.size();//������ �������
	for (int i = 0; i < n-1; i++)//���� ���. ������
	{
		mn = i;
		for (int q = i + 1; q < n; q++)//���� ������ �������
		{
			if (a[mn] > a[q])
			{
				mn = q;
			}
		}
		if (mn != i)//�������� �������� ���� ��������
		{
			swap(a[i], a[mn]);
		}
	}
}
*/

//������� ��� �������������� ������� � ��������
void piramid(vector<int>& a, int n, int i)
{
	int max = i;//����. ������� ��� ������
	int left = 2 * i + 1;//����� �������� �������
	int right = 2 * i + 2;//������ �������� �������

	//���� ����� �������� ������� ������ �����
	if (left<n && a[left]>a[max])
	{
		max = left;
	}
	//���� ������ �������� ������� ������ �����
	if (right<n && a[right]>a[max])
	{
		max = right;
	}

	//���� ���������� ������� �� �������� ������
	if (max != i)
	{
		swap(a[i], a[max]);
		//���������� ����������� ��������� � ����
		piramid(a, n, max);
	}
}

//�������� ������� ������������� ����������
void piramidSort(vector<int>& a)
{
	int n = a.size();

	//���������� ����(��������)
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		piramid(a, n, i);
	}
	//���������� ��������� �������� �� ����
	for (int i = n - 1; i > 0; i--)
	{
		//���������� ������� ������ � ����� �������
		swap(a[0], a[i]);
		//�������� �������
		piramid(a, i, 0);
	}
}
//!
// ������� ��� ������ ������� � ������ �������
void printDuration(microseconds duration) {
	milliseconds millisec = duration_cast<milliseconds>(duration); // �������� ����� � �������������
	int microsec = duration.count() % 1000; // ������� ������� � �������������

	cout << millisec.count()
		<< setfill('0') << setw(3) << microsec
		<< " micorsec" << endl;
}

// ������� ��������� ��� qsort
int compare(const void* a, const void* b) {
	return (*(int*)a - *(int*)b);
}

//������� ���������� �����
int getRandomNumber(int min, int max) 
{
	return rand() % (max - min) + min;
}

//! 
int main()
{
	setlocale(LC_ALL, "ru");
	ifstream input("d16.txt");//������ �����
	ofstream output("ar16.txt");//������ �����
	//�������� ������� ������:
	if (!input)
	{
		cerr << "������ �������� ������������ �����" << endl;
		return 16;
	}
	if (!output)
	{
		cerr << "������ �������� ������������ �����" << endl;
		return -16;
	}

	vector<int> a,aCopy;//razmer a.size(), ochistka a.clear()		//!
	int num;//���������� ��� �����

	while (input >> num)//���������� ����� ����� � ������
	{
		a.push_back(num);
	}
	//!
	aCopy = a;
	// ����� ������� ���������� �������������
	high_resolution_clock::time_point startPiramid = high_resolution_clock::now();
	piramidSort(a);//���������� ���������
	high_resolution_clock::time_point stopPiramid = high_resolution_clock::now();
	// ������� ������� ���������� ���������� ��������
	microseconds durationPiramid = duration_cast<microseconds>(stopPiramid - startPiramid);
	cout << "Piramid sort time for " << a.size() << " elements: ";
	printDuration(durationPiramid);

	// ����� ������� ����������� ������� qsort
	high_resolution_clock::time_point startQSort = high_resolution_clock::now();
	qsort(aCopy.data(), aCopy.size(), sizeof(int), compare);
	high_resolution_clock::time_point stopQSort = high_resolution_clock::now();

	// ������� ������� ���������� qsort
	microseconds durationQSort = duration_cast<microseconds>(stopQSort - startQSort);
	cout << "qsort time for " << aCopy.size() << " elements: ";
	printDuration(durationQSort);
	//!
	for (const int& num : a)//���� ��� ������ ������������� �����
	{
		output << num << endl;
	}
	//�������� ������+������� �������
	input.close();
	output.close();
	a.clear();

	//�������� ����� ������
	/*����������: ����� ��� ����� ��������� ����������� �������� ����������, ����� ��� ������ ��������� ������!*/
	//��� 100 ���������:
	input.open("d100.txt");
	output.open("ar100.txt");
	//�������� ������� ������:
	if (!input)
	{
		cerr << "������ �������� ������������ �����" << endl;
		return 16;
	}
	if (!output)
	{
		cerr << "������ �������� ������������ �����" << endl;
		return -16;
	}
	while (input >> num)//���������� ����� ����� � ������
	{
		a.push_back(num);
	}
	//!
	aCopy = a;
	// ����� ������� ���������� �������������
	startPiramid = high_resolution_clock::now();
	piramidSort(a);//���������� ���������
	stopPiramid = high_resolution_clock::now();
	// ������� ������� ���������� ���������� �������������
	durationPiramid = duration_cast<microseconds>(stopPiramid - startPiramid);
	cout << "Piramid sort time for " << a.size() << " elements: ";
	printDuration(durationPiramid);

	// ����� ������� ����������� ������� qsort
	startQSort = high_resolution_clock::now();
	qsort(aCopy.data(), aCopy.size(), sizeof(int), compare);
	stopQSort = high_resolution_clock::now();

	// ������� ������� ���������� qsort
	durationQSort = duration_cast<microseconds>(stopQSort - startQSort);
	cout << "qsort time for " << aCopy.size() << " elements: ";
	printDuration(durationQSort);
	//!
	for (const int& num : a)//���� ��� ������ ������������� �����
	{
		output << num << endl;
	}
	//�������� ������+������� �������
	input.close();
	output.close();
	a.clear();

	//��� 500 ���������:
	input.open("d500.txt");
	output.open("ar500.txt");
	//�������� ������� ������:
	if (!input)
	{
		cerr << "������ �������� ������������ �����" << endl;
		return 16;
	}
	if (!output)
	{
		cerr << "������ �������� ������������ �����" << endl;
		return -16;
	}
	while (input >> num)//���������� ����� ����� � ������
	{
		a.push_back(num);
	}
	//!
	aCopy = a;
	// ����� ������� ���������� �������������
	startPiramid = high_resolution_clock::now();
	piramidSort(a);//���������� ���������
	stopPiramid = high_resolution_clock::now();
	// ������� ������� ���������� ���������� ���������
	durationPiramid = duration_cast<microseconds>(stopPiramid - startPiramid);
	cout << "Piramid sort time for " << a.size() << " elements: ";
	printDuration(durationPiramid);

	// ����� ������� ����������� ������� qsort
	startQSort = high_resolution_clock::now();
	qsort(aCopy.data(), aCopy.size(), sizeof(int), compare);
	stopQSort = high_resolution_clock::now();

	// ������� ������� ���������� qsort
	durationQSort = duration_cast<microseconds>(stopQSort - startQSort);
	cout << "qsort time for " << aCopy.size() << " elements: ";
	printDuration(durationQSort);
	//!
	for (const int& num : a)//���� ��� ������ ������������� �����
	{
		output << num << endl;
	}
	//�������� ������+������� �������
	input.close();
	output.close();
	a.clear();

	//��� 1000 ���������:
	input.open("d1000.txt");
	output.open("ar1000.txt");
	//�������� ������� ������:
	if (!input)
	{
		cerr << "������ �������� ������������ �����" << endl;
		return 16;
	}
	if (!output)
	{
		cerr << "������ �������� ������������ �����" << endl;
		return -16;
	}
	while (input >> num)//���������� ����� ����� � ������
	{
		a.push_back(num);
	}
	//!
	aCopy = a;
	// ����� ������� ���������� �������������
	startPiramid = high_resolution_clock::now();
	piramidSort(a);//���������� �������������
	stopPiramid = high_resolution_clock::now();
	// ������� ������� ���������� ������������� ����������
	durationPiramid = duration_cast<microseconds>(stopPiramid - startPiramid);
	cout << "Piramid sort time for " << a.size() << " elements: ";
	printDuration(durationPiramid);

	// ����� ������� ����������� ������� qsort
	startQSort = high_resolution_clock::now();
	qsort(aCopy.data(), aCopy.size(), sizeof(int), compare);
	stopQSort = high_resolution_clock::now();

	// ������� ������� ���������� qsort
	durationQSort = duration_cast<microseconds>(stopQSort - startQSort);
	cout << "qsort time for " << aCopy.size() << " elements: ";
	printDuration(durationQSort);
	//!
	for (const int& num : a)//���� ��� ������ ������������� �����
	{
		output << num << endl;
	}
	//�������� ������+������� �������
	input.close();
	output.close();
	a.clear();

	//��� 5000 ���������:
	input.open("d5000.txt");
	output.open("ar5000.txt");
	//�������� ������� ������:
	if (!input)
	{
		cerr << "������ �������� ������������ �����" << endl;
		return 16;
	}
	if (!output)
	{
		cerr << "������ �������� ������������ �����" << endl;
		return -16;
	}
	while (input >> num)//���������� ����� ����� � ������
	{
		a.push_back(num);
	}
	//!
	aCopy = a;
	// ����� ������� ���������� �������������
	startPiramid = high_resolution_clock::now();
	piramidSort(a);//���������� �������������
	stopPiramid = high_resolution_clock::now();
	// ������� ������� ������������� ����������
	durationPiramid = duration_cast<microseconds>(stopPiramid - startPiramid);
	cout << "Piramid sort time for " << a.size() << " elements: ";
	printDuration(durationPiramid);

	// ����� ������� ����������� ������� qsort
	startQSort = high_resolution_clock::now();
	qsort(aCopy.data(), aCopy.size(), sizeof(int), compare);
	stopQSort = high_resolution_clock::now();

	// ������� ������� ���������� qsort
	durationQSort = duration_cast<microseconds>(stopQSort - startQSort);
	cout << "qsort time for " << aCopy.size() << " elements: ";
	printDuration(durationQSort);
	//!
	for (const int& num : a)//���� ��� ������ ������������� �����
	{
		output << num << endl;
	}
	//�������� ������+������� �������
	input.close();
	output.close();
	a.clear();
	//��������� ���������:
	cout << "��������� ���������" << endl;
	cout << "������ ��� ����������? 1-���������� � ������������� ���������� �������" << endl;
	cin >> num;
	while (num == 1)
	{
		int k,min,max;//���������� �����,����������� � ������������ �����
		cout << "������� ����������, ����������� � ������������ �����" << endl;
		cin >> k >> min >> max;
		for (int i = 0; i < k; i++) 
		{
			a.push_back(getRandomNumber(min,max));// �������� [min, max]
		}
		output.open("any.txt");
		//�������� ������� ������:
		if (!output)
		{
			cerr << "������ �������� ������������ �����" << endl;
			return -16;
		}
		//!
		aCopy = a;
		// ����� ������� ���������� �������������
		startPiramid = high_resolution_clock::now();
		piramidSort(a);//���������� ���������
		stopPiramid = high_resolution_clock::now();
		// ������� ������� ���������� ���������� �������������
		durationPiramid = duration_cast<microseconds>(stopPiramid - startPiramid);
		cout << "Piramid sort time for " << a.size() << " elements: ";
		printDuration(durationPiramid);

		// ����� ������� ����������� ������� qsort
		startQSort = high_resolution_clock::now();
		qsort(aCopy.data(), aCopy.size(), sizeof(int), compare);
		stopQSort = high_resolution_clock::now();

		// ������� ������� ���������� qsort
		durationQSort = duration_cast<microseconds>(stopQSort - startQSort);
		cout << "qsort time for " << aCopy.size() << " elements: ";
		printDuration(durationQSort);
		//!
		for (const int& num : a)//���� ��� ������ ������������� �����
		{
			output << num << endl;
		}

		input.close();
		output.close();
		a.clear();
		cout << "��������� 1?" << endl; cin >> num;
	}
	return 0;
}