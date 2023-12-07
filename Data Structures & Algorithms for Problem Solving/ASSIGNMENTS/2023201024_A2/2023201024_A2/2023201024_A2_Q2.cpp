#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

#define ll long long
#define ull unsigned long long
#define mod 1000000007
#define INT_MAX 2147000000

//----------- Matrix each Cell<int> structure in array ------------------//
template <typename T>
struct Cell
{
    int x;
    int y;
    T val;
};

template <typename T>
struct Node
{
    int x;
    int y;
    T val;
    Node<T>* next;
};

//----------- Implementation of custom dynamic array -----------------//


template <typename T>
class D_array
{
    Cell<T> *a = nullptr;
    int a_size = 0;
    int a_cap = 0;

    void increase_array(int cap)
    {
        Cell<T> *na = new Cell<T>[cap];
        for (int i = 0; i < a_size; i++)
        {
            na[i] = a[i];
        }
        delete[] a;
        a = na;
    }

public:

    static bool comp(Cell<T> p, Cell<T> q)
    {
        if (p.x == q.x)
            return p.y < q.y;
        return p.x < q.x;
    }

    void push_back(Cell<T> c)
    {
        if (a_size == a_cap)
        {
            int new_cap = (a_cap == 0) ? 1 : (2 * a_cap);
            increase_array(new_cap);
            a_cap = new_cap;
        }
        a[a_size] = c;
        a_size++;
    }
    int size()
    { 
        return a_size;
    }

    Cell<T> at(int index)
    {
        if (index >= a_size)
        {
            Cell<T> temp;
            temp.val = -1;
            return temp;
        }
        return a[index];
    }

    void clear()
    {
        Cell<T> *na = new Cell<T>[1];
        delete[] a;
        a = na;
        a_size = 0;
        a_cap = 0;
    }

    void set_x(int i, int xx)
    {
        if ((i >= 0) && (i < a_cap))
        {
            a[i].x = xx;
        }
    }

    void set_y(int i, int yy)
    {
        if ((i >= 0) && (i < a_cap))
        {
            a[i].y = yy;
        }
    }

    int begin()
    {
        return 0;
    }

    int end()
    {
        return a_size;
    }

    void sort()
    {
        ::sort(a, a + a_size, comp);
    }
};

template <typename T>
class spraceMat
{
public:
    int n1, m1, n2, m2;
    D_array<T> mat1;
    D_array<T> mat2;

    Node<T> *head1 = nullptr;
    Node<T> *head2 = nullptr;
    int s1 = 0;
    int s2 = 0;

    //===================================================================//
    //                  ARRAY IMPLEMENTATION                             //
    //===================================================================//

    void input_mat1_array()
    {
        mat1.clear();
        // cout<<"enter array size";
        cin >> n1 >> m1;
        for (int i = 0; i < n1; i++)
        {
            for (int j = 0; j < m1; j++)
            {
                T x;
                cin >> x;
                if (x != 0)
                {
                    Cell<T> c;
                    c.x = i;
                    c.y = j;
                    c.val = x;
                    mat1.push_back(c);
                }
            }
        }
    }

    void input_mat2_array()
    {
        mat2.clear();
        // cout<<"enter array size";
        cin >> n2 >> m2;
        for (int i = 0; i < n2; i++)
        {
            for (int j = 0; j < m2; j++)
            {
                T x;
                cin >> x;
                if (x != 0)
                {
                    Cell<T> c;
                    c.x = i;
                    c.y = j;
                    c.val = x;
                    mat2.push_back(c);
                }
            }
        }
    }

    void add_mat_array()
    {
        D_array<T> ans;

        int n = mat1.size();
        int m = mat2.size();

        int i = 0;
        int j = 0;
        while (i < n && j < m)
        {
            if ((mat1.at(i).x == mat2.at(j).x) && (mat1.at(i).y == mat2.at(j).y))
            {
                Cell<T> temp;
                temp.val = (mat1.at(i).val + mat2.at(j).val);
                temp.x = mat1.at(i).x;
                temp.y = mat1.at(i).y;
                ans.push_back(temp);
                i++;
                j++;
            }
            else if ((mat1.at(i).x < mat2.at(j).x) || ((mat1.at(i).x == mat2.at(j).x) && (mat1.at(i).y < mat2.at(j).y)))
            {
                ans.push_back(mat1.at(i));
                i++;
            }
            else if ((mat1.at(i).x > mat2.at(j).x) || ((mat1.at(i).x == mat2.at(j).x) && (mat1.at(i).y > mat2.at(j).y)))
            {
                ans.push_back(mat2.at(j));
                j++;
            }
        }

        while (i < n)
        {
            ans.push_back(mat1.at(i));
            i++;
        }

        while (j < m)
        {
            ans.push_back(mat2.at(j));
            j++;
        }

        int k = 0;
        int ans_size = ans.size();
        for (int i = 0; i < n1; i++)
        {
            for (int j = 0; j < m1; j++)
            {
                if ((k < ans_size) && (ans.at(k).x == i) && (ans.at(k).y == j))
                {
                    cout << ans.at(k++).val << " ";
                }
                else
                {
                    cout << 0 << " ";
                }
            }
            cout << "\n";
        }
    }

    void print(D_array<T> &ans, int n, int m)
    {
        int k = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if ((ans.at(k).x == i) && (ans.at(k).y == j))
                {
                    cout << ans.at(k++).val << " ";
                }
                else
                {
                    cout << 0 << " ";
                }
            }
            cout << "\n";
        }
        //cout << k << "\n";
    }

    void traspose_array()
    {
        D_array<T> ans;
        int n = mat1.size();
        for (int i = 0; i < n; i++)
        {
            Cell<T> c;
            c.x = mat1.at(i).y;
            c.y = mat1.at(i).x;
            c.val = mat1.at(i).val;
            ans.push_back(c);
        }

        int temp = n1;
        n1 = m1;
        m1 = temp;

        ans.sort();
        print(ans, n1, m1);
    }

    void mul_mat_array()
    {
        D_array<T>ans, merged;
        int n = mat1.size();
        int m = mat2.size();

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (mat1.at(i).y == mat2.at(j).x)
                {
                    Cell<T> c;
                    c.x = mat1.at(i).x;
                    c.y = mat2.at(j).y;
                    c.val = (mat1.at(i).val * mat2.at(j).val);
                    ans.push_back(c);
                }
            }
        }

        ans.sort();
        int size = ans.size();

        // for (int i = 0; i < size; i++)
        // {
        //     cout << ans.at(i).x << " - " << ans.at(i).y << " - " << ans.at(i).val << "\n";
        // }
        // cout << "\n";

        for (int i = 0; i < size;)
        {
            int j = i + 1;
            T new_val = ans.at(i).val;

            while (j < size && ans.at(i).x == ans.at(j).x && ans.at(i).y == ans.at(j).y)
            {
                new_val += ans.at(j).val;
                j++;
            }

            Cell<T> c;
            c.x = ans.at(i).x;
            c.y = ans.at(i).y;
            c.val = new_val;
            merged.push_back(c);
            i = j;
        }

        int newn = n1;
        int newm = m2;

        print(merged, newn, newm);
    }

    //===================================================================//
    //                  LINKED LIST IMPLEMENTATION                       //
    //===================================================================//
    void input_head1_ll()
    {
        head1 = NULL;
        s1 = 0;
        // cout<<"enter array size";
        cin >> n1 >> m1;
        bool fnode = 1;
        Node<T>* curr = head1;
        for (int i = 0; i < n1; i++)
        {
            for (int j = 0; j < m1; j++)
            {
                T x;
                cin >> x;
                if (x != 0)
                {
                    s1++;
                    Node<T>* temp = new Node<T>;
                    temp->x = i;
                    temp->y = j;
                    temp->val = x;
                    temp->next = nullptr;
                    if(fnode)
                    {
                        head1 = temp;
                        curr = temp;
                        fnode = 0;                    
                    }
                    else
                    {
                        curr->next = temp;
                        curr = curr->next;
                    }
                }
            }
        }
    }

    void input_head2_ll()
    {
        head2 = NULL;
        s2 = 0;
        // cout<<"enter ll size";
        cin >> n2 >> m2;
        bool fnode = 1;
        Node<T>* curr = head2;
        for (int i = 0; i < n2; i++)
        {
            for (int j = 0; j < m2; j++)
            {
                T x;
                cin >> x;
                if (x != 0)
                {
                    s2++;
                    Node<T>* temp = new Node<T>;
                    temp->x = i;
                    temp->y = j;
                    temp->val = x;
                    temp->next = nullptr;
                    if(fnode)
                    {
                        head2 = temp;
                        curr = temp;
                        fnode = 0;                    
                    }
                    else
                    {
                        curr->next = temp;
                        curr = curr->next;
                    }
                }
            }
        }
    }

    void print_ll(Node<T>*head, int n, int m)
    {
        Node<T>*curr = head;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (curr && (curr->x == i) && (curr->y == j))
                {
                    cout<<curr->val<<" ";
                    curr=curr->next;
                }
                else
                    cout<<"0 ";
                
            }
            cout << "\n";
        }
    }

    void add_ll()
    {
        Node<T> *curr1 = head1, *curr2 = head2, *curr3 = NULL;
        Node<T> *ans = nullptr;
        curr3 = ans;
        while (curr1 && curr2)
        {
            if((curr1->x == curr2->x) && (curr1->y == curr2->y))
            {
                Node<T>*temp = new Node<T>;
                temp->val = curr1->val + curr2->val;
                temp->x = curr1->x;
                temp->y = curr1->y;
                temp->next = nullptr;
                if(ans == nullptr)
                {
                    ans = temp;
                    curr3 = temp;
                }
                else
                {
                    curr3->next = temp;
                    curr3 = curr3->next;
                }
                curr1 = curr1->next;
                curr2 = curr2->next;
            }
            else if((curr1->x < curr2->x) || ((curr1->x == curr2->x) && (curr1->y < curr2->y)))
            {
                Node<T>*temp = new Node<T>;
                temp->val = curr1->val ;
                temp->x = curr1->x;
                temp->y = curr1->y;
                temp->next = nullptr;
                if(ans == nullptr)
                {
                    ans = temp;
                    curr3 = temp;
                }
                else
                {
                    curr3->next = temp;
                    curr3 = curr3->next;
                }
                curr1 = curr1->next;
            }
            else if((curr1->x > curr2->x) || ((curr1->x == curr2->x) && (curr1->y > curr2->y)))
            {
                Node<T>*temp = new Node<T>;
                temp->val = curr2->val;
                temp->x = curr2->x;
                temp->y = curr2->y;
                temp->next = nullptr;
                if(ans == nullptr)
                {
                    ans = temp;
                    curr3 = temp;
                }
                else
                {
                    curr3->next = temp;
                    curr3 = curr3->next;
                }
                curr2 = curr2->next;
            }
        }

        while (curr1)
        {
            Node<T>*temp = new Node<T>;
            temp->val = curr1->val ;
            temp->x = curr1->x;
            temp->y = curr1->y;
            temp->next = nullptr;

            if(ans == nullptr)
            {
                ans = temp;
                curr3 = temp;
            }
            else
            {
                curr3->next = temp;
                curr3 = curr3->next;
            }
            curr1 = curr1->next;
        }

        while (curr2)
        {   
            Node<T>*temp = new Node<T>;
            temp->val = curr2->val;
            temp->x = curr2->x;
            temp->y = curr2->y;
            temp->next = nullptr;
            if(ans == nullptr)
            {
                ans = temp;
                curr3 = temp;
            }
            else
            {
                curr3->next = temp;
                curr3 = curr3->next;
            }
            curr2 = curr2->next;
        }
        print_ll(ans, n1, m1);
    }

    Node<T>*middle(Node<T>*head)
    {
        if (head == NULL)
            return head;

        Node<T>*slow = head;
        Node<T>*fast = head->next;

        while (fast != NULL && fast->next != NULL)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }

    Node<T>* merge(Node<T>* left, Node<T>* right)
    {
        Node<T>* result = NULL;

        if (left == NULL)
            return right;
        if (right == NULL)
            return left;

        if ((left->x < right->x) || (left->x == right->x && left->y < right->y))
        {
            result = left;
            result->next = merge(left->next, right);
        }
        else
        {
            result = right;
            result->next = merge(left, right->next);
        }

        return result;
    }

    Node<T>* sort_ll(Node<T>* head)
    {
        if (head == NULL || head->next == NULL)
            return head;

        Node<T>* mid = middle(head);

        Node<T>* left = head;
        Node<T>* right = mid->next;
        mid->next = NULL;

        left = sort_ll(left);
        right = sort_ll(right);

        return merge(left, right);
    }

    void traspose_ll()
    {
        Node<T>* temp = nullptr;
        Node<T>* curr = head1;
        while (curr)
        {
            int t = curr->y;
            curr->y = curr->x;
            curr->x = t;
            curr = curr->next;
        }

        int t = n1;
        n1 = m1;
        m1 = t;

        Node<T>* ans = sort_ll(head1);
        print_ll(ans, n1, m1);
    }

    void mul_ll()
    {
        Node<T>* result = nullptr;
        Node<T>* curr1 = head1;
        Node<T>* curr2 = head2;

        while (curr1 != nullptr)
        {
            while (curr2 != nullptr)
            {
                if (curr1->y == curr2->x)
                {
                    Node<T>* temp = new Node<T>;
                    temp->x = curr1->x;
                    temp->y = curr2->y;
                    temp->val = (curr1->val * curr2->val);
                    temp->next = nullptr;

                    if (result == nullptr)
                    {
                        result = temp;
                    }
                    else
                    {
                        Node<T>* last = result;
                        while (last->next != nullptr)
                        {
                            last = last->next;
                        }
                        last->next = temp;
                    }
                }
                curr2 = curr2->next;
            }
            curr2 = head2;
            curr1 = curr1->next;
        }

        result = sort_ll(result);

        Node<T>* current = result;
        while (current != nullptr && current->next != nullptr)
        {
            if (current->x == current->next->x && current->y == current->next->y)
            {
                current->val += current->next->val;
                Node<T>* temp = current->next;
                current->next = current->next->next;
                delete temp;
            }
            else
            {
                current = current->next;
            }
        }
        int newn = n1;
        int newm = m2;

        print_ll(result, newn, newm);
    }
};


//=====================================================================//
//                   MAIN FUNCTION                                     //
//=====================================================================//
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int choice;
    // cout<<"1. Array   2.Linklist";
    cin >> choice;
    spraceMat<float> sl;
    while (choice != 0)
    {
        switch (choice)
        {
        case 0:
        {
            break;
        }
        case 1: // array
        {
            int op;
            cin >> op;
            if (op == 1) // addition
            {
                sl.input_mat1_array();
                sl.input_mat2_array();
                sl.add_mat_array();
            }
            else if (op == 2) // transpose
            {
                sl.input_mat1_array();
                sl.traspose_array();
            }
            else if (op == 3) // multiplication
            {
                sl.input_mat1_array();
                sl.input_mat2_array();
                sl.mul_mat_array();
            }
            break;
        }
        case 2: // linklist
        {
            int op;
            cin >> op;
            if (op == 1) // addition
            {
                sl.input_head1_ll();
                sl.input_head2_ll();
                sl.add_ll();
            }
            else if (op == 2) // transpose
            {
                sl.input_head1_ll();
                sl.traspose_ll();
            }
            else if (op == 3) // multiplication
            {
                sl.input_head1_ll();
                sl.input_head2_ll();
                sl.mul_ll();
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
    return 0;
}
