#include <iostream>
#include "memory.cpp"

using namespace std;

int main()
{
	srand(time(NULL));

	// memory of 10 pages with set Page numbers
	vector<int> pages_array = {1, 2, 2, 3, 7, 5, 3, 2, 9, 4};
	Memory mem(pages_array, 2);
	mem.print_pages();

	// Memory of 10 pages with random numbers
	Memory mem2(15, 5);
	mem2.print_pages();

	//The print call on a memory instance should display a full table
	cout << endl;
	mem2.print();


	return 0;
}