#include "Header.h"

typedef struct Tree//структура, представляющая элемент дерева
{
	char key;
	struct Tree* left;
	struct Tree* right;
	struct Tree* back;
	int level;
	char info;
};

void randomMas(char * mas, int &N)
{
	srand(time(NULL));   // Initialization, should only be called once.

	cout << "Введите количество элементов:";
	cin >> N;

	if ((N < 1) || (N > 52))
	{
		cout << "Некорректное значение"<<endl;
		cout << "Выход по ошибке";
		exit(0);//проверка на коректность значения
	}
	for (int i = 0; i < N; i++)
	{
		bool noRepetitions = false;//флаг
		while (noRepetitions==false)
		{
			noRepetitions = true;
			char ells[2] = { 'A' + rand() % 26 ,'a' + rand() % 26 };//рандом
			char ell = ells[rand()%2];//рандом

			for (int j = 0; j < i; j++)
			{
				if (ell == mas[j])//сравнение
				{
					noRepetitions = false;//активация флага
				}
			}
			mas[i] = ell;
		}
		cout << mas[i] << " ";
	}
}

Tree* RemoveNode(Tree* currentNode, int key, Tree* first)//удаление узла 
{
	currentNode = search(first, key);//поиск узла
	if (currentNode == nullptr) {
		cout << "Заданного узла не существует." << endl;
		return first;
	}/*
	if (currentNode->level == 0) 
	{
		cout << "Нельзя удалить корень.\n";
		return first;
	}*/
	//Если удаляемый узел не имеет потомков
	if ((currentNode->left == nullptr) && (currentNode->right == nullptr)) {
		cout << "Узел " << currentNode->key << " не имеет потомков\nУдаление ..." << endl;
		if (currentNode == currentNode->back->left)//удалени с чисткой родителей
		{
			currentNode->back->left = nullptr;
			freemem(currentNode);
		}
		else {
			currentNode->back->right = nullptr;
			freemem(currentNode);
		}
	}

	//Если удаляемуй узел имеет потомка СЛЕВА
	else if ((currentNode->left != nullptr) && (currentNode->right == nullptr)) {
		cout << "Узел " << currentNode->key << " имеет левого потомка\nУдаление ..." << endl;

		//Если удаляется корневой элемент
		if (currentNode->back == nullptr) {
			first = currentNode->left;
			delete first->back;
			changeLvL(first);
			return first;
		}
		//чистка родителей
		if (currentNode == currentNode->back->left) {
			currentNode->back->left = currentNode->left;
			currentNode->left->back = currentNode->back;
		}
		else {
			currentNode->back->right = currentNode->left;
			currentNode->left->back = currentNode->back;
		}
		changeLvL(currentNode->left);//уменьшение левелов рекурсия

		delete currentNode;//зачистка
	}

	//Если удаляемуй узел имеет потомка СПРАВА
	else if ((currentNode->left == nullptr) && (currentNode->right != nullptr)) {
		cout << "Узел " << currentNode->key << " имеет правого потомка\nУдаление  ..." << endl;

		//Если удаляется корневой элемент
		if (currentNode->back == nullptr) {
			first = currentNode->right;
			delete first->back;
			changeLvL(first);
			return first;
		}
		//замена родителей
		if (currentNode == currentNode->back->left) {
			currentNode->back->left = currentNode->right;
			currentNode->right->back = currentNode->back;
		}
		else {
			currentNode->back->right = currentNode->right;
			currentNode->right->back = currentNode->back;
		}

		changeLvL(currentNode->right);//меняем левыел рекурсивно

		delete currentNode;//зачистка
	}

	//Если узел имеет двух потомков
	else {
		cout << "Узел " << currentNode->key << " имеет двух потомков " << endl;
		Tree* minNode = searchMin(currentNode->right);//поиск элемента для замены
		cout << "Узел " << currentNode->key << " будет земенен на узел " << minNode->key << endl;
		//зачистка элемента для замены
		//перестановка правого поддерева
		//перестановка правого поддеревачистка родителей
		if (minNode->right != nullptr) {
			minNode->right->back = minNode->back;

			if (minNode == minNode->back->right) minNode->back->right = minNode->right;
			else minNode->back->left = minNode->right;

			changeLvL(minNode->right);
		}
		else if (minNode != currentNode->right) minNode->back->left = nullptr;
		else minNode->back->right = nullptr;

		if (currentNode->back == nullptr) {
			cout << "Удаляемый узел - корень" << endl;
			first = minNode;
			first->back = nullptr;
		}
		else {
			if (currentNode->back->left == currentNode) currentNode->back->left = minNode;
			else currentNode->back->right = minNode;
			minNode->back = currentNode->back;
		}
		//добавление значений новому элементу
		minNode->left = currentNode->left;
		minNode->right = currentNode->right;
		minNode->level = currentNode->level;
		currentNode->left->back = minNode;
		if (currentNode->right != nullptr) currentNode->right->back = minNode;

		delete currentNode;//зачистка
	}
	return first;
}

Tree* create(int i)//создание нового элемента дерева
{
	Tree* elem = new Tree;
	elem->key = i;
	elem->left = NULL;
	elem->right = NULL;
	elem->level = NULL;
	return elem;
}

void insert(Tree* root, Tree* elem)//вставка элемента elem в дерево с корнем root
{

	if (elem->key < root->key)
	{
		//идем в левое поддерево
		if (root->left == NULL)
		{
			root->left = elem;//вставляем новый элемент
			root->left->level = root->level + 1;
			root->left->back = root;
		}
		else
			insert(root->left, elem);
	}
	else
	{
		//идем в правое поддерево
		if (root->right == NULL)
		{
			root->right = elem;
			root->right->level = root->level + 1;
			root->right->back = root;
		}
		else
			insert(root->right, elem);
	}
}

void printTree(Tree* currentNode, int level)//печать дерева 
{
	if (currentNode) {
		printTree(currentNode->right, level + 1);						// вывод правого поддерева
		for (int i = 0; i < level; i++) cout << "\t";
		cout << " " << currentNode->key << endl;							// вывод корня поддерева
		printTree(currentNode->left, level + 1);
		// вывод левого поддерева
	}
}

Tree* addElement(char *mas)//подстановка элементов в дерево
{
	Tree* root = create(mas[0]);//создание
	root->level = 0;
	root->back = nullptr;
	for (int i = 1; i < countEl; i++)
	{
		Tree* el = create(mas[i]);//создание
		insert(root, el);//вставка
	}
	return root;
}

Tree* search(Tree* currentNode, int key)//поиск элемента по ключу
{
	if (currentNode == nullptr) {
		cout << "...\n" << "Элемент не найден." << endl;
		return nullptr;
	}
	if (key == currentNode->key) {
		cout << currentNode->key << endl << "Элемент найден." << endl;
		return currentNode;
	}
	//строим путь
	else if (key < currentNode->key) {
		cout << currentNode->key << " --> ";
		search(currentNode->left, key);
	}
	else {
		cout << currentNode->key << " --> ";
		search(currentNode->right, key);
	}
}

Tree* searchMin(Tree* currentNode)//поиск минимального узла 
{
	if (currentNode->left == nullptr) return currentNode;
	else searchMin(currentNode->left);
}

void changeLvL(Tree* currentNode)//измение уровня узла
{
	if (currentNode) {
		changeLvL(currentNode->left);
		currentNode->level--;//уменьшаем лвл
		changeLvL(currentNode->right);
	}
}

void inOrderTravers(Tree* currentNode, int& count, int& maxLvl)//Симметричный обход(центральньный)
{
	if (currentNode) 
	{
		inOrderTravers(currentNode->left, count, maxLvl);
		//cout << currentNode->key << " ";
		count++;
		if (currentNode->level > maxLvl) maxLvl = currentNode->level;
		inOrderTravers(currentNode->right, count, maxLvl);
	}
}

void freemem(Tree* currentNode)//очистка памяти
{
	if (currentNode != nullptr) {
		freemem(currentNode->left);
		freemem(currentNode->right);
		delete currentNode;
	}
}

int outputInfo()//вывод инфо из меню
{
	int choice;
	cout << "\n1 - Вставка нового узла\n";
	cout << "2 - Поиск существующего узла\n";
	cout << "3 - Удаление узла\n";
	cout << "4 - Вывод дерева\n";
	cout << "5 - Нахождение высоты дерева и количества узлов\n";
	cout << "6 - кол-во согласныхв узлах, с одинак. высотой поддеревьев\n";
	//cout << "7 - рандом нового дерева\n";
	cout << "Иначе - Выход\n";
	cout << "\nВаш выбор: ";
	cin >> choice;
	cout << "\n";
	return choice;
}

void outputLvL(Tree* first)//вывод левелов
{
	int count = 0;
	int maxLvl = 0;
	inOrderTravers(first, count, maxLvl);//симетричный обход
	cout << "\n";
	for (int i = 0; i <= maxLvl; i++)
		cout << "Lvl " << i << ":\t";
	cout << "\n\n";
}

void findSoglSimilarHight(Tree* currentNode,int &countS)
{
	if (currentNode)
	{ 
		int hightLeft=0;
		int hightRight=0;
		bool exists = false;
		int count=0;
		int maxLvl=0;
		for (int i = 0; i < 12; i++)
		{
			if ((currentNode->key) == glasnie[i])
			{
				exists = true;
			}
		}

		inOrderTravers(currentNode->left, count, maxLvl);//обновление maxLvl
		if (not(currentNode->left))
		{
			hightLeft = 0;
		}
		else
		{
			hightLeft = maxLvl -currentNode->level;//обновление значения
		}
		maxLvl = 0;//сброс
		inOrderTravers(currentNode->right, count, maxLvl);//обновление maxLvl
		if (not(currentNode->right)) 
		{ 
			hightRight = 0;
		}
		else 
		{ 
			hightRight = maxLvl -currentNode->level;//обновление значения
		}

		if (not (exists) && (hightLeft == hightRight))
		{
			countS++;
			cout << currentNode->key << " " << exists << " " << hightLeft << " " << hightRight << endl;//вывод
		}
		findSoglSimilarHight(currentNode->left,countS);//рекурсия
		findSoglSimilarHight(currentNode->right,countS);//рекурсия

	}

}

void menu(char *	tree, Tree* first)//меню
{
	int choice = 0;
	bool firstInlet = true;//первый вход
	while (((choice > 0) && (choice < 8)) || firstInlet)
	{
		int countSogl = 0;
		int count;
		int maxLvl;
		char key;
		Tree* elem;
		firstInlet = false;
		choice = outputInfo();
		switch (choice) {
		case 1://вставка
			cout << "Введите элемент, который нужно добавить: ";
			cin >> key;
			elem = create(key);
			insert(first, elem);
			cout << "\nУзел добавлен. Новое дерево:\n";
			break;
		case 2://поиск
			cout << "Введите искомый элемент: ";
			cin >> key;
			cout << "Путь: ";
			search(first, key);
			break;
		case 3://удаление
			cout << "Введите число, которое нужно удалить: ";
			cin >> key;
			first = RemoveNode(first, key, first);
			break;
		case 4://вывод
			outputLvL(first);
			printTree(first, 0);
			break;
		case 5://высота 
			count = 0;
			maxLvl = 0;
			inOrderTravers(first, count, maxLvl);
			cout << "\n Высота дерева: " << maxLvl + 1 << endl;
			cout << " Количество узлов: " << count << endl;
			break;
		case 6:
			countSogl = 0;
			findSoglSimilarHight(first,countSogl);
			cout << "\n Количество подходящих согласных:" << countSogl << endl;
			break;
		/*case 7:
			randomMas(tree, countEl);
			freemem(first->right);
			freemem(first->left);
			first = addElement(tree,first);
			break;*/
		default:
			freemem(first);
			delete[] tree;
			cout << "Программа успешно завершена." << endl;
		}
	}
}