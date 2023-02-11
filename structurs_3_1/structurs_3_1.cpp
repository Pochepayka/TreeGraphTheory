#include "Header.h"
int main()
{
	setlocale(LC_ALL, "RUSSIAN"); // подключение русского языка 
	Tree* first = NULL;
	//randomMas(tree,countEl);//рандомим массив
	first = addElement(tree);//добовляем элементы в дерево
	menu(tree, first);//запускаем меню
}

