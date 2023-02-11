// structure_sem3_laba2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
/*
Для взвешенного ориентированного графа, состоящего как минимум из 10 вершин, реализовать по вариантам:
1.	алгоритм поиска кратчайшего пути;
2.	сделав тот же самый граф неориентированным, построить его остовное дерево минимальной стоимости.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;

const char* FNAME = "Test_01.txt";                // файл с размером исходного списка
int nVershin;
float** graf;
int* used;

/*int graf[10][10] =
{ {0,1,2,4,3,0,0,0,7,0},
  {1,0,2,1,0,0,0,3,0,0},
  {2,2,0,0,3,0,2,0,3,1},
  {4,1,0,0,0,4,3,0,0,0},
  {3,0,3,0,0,1,0,2,2,4},
  {0,0,0,4,1,0,1,3,0,0},
  {0,0,2,3,0,1,0,1,5,3},
  {1,3,0,0,2,3,1,0,2,0},
  {6,0,0,2,0,0,1,0,2,0},
  {0,4,0,0,2,3,1,0,2,0}
};*/

void krusksla(int* used, float** graf, int N);
int FIN(const char* file,float**graff, int& N);
void deleteMass(int* mas1, float** mas2,int n);
void printGraph(float**graf,int n);
void floid(int*used,float** graf, int n);
void createMass(int*usedd, float**graff,int n);

void createMass(int* usedd, float** graff, int n) 
{
	graff = new float* [n];
	for (int i = 0; i < n; i++)
		graff[i] = new float[n];// { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	usedd = new int[n];// { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	usedd[0] = 1;
	for (int i = 1; i < n; i++) usedd[i] = 0;
}
int FIN(const char* file, float** graff, int& N) 
{//------------------------------begin FIN-----------------------//
	ifstream fin(file); // файл ввода

	if (!fin)           // Если файл не найден
	{
		cout << "Ошибка! Файл не найден" << endl; //вывод сообщения об ошибки
		fin.close();                              //закрыть файл
		system("pause");
		return 1;                                // выход по ошибке
	}
	if (fin.peek() == EOF)                        //если найденный файл пуст
	{
		cout << "Ошибка! файл пустой!" << endl;   //вывод сообщения об ошибке
		fin.close();                              //закрыть файл
		system("pause");
		return 2;                                // выход по ошибке
	}
		if (fin.fail())                          // если в файле не чилсо
	{
		fin.close();                         //закрытие файла
		cout << "Файл   содержит не числа" << endl;
		system("PAUSE");
		return 3;
	}
	fin >> N;  //чтение из файла размера массива
	if (N < 1) // если N не натуральное
	{
		cout << "Ошибка! N  не натуральное !!! " << endl;   // вывод сообщения об ошибке
		fin.close();          //закрыть файл
		system("pause");
		return 4;            // выход по ошибке
	}
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			if (fin.fail() || (fin.eof()))                          // если в файле не чилсо
			{
				fin.close();                         //закрытие файла
				cout << "Файл   содержит не числа" << endl;
				system("PAUSE");
				return 5;
			}
			fin >> graff[i][j];
		}
	return 0;
}//------------------------------end FIN-----------------------//
void krusksla( int* used, float** graf, int N)
{//------------------------------begin kruskala-----------------------//
	int i;
	int j;
	int ii;
	int jj;
	int n = 1;
	int sum = 0;

	cout << "Рёбра остовного дерева минимального веса:" << endl;
	while (n < N)
	{
		int min = 100000;
		for (i = 0; i < N; i++)
		{
			for (j = 0; j < N; j++)
			{
				if ((graf[i][j] < min) && (graf[i][j] != 0)//минимальное не равное 0
					&& ((used[i] == 0) || (used[j] == 0))//только одна из вершин не задействована
					&& ((used[i] == 1) || (used[j] == 1)))
				{
					min = graf[i][j];
					ii = i;
					jj = j;
				}
			}
		}
		used[ii] = 1;
		used[jj] = 1;
		sum += graf[ii][jj];
		graf[ii][jj] = 0;
		graf[jj][ii] = 0;
		n++;
		cout << ii + 1 << " - " << jj + 1 << "; ";
	}
	cout << endl << "sum = " << sum << endl;
}//------------------------------end kruskala-----------------------//
void floid(int* used, float** graf, int n)
{//------------------------------begin floid-------------------------//
	const int inf = 10000;//бесконечность
	int i;
	int j;
	int rad = 100000;
	int dia = 0;
	int exs[8] = { 0,0,0,0,0,0,0,0 };
	bool wisiter[8];//посещена вершина или нет?
	int distante[8];//расстояние до вершин

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			//начальные значения
			wisiter[j] = false;
			distante[j] = inf;
		}
		wisiter[i] = true;
		distante[i] = 0;

		queue<int>q;//очередь
		q.push(i);//добавление очереди
		while (!q.empty())//пока очередь не пуста
		{
			int vetrex = q.front();//передняя вершина из очереди
			q.pop();//удалить элемент из очереди
			for (j = 0; j < 8; j++)
			{
				if ((!wisiter[j]) && (graf[vetrex][j]) && (graf[vetrex][j] + distante[vetrex] < distante[j]))
					//если вершина не посещена, до неё есть путь короче чем путь до неё раньше
				{
					distante[j] = graf[vetrex][j] + distante[vetrex];//новый меньший путь до вершины
					q.push(j);//добавить вершину в очередь
				}
			}
		}
		//расчёт эксентриситета вывод таблицы растояний между точками:
		int max = 0;
		for (j = 0; j < 8; j++)
		{
			if (distante[j] > max)
			{
				max = distante[j];
			}
			cout << distante[j] << " ";
		}
		exs[i] = max;
		cout << endl;
	}
	//вывод эксинтриситета расчёт деаметра и радиуса:
	for (i = 0; i < 8; i++)
	{
		cout << "exs[" << i + 1 << "] = " << exs[i] << endl;
		if (exs[i] > dia)
		{
			dia = exs[i];
		}
		if (exs[i] < rad)
		{
			rad = exs[i];
		}
	}
	//вывод результатов:
	cout << "rad = " << rad << endl;
	cout << "dia = " << dia << endl;
	cout << "центры:";
	for (i = 0; i < 8; i++)
	{
		if (exs[i] == rad)
		{
			cout << " " << i + 1;
		}
	}
	cout << endl << "переферийные:";
	for (i = 0; i < 8; i++)
	{
		if (exs[i] == dia)
		{
			cout << " " << i + 1;
		}
	}
}//------------------------------end floid---------------------------//
void deleteMass(int* mas1, float** mas2,int n)
{//------------------------------begin deleteMass--------------------//

	for (int i = 0; i < n; i++)
		delete[] mas2[i];
	delete[] mas2;
	delete[] mas1;
}//------------------------------end deleteMass----------------------//
void printGraph(float** graf, int n)
{//------------------------------begin printGraph--------------------//
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << graf[i][j] << " ";
		}
		cout << "\n";
	}
}//------------------------------end printGraf-----------------------//

int main()
{
	system("cls"); //очистка экрана
	setlocale(LC_ALL, "RUSSIAN"); //подключение русского языка
	system("color F0");	//экран белый, буквы черные

	// float** graf = new float* [nVershin];
	//for (int i = 0; i < nVershin; i++)
	//	graf[i] = new float[nVershin];

	//int* used = new int[nVershin];// { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	//used[0] = 1;
	//for (int i = 1; i < nVershin; i++) used[i] = 0;
	createMass(used, graf, nVershin);

	int readCode = FIN(FNAME, graf, nVershin);

	if (readCode == 0)
	{
		printGraph(graf, nVershin);
		cout << "\nАлгоритм Крускала\n";
		krusksla(used, graf, nVershin);

		cout << "\nАлгоритм Флойда Уоршелла\n";
		floid(used, graf, nVershin);
	}

	deleteMass(used, graf, nVershin);
}//end main