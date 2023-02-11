// laba_diskr(24 var).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
//основная матрица граффа
int graf[8][8] =
{ { 0,1,2,4,3,0,0,0 },
{ 1,0,2,1,0,0,0,3 },
{ 2,2,0,0,3,0,2,0 },
{ 4,1,0,0,0,4,3,0 },
{ 3,0,3,0,0,1,0,2 },
{ 0,0,0,4,1,0,1,3 },
{ 0,0,2,3,0,1,0,1 },
{ 0,3,0,0,2,3,1,0 } };
const int inf = 10000;//бесконечность
int i;
int j;
int rad = 100000;
int dia = 0;
int exs[8] = { 0,0,0,0,0,0,0,0 };
bool wisiter[8];//посещена вершина или нет?
int distante[8];//расстояние до вершин
int main()
{
	system("cls"); //очистка экрана
	setlocale(LC_ALL, "RUSSIAN"); //подключение русского языка
	system("color F0");	//экран белый, буквы черные
	for (i=0;i<8;i++)
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
		cout << "exs[" << i+1 << "] = " << exs[i] << endl;
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
}//end main
//------------------------------end laba2_diskr---------------------//