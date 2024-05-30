#include<iostream>
#include<vector>
#include<set>
#include<chrono>
#include"RBTree.h"
#include"tests.h"

using std::cout;

//����� �������
void cmd_insert_tests() {
	RBTree<int> tree;
	cout << "---------------����� �������------------------\n";

	//�������
	cout << "�������� � ������ ������" << "\n";
	tree.insert(0);
	tree.PrintTree();
	cout << "�����������: " << *tree.begin() << "\n";
	cout << "������������: " << *(--tree.end()) << "\n";
	cout << "---------------------------------\n";

	//����� ������������
	cout << "����� ������������" << "\n";
	tree.insert(3);
	tree.PrintTree();
	cout << "�����������: " << *tree.begin() << "\n";
	cout << "������������: " << *(--tree.end()) << "\n";
	cout << "---------------------------------\n";

	//����� �����������
	cout << "����� �����������" << "\n";
	tree.insert(-3);
	tree.PrintTree();
	cout << "�����������: " << *tree.begin() << "\n";
	cout << "������������: " << *(--tree.end()) << "\n";
	cout << "---------------------------------\n";

	//������� ��� ����
	cout << "������� ��� ����" << "\n";
	tree.insert(-3);
	tree.PrintTree();
	cout << "�����������: " << *tree.begin() << "\n";
	cout << "������������: " << *(--tree.end()) << "\n";
	cout << "---------------------------------\n";

	//������ 1: �������� ����� ��������, ���� ������������ ���� �������
	cout << "������ 1: �������� ����� ��������, ���� ������������ ���� �������" << "\n";
	tree.insert(-6);
	tree.PrintTree();
	cout << "�����������: " << *tree.begin() << "\n";
	cout << "������������: " << *(--tree.end()) << "\n";
	cout << "---------------------------------\n";

	//������ 2: �������� ����� ��������, ���� ����� ��������, ���� ������������ ���� ������
	cout << "������ 2: �������� ����� ��������, ���� ����� ��������, ���� ������������ ���� ������" << "\n";
	tree.insert(-9);
	tree.PrintTree();
	cout << "�����������: " << *tree.begin() << "\n";
	cout << "������������: " << *(--tree.end()) << "\n";
	cout << "---------------------------------\n";

	//������ 3: �������� ������ ��������, ���� ������������ ���� �������
	cout << "������ 3: �������� ������ ��������, ���� ������������ ���� �������" << "\n";
	tree.insert(-5);
	tree.PrintTree();
	cout << "�����������: " << *tree.begin() << "\n";
	cout << "������������: " << *(--tree.end()) << "\n";
	cout << "---------------------------------\n";

	//������ 4: �������� ����� ��������, ���� ������ ��������, ���� ������������ ���� ������
	cout << "������ 4: �������� ����� ��������, ���� ������ ��������, ���� ������������ ���� ������" << "\n";
	tree.insert(-4);
	tree.PrintTree();
	cout << "�����������: " << *tree.begin() << "\n";
	cout << "������������: " << *(--tree.end()) << "\n";
	cout << "---------------------------------\n";

	tree.clear();
	cout << "������� ������ � ������� ��� ��������� �����" << "\n";
	tree.insert(0);
	tree.insert(-4);
	tree.insert(6);
	tree.PrintTree();
	cout << "�����������: " << *tree.begin() << "\n";
	cout << "������������: " << *(--tree.end()) << "\n";
	cout << "---------------------------------\n";

	//��� �����������
	cout << "��� ������������� ������" << "\n";
	tree.insert(9);
	tree.PrintTree();
	cout << "�����������: " << *tree.begin() << "\n";
	cout << "������������: " << *(--tree.end()) << "\n";
	cout << "---------------------------------\n";

	//������ 5: �������� ������ ��������, ���� ������ ��������, ���� ������������ ���� ������
	cout << "������ 5: �������� ������ ��������, ���� ������ ��������, ���� ������������ ���� ������" << "\n";
	tree.insert(13);
	tree.PrintTree();
	cout << "�����������: " << *tree.begin() << "\n";
	cout << "������������: " << *(--tree.end()) << "\n";
	cout << "---------------------------------\n";

	//��� �����������
	cout << "��� ������������� ������" << "\n";
	tree.insert(15);
	tree.PrintTree();
	cout << "�����������: " << *tree.begin() << "\n";
	cout << "������������: " << *(--tree.end()) << "\n";
	cout << "---------------------------------\n";

	//������ 6: �������� ������ ��������, ���� ����� ��������, ���� ������������ ���� ������
	cout << "������ 6: �������� ������ ��������, ���� ����� ��������, ���� ������������ ���� ������" << "\n";
	tree.insert(14);
	tree.PrintTree();
	cout << "�����������: " << *tree.begin() << "\n";
	cout << "������������: " << *(--tree.end()) << "\n";
	cout << "---------------------------------\n";
}

//����� ��������
void cmd_erase_tests() {
	RBTree<int> tree;
	cout << "--------------------����� ��������------------------------\n";
	
	cout << "��������� ������:\n";
	std::vector<int> elems = { 1, 2, 6, 3, 5, 8, 7, 4, 9, 10 };
	tree.insert(elems.begin(), elems.end());
	tree.PrintTree();
	
	cout << "�����������: " << *tree.begin() << "\n";
	cout << "������������: " << *(--tree.end()) << "\n";
	cout << "----------------------------------------------------------\n";

	//�������� �������� �����
	cout << "������ 1: ���� ��� ��������, ��� ��������� �������:\n";
	tree.erase(10);
	tree.PrintTree();

	cout << "�����������: " << *tree.begin() << "\n";
	cout << "������������: " << *(--tree.end()) << "\n";
	cout << "----------------------------------------------------------\n";

	//�������� �������� ���� � ����� ���������
	cout << "������ 2: ���� � ����� ���������, ��� ��������� �������:\n";
	tree.erase(7);
	tree.PrintTree();

	cout << "�����������: " << *tree.begin() << "\n";
	cout << "������������: " << *(--tree.end()) << "\n";
	cout << "----------------------------------------------------------\n";

	//�������� �������� ���� � ����� ���������
	cout << "������ 3: ���� � ����� ���������, � ���������� �������:\n";
	tree.erase(8);
	tree.PrintTree();

	cout << "�����������: " << *tree.begin() << "\n";
	cout << "������������: " << *(--tree.end()) << "\n";
	cout << "----------------------------------------------------------\n";

	//�������� �������� ���� � ����� ���������
	cout << "������ 4: ���� ��� ��������, � ���������� �������:\n";
	tree.erase(1);
	tree.PrintTree();

	cout << "�����������: " << *tree.begin() << "\n";
	cout << "������������: " << *(--tree.end()) << "\n";
	cout << "----------------------------------------------------------\n";

	cout << "������ 5: ���� c ����� ��������, � ���������� �������:\n";
	tree.erase(9);
	tree.PrintTree();

	cout << "�����������: " << *tree.begin() << "\n";
	cout << "������������: " << *(--tree.end()) << "\n";
	cout << "----------------------------------------------------------\n";
}

//����� ���������� � �������� �� �����
void file_tests() {
	//����� �����
	cout << "---------------����������� � ���� �����-----------------\n";
	RBTree<int> intTreeOut({ 1, 2, 3, 4, 5, 6 });
	cout << "������ ������� ��������:\n";
	intTreeOut.PrintTree();

	//���������� � ����
	std::ofstream outFile("intTree.txt");
	intTreeOut.serialize(outFile);
	outFile.close();

	//�������� �� �����
	RBTree<int> intTreeIn({ 9, 0, -1 });
	cout << "������ �� ����������:\n";
	intTreeIn.PrintTree();

	cout << "������ ����� ����������:\n";
	std::ifstream inFile("intTree.txt");
	intTreeIn.deserialize(inFile);
	inFile.close();
	intTreeIn.PrintTree();

	cout << "intTreeOut == intTreeIn: " << intTreeOut.isEqualTo(intTreeIn) << "\n";

	//�������
	cout << "---------------����������� � ���� ��������-----------------\n";
	RBTree<char> chTreeOut({ 'A', 'C', 'E', 'F', 'B', 'D' });
	cout << "������ ������� ��������:\n";
	chTreeOut.PrintTree();

	//���������� � ����
	std::ofstream outFile1("charTree.txt");
	chTreeOut.serialize(outFile1);
	outFile1.close();

	//�������� �� �����
	RBTree<char> chTreeIn({ 'G', 'L', 'H' });
	cout << "������ �� ����������:\n";
	chTreeIn.PrintTree();

	cout << "������ ����� ����������:\n";
	std::ifstream inFile1("charTree.txt");
	chTreeIn.deserialize(inFile1);
	inFile1.close();
	chTreeIn.PrintTree();

	cout << "chTreeOut == chTreeIn: " << chTreeOut.isEqualTo(chTreeIn) << "\n";
}

void time_tests(int n) {
	using namespace std;
	using namespace std::chrono;

	//�������
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

	//�����
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

	//��������
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

	//�����
	cout << "������ �����: " << n << "\n";
	cout << "--------------------------------------------------------------\n";
	cout << "������� ����� ������� ��� RBTree: " << (ins_tree_span.count() / n) << "\n";
	cout << "������� ����� ������� ��� set: " << (ins_set_span.count() / n) << "\n";
	cout << "--------------------------------------------------------------\n";	
	cout << "������� ����� ������ ��� RBTree: " << (find_tree_span.count() / n) << "\n";
	cout << "������� ����� ������ ��� set: " << (find_set_span.count() / n) << "\n";	
	cout << "--------------------------------------------------------------\n";
	cout << "������� ����� �������� ��� RBTree: " << (erase_tree_span.count() / n) << "\n";
	cout << "������� ����� �������� ��� set: " << (erase_set_span.count() / n) << "\n";
	cout << "--------------------------------------------------------------\n";
}