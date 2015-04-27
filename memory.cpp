#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <time.h>

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

public:
    //pages will be a vector of Pages
    vector<Page> pages;
    //vector of the ints of all the pages. To be used to pass along randomly generated page vectors
    //to another Memory constructor
    vector<int> raw_pages;
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

        //fill in raw_pages
        for (int page=0;page<pages.size();page++)
        {
            raw_pages.push_back(pages[page].number);
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

    vector<double> play_fifo(bool step=false)
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
        double hits = 0;
        double faults = 0;

        chrono::time_point<chrono::system_clock> start, end;
        start = std::chrono::system_clock::now();


        vector<Page> page_vector;
        vector<Page>::const_iterator pages_iterator;

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
                if (step)
                {
                    print();
                    cin.ignore();
                    cout << endl;
                }
            }

        }

        end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;

        vector<double> final = {elapsed_seconds.count(), hits, faults};
        return final;
    };

    vector<double> play_lru(bool step=false)
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
        double hits = 0;
        double faults = 0;

        chrono::time_point<chrono::system_clock> start, end;
        start = std::chrono::system_clock::now();

        vector<Page> page_vector;
        vector<Page>::iterator pages_iterator;
        //oldest_element_index will track the position of the page that will be removed next
        Page last_used_page;

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
                    int max_pages = 0;
                    //loop through all pages before the current one to determine the LRU page
                    for (int lru_search = column-1; lru_search > 0; lru_search--)
                    {

                        for (int page=0; page<page_vector.size();page++)
                        {
                            Page lru;
                            if (pages[column].number == 7)
                            {
                                lru = last_used_page;
                            }

                            if (page_vector[page] == pages[lru_search])
                            {
                                last_used_page = pages[lru_search];
                                max_pages++;
                                break;
                            }

                        }

                        if (max_pages == page_vector.size())
                        {
                            break;
                        }

                    }

                    //loop through page_vector and replace last_used_page with the current page
                    for (int page=0; page<page_vector.size(); page++)
                    {
                        if (page_vector[page] == last_used_page)
                        {
                            page_vector[page] = pages[column];
                            break;
                        }
                    }

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
                if (step)
                {
                    print();
                    cin.ignore();
                    cout << endl;
                }
            }

        }

        end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;

        vector<double> final = {elapsed_seconds.count(), hits, faults};
        return final;
    };

    vector<double> play_optimal(bool step=false)
    /*
    The function that will simulate the Optimal algorithm with the current Memory instance

    Return type: vector
    Return: a vector of all data recorded for the algorithm where:
        Element at index 0 = the time it took to run the algorithm
        Element at index 1 = The number of hits the algorithm produced
        Element at index 2 = The number of faults the algorithm produced
    */
    {
        double hits = 0;
        double faults = 0;

        chrono::time_point<chrono::system_clock> start, end;
        start = std::chrono::system_clock::now();

        vector<Page> page_vector;
        vector<Page>::iterator pages_iterator;
        //oldest_element_index will track the position of the page that will be removed next
        Page last_used_page;

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
                    vector<Page> tbr;

                    for (int tbr_search = column+1; tbr_search < pages.size(); tbr_search++)
                    {
                        for (int page=0; page<page_vector.size(); page++)
                        {
                            if (page_vector[page] == pages[tbr_search])
                            {
                                tbr.push_back(page_vector[page]);
                            }
                        }
                    }

                    if (tbr.size() == page_vector.size())
                    {
                        Page remove = tbr[tbr.size() - 1];
                        for (int page=0; page<page_vector.size(); page++)
                        {
                            if (remove == page_vector[page])
                            {
                                page_vector[page] = pages[column];
                            }
                        }
                    }
                    else
                    {
                        for (int page=0; page<page_vector.size(); page++)
                        {
                            vector<Page>::iterator iter;
                            iter = find(tbr.begin(), tbr.end(), page_vector[page]);
                            if (iter == tbr.end()) {
                                page_vector[page] = pages[column];
                                break;
                            }
                        }
                    }
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

        end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;

        vector<double> final = {elapsed_seconds.count(), hits, faults};
        return final;
    };



};


class TestCase
{
    public:
        int page_count;
        int segments;
        int count;
        
        TestCase(int iterations, int pages, int segment_count)
        {
            count = iterations;
            page_count = pages;
            segments = segment_count;
        }

        void test_fifo()
        {
            vector<double> results = {0, 0, 0};
            Memory memory(page_count, segments);

            for (int i=0; i<count; i++)
            {
                vector<double> final = memory.play_fifo();
                results[0] += final[0];
                results[1] += final[1];
                results[2] += final[2];
            }

            vector<double> averages = average_vector(results);
            cout << "FIFO RESULTS FOR " << count << " ITERATIONS: " << endl;
            cout << "\tAverage time: " << averages[0] << endl;
            cout << "\tAverage hits: " << averages[1] << endl;
            cout << "\tAverage faults: " << averages[2] << endl;
        };

        void test_lru()
        {
            vector<double> results = {0, 0, 0};
            Memory memory(page_count, segments);

            for (int i=0; i<count; i++)
            {
                vector<double> final = memory.play_lru();
                results[0] += final[0];
                results[1] += final[1];
                results[2] += final[2];
            }

            vector<double> averages = average_vector(results);
            cout << "LRU RESULTS FOR " << count << " ITERATIONS: " << endl;
            cout << "\tAverage time: " << averages[0] << endl;
            cout << "\tAverage hits: " << averages[1] << endl;
            cout << "\tAverage faults: " << averages[2] << endl;
        };

        void test_optimal()
        {
            vector<double> results = {0, 0, 0};
            Memory memory(page_count, segments);

            for (int i=0; i<count; i++)
            {
                vector<double> final = memory.play_optimal();
                results[0] += final[0];
                results[1] += final[1];
                results[2] += final[2];
            }

            vector<double> averages = average_vector(results);
            cout << "OPTIMAL RESULTS FOR " << count << " ITERATIONS: " << endl;
            cout << "\tAverage time: " << averages[0] << endl;
            cout << "\tAverage hits: " << averages[1] << endl;
            cout << "\tAverage faults: " << averages[2] << endl;
        };

        vector<double> average_vector(vector<double> results)
        {
            vector<double> final;
            final.push_back(results[0]/count);
            final.push_back(results[1]/count);
            final.push_back(results[2]/count);

            return final;
        };

};