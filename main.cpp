#include <iostream>
#include "memory.cpp"

using namespace std;

int main()
{
	srand(time(NULL));

	// memory of 10 pages and 2 segments with set Page numbers
	// vector<int> pages_array = {2, 3, 4, 2, 1, 3, 7, 5, 4, 3};
	vector<int> pages_array = {0, 4, 3, 2, 1, 4, 6, 3, 0};
	Memory mem(pages_array, 3);
	// mem.print_pages();

	// // Memory of 15 pages and 5 segments with random numbers
	// Memory mem2(15, 5);
	// mem2.print_pages();

	// //The print call on a memory instance should display a full table
	// cout << endl;
	// mem2.print();

	mem.play_optimal();
	mem.print();

	return 0;
}