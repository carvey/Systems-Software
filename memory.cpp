#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;

class Page
{
	public:
		int number;

		Page()
		{
			number = rand() % 10;
		}

		Page(int num)
		{
			number = num;
		};

};

class Memory
{
	public:
		vector<Page> pages;
		int segments;

		Memory(int size = 10, int memory_segments=3)
		{
			segments = memory_segments;

			for (int i = 0; i < size; i++)
			{
				pages.push_back(Page());
			}
		};

		Memory(vector<int> pages_vector, int memory_segments=3)
		{
			segments = memory_segments;
			
			for (int i = 0; i < pages_vector.size(); i++)
			{
				pages.push_back(
					Page(pages_vector.at(i))
					);
			}
		};

		void print_pages()
		{
			cout << "[";
			for (int i=0; i<pages.size(); i++)
			{
				cout << pages.at(i).number;
				if (i != pages.size()-1)
					cout << ", ";
				else
				{
					cout << "]";
					cout << endl;
				}
			}
		};

		void print()
		{
			for (int i = 0; i < pages.size(); i++)
			{
				cout << "  " << pages.at(i).number << " ";
			}

			cout << endl;
			
			for (int i = 0; i < segments; i++)
			{
				cout << "-";
				for (int i = 0; i < pages.size(); i++)
				{
					cout << "----";
				}
				cout << endl;

				for (int k=0; k < pages.size(); k++)
				{
					cout << "|   ";
				}
				cout << "|";
				cout << endl;
			}

			cout << "-";
			for (int i = 0; i < pages.size(); i++)
			{
				cout << "----";
			}
			cout << endl;

		};
};