#include <iostream>
#include "RBTree.h"
#include "tests.h"
#include <fstream>

using std::cout;

int main() {
	setlocale(LC_ALL, "Russian");
	
	//cmd_insert_tests();
	//cmd_erase_tests();
	//file_tests();

	time_tests(10000);
	time_tests(10000000);
}