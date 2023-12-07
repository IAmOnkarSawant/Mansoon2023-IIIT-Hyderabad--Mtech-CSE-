
#include <iostream>
#include <vector>
#define MOD 9973;

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

    
};

template <typename T1, typename T2>
class unordered_map
{
    avl_tree<T1, T2> table[9973];
    int um_size = 0;

    int c_hash(T1 key)
    {
        return (int)key%MOD;
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
    // void levelOrder()
    // {
    //     for (int i = 0; i < 9973; i++)
    //     {
    //         if(!table[i].avl_empty())
    //             table[i].levelOrder();
    //     }
        
    // }

};

int cntSubarray(int nums[],int n, int K) {
    int count = 0;
    int sum = 0;

    unordered_map<int, int> m;
    m.insert(0, 1); 

    for (int i = 0; i < n ; i++) 
    {
        sum += nums[i];
        if (m.contains(sum - K)) 
        {
            count += m[sum - K];
        }
        m[sum]++;
    }

    return count;
}
 
int main()
{
   int n, k;
   cin>>n>>k;
   int a[n];
   for (int i = 0; i < n; i++)
   {
        cin>>a[i];
   }
   cout<<cntSubarray(a, n, k)<<"\n";
   return 0;
}

