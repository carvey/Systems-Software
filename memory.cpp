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

    char print()
    {
        if (number == -1)
        {
            return ' ';
        }
        else
        {
            return (char)number;
        }
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
    {
        double time = 0;
        double hits = 0;
        double faults = 0;

        //implement fifo here

        vector<double> final = {time, hits, faults};
        return final;
    };

    vector<double> play_lru()
    {
        double time = 0;
        double hits = 0;
        double faults = 0;

        //implement lru here

        vector<double> final = {time, hits, faults};
        return final;
    };

    vector<double> play_optimal()
    {

        double time = 0;
        double hits = 0;
        double faults = 0;

        //implement optimal here

        vector<double> final = {time, hits, faults};
        return final;
    };


};