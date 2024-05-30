#include<iostream>
#include<vector>
#include<set>
#include<chrono>
#include"RBTree.h"
#include"tests.h"

using std::cout;

//Тесты вставки
void cmd_insert_tests() {
	RBTree<int> tree;
	cout << "---------------Тесты вставки------------------\n";

	//Вставка
	cout << "Вставляю в пустое дерево" << "\n";
	tree.insert(0);
	tree.PrintTree();
	cout << "Минимальный: " << *tree.begin() << "\n";
	cout << "Максимальный: " << *(--tree.end()) << "\n";
	cout << "---------------------------------\n";

	//Меняю максимальный
	cout << "Меняю максимальный" << "\n";
	tree.insert(3);
	tree.PrintTree();
	cout << "Минимальный: " << *tree.begin() << "\n";
	cout << "Максимальный: " << *(--tree.end()) << "\n";
	cout << "---------------------------------\n";

	//Меняю минимальный
	cout << "Меняю минимальный" << "\n";
	tree.insert(-3);
	tree.PrintTree();
	cout << "Минимальный: " << *tree.begin() << "\n";
	cout << "Максимальный: " << *(--tree.end()) << "\n";
	cout << "---------------------------------\n";

	//Элемент уже есть
	cout << "Элемент уже есть" << "\n";
	tree.insert(-3);
	tree.PrintTree();
	cout << "Минимальный: " << *tree.begin() << "\n";
	cout << "Максимальный: " << *(--tree.end()) << "\n";
	cout << "---------------------------------\n";

	//Случай 1: родитель левый дочерний, дядя вставляемого узла красный
	cout << "Случай 1: родитель левый дочерний, дядя вставляемого узла красный" << "\n";
	tree.insert(-6);
	tree.PrintTree();
	cout << "Минимальный: " << *tree.begin() << "\n";
	cout << "Максимальный: " << *(--tree.end()) << "\n";
	cout << "---------------------------------\n";

	//Случай 2: родитель левый дочерний, узел левый дочерний, дядя вставляемого узла черный
	cout << "Случай 2: родитель левый дочерний, узел левый дочерний, дядя вставляемого узла черный" << "\n";
	tree.insert(-9);
	tree.PrintTree();
	cout << "Минимальный: " << *tree.begin() << "\n";
	cout << "Максимальный: " << *(--tree.end()) << "\n";
	cout << "---------------------------------\n";

	//Случай 3: родитель правый дочерний, дядя вставляемого узла красный
	cout << "Случай 3: родитель правый дочерний, дядя вставляемого узла красный" << "\n";
	tree.insert(-5);
	tree.PrintTree();
	cout << "Минимальный: " << *tree.begin() << "\n";
	cout << "Максимальный: " << *(--tree.end()) << "\n";
	cout << "---------------------------------\n";

	//Случай 4: родитель левый дочерний, узел правый дочерний, дядя вставляемого узла черный
	cout << "Случай 4: родитель левый дочерний, узел правый дочерний, дядя вставляемого узла черный" << "\n";
	tree.insert(-4);
	tree.PrintTree();
	cout << "Минимальный: " << *tree.begin() << "\n";
	cout << "Максимальный: " << *(--tree.end()) << "\n";
	cout << "---------------------------------\n";

	tree.clear();
	cout << "Очистка дерева и вставка без нарушения цвета" << "\n";
	tree.insert(0);
	tree.insert(-4);
	tree.insert(6);
	tree.PrintTree();
	cout << "Минимальный: " << *tree.begin() << "\n";
	cout << "Максимальный: " << *(--tree.end()) << "\n";
	cout << "---------------------------------\n";

	//Уже рассмотрели
	cout << "Уже рассмотренный случай" << "\n";
	tree.insert(9);
	tree.PrintTree();
	cout << "Минимальный: " << *tree.begin() << "\n";
	cout << "Максимальный: " << *(--tree.end()) << "\n";
	cout << "---------------------------------\n";

	//Случай 5: родитель правый дочерний, узел правый дочерний, дядя вставляемого узла черный
	cout << "Случай 5: родитель правый дочерний, узел правый дочерний, дядя вставляемого узла черный" << "\n";
	tree.insert(13);
	tree.PrintTree();
	cout << "Минимальный: " << *tree.begin() << "\n";
	cout << "Максимальный: " << *(--tree.end()) << "\n";
	cout << "---------------------------------\n";

	//Уже рассмотрели
	cout << "Уже рассмотренный случай" << "\n";
	tree.insert(15);
	tree.PrintTree();
	cout << "Минимальный: " << *tree.begin() << "\n";
	cout << "Максимальный: " << *(--tree.end()) << "\n";
	cout << "---------------------------------\n";

	//Случай 6: родитель правый дочерний, узел левый дочерний, дядя вставляемого узла черный
	cout << "Случай 6: родитель правый дочерний, узел левый дочерний, дядя вставляемого узла черный" << "\n";
	tree.insert(14);
	tree.PrintTree();
	cout << "Минимальный: " << *tree.begin() << "\n";
	cout << "Максимальный: " << *(--tree.end()) << "\n";
	cout << "---------------------------------\n";
}

//Тесты удаления
void cmd_erase_tests() {
	RBTree<int> tree;
	cout << "--------------------Тесты удаления------------------------\n";
	
	cout << "Начальное дерево:\n";
	std::vector<int> elems = { 1, 2, 6, 3, 5, 8, 7, 4, 9, 10 };
	tree.insert(elems.begin(), elems.end());
	tree.PrintTree();
	
	cout << "Минимальный: " << *tree.begin() << "\n";
	cout << "Максимальный: " << *(--tree.end()) << "\n";
	cout << "----------------------------------------------------------\n";

	//Удаление красного листа
	cout << "Случай 1: Узел без потомков, без нарушения свойств:\n";
	tree.erase(10);
	tree.PrintTree();

	cout << "Минимальный: " << *tree.begin() << "\n";
	cout << "Максимальный: " << *(--tree.end()) << "\n";
	cout << "----------------------------------------------------------\n";

	//Удаление красного узла с двумя потомками
	cout << "Случай 2: Узел с двумя потомками, без нарушения свойств:\n";
	tree.erase(7);
	tree.PrintTree();

	cout << "Минимальный: " << *tree.begin() << "\n";
	cout << "Максимальный: " << *(--tree.end()) << "\n";
	cout << "----------------------------------------------------------\n";

	//Удаление красного узла с двумя потомками
	cout << "Случай 3: Узел с двумя потомками, с нарушением свойств:\n";
	tree.erase(8);
	tree.PrintTree();

	cout << "Минимальный: " << *tree.begin() << "\n";
	cout << "Максимальный: " << *(--tree.end()) << "\n";
	cout << "----------------------------------------------------------\n";

	//Удаление красного узла с двумя потомками
	cout << "Случай 4: Узел без потомков, с нарушением свойств:\n";
	tree.erase(1);
	tree.PrintTree();

	cout << "Минимальный: " << *tree.begin() << "\n";
	cout << "Максимальный: " << *(--tree.end()) << "\n";
	cout << "----------------------------------------------------------\n";

	cout << "Случай 5: Узел c одним потомком, с нарушением свойств:\n";
	tree.erase(9);
	tree.PrintTree();

	cout << "Минимальный: " << *tree.begin() << "\n";
	cout << "Максимальный: " << *(--tree.end()) << "\n";
	cout << "----------------------------------------------------------\n";
}

//Тесты сохранения и загрузки из файла
void file_tests() {
	//Целые числа
	cout << "---------------Копирование в файл целых-----------------\n";
	RBTree<int> intTreeOut({ 1, 2, 3, 4, 5, 6 });
	cout << "Дерево которое сохраняю:\n";
	intTreeOut.PrintTree();

	//Сохранение в файл
	std::ofstream outFile("intTree.txt");
	intTreeOut.serialize(outFile);
	outFile.close();

	//Считываю из файла
	RBTree<int> intTreeIn({ 9, 0, -1 });
	cout << "Дерево до считывания:\n";
	intTreeIn.PrintTree();

	cout << "Дерево после считывания:\n";
	std::ifstream inFile("intTree.txt");
	intTreeIn.deserialize(inFile);
	inFile.close();
	intTreeIn.PrintTree();

	cout << "intTreeOut == intTreeIn: " << intTreeOut.isEqualTo(intTreeIn) << "\n";

	//Символы
	cout << "---------------Копирование в файл символов-----------------\n";
	RBTree<char> chTreeOut({ 'A', 'C', 'E', 'F', 'B', 'D' });
	cout << "Дерево которое сохраняю:\n";
	chTreeOut.PrintTree();

	//Сохранение в файл
	std::ofstream outFile1("charTree.txt");
	chTreeOut.serialize(outFile1);
	outFile1.close();

	//Считываю из файла
	RBTree<char> chTreeIn({ 'G', 'L', 'H' });
	cout << "Дерево до считывания:\n";
	chTreeIn.PrintTree();

	cout << "Дерево после считывания:\n";
	std::ifstream inFile1("charTree.txt");
	chTreeIn.deserialize(inFile1);
	inFile1.close();
	chTreeIn.PrintTree();

	cout << "chTreeOut == chTreeIn: " << chTreeOut.isEqualTo(chTreeIn) << "\n";
}

void time_tests(int n) {
	using namespace std;
	using namespace std::chrono;

	//Вставка
	RBTree<int> tree;
	high_resolution_clock::time_point ins_tree_time1 = high_resolution_clock::now();
	for (int i = 0; i < n; ++i)
		tree.insert(i);
	high_resolution_clock::time_point ins_tree_time2 = high_resolution_clock::now();
	duration<double> ins_tree_span = duration_cast<chrono::nanoseconds>(ins_tree_time2 - ins_tree_time1);

	set<int> s;
	high_resolution_clock::time_point ins_set_time1 = high_resolution_clock::now();
	for (int i = 0; i < n; ++i)
		s.insert(i);
	high_resolution_clock::time_point ins_set_time2 = high_resolution_clock::now();
	duration<double> ins_set_span = duration_cast<chrono::nanoseconds>(ins_set_time2 - ins_set_time1);

	//Поиск
	high_resolution_clock::time_point find_tree_time1 = high_resolution_clock::now();
	for (int i = 0; i < n; ++i)
		tree.find(i);
	high_resolution_clock::time_point find_tree_time2 = high_resolution_clock::now();
	duration<double> find_tree_span = duration_cast<chrono::nanoseconds>(find_tree_time2 - find_tree_time1);
	
	high_resolution_clock::time_point find_set_time1 = high_resolution_clock::now();
	for (int i = 0; i < n; ++i)
		s.find(i);
	high_resolution_clock::time_point find_set_time2 = high_resolution_clock::now();
	duration<double> find_set_span = duration_cast<chrono::nanoseconds>(find_set_time2 - find_set_time1);

	//Удаление
	high_resolution_clock::time_point erase_tree_time1 = high_resolution_clock::now();
	auto it1 = tree.begin();
	while(it1 != tree.end())
		it1 = tree.erase(it1);
	high_resolution_clock::time_point erase_tree_time2 = high_resolution_clock::now();
	duration<double> erase_tree_span = duration_cast<chrono::nanoseconds>(erase_tree_time2 - erase_tree_time1);

	high_resolution_clock::time_point erase_set_time1 = high_resolution_clock::now();
	auto it2 = s.begin();
	while (it2 != s.end())
		it2 = s.erase(it2);
	high_resolution_clock::time_point erase_set_time2 = high_resolution_clock::now();
	duration<double> erase_set_span = duration_cast<chrono::nanoseconds>(erase_set_time2 - erase_set_time1);

	//Вывод
	cout << "Размер входа: " << n << "\n";
	cout << "--------------------------------------------------------------\n";
	cout << "Среднее время вставки для RBTree: " << (ins_tree_span.count() / n) << "\n";
	cout << "Среднее время вставки для set: " << (ins_set_span.count() / n) << "\n";
	cout << "--------------------------------------------------------------\n";	
	cout << "Среднее время поиска для RBTree: " << (find_tree_span.count() / n) << "\n";
	cout << "Среднее время поиска для set: " << (find_set_span.count() / n) << "\n";	
	cout << "--------------------------------------------------------------\n";
	cout << "Среднее время удаления для RBTree: " << (erase_tree_span.count() / n) << "\n";
	cout << "Среднее время удаления для set: " << (erase_set_span.count() / n) << "\n";
	cout << "--------------------------------------------------------------\n";
}