#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define ll long long
#define ull unsigned long long
#define mod 1000000007

//*****************************************************************//
//                  Implementation of custom Deque                 //
//*****************************************************************//
template <typename T>
class MyDeque
{
public:
    T *a;
    int d_size;
    int d_capacity;
    int d_front;
    int d_rear;
    T default_val = T();

    //*****************************************************************
    //                Option 1: default contructor
    //*****************************************************************
    MyDeque()
    {
        //cout << "in default constructor\n";
        a = new T[1];
        for(int i = 0; i < 1; i++)
        {
            a[i] = default_val;
        }
        d_size = 0;
        d_capacity = 0;
        d_front = 0;
        d_rear = 0;
    }

    //*****************************************************************
    //          Option 2: parametrised constructor with size n
    //*****************************************************************
    MyDeque(int n)
    {
        a = new T[n];
        for(int i = 0; i < n; i++)
        {
            a[i] = default_val;
        }
        d_size = 0;
        d_capacity = n;
        d_front = 0;
        d_rear = 0;
    }

    //*****************************************************************
    // Option 3: parametrised constructor with size n and x as default
    //*****************************************************************
    MyDeque(int n, T x)
    {
        a = new T[n];
        default_val = x;
        for(int i = 0; i < n; i++)
        {
            a[i] = default_val;
        }
        d_size = n;
        d_capacity = n;
        d_front = 0;
        d_rear = 0;
    }

    //*****************************************************************
    //          Option 4: Push Back
    //*****************************************************************
    bool push_back(T x)
    {
        //cout << x << "\n";

        if ((d_front == d_rear && d_size != 0) || (d_capacity == 0))
        { // full array (or) capacity = 0
            //cout << "\nbefore: ";
            //print();
            int new_size = (2 * d_capacity) + 1;
            T *newa = new T[new_size];
            int k = 1;
            for(int i = 0; i < new_size; i++)
            {
                newa[i] = default_val;
            }
            for (int i = d_front + 1; i <= (d_front + d_size); i++)
            {
                newa[k++] = a[(i) % d_capacity];
            }
            d_capacity = new_size;
            delete[] a;
            a = newa;
            //cout << "\nafter: ";
            //print();
            d_front = 0;
            d_rear = d_size;
            d_rear = (d_rear + 1) % (d_capacity);
            a[d_rear] = x;
            d_size++;
        }
        else
        {
            d_rear = (d_rear + 1) % (d_capacity);
            a[d_rear] = x;
            d_size++;
        }
        return 1;
    }

    //*****************************************************************
    //          Option 5: pop back
    //*****************************************************************
    bool pop_back()
    {
        if ((d_front == d_rear) && (d_size == 0))
            return 0;
        else
        {
            d_size--;
            a[d_rear] = default_val;
            if (d_rear == 0)
                d_rear = d_capacity - 1;
            else
                d_rear -= 1;
        }
        return 1;
    }

    //*****************************************************************
    //          Option 6: push_front
    //*****************************************************************
    bool push_front(T x)
    {
        // cout << x << "\n";
        if ((d_front == d_rear && d_size != 0) || (d_capacity == 0))
        { // full array (or) capacity = 0
            //cout << "\nbefore: ";
            //print();
            int new_size = (2 * d_capacity) + 1;
            T *newa = new T[new_size];
            int k = 1;
            for(int i = 0; i < new_size; i++)
            {
                newa[i] = default_val;
            }
            for (int i = d_front + 1; i <= (d_front + d_size); i++)
            {
                newa[k++] = a[(i) % d_capacity];
            }
            d_capacity = new_size;
            delete[] a;
            a = newa;
            //cout << "\nafter: ";
            //print();
            d_front = 0;
            d_rear = d_size;
            a[d_front] = x;
            if (d_front == 0)
                d_front = d_capacity - 1;
            else
                d_front -= 1;
            d_size++;
        }
        else
        {
            a[d_front] = x;
            if (d_front == 0)
                d_front = d_capacity - 1;
            else
                d_front -= 1;
            d_size++;
        }
        return 1;
    }

    //*****************************************************************
    //          Option 7: pop front
    //*****************************************************************
    bool pop_front()
    {
        if ((d_front == d_rear) && (d_size == 0))
            return 0;
        else
        {
            d_size--;
            a[d_front] = default_val;
            d_front = (d_front + 1) % d_capacity;
        }
        return 1;
    }

    //*****************************************************************
    //          Option 8: front of Deque
    //*****************************************************************
    T front()
    {
        if (d_front == d_rear && d_size == 0)
        {
            return default_val;
        }
        return a[(d_front + 1) % d_capacity];
    }

    //*****************************************************************
    //          Option 9: Back of Deque
    //*****************************************************************
    T back()
    {
        if (d_front == d_rear && d_size == 0)
        {
            return default_val;
        }
        return a[d_rear];
    }

    //*****************************************************************
    //          Option 10: a[n] nth number
    //*****************************************************************
    // operator overloading
    T &operator[](int index)
    {
        //cout << "overloading\n";
        if (index >= d_size || index < -d_size)
        {
            return default_val;
        }
        if (index < 0)
        {
            index = (d_rear + index + d_capacity)%d_capacity;
        }
        else
            index = (d_front + index + d_capacity)%d_capacity;
        return a[index];
    }

    //*****************************************************************
    //          Option 11: check is empty
    //*****************************************************************
    bool empty()
    {
        return d_size == 0;
    }

    //*****************************************************************
    //          Option 12: size of Deque
    //*****************************************************************
    int size()
    {
        return d_size;
    }

    //*****************************************************************
    //         Option 13: change the size dynamically
    //*****************************************************************
    void resize(int n)
    {
        if (d_capacity < n)
        {
            int new_size = (2 * n) + 1;
            T *newa = new T[new_size];
            int k = 1;
            for(int i = 0; i < new_size; i++)
            {
                newa[i] = default_val;
            }
            for (int i = d_front + 1; i <= (d_front + d_size); i++)
            {
                newa[k++] = a[(i) % d_capacity];
            }
            d_capacity = new_size;
            delete[] a;
            a = newa;
            d_front = 0;
            d_rear = d_size;
        }

        if (n > d_size)
        {
            int elements_to_insert = (n - d_size);
            while (elements_to_insert--)
            {
                d_rear = (d_rear + 1) % (d_capacity);
                a[d_rear] = default_val;
                d_size++;
            }
        }
        else
        {
            int elements_to_delete = (d_size - n);
            // cout << elements_to_delete << "\n";
            while (elements_to_delete--)
            {
                if (d_rear == 0)
                    d_rear = d_capacity - 1;
                else
                    d_rear -= 1;
            }
        }
    }

    //*****************************************************************
    //          Option 14: resize the deque
    //*****************************************************************
    void resize(int n, T d) // function overloading
    {
        if (d_capacity < n)
        {
            int new_size = (2 * n) + 1;
            T *newa = new T[new_size];
            int k = 1;
            for(int i = 0; i < new_size; i++)
            {
                newa[i] = default_val;
            }
            for (int i = d_front + 1; i <= (d_front + d_size); i++)
            {
                newa[k++] = a[(i) % d_capacity];
            }
            d_capacity = new_size;
            delete[] a;
            a = newa;
            d_front = 0;
            d_rear = d_size;
        }

        if (n > d_size)
        {
            int elements_to_insert = (n - d_size);
            while (elements_to_insert--)
            {
                d_rear = (d_rear + 1) % (d_capacity);
                a[d_rear] = d;
                d_size++;
            }
        }
        else
        {
            int elements_to_delete = (d_size - n);
            cout << elements_to_delete << "\n";
            while (elements_to_delete--)
            {
                if (d_rear == 0)
                    d_rear = d_capacity - 1;
                else
                    d_rear -= 1;
            }
        }
    }

    //*****************************************************************
    //          Option 15: reserve or change capacity to n
    //*****************************************************************
    void reserve(int n)
    {
        if (d_capacity < n)
        {
            int new_size = n;
            T *newa = new T[new_size];
            int k = 1;
            for(int i = 0; i < new_size; i++)
            {
                newa[i] = default_val;
            }
            for (int i = d_front + 1; i <= (d_front + d_size); i++)
            {
                newa[k++] = a[(i) % d_capacity];
            }
            d_capacity = new_size;
            delete[] a;
            a = newa;
            d_front = 0;
            d_rear = d_size;
        }
    }

    //*****************************************************************
    //          Option 16: Shrink and fit
    //*****************************************************************
    void shrink_to_fit() // assuming d_size < capacity
    {
        int new_size = (d_size);
        T *newa = new T[new_size];
        int k = 1;
        for(int i = 0; i < new_size; i++)
        {
            newa[i] = default_val;
        }
        for (int i = d_front + 1; i <= (d_front + d_size); i++)
        {
            newa[(k) % d_size] = a[(i) % d_capacity];
            k++;
        }
        d_capacity = new_size;
        a = newa;
        d_front = 0;
        d_rear = 0;
    }

    //*****************************************************************
    //          Option 17: clear the deque
    //*****************************************************************
    void clear()
    {
        d_size = 0;
        d_front = 0;
        d_rear = 0;
    }

    //*****************************************************************
    //          Option 18: capacity change
    //*****************************************************************
    int capacity()
    {
        return d_capacity;
    }

    //*****************************************************************
    //          Option 19: Print for testing
    //*****************************************************************
    // void print()
    // {
    //     // cout<<"A[-3]: "<<a[-3]<<"\n";
    //     //         cout<<"A[-1]: "<<a[-1]<<"\n";
    //     //                 cout<<"A[-4]: "<<a[-4]<<"\n";
    //     cout << d_size << " - " << d_capacity << " - " << d_front << " - " << d_rear << " \n";
    //     for (int i = 0; i < d_capacity; i++)
    //     {
    //         cout << a[i] << " ";
    //     }
    // }
};

//*****************************************************************
//              Main Function
//*****************************************************************


int main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // implementing switch case for taking decision based on choice
    int choice;
    cin >> choice;
    MyDeque<int> dq;
    while (choice != 0)
    {
        switch (choice)
        {
        case 0:
            break;
        case 1:
            dq =  MyDeque<int>();
            break;
        case 2:
            // cout << "Enter size of deque\n";
            int n;
            cin >> n;
            dq = MyDeque<int>(n);
            break;
        case 3:
            int m;
            int x;
            // cout << "Enter size of deque\n";
            cin >> m;
            // cout << "Enter default element\n";
            cin >> x;
            dq = MyDeque<int>(m, x);
            break;
        case 4:
            // cout << "Enter element to be inserted\n";
            int ele;
            cin >> ele;
            dq.push_back(ele);
            break;
        case 5:
            dq.pop_back();
            break;
        case 6:
            // cout << "Enter element to be inserted\n";
            cin >> ele;
            dq.push_front(ele);
            break;
        case 7:
            dq.pop_front();
            break;
        case 8:
            cout << dq.front() << "\n";
            break;
        case 9:
            cout << dq.back() << "\n";
            break;
        case 10:
            cout<<dq[-1];//<<" "<<dq[1];
            break;
        case 11:
        {
            bool emty = dq.empty();
            if (emty)
                cout << "";
            else
                cout << "";
            break;
        }
        case 12:
            cout << dq.size() << "\n";
            break;
        case 13:
        {
            // cout << "enter the size in which we want to resize\n";
            int re_size;
            cin >> re_size;
            dq.resize(re_size);
            break;
        }
        case 14:
        {
            // cout << "enter the size in which we want to resize\n";
            int re_size;
            int default_rs;
            cin >> re_size;
            // cout << "enter the default value for resize\n";
            cin >> default_rs;
            dq.resize(re_size, default_rs);
            break;
        }
        case 15:
        {
            int n;
            // cout << "enter the size in which we want to reserve\n";
            cin >> n;
            dq.reserve(n);
            break;
        }
        case 16:
            dq.shrink_to_fit();
            break;
        case 17:
            dq.clear();
            break;
        case 18:
            cout << dq.capacity() << "\n";
            break;
        default:
            cout << "";
        }
        // cout << "enter choice\n";
        cin >> choice;
    }
    return 0;
}

