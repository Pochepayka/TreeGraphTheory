#pragma once
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <random>
using namespace std; 
typedef struct Tree;
void randomMas(char * mas, int &N);
Tree* RemoveNode(Tree* currentNode, int key, Tree* first);
Tree* create(int i);
void insert(Tree* root, Tree* elem);
void printTree(Tree* currentNode, int level);
Tree* addElement(char *mas);
Tree* search(Tree* currentNode, int key);
Tree* searchMin(Tree* currentNode);
void changeLvL(Tree* currentNode);
void inOrderTravers(Tree* currentNode, int& count, int& maxLvl);
void freemem(Tree* currentNode);
int outputInfo();
void outputLvL(Tree* first);
void menu(char tree[], Tree* first);
void findSoglSimilarHight(Tree* currentNode,int &countS);
extern string glasnie;
extern int countEl;
extern char *tree;