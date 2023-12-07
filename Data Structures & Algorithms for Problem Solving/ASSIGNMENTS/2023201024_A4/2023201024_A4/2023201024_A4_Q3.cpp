#include <iostream>
#include <ctime>     // time calculations
#include <fstream>   // file handling
#include <algorithm> // for sort
#include <iomanip>   // setprecision
#include <string>
#include <vector>

using namespace std;
#define ll long long
#define ull unsigned long long
#define mod 1000000007
#define INT_MAX 2147000000
#define CHUNK_SIZE 98545665
int global_ = 1;
//*****************************************************************//
//            Implementation of custom Priority Queue              //
//*****************************************************************//
class Priority_Queue
{
private:
    pair<int, int> *a = NULL;
    int pq_size = 0;
    int pq_capacity = 0;

    void increase_array(int cap)
    {
        pair<int, int> *na = new pair<int, int>[cap];
        for (int i = 0; i < pq_capacity; i++)
        {
            na[i] = a[i];
        }
        delete[] a;
        a = na;
    }

    int parent(int index)
    {
        if (index == 0)
            return -1;
        return (index - 1) / 2;
    }

    int left(int index)
    {
        int x = (2 * index + 1);
        if (x >= pq_size)
            return -1;
        return x;
    }

    int right(int index)
    {
        int x = (2 * index + 2);
        if (x >= pq_size)
            return -1;
        return x;
    }

    void perculate_down()
    {
        int i = 0;
        while (1)
        {
            int l = left(i);
            int r = right(i);
            int minindex = i;

            if (l != -1 && a[l].first < a[minindex].first)
            {
                minindex = l;
            }

            if (r != -1 && a[r].first < a[minindex].first)
            {
                minindex = r;
            }

            if (minindex != i)
            {
                pair<int, int> temp = a[minindex];
                a[minindex] = a[i];
                a[i] = temp;
            }
            else
            {
                break;
            }
            i = minindex;
        }
    }

    void heapify_up(int pos)
    {
        while (pos > 0)
        {
            int p = parent(pos);
            // cout<<"in heapfyup: "<<pos<<" -> "<<p<<"\n";
            if (a[pos].first < a[p].first)
            {
                pair<int, int> temp = a[pos];
                a[pos] = a[p];
                a[p] = temp;

                pos = p;
            }
            else
            {
                break;
            }
            // p = parent(pos);
        }
    }

public:
    bool is_minheap = 1;
    //*****************************************************************
    //                Option 1: default contructor
    //*****************************************************************
    Priority_Queue()
    {
        int pq_size = 0;
        int pq_capacity = 0;
        bool is_minheap = global_;
        a = new pair<int, int>[1];
    }

    //*****************************************************************
    //          Option 3: current size
    //*****************************************************************
    int size()
    {
        return pq_size;
    }

    //*****************************************************************
    //          Option 4: PUSH
    //*****************************************************************

    void push(pair<int, int> ele)
    {
        // Overflow
        if (pq_size == pq_capacity)
        {
            int new_cap = (pq_capacity == 0) ? 1 : 2 * pq_capacity;
            increase_array(new_cap);
            pq_capacity = new_cap;
        }

        if (is_minheap)
        {
            a[pq_size].first = ele.first;
            a[pq_size].second = ele.second;
            heapify_up(pq_size);
            pq_size++;
        }
        else
        {
            a[pq_size].first = -ele.first;
            a[pq_size].second = -ele.second;
            heapify_up(pq_size);
            pq_size++;
        }
    }

    //*****************************************************************
    //          Option 5: TOP
    //*****************************************************************
    pair<int, int> top()
    {
        if (pq_size == 0) // what happens when pq_size is empty?????
            return {-1, -1};
        if (is_minheap)
            return a[0];
        return {-1 * a[0].first, -1 * a[0].second};
    }

    //*****************************************************************
    //          Option 6: POP
    //*****************************************************************
    void pop()
    {
        if (pq_size == 0)
        {
            return;
        }
        swap(a[pq_size - 1], a[0]);
        pq_size--;
        perculate_down();
    }

    //*****************************************************************
    //          Option 7: empty
    //*****************************************************************
    int empty()
    {
        if (pq_size == 0)
            return 1;
        return 0;
    }

    void print()
    {
        for (int i = 0; i < pq_capacity; i++)
        {
            cout << a[i].first << ", " << a[i].second << " ";
        }
        cout << "\n";
    }
};

// creting priority queue
// Priority_Queue *pq = new Priority_Queue();
// pq->is_minheap = 1;

void k_way_merge(vector<string> &temp_files, string &output_file)
{

    ofstream output;
    output.open(output_file);
    if (!output)
    {
        cerr << "Error: while open output file." << endl;
        return;
    }

    // creting priority queue (min heap)
    Priority_Queue *minh = new Priority_Queue();
    minh->is_minheap = 1;

    int n = temp_files.size();
    vector<ifstream> input_files(n);
    vector<int> values(n);
    n--;
    while (n >= 0)
    {
        input_files[n].open(temp_files[n]);
        if (input_files[n])
        {
            input_files[n] >> values[n];
        }
        n--;
    }

    // Create a min-heap and push the initial values
    for (int i = 0; i < temp_files.size(); i++)
    {
        if (input_files[i])
            minh->push({values[i], i});
    }

    while (!minh->empty())
    {
        pair<int, int> curr = minh->top();
        minh->pop();
        int min_val = curr.first;
        int i = curr.second;
        cout << min_val << " ";
        output << min_val << " "; // Output the minimum value

        if (input_files[i])
        {
            if (input_files[i] >> values[i])
            {
                minh->push({values[i], i}); // Push new data into the priority queue
            }
            else
            {
                // If there's no more data in this input file, close it
                input_files[i].close();
            }
        }
    }

    for (int i = 0; i < temp_files.size(); i++)
    {
        input_files[i].close();
        remove(temp_files[i].c_str());
    }
}

void External_sort(string input_file, string output_file)
{

    FILE *input = fopen(input_file.c_str(), "r");
    vector<string> temp_files;
    if (!input)
    {
        cerr << "Error: while open input file." << endl;
        return;
    }
    else
    {
        int ctr = 0;
        vector<int> chunk_values;
        int chunk_int = 0;
        // cout<<1<<"\n";
        int num;
        while (fscanf(input, "%d", &num) == 1)
        {
            chunk_values.push_back(num);
            if (chunk_values.size() >= CHUNK_SIZE)
            {
                // for (int i = 0; i < chunkData.size(); i++)
                // {
                //     cout<<chunkData[i]<<" ";
                // }cout<<"\n";

                sort(chunk_values.begin(), chunk_values.end());

                // for (int i = 0; i < chunkData.size(); i++)
                // {
                //     cout<<chunkData[i]<<" ";
                // }cout<<"\n";

                // TEMP FILE CREATION
                string file_name = "temp_" + to_string(ctr++) + ".txt";
                temp_files.push_back(file_name);

                // writing into the file
                ofstream t_file(file_name);
                if (!t_file.is_open())
                {
                    cerr << "Error opening temporary input file " << file_name << ".\n";
                    return;
                }
                for (auto i : chunk_values)
                    t_file << i << endl;

                chunk_int = chunk_values.size();
                chunk_values.clear();
                t_file.close();
            }
        }
        // cout<<11<<"\n";
        if (!chunk_values.empty())
        {
            sort(chunk_values.begin(), chunk_values.end());
            string file_name = "temp_" + to_string(ctr++) + ".txt";
            temp_files.push_back(file_name);

            // writing into the file
            ofstream t_file(file_name);
            for (auto i : chunk_values)
                t_file << i << endl;
            chunk_values.clear();
            t_file.close();
        }
        // LOGS
        cout << "Number of integers in a temporary file: " << CHUNK_SIZE << endl;
        cout << "Number of temporary files created: " << temp_files.size() << endl;
    }

    // Merge the sorted chunks using a min-heap
    k_way_merge(temp_files, output_file);
}

int main(int argc, char *argv[])
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (argc != 3)
    {
        cout << "invalid input format\n";
        cout << argv[0] << " .../input_file .../output_file" << endl;
        return 0;
    }

    // string input_file = "input1.txt";
    // string output_file = "output.txt";

    string input_file = argv[1];
    string output_file = argv[2];

    // TIME CALCULATION
    clock_t start_time = clock();
    External_sort(input_file, output_file);
    clock_t end_time = clock();
    double total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    cout << "Total time taken by the program: " << fixed << setprecision(2) << total_time << " seconds" << endl;

    return 0;
}
