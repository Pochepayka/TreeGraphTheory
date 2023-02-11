// Prima.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
//основная матрица граффа
int graf[8][8] =
{ {0,1,2,4,3,0,0,0},
  {1,0,2,1,0,0,0,3},
  {2,2,0,0,3,0,2,0},
  {4,1,0,0,0,4,3,0},
  {3,0,3,0,0,1,0,2},
  {0,0,0,4,1,0,1,3},
  {0,0,2,3,0,1,0,1},
  {0,3,0,0,2,3,1,0}
};
//массив включенных вершин
const int inf = 10000;//бесконечность
bool used[8] = { false,false,false,false,false,false,false,false };
int i;
int j;
int ii;
int jj;
int min;
int n = 0;
float sum = 0;
int main()
{
	system("cls"); //очистка экрана
	setlocale(LC_ALL, "RUSSIAN"); //подключение русского языка
	system("color F0");	//экран белый, буквы черные
}
