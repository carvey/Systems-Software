#include <iostream>
#include "memory.cpp"

using namespace std;

int main()
{
	srand(time(NULL));

	// memory of 10 pages and 2 segments with set Page numbers
	vector<int> pages_array = {4, 7, 3, 0, 1, 7, 3, 8, 5, 4, 5, 3, 4, 7};
	Memory mem(pages_array, 3);
	// mem.print_pages();

	// // Memory of 15 pages and 5 segments with random numbers
	// Memory mem2(15, 5);
	// mem2.print_pages();

	// //The print call on a memory instance should display a full table
	// cout << endl;
	// mem2.print();

	mem.play_fifo();
	mem.print();

	return 0;
}