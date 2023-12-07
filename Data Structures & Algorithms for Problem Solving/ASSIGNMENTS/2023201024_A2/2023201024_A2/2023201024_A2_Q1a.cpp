#include <iostream>
#include <string>
using namespace std;

#define ll long long
#define ull unsigned long long
#define mod 1000000007
#define INT_MAX 2147000000
int global_ = 1;
//*****************************************************************//
//            Implementation of custom Priority Queue              //
//*****************************************************************//
class Priority_Queue
{
private:
    int *a = NULL;
    int pq_size = 0;
    int pq_capacity = 0;

    void increase_array(int cap)
    {
        int *na = new int[cap];
        for (int i = 0; i < pq_capacity; i++)
        {
            na[i] = a[i];
        }
        delete[] a;
        a = na;
    }

    int parent(int index)
    {
        if(index == 0)
            return -1;
        return (index - 1)/2;
    }

    int left (int index)
    {
        int x = (2*index + 1);
        if(x >= pq_size)
            return -1;
        return x;
    }

    int right (int index)
    {
        int x = (2*index + 2);
        if(x >= pq_size)
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

            if (l != -1 && a[l] < a[minindex])
            {
                minindex = l;
            }

            if (r != -1 && a[r] < a[minindex]) 
            {
                minindex = r;
            }

            if (minindex != i)
            {
                int temp = a[minindex];
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
            if (a[pos] < a[p])
            {
                int temp = a[pos];
                a[pos] = a[p];
                a[p] = temp;

                pos = p;
            }
            else
            {
                break;
            }
            //p = parent(pos);  
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
        a = new int[1];
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

    void push(int ele)
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
            a[pq_size] = ele; 
            heapify_up(pq_size);
            pq_size++;
        }
        else
        {
            a[pq_size] = -ele; 
            heapify_up(pq_size);
            pq_size++;
        }
    }


    //*****************************************************************
    //          Option 5: TOP
    //*****************************************************************
    int top()
    {
        if(pq_size == 0) // what happens when pq_size is empty?????
            return -1;
        if (is_minheap)
            return a[0];
        return (-1 * a[0]);
    }

    //*****************************************************************
    //          Option 6: POP
    //*****************************************************************
    void pop()
    {
        if(pq_size == 0)
        {
            return;
        }
        int temp = a[pq_size-1];
        a[pq_size-1] = a[0];
        a[0] = temp;
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
            cout << a[i] << " ";
        }
        cout << "\n";
        
    }
};

//*****************************************************************
//              Main Function
//*****************************************************************
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int choice;
    cin >> choice;
    Priority_Queue *pq = nullptr;
    while (choice != 0)
    {
        switch (choice)
        {
        case 0:
        {
            break;
        }
        case 1:
        {
            // min heap
            pq = new Priority_Queue();
            pq->is_minheap = 1;
            break;
        }
        case 2:
        {
            // max heap
            pq = new Priority_Queue();
            pq->is_minheap = 0;
            break;
        }
        case 3:
        {
            cout << pq->size() << "\n";
            break;
        }
        case 4:
        {
            int ele;
            cin >> ele;
            pq->push(ele);
            break;
        }
        case 5:
        {
            cout << pq->top() << "\n";
            break;
        }
        case 6:
        {
            pq->pop();
            break;
        }
        case 7:
        {
            cout << boolalpha << pq->empty() << "\n";
            break;
        }
        case 8:
        {
            pq->print();
            break;
        }
        case 9:
        {
            while (!pq->empty())
            {
                cout<<pq->top()<<" ";
                pq->pop();
            }
            break;
        }
        default:
        {
            cout << "choose valid option\n";
        }
        }
        cin >> choice;
    }
    delete pq;
    return 0;
}
