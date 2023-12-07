#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <utility>
#define MOD 998244353
using namespace std;

template <typename T>
struct node
{
    T key;
    int prio;
    int t_size;
    node *left;
    node *right;

    node(T val)
    {
        key = val;
        prio = rand() % MOD;
        t_size = 1; 
        left = NULL;
        right = NULL;
    }
};

template <typename T>
class treap
{
    node<T> *root;
    void clear_help(node<T> *root)
    {
        if (!root)
            return;
        clear_help(root->left);
        clear_help(root->right);
        delete root;
    }

    void update_t_size(node<T> *curr)
    {
        if (curr)
        {
            int lsz = 0;
            if (curr->left)
                lsz = curr->left->t_size;

            int rsz = 0;
            if (curr->right)
                rsz = curr->right->t_size;

            curr->t_size = (1 + lsz + rsz);
        }
    }

    // merge with 2 pointers used in erase
    node<T> *merge(node<T> *left, node<T> *right)
    {
        if (!left)
        {
            return right;
        }
        if (!right)
        {
            return left;
        }
        if (left->prio > right->prio)
        {
            left->right = merge(left->right, right);
            update_t_size(left);
            return left;
        }
        else
        {
            right->left = merge(left, right->left);
            update_t_size(right);
            return right;
        }
    }

    // merge with 3 pointers
    void merge(node<T> *&root, node<T> *left, node<T> *right)
    {
        if (!left)
        {
            root = right;
        }
        else if (!right)
        {
            root = left;
        }
        else if (left->prio > right->prio)
        {
            merge(left->right, left->right, right);
            root = left;
        }
        else
        {
            merge(right->left, left, right->left);
            root = right;
        }

        // update related information
        update_t_size(root);
    }

    void split(node<T> *curr, T val, node<T> *&left, node<T> *&right)
    {
        if (!curr)
        {
            left = NULL;
            right = NULL;
            return;
        }

        if (val < curr->key)
        {
            split(curr->left, val, left, curr->left);
            right = curr;
        }
        else
        {
            split(curr->right, val, curr->right, right);
            left = curr;
        }

        update_t_size(left);
        update_t_size(right);
    }

    node<T> *erase_help(node<T> *curr, int index)
    {
        int left_size = 0;
        if (curr->left != NULL)
            left_size = curr->left->t_size;
        else
            left_size = 0;

        // if found remove root and merge
        if (index == left_size)
        {
            return merge(curr->left, curr->right);
        }
        else if (index < left_size)
        {
            curr->left = erase_help(curr->left, index);
        }
        else
        {
            curr->right = erase_help(curr->right, index - left_size - 1);
        }

        update_t_size(curr);
        return curr;
    }

    // index to node find
    // node<T> *index_to_node(node<T> *curr, int index)
    // {
    //     int left_size = curr->left ? curr->left->t_size : 0;
    //     if (index == left_size)
    //     {
    //         return curr;
    //     }
    //     else if (index < left_size)
    //     {
    //         return index_to_node(curr->left, index);
    //     }
    //     else
    //     {
    //         return index_to_node(curr->right, index - left_size - 1);
    //     }
    // }

    // just like search in BST with index calculations
    int index_of_help(node<T> *curr, T val)
    {
        if (!curr)
            return -1;

        if (val == curr->key)
        {
            int left_index = index_of_help(curr->left, val);
            if (left_index != -1)
            {
                return left_index;
            }
            int left_size = curr->left ? curr->left->t_size : 0;
            return left_size;
        }
        // going left
        else if (val < curr->key)
        {
            return index_of_help(curr->left, val);
        }
        // going right
        else
        {
            int right_index = index_of_help(curr->right, val);
            if (right_index != -1)
            {
                int left_size = curr->left ? curr->left->t_size : 0;
                return left_size + 1 + right_index;
            }
            else
            {
                return -1;
            }
        }
    }

    T at_index_help(node<T> *curr, int index)
    {
        if (!curr)
        {
            return T();
        }

        int left_size = 0;
        if (curr->left != NULL)
            left_size = curr->left->t_size;
        else
            left_size = 0;

        if (index == left_size)
        {
            return curr->key;
        }
        else if (index < left_size)
        {
            return at_index_help(curr->left, index);
        }
        else
        {
            return at_index_help(curr->right, index - left_size - 1);
        }
    }

    void to_array_help(node<T> *curr, vector<T> &ans)
    {
        if (!curr)
            return;

        to_array_help(curr->left, ans);
        ans.push_back(curr->key);
        to_array_help(curr->right, ans);
    }

    int count_helper(node<T> *curr, T val)
    {
        if (!curr)
            return 0;

        int count = 0;

        if (val == curr->key)
            count++;

        count += count_helper(curr->left, val);
        count += count_helper(curr->right, val);

        return count;
    }

    int lower_bound_helper(node<T> *curr, T val)
    {
        if (!curr)
            return 0;

        if (val <= curr->key)
            return lower_bound_helper(curr->left, val);

        else
        {
            int left_count = (curr->left ? curr->left->t_size : 0);
            int right_count = lower_bound_helper(curr->right, val);
            return left_count + 1 + right_count;
        }
    }

    int upper_bound_help(node<T> *curr, T val)
    {
        if (!curr)
            return 0;

        int left_count = 0;

        if (val == curr->key)
        {
            left_count = 1;
            if (curr->right)
                left_count += curr->right->t_size;
        }
        else if (val < curr->key)
            left_count = upper_bound_help(curr->left, val);

        else
            left_count = 1 + (curr->left ? curr->left->t_size : 0) + upper_bound_help(curr->right, val);
        return left_count;
    }

public:
    treap()
    {
        srand(time(0));
        root = NULL;
    }

    bool empty() // boolalfa add
    {
        if (root == NULL)
            return 1;
        return 0;
    }

    int size()
    {
        if (root)
            return root->t_size;
        return 0;
    }

    void clear()
    {
        clear_help(root);
        root = NULL;
    }

    int insert(T val)
    {
        // new node
        node<T> *new_node = new node<T>(val);

        // for split
        node<T> *left;
        node<T> *right;
        split(root, val, left, right);

        // update index
        int index = left ? left->t_size : 0;

        node<T> *merged = nullptr;
        merge(merged, left, new_node);
        merge(root, merged, right);
        index = indexOf(val);
        update_t_size(root);
        return index;
    }

    bool erase(int index)
    {
        // index invalid
        if (index < 0 || index >= size())
        {
            return false;
        }

        root = erase_help(root, index);
        return true;
    }

    int indexOf(T val)
    {
        return index_of_help(root, val);
    }

    T atIndex(int index)
    {
        if (index < 0 || index >= size())
        {
            // Index is out of bounds
            return T();
        }

        return at_index_help(root, index);
    }

    vector<T> to_array()
    {
        vector<T> ans;
        to_array_help(root, ans);
        return ans;
    }

    treap<T> *merge(treap<T> *t2)
    {
        treap<T> *new_t = new treap<T>();
        new_t->root = merge(root, t2->root);
        return new_t;
    }

    int count(T val)
    {
        return count_helper(root, val);
    }

    int lower_bound(T val)
    {
        return lower_bound_helper(root, val);
    }

    int upper_bound(T val)
    {
        return upper_bound_help(root, val);
    }
    //*********************************************************************************************

    bool erase(int first, int last)
    {
        if ((first < 0) || (last > size() - 1))
            if (first > last)
                return 0;

        treap<T> *leftTreap;
        treap<T> *rightTreap;

        pair<node<T> *, node<T> *> leftAndMiddle = split_help(root, first);
        pair<node<T> *, node<T> *> middleAndRight = split_help(leftAndMiddle.second, last - first + 1);

        leftTreap = new treap<T>();
        leftTreap->root = leftAndMiddle.first;
        rightTreap = new treap<T>();
        rightTreap->root = middleAndRight.second;

        root = merge(leftAndMiddle.first, middleAndRight.second);
        update_t_size(root);

        delete leftTreap;
        delete rightTreap;
        return 1;
    }

    pair<node<T> *, node<T> *> split_help(node<T> *curr, int index)
    {
        if (!curr)
            return {NULL, NULL};

        int left_size = 0;
        if (curr->left != NULL)
            left_size = curr->left->t_size;
        else
            left_size = 0;

        if (left_size >= index)
        {
            pair<node<T> *, node<T> *> left_split = split_help(curr->left, index);
            curr->left = left_split.second;
            update_t_size(curr);
            return {left_split.first, curr};
        }
        else
        {
            pair<node<T> *, node<T> *> right_split = split_help(curr->right, index - left_size - 1);
            curr->right = right_split.first;
            update_t_size(curr);
            return {curr, right_split.second};
        }
    }

    pair<treap<T> *, treap<T> *> split(int index)
    {
        treap<T> *treap1 = new treap<T>();
        treap<T> *treap2 = new treap<T>();
        pair<node<T> *, node<T> *> temp = split_help(root, index);
        treap1->root = temp.first;
        treap2->root = temp.second;
        return {treap1, treap2};
    }

    treap<T> *slice(int first, int last)
    {
        if ((first < 0) || (last > size() - 1))
            if (first > last)
                return 0;

        node<T> *left;
        node<T> *middle;
        node<T> *right;

        split(root, first, left, middle);
        split(middle, last - first + 1, middle, right);

        root = merge(left, right);
        update_t_size(root);
        treap<T> *temp = new treap<T>();
        temp->root = middle;

        // root = temp;
        return temp;
    }
};
// void printt(treap<int> *myTreap)
// {
//     vector<int> sortedValues = myTreap->to_array();
//     cout << "Values in sorted order: ";
//     for (int val : sortedValues)
//     {
//         cout << val << " ";
//     } 
//     cout << endl;
// }

int main()
{
    // /************************
    //          Treap 1
    // ************************/
    // treap<int> *myTreap = new treap<int>();

    // cout << "Inserting values 5, 2, 2, 8, 1, 1, 6." << endl;
    // myTreap->insert(5);
    // myTreap->insert(2);
    // myTreap->insert(2);
    // myTreap->insert(8);
    // myTreap->insert(1);
    // myTreap->insert(1);
    // myTreap->insert(6);
    // cout << "Treap size: " << myTreap->size() << endl;
    // cout << "Inserting value 9." << endl;
    // int in = myTreap->insert(6);
    // cout << "Inserted at index: " << in << endl;

    // /**************************
    //          Treap 2
    // **************************/
    // treap<int> *myTreap1 = new treap<int>();

    // cout << "Inserting values 15, 13, 15, 18, 16, 14" << endl;
    // myTreap1->insert(15);
    // // myTreap->insert(2);
    // myTreap1->insert(13);
    // myTreap1->insert(15);
    // // myTreap->insert(1);
    // myTreap1->insert(18);
    // myTreap1->insert(16);
    // cout << "Treap size: " << myTreap1->size() << endl;
    // cout << "Inserting value 14." << endl;
    // in = myTreap1->insert(10);
    // cout << "Inserted at index: " << in << endl;

    // /****************** Merge testing *****************************/
    // treap<int> *merged = myTreap->merge(myTreap1);
    // cout << "Values in sorted order: ";
    // printt(merged);
    // cout << endl;
    // cout << "*********Merge testing complete***********\n";
    // cout << "count: " << merged->count(15) << "\n";

    // /****************** lower bound *******************************/
    // int count1 = merged->lower_bound(10);
    // int count2 = merged->lower_bound(8);

    // // Print the results
    // cout << "Count of elements less than 10: " << count1 << endl;
    // cout << "Count of elements less than 8: " << count2 << endl;

    // /****************** upper bound *******************************/
    // count1 = merged->upper_bound(3); // Should return the count of elements less than or equal to 3
    // count2 = merged->upper_bound(6); // Should return the count of elements less than or equal to 6

    // // Print the results
    // cout << "Count of elements less than or equal to 3: " << count1 << endl;
    // cout << "Count of elements less than or equal to 6: " << count2 << endl;

    // /****************** Split testing *****************************/
    // pair<treap<int> *, treap<int> *> splitted = merged->split(12);
    // cout << "Values in sorted order: ";
    // printt(splitted.first);
    // cout << endl;
    // printt(splitted.second);
    // cout << endl;
    // cout << "*********split testing complete***********\n";

    // /**************************************************************/
    // cout << "Treap size before erasing range: " << merged->size() << endl;
    // cout << "Erasing elements by range (1, 4):" << endl;
    // for (int i = 2; i <= 5; i++)
    // {
    //     cout << merged->atIndex(i) << ", ";
    // }
    // cout << "\n";
    // merged->erase(2, 5); // Erase the elements in the range [1, 4]
    // printt(merged);
    // cout << "Treap size after erasing range: " << merged->size() << endl;

    // /*************************************************************/
    // // cout << "Preorder traversal of the treap: ";
    // // printt(myTreap);
    // // cout << endl;

    // // cout << "Finding the index of 2:" << endl;
    // // int idx = myTreap->index_of(2);
    // // cout << "Index of 2: " << idx << endl;

    // // cout << "Finding the value at index 3:" << endl;
    // // int value_at_index_3 = myTreap->atIndex(3);
    // // cout << "Value at index 3: " << value_at_index_3 << endl;

    // // cout << "Erasing elements by index:" << endl;
    // // bool erased = myTreap->erase(3); // Erase the element at index 3
    // // cout << "Erased element at index 3: " << (erased ? "true" : "false") << endl;

    // // erased = myTreap->erase(1); // Erase the element at index 1
    // // cout << "Erased element at index 1: " << (erased ? "true" : "false") << endl;

    // // cout << "Treap size after erasing: " << myTreap->size() << endl;

    // cout << "Preorder traversal of the treap: ";
    // printt(myTreap);
    // cout << endl;

    // cout << "Erasing elements by range (1, 4):" << endl;
    // myTreap->erase(1, 4); // Erase the elements in the range [1, 4]
    // cout << "Treap size after erasing range: " << myTreap->size() << endl;

    // cout << "Preorder traversal of the treap after erasing range: ";
    // printt(myTreap);
    // cout << endl;

    // // Testing 'slice' function
    // cout << "Slicing the treap from index 1 to 4:" << endl;
    // treap<int> *slicedTreap = merged->slice(1, 4);
    // cout << "Sliced treap size: " << slicedTreap->size() << endl;
    // cout << "Preorder traversal of the sliced treap: ";
    // printt(slicedTreap);
    // cout << endl;
    // Cleanup
    // delete slicedTreap;

    treap<int> t;
    int choice;
    vector<int> arr;
    int val, index, first, last;
    int i;
    treap<int> *slicedTreap;
    while (true)
    {
        cin >> choice;

        switch (choice)
        {
        case 0: 
            break;
        case 1:
            cout << boolalpha << t.empty() << endl;
            break;
        case 2:
            cout << t.size() << endl;
            break;
        case 3:
            t.clear();
            break;
        case 4:
            cin >> val;
            i = t.insert(val);
            cout << i << endl;
            break;
        case 5:
            cin >> index;
            cout << boolalpha << t.erase(index) << endl;
            break;
        case 6:
            cin >> val;
            cout << t.indexOf(val) << endl;
            break;
        case 7:
            cin >> index;
            cout << t.atIndex(index) << endl;
            break;
        case 10:
            cin >> first >> last;
            cout << boolalpha << t.erase(first, last) << endl;
            break;
        case 11:
            cin >> first >> last;
            slicedTreap = t.slice(first, last);
            break;
        case 12:
            cin >> val;
            cout << t.lower_bound(val) << endl;
            break;
        case 13:
            cin >> val;
            cout << t.upper_bound(val) << endl;
            break;
        case 14:
            cin >> val;
            cout << t.count(val) << endl;
            break;
        case 15:
            arr = t.to_array();
            for (auto i : arr)
                cout << i << " ";
            cout << endl;
            break;
        }
    }

    return 0;
}