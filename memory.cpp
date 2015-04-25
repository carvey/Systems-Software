#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>

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

    string print()
    {
        if (number == -1)
        {
            return " ";
        }
        else
        {
            return to_string(number);
        }
    }

    bool empty()
    {
        if (number == -1)
            return true;
        return false;
    }

    //allows Page objects to be compared with the == operator
    bool operator==(const Page& p) const
    {
        return number == p.number;
    }

};

class Memory
{
private:
    vector<Page> y_vector;
    vector<Page> x_vector;

public:
    vector<Page> pages;
    vector<vector<Page> > ps_mapping;
    int segments;

    Memory(int size = 10, int memory_segments=3)
    {
        segments = memory_segments;

        for (int i = 0; i < size; i++)
        {
            pages.push_back(Page());
        }

        for (int i=0; i<size; i++)
        {
            vector<Page> row(segments, Page(-1));
            ps_mapping.push_back(row);
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

        int size = pages.size();
        for (int i=0; i<size; i++)
        {
            vector<Page> row(segments, Page(-1));
            ps_mapping.push_back(row);
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
            for (int j = 0; j < pages.size(); j++)
            {
                cout << "----";
            }
            cout << endl;

            for (int k=0; k < pages.size(); k++)
            {
                cout << "| " << ps_mapping[k][i].print() << " ";
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

    vector<double> play_fifo()
    /*
    The function that will simulate the FIFO algorithm with the current Memory instance

    FIFO: First in first out
        The first page to come in will be the first page to leave once another location in memory 
        is needed but currently filled

    Return type: vector
    Return: a vector of all data recorded for the algorithm where:
        Element at index 0 = the time it took to run the algorithm
        Element at index 1 = The number of hits the algorithm produced
        Element at index 2 = The number of faults the algorithm produced
    */
    {
        double time = 0;
        double hits = 0;
        double faults = 0;

        vector<Page> page_vector;
        vector<Page>::const_iterator pages_iterator;
        //oldest_element_index will track the position of the page that will be removed next
        int oldest_element_index = 0;

        //loop over the columns in ps_mapping (this lines up with the current page also)
        for (int column=0; column<ps_mapping.size(); column++)
        {

            //check for a hit
            pages_iterator = find(page_vector.begin(), page_vector.end(), pages[column]);
            //hit - pass all the other logic and go straight to adding the pages to ps_mappings
            if (pages_iterator != page_vector.end()) {
                hits++;
            }
            //no hit
            else
            {
                faults++;
                //this will check to see if the rows are filled out or not
                if (page_vector.size() == segments)
                {
                    //check whether the page at oldest_element_index needs to move back up to the top row
                    if (oldest_element_index == page_vector.size()){
                        oldest_element_index = 0;
                        //will replace the oldest page in the vector with the newest page (located at pages[column])
                        page_vector[oldest_element_index] = pages[column];
                    }
                    //if oldest_element_index is still at the top or somewhere in the middle of a column's rows
                    else
                        page_vector[oldest_element_index] = pages[column];
                        oldest_element_index++;
                }
                //when the rows arent filled all the way to the bottom
                else
                {
                    page_vector.push_back(pages.at(column));
                }
            }

            
            //loop over each page currently in page_vector (this will also line up with a columns rows)
            //this will put the new page in ps_mapping so it can be drawn out
            for (int row=0; row<page_vector.size(); row++)
            {
                ps_mapping.at(column).at(row) = page_vector.at(row);
            }

        }

        vector<double> final = {time, hits, faults};
        return final;
    };

    vector<double> play_lru()
    /*
    The function that will simulate the LRU algorithm with the current Memory instance

    LRU: Least Recently Used
        Like FIFO, but once a page already in memory is used again (hit), then it will now be the 
        last element to leave memory

    Return type: vector
    Return: a vector of all data recorded for the algorithm where:
        Element at index 0 = the time it took to run the algorithm
        Element at index 1 = The number of hits the algorithm produced
        Element at index 2 = The number of faults the algorithm produced
    */
    {
        double time = 0;
        double hits = 0;
        double faults = 0;

        //implement lru here

        vector<double> final = {time, hits, faults};
        return final;
    };

    vector<double> play_optimal()
    /*
    The function that will simulate the Optimal algorithm with the current Memory instance

    Return type: vector
    Return: a vector of all data recorded for the algorithm where:
        Element at index 0 = the time it took to run the algorithm
        Element at index 1 = The number of hits the algorithm produced
        Element at index 2 = The number of faults the algorithm produced
    */
    {

        double time = 0;
        double hits = 0;
        double faults = 0;

        //implement optimal here

        vector<double> final = {time, hits, faults};
        return final;
    };


};