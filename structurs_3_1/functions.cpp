#include "Header.h"

typedef struct Tree//���������, �������������� ������� ������
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

	cout << "������� ���������� ���������:";
	cin >> N;

	if ((N < 1) || (N > 52))
	{
		cout << "������������ ��������"<<endl;
		cout << "����� �� ������";
		exit(0);//�������� �� ����������� ��������
	}
	for (int i = 0; i < N; i++)
	{
		bool noRepetitions = false;//����
		while (noRepetitions==false)
		{
			noRepetitions = true;
			char ells[2] = { 'A' + rand() % 26 ,'a' + rand() % 26 };//������
			char ell = ells[rand()%2];//������

			for (int j = 0; j < i; j++)
			{
				if (ell == mas[j])//���������
				{
					noRepetitions = false;//��������� �����
				}
			}
			mas[i] = ell;
		}
		cout << mas[i] << " ";
	}
}

Tree* RemoveNode(Tree* currentNode, int key, Tree* first)//�������� ���� 
{
	currentNode = search(first, key);//����� ����
	if (currentNode == nullptr) {
		cout << "��������� ���� �� ����������." << endl;
		return first;
	}/*
	if (currentNode->level == 0) 
	{
		cout << "������ ������� ������.\n";
		return first;
	}*/
	//���� ��������� ���� �� ����� ��������
	if ((currentNode->left == nullptr) && (currentNode->right == nullptr)) {
		cout << "���� " << currentNode->key << " �� ����� ��������\n�������� ..." << endl;
		if (currentNode == currentNode->back->left)//������� � ������� ���������
		{
			currentNode->back->left = nullptr;
			freemem(currentNode);
		}
		else {
			currentNode->back->right = nullptr;
			freemem(currentNode);
		}
	}

	//���� ��������� ���� ����� ������� �����
	else if ((currentNode->left != nullptr) && (currentNode->right == nullptr)) {
		cout << "���� " << currentNode->key << " ����� ������ �������\n�������� ..." << endl;

		//���� ��������� �������� �������
		if (currentNode->back == nullptr) {
			first = currentNode->left;
			delete first->back;
			changeLvL(first);
			return first;
		}
		//������ ���������
		if (currentNode == currentNode->back->left) {
			currentNode->back->left = currentNode->left;
			currentNode->left->back = currentNode->back;
		}
		else {
			currentNode->back->right = currentNode->left;
			currentNode->left->back = currentNode->back;
		}
		changeLvL(currentNode->left);//���������� ������� ��������

		delete currentNode;//��������
	}

	//���� ��������� ���� ����� ������� ������
	else if ((currentNode->left == nullptr) && (currentNode->right != nullptr)) {
		cout << "���� " << currentNode->key << " ����� ������� �������\n��������  ..." << endl;

		//���� ��������� �������� �������
		if (currentNode->back == nullptr) {
			first = currentNode->right;
			delete first->back;
			changeLvL(first);
			return first;
		}
		//������ ���������
		if (currentNode == currentNode->back->left) {
			currentNode->back->left = currentNode->right;
			currentNode->right->back = currentNode->back;
		}
		else {
			currentNode->back->right = currentNode->right;
			currentNode->right->back = currentNode->back;
		}

		changeLvL(currentNode->right);//������ ������ ����������

		delete currentNode;//��������
	}

	//���� ���� ����� ���� ��������
	else {
		cout << "���� " << currentNode->key << " ����� ���� �������� " << endl;
		Tree* minNode = searchMin(currentNode->right);//����� �������� ��� ������
		cout << "���� " << currentNode->key << " ����� ������� �� ���� " << minNode->key << endl;
		//�������� �������� ��� ������
		//������������ ������� ���������
		//������������ ������� ��������������� ���������
		if (minNode->right != nullptr) {
			minNode->right->back = minNode->back;

			if (minNode == minNode->back->right) minNode->back->right = minNode->right;
			else minNode->back->left = minNode->right;

			changeLvL(minNode->right);
		}
		else if (minNode != currentNode->right) minNode->back->left = nullptr;
		else minNode->back->right = nullptr;

		if (currentNode->back == nullptr) {
			cout << "��������� ���� - ������" << endl;
			first = minNode;
			first->back = nullptr;
		}
		else {
			if (currentNode->back->left == currentNode) currentNode->back->left = minNode;
			else currentNode->back->right = minNode;
			minNode->back = currentNode->back;
		}
		//���������� �������� ������ ��������
		minNode->left = currentNode->left;
		minNode->right = currentNode->right;
		minNode->level = currentNode->level;
		currentNode->left->back = minNode;
		if (currentNode->right != nullptr) currentNode->right->back = minNode;

		delete currentNode;//��������
	}
	return first;
}

Tree* create(int i)//�������� ������ �������� ������
{
	Tree* elem = new Tree;
	elem->key = i;
	elem->left = NULL;
	elem->right = NULL;
	elem->level = NULL;
	return elem;
}

void insert(Tree* root, Tree* elem)//������� �������� elem � ������ � ������ root
{

	if (elem->key < root->key)
	{
		//���� � ����� ���������
		if (root->left == NULL)
		{
			root->left = elem;//��������� ����� �������
			root->left->level = root->level + 1;
			root->left->back = root;
		}
		else
			insert(root->left, elem);
	}
	else
	{
		//���� � ������ ���������
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

void printTree(Tree* currentNode, int level)//������ ������ 
{
	if (currentNode) {
		printTree(currentNode->right, level + 1);						// ����� ������� ���������
		for (int i = 0; i < level; i++) cout << "\t";
		cout << " " << currentNode->key << endl;							// ����� ����� ���������
		printTree(currentNode->left, level + 1);
		// ����� ������ ���������
	}
}

Tree* addElement(char *mas)//����������� ��������� � ������
{
	Tree* root = create(mas[0]);//��������
	root->level = 0;
	root->back = nullptr;
	for (int i = 1; i < countEl; i++)
	{
		Tree* el = create(mas[i]);//��������
		insert(root, el);//�������
	}
	return root;
}

Tree* search(Tree* currentNode, int key)//����� �������� �� �����
{
	if (currentNode == nullptr) {
		cout << "...\n" << "������� �� ������." << endl;
		return nullptr;
	}
	if (key == currentNode->key) {
		cout << currentNode->key << endl << "������� ������." << endl;
		return currentNode;
	}
	//������ ����
	else if (key < currentNode->key) {
		cout << currentNode->key << " --> ";
		search(currentNode->left, key);
	}
	else {
		cout << currentNode->key << " --> ";
		search(currentNode->right, key);
	}
}

Tree* searchMin(Tree* currentNode)//����� ������������ ���� 
{
	if (currentNode->left == nullptr) return currentNode;
	else searchMin(currentNode->left);
}

void changeLvL(Tree* currentNode)//������� ������ ����
{
	if (currentNode) {
		changeLvL(currentNode->left);
		currentNode->level--;//��������� ���
		changeLvL(currentNode->right);
	}
}

void inOrderTravers(Tree* currentNode, int& count, int& maxLvl)//������������ �����(�������������)
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

void freemem(Tree* currentNode)//������� ������
{
	if (currentNode != nullptr) {
		freemem(currentNode->left);
		freemem(currentNode->right);
		delete currentNode;
	}
}

int outputInfo()//����� ���� �� ����
{
	int choice;
	cout << "\n1 - ������� ������ ����\n";
	cout << "2 - ����� ������������� ����\n";
	cout << "3 - �������� ����\n";
	cout << "4 - ����� ������\n";
	cout << "5 - ���������� ������ ������ � ���������� �����\n";
	cout << "6 - ���-�� ���������� �����, � ������. ������� �����������\n";
	//cout << "7 - ������ ������ ������\n";
	cout << "����� - �����\n";
	cout << "\n��� �����: ";
	cin >> choice;
	cout << "\n";
	return choice;
}

void outputLvL(Tree* first)//����� �������
{
	int count = 0;
	int maxLvl = 0;
	inOrderTravers(first, count, maxLvl);//����������� �����
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

		inOrderTravers(currentNode->left, count, maxLvl);//���������� maxLvl
		if (not(currentNode->left))
		{
			hightLeft = 0;
		}
		else
		{
			hightLeft = maxLvl -currentNode->level;//���������� ��������
		}
		maxLvl = 0;//�����
		inOrderTravers(currentNode->right, count, maxLvl);//���������� maxLvl
		if (not(currentNode->right)) 
		{ 
			hightRight = 0;
		}
		else 
		{ 
			hightRight = maxLvl -currentNode->level;//���������� ��������
		}

		if (not (exists) && (hightLeft == hightRight))
		{
			countS++;
			cout << currentNode->key << " " << exists << " " << hightLeft << " " << hightRight << endl;//�����
		}
		findSoglSimilarHight(currentNode->left,countS);//��������
		findSoglSimilarHight(currentNode->right,countS);//��������

	}

}

void menu(char *	tree, Tree* first)//����
{
	int choice = 0;
	bool firstInlet = true;//������ ����
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
		case 1://�������
			cout << "������� �������, ������� ����� ��������: ";
			cin >> key;
			elem = create(key);
			insert(first, elem);
			cout << "\n���� ��������. ����� ������:\n";
			break;
		case 2://�����
			cout << "������� ������� �������: ";
			cin >> key;
			cout << "����: ";
			search(first, key);
			break;
		case 3://��������
			cout << "������� �����, ������� ����� �������: ";
			cin >> key;
			first = RemoveNode(first, key, first);
			break;
		case 4://�����
			outputLvL(first);
			printTree(first, 0);
			break;
		case 5://������ 
			count = 0;
			maxLvl = 0;
			inOrderTravers(first, count, maxLvl);
			cout << "\n ������ ������: " << maxLvl + 1 << endl;
			cout << " ���������� �����: " << count << endl;
			break;
		case 6:
			countSogl = 0;
			findSoglSimilarHight(first,countSogl);
			cout << "\n ���������� ���������� ���������:" << countSogl << endl;
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
			cout << "��������� ������� ���������." << endl;
		}
	}
}