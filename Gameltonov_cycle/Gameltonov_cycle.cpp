
#include <iostream>
#include <Windows.h>
#define n 8

using namespace std;

int c[n];   // номер хода, на котором посещается вершина
int path[n]; // номера посещаемых вершин
int v0 = 2;    // начальная вершина

 //матрица смежности 
int a[n][n] = {
{ 0,0,0,1,0,1,0,0 },
{ 1,0,0,1,1,0,0,0 },
{ 0,1,0,0,0,0,0,0 },
{ 0,0,0,0,0,1,0,1 },
{ 0,0,1,0,0,0,0,1 },
{ 0,0,1,0,0,0,0,1 },
{ 1,0,1,0,1,0,0,0 },
{ 0,0,0,0,0,0,1,0 } };

//подпрограмма печати результата
void printGam(void)
{
    int p;
    for (p = n - 1; p >= 0; p--)
        cout << path[p] + 1 << " ";
    cout << endl;
}
//подпрограмма нахождения гамильтонова цикла
int gamilton(int k) // k = 1
{
    int v, q1 = 0;
    for (v = 0; v < n && !q1; v++) // обход матрицы
    {
        if (a[v][path[k - 1]])//|| a[path[k - 1]][v]) для не ориентированного графа
        {
            if (k == n && v == v0) q1 = 1;
            else
                if (c[v] == -1) // формирует путь
                {
                    c[v] = k; // номер хода
                    path[k] = v; // занесение вершины
                    q1 = gamilton(k + 1);
                    if (!q1) c[v] = -1;
                }
                else
                    continue;
        }
    }   return q1; // если нашел путь возвращает единицу
}

void main()
{
    system("cls"); //очистка экрана
    setlocale(LC_ALL, "RUSSIAN"); //подключение русского языка
    system("color F0");	//экран белый, буквы черные
    int j;
    cout << "Gamilton's circle:\n";
    for (j = 0; j < n; j++)
        c[j] = -1;
    path[0] = v0;
    c[v0] = v0;
    if (gamilton(1))
        printGam();
    else
        cout << "No solutions\n";
}