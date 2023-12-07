#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#define MOD 9973

using namespace std;

template <typename T1, typename T2>
struct Node
{
    T1 key;
    T2 value;
    Node *left;
    Node *right;

    Node(T1 k, T2 v)
    {
        key = k;
        value = v;
        left = NULL;
        right = NULL;
    }
};

template <typename T1, typename T2>
class avl_tree
{
    int om_size = 0;
    Node<T1, T2> *root = NULL;
    
    int height(Node<T1, T2> *curr)
    {
        if (!curr)
            return 0;

        int l, r;
        l = height(curr->left);
        r = height(curr->right);

        return (1 + max(l, r));
    }

    Node<T1, T2> *lRot(Node<T1, T2> *curr)
    {
        Node<T1, T2> *temp = curr->right->left;
        Node<T1, T2> *newroot = curr->right;
        newroot->left = curr;
        newroot->left->right = temp;
        return newroot;
    }

    Node<T1, T2> *rRot(Node<T1, T2> *curr)
    {
        Node<T1, T2> *temp = curr->left->right;
        Node<T1, T2> *newroot = curr->left;
        newroot->right = curr;
        newroot->right->left = temp;
        return newroot;
    }

    Node<T1, T2> *insertRec(Node<T1, T2> *curr, T1 k, T2 v)
    {
        if (curr == NULL)
        {
            Node<T1, T2> *temp = new Node<T1, T2>(k, v);
            return temp;
        }

        if (curr->key > k)
            curr->left = insertRec(curr->left, k, v);
        else if (curr->key < k)
            curr->right = insertRec(curr->right, k, v);

        int l = height(curr->left);
        int r = height(curr->right);

        int bal = l - r;
        if (bal > 1)
        {
            if (curr->left->key > k)
                return rRot(curr);
            else
            {
                curr->left = lRot(curr->left);
                return rRot(curr);
            }
        }
        else if (bal < -1)
        {
            if (curr->right->key < k)
                return lRot(curr);
            else
            {
                curr->right = rRot(curr->right);
                return lRot(curr);
            }
        }
        return curr;
    }

    bool containsRec(Node<T1, T2> *curr, T1 k)
    {
        bool a;
        if (!curr)
            return 0;
        if (curr->key == k)
            return 1;
        else if(curr->key > k)
            a = containsRec(curr->left, k);
        else
            a = containsRec(curr->right, k);

        return a;
    }

    bool updateRec(Node<T1, T2> *curr, T1 k, T2 val)
    {
        bool a;
        if (!curr)
            return 0;
        if (curr->key == k)
        {
            curr->value = val;
            return 1;
        }
        else if(curr->key > k)
            a = updateRec(curr->left, k, val);
        else
            a = updateRec(curr->right, k, val);

        return a;
    }

    T2& valueRec(Node<T1, T2> *curr, T1 k)
    {
        if (!curr)
        {
            root = insertRec(root, k, T2());
            om_size++;
            return valueRec(root, k);
        }
        if (curr->key == k)
            return curr->value;
        else if (curr->key > k)
            return valueRec(curr->left, k);
        else
            return valueRec(curr->right, k);
    }


    Node<T1, T2> *eraseRec(Node<T1, T2> *curr, T1 k)
    {
        if (!curr)
            return NULL;

        if (curr->key == k)
        {
            Node<T1, T2> *r = curr->right;
            if (!r)
            {
                Node<T1, T2> *l = curr->left;
                delete curr;
                return l;  
            }
            else if (!curr->left)
            {
                delete curr;
                return r;  
            }
            else
            {
                while (r->left != NULL)
                    r = r->left;
                curr->key = r->key;
                curr->right = eraseRec(curr->right, r->key); 
            }
        }
        else if (curr->key > k)
            curr->left = eraseRec(curr->left, k);
        else if (curr->key < k)
            curr->right = eraseRec(curr->right, k);

        // Balance
        int l = height(curr->left);
        int r = height(curr->right);
        int bal = l - r;
        if (bal > 1)
        {
            if (height(curr->left) >= height(curr->right))
                return rRot(curr);
            else
            {
                curr->left = lRot(curr->left);
                return rRot(curr);
            }
        }
        else if (bal < -1)
        {
            if (height(curr->left) <= height(curr->right))
                return lRot(curr);
            else
            {
                curr->right = rRot(curr->right);
                return lRot(curr);
            }
        }

        return curr;
    }

    void clearRec(Node<T1, T2> *curr)
    {
        if(curr == NULL)
            return;

        clearRec(curr->left);
        clearRec(curr->right);
        delete curr;
    }

    void inorder(Node<T1, T2> *curr, vector<T1>& ans)
    {
        if(curr == NULL)
            return;
        inorder(curr->left, ans);
        ans.push_back(curr->key);
        inorder(curr->right, ans);
    }

public:
    avl_tree()
    {
        om_size = 0;
        root = NULL;
    }

    bool avl_empty()
    {
        return (om_size == 0);
    }

    int avl_size()
    {
        return om_size;
    }

    bool avl_contains(T1 key)
    {
        return containsRec(root, key);
    }

    bool avl_insert(T1 k, T2 v)
    {
        if(avl_contains(k))
            return 0;
        om_size++;
        root = insertRec(root, k, v);
        return 1;
    }

    bool avl_update(T1 k, T2 v)
    {
        updateRec(root, k, v);
        return 1;
    }

    bool avl_erase(T1 key)
    {
        if (!avl_contains(key))
        {
            return false;
        }
        root = eraseRec(root, key);
        om_size--;
        return true;
    }


    void avl_clear()
    {
        if(root == NULL)
            return;
        clearRec(root);
        root = NULL;
        om_size = 0;
    }

    vector<T1> avl_keys()
    {
        vector<T1> ans;
        inorder(root, ans);
        return ans;
    }

    T2& operator[](T1 key)
    {
        return valueRec(root, key);
    }

    
    // void levelOrder()
    // {
    //     //cout<<om_size<<"\n";
    //     if (root == NULL)
    //         return;
    //     queue<Node<T1, T2> *> q;
    //     q.push(root);
    //     while (!q.empty())
    //     {
    //         int s = q.size();
    //         for (int i = 0; i < s; i++)
    //         {
    //             Node<T1, T2> *node = q.front();
    //             q.pop();
    //             if (node->left != NULL)
    //                 q.push(node->left);
    //             if (node->right != NULL)
    //                 q.push(node->right);
    //             cout << node->key << ": " << node->value << " ";
    //         }
    //     }
    // }
};

template <typename T1, typename T2>
class unordered_map
{
    avl_tree<T1, T2> table[9973];
    int um_size = 0;

    long long customStringHash(const string& str) 
    {
        long long hash = 0;
        for (char c : str) 
        {
            hash = ((hash * 31)%MOD + c)%MOD; 
        }
        return hash;
    }

    int c_hash(T1 key)
    {
        string s;
        if(typeid(key) != typeid(string))
        {
             s = (key);// use to_string for int, float, double, long, long long
        }                       // use string for string
        long long slot = customStringHash(s);

        return slot%MOD;
    }

public:
    unordered_map()
    {
        um_size = 0;
    }

    bool insert(T1 key, T2 value)
    {
        um_size++;
        int slot = c_hash(key);
        return table[slot].avl_insert(key, value);
    }

    bool erase(T1 key)
    {
        int slot = c_hash(key);
        return table[slot].avl_erase(key);
    }

    bool contains(T1 key)
    {
        int slot = c_hash(key);
        return table[slot].avl_contains(key);
    }

    T2& operator[](T1 key)
    {
        int slot = c_hash(key);
        return table[slot][key];
    }

    void clear()
    {
        for (int i = 0; i < 9973; i++)
        {
            if(!table[i].avl_empty())
                table[i].avl_clear();
        }
    }

    int size()
    {
        um_size = 0;
        for (int i = 0; i < 9973; i++)
        {
            if(!table[i].avl_empty())
                um_size += table[i].avl_size();
        }
        return um_size;
    }

    bool empty()
    {
        for (int i = 0; i < 9973; i++)
        {
            if(!table[i].avl_empty())
                return 0;
        }
        return 1;
    }

    vector<T1> keys()
    {
        vector<T1> ans;
        for (int i = 0; i < 9973; i++)
        {
            vector<T1> temp;
            if(!table[i].avl_empty())
                temp = table[i].avl_keys();
            for (int i = 0; i < temp.size(); i++)
            {
                ans.push_back(temp[i]);
            }
        }
        return ans;
    }
    void levelOrder()
    {
        for (int i = 0; i < 9973; i++)
        {
            if(!table[i].avl_empty())
                table[i].levelOrder();
        }
        
    }

};
 
int main()
{
    unordered_map<long, int> um;
    // um.insert("1", 10);
    // um.insert("2", 20);
    // um.insert("3", 30);
    // um.levelOrder();cout<<"\n";
    // um.insert("4", 40);
    // um.levelOrder();cout<<"\n";
    // um.insert("5", 50);
    // um.levelOrder();cout<<"\n";
    // um.insert("6", 60);
    // um.levelOrder();cout<<"\n";
    // um.insert("8", 70);
    // um.levelOrder();cout<<"\n";

    // vector<string> t = um.keys();
    // cout<<t.size();
    // for (int i = 0; i < t.size(); i++)
    // {
    //     cout<<t[i]<<" ";
    // }
    // cout<<"\n";
    
    // cout << um.contains("3") << "\n";
    // cout << um.contains("10") << "\n";
    // cout << um.contains("7") << "\n";
    // um.erase("2");
    // um.levelOrder();cout<<"\n";
    // um.erase("3");
    // um.levelOrder();cout<<"\n";
    // cout<<um.empty()<<"\n";
    // //um.clear();
    // cout<<um.empty()<<"\n";
    // cout<<um.size()<<"\n";
    // um.levelOrder();cout<<"\n";

    // cout<<"erase\n";
    // um.erase("1");
    // um.levelOrder();
    // cout<<um["6"]<<"\n";

    int q;
    cin>>q;
    long key;
    int value; 
    vector<long> t1;
    while(q--)
    {
        int ch;
        std::cin>>ch;
        switch (ch)
        {
        case 1:
            std::cin>>key;
            std::cin>>value;
            cout<<boolalpha<<um.insert(key, value)<<"\n";
            break;
        case 2:
            std::cin>>key;
            cout<<boolalpha<<um.erase(key)<<"\n";
            break;
        case 3:
            std::cin>>key;
            cout<<boolalpha<<um.contains(key)<<"\n";
            break;
        case 4:
            std::cin>>key;
            cout<<um[key]<<"\n";
            break;
        case 5:
            um.clear();
            break;
        case 6:
            cout<<um.size()<<"\n";
            break;
        case 7:
            cout<<boolalpha<<um.empty()<<"\n";
            break;
        case 8:
            t1 = um.keys();
            for (int i = 0; i < t1.size(); i++)
            {
                cout<<t1[i]<<"\n";
            }
            break;
        default:
            break;
        }
    }

    return 0;
}