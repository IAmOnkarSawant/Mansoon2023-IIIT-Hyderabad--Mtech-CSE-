#include <iostream>
#include <vector>
#include <queue>

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
class ordered_map
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
            return (curr->value);
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

    pair<bool, T1> lbRec(Node<T1, T2> *curr, T1 key)
    {
        if(!curr)
        {
            return {false, T1()};
        }
        lbRec(curr->left, key);
        if(curr->key >= key)
        {
            return {true, curr->key};
        }
        lbRec(curr->right, key);
    }

    Node<T1, T2> *prev = NULL;
    pair<bool, T1> ubRec(Node<T1, T2> *curr, T1 key)
    {
        if(!curr)
        {
            return {false, T1()};
        }
        ubRec(curr->left, key);

        if(curr->key == key)
            return {true, curr->key};
        else if(curr->key > key )
            return {true, prev->key};
        else
            prev = curr;

        ubRec(curr->right, key);
    }

public:
    ordered_map()
    {
        om_size = 0;
        root = NULL;
    }

    bool empty()
    {
        return (om_size == 0);
    }

    int size()
    {
        return om_size;
    }

    bool contains(T1 key)
    {
        return containsRec(root, key);
    }

    bool insert(T1 k, T2 v)
    {
        if(contains(k))
            return 0;
        om_size++;
        root = insertRec(root, k, v);
        return 1;
    }

    bool update(T1 k, T2 v)
    {
        updateRec(root, k, v);
        return 1;
    }

    bool erase(T1 key)
    {
        if (!contains(key))
        {
            return false;
        }
        root = eraseRec(root, key);
        om_size--;
        return true;
    }


    void clear()
    {
        if(root == NULL)
            return;
        clearRec(root);
        root = NULL;
        om_size = 0;
    }

    vector<T1> keys()
    {
        vector<T1> ans;
        inorder(root, ans);
        return ans;
    }

    T2& operator[](T1 key)
    {
        return valueRec(root, key);
    }

    pair<bool, T1> lower_bound(T1 key)
    {
        return lbRec(root, key);
    }

    pair<bool, T1> upper_bound(T1 key)
    {
        return ubRec(root, key);
    }

    void levelOrder()
    {
        cout<<om_size<<"\n";
        if (root == NULL)
            return;
        queue<Node<T1, T2> *> q;
        q.push(root);
        while (!q.empty())
        {
            int s = q.size();
            for (int i = 0; i < s; i++)
            {
                Node<T1, T2> *node = q.front();
                q.pop();
                if (node->left != NULL)
                    q.push(node->left);
                if (node->right != NULL)
                    q.push(node->right);
                cout << node->key << ": " << node->value << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }    
};

int main()
{
    int n;
    ordered_map<pair<int,int>, int>m;
    cin>>n;
    pair<int, int>arr[n];
    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin>>a>>b;
        if(a>b)
            swap(a,b);

        arr[i] = {a,b};
        if(!m.contains({a,b}))
        {
            m.insert({a,b}, 1);
        }
        else
        {
            // cout<<a<<" "<<b<<" = "<<m[{a,b}]<<"\n";
            int val = m[{a, b}];
            m.update({a, b}, (val+1));
            // cout<<a<<" "<<b<<" = "<<m[{a,b}]<<"\n\n";
        }
        
    }
    
    
    long long total = 0;
    // vector<pair<int,int>> k = m.keys();
    // for (int i = 0; i < k.size(); i++)
    // {
    //     cout<<k[i].first<<" "<<k[i].second<<" = "<<m[k[i]]<<"\n";
    // }

    for (int i = 0; i < n; i++)
    {
        int val = m[arr[i]];
        m.update(arr[i], (val-1));
        total += m[arr[i]];
    }
    
    cout<<total<<"\n";
}