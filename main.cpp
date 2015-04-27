#include <iostream>
#include "memory.cpp"

using namespace std;

int main()
{
	srand(time(NULL));

	cout << "----------------------------------------------" << endl;
	cout << "| VIRTUAL MEMORY PAGE REPLACEMENT ALGORITHMS |" << endl;
	cout << "|--------------------------------------------|" << endl;
	cout << "| Charles Arvey                              |" << endl;
	cout << "| Christopher Hanson                         |" << endl;
	cout << "| Alexandria Sanders                         |" << endl;
	cout << "| Garret Edwards                             |" << endl;
	cout << "| Shannon Sergeant                           |" << endl;
	cout << "----------------------------------------------" << endl << endl;


	// memory of 10 pages and 2 segments with set Page numbers
	vector<int> pages_array_mem1 = {4, 7, 3, 0, 1, 7, 3, 8, 5, 4, 5, 3, 4, 7};
	Memory memory_1(pages_array_mem1, 5);
	cout << "Pages in memory: ";
	memory_1.print_pages();
	cout << endl << "FIFO: Press Enter to go through each step" << endl;
	memory_1.play_fifo(true);

	vector<int> pages_array_mem2 = {2, 3, 4, 2, 1, 3, 7, 5, 4, 3};
	Memory memory_2(pages_array_mem2, 3);
	cout << "Pages in memory: ";
	memory_2.print_pages();
	cout << endl << "Final LRU Table" << endl;
	memory_2.play_lru();
	memory_2.print();
	cout << endl;


	cout << endl;
	vector<int> pages_array_mem3 = {0, 4, 3, 2, 1, 4, 6, 3, 0};
	Memory memory_3(pages_array_mem3, 3);
	cout << "Pages in memory: ";
	memory_3.print_pages();
	cout << endl << "Final Optimal Table" << endl;
	memory_3.play_optimal();
	memory_3.print();

	cout << endl;
	int page_count;
	cout << "Number of pages to test with: ";
	cin >> page_count;

	int test_iterations;
	cout << "Number of iterations to test with: ";
	cin >> test_iterations;
	cout << endl;

	Memory mem2(page_count, 3);
	Memory mem3(mem2.raw_pages, 5);

	cout << "----------";
	cout << "Testing with 3 Memory Segments";
	cout << "----------" << endl;
	TestCase test_mem2(mem2);
	test_mem2.test_fifo(test_iterations);
	test_mem2.test_lru(test_iterations);
	test_mem2.test_optimal(test_iterations);

	cout << endl;

	cout << "----------";
	cout << "Testing with 5 Memory Segments";
	cout << "----------" << endl;
	TestCase test_mem3(mem3);
	test_mem3.test_fifo(test_iterations);
	test_mem3.test_lru(test_iterations);
	test_mem3.test_optimal(test_iterations);

	return 0;
}