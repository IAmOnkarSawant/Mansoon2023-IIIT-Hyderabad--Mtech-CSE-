#include <iostream>
#include <vector>

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

        if (curr->key < k)
            curr->right = insertRec(curr->right, k, v);
        else
            curr->left = insertRec(curr->left, k, v);

        int l = height(curr->left);
        int r = height(curr->right);

        int bal = l - r;
        if (bal > 1)
        {
            if (curr->left->key < k)
            {
                curr->left = lRot(curr->left);
                return rRot(curr);
            }
            else
            {
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
        else if(curr->key < k)
            a = containsRec(curr->right, k);
        else
            a = containsRec(curr->left, k);

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
        else if(curr->key < k)
            a = updateRec(curr->right, k, val);
        else
            a = updateRec(curr->left, k, val);

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
        else if (curr->key < k)
            return valueRec(curr->right, k);
        else
            return valueRec(curr->left, k);
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
        else if (curr->key < k)
            curr->right = eraseRec(curr->right, k);
        else 
            curr->left = eraseRec(curr->left, k);

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

    Node<T1, T2> *lbn = NULL;
    pair<bool, T1> lbRec(Node<T1, T2> *curr, T1 key) 
    {
        if (!curr) 
        {
            if (lbn)
                return {true, lbn->key};
            return {false, T1()};
        }
        
        if (curr->key == key) 
        {
            lbn = curr;
            return {true, key};
        } 
        else if (curr->key < key) 
        {
            
            return lbRec(curr->right, key);
        } 
        else 
        {
            lbn = curr;
            return lbRec(curr->left, key);
        }
    }   

    Node<T1, T2> *ubn = NULL;
    pair<bool, T1> ubRec(Node<T1, T2> *curr, T1 key) 
    {
        if (!curr) 
        {
            if (ubn)
                return {true, ubn->key};
            return {false, T1()};
        }
        
        if (curr->key < key || curr->key == key) 
        {
            return ubRec(curr->right, key);
        } 
        else 
        {
            ubn = curr;
            auto result = ubRec(curr->left, key);
            if (result.first) {
                return result;
            } else {
                return {true, ubn->key};
            }
        }
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
        lbn = NULL;
        return lbRec(root, key);
    }

    pair<bool, T1> upper_bound(T1 key) 
    {
        ubn = NULL;
        return ubRec(root, key);
    }

    // void levelOrder()
    // {
    //     cout<<om_size<<"\n";
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
    //         cout << "\n";
    //     }
    //     cout << "\n";
    // }
};

int main()
{
    ordered_map<int, int> um;
    // um.insert(1, 10);
    // um.insert(2, 20);
    // um.insert(3, 30);
    // // um.levelOrder();
    // um.insert(4, 40);
    // // um.levelOrder();
    // um.insert(5, 50);
    // // um.levelOrder();
    // um.insert(6, 60);
    // // um.levelOrder();
    // um.insert(8, 70);
    // // um.levelOrder();
    // cout<<um.lower_bound(7).second<<"\n";
    // cout<<um.lower_bound(-1).second<<"\n";
    // cout<<um.lower_bound(8).second<<"\n";

    // cout<<um.upper_bound(7).second<<"\n";
    // cout<<um.upper_bound(6).second<<"\n";
    // cout<<um.upper_bound(8).second<<"\n";

    // vector<int> t = um.keys();
    // cout<<t.size();
    // for (int i = 0; i < t.size(); i++)
    // {
    //     cout<<t[i]<<" ";
    // }
    // cout<<"\n";
    
    // cout << um.contains(3) << "\n";
    // cout << um.contains(10) << "\n";
    // cout << um.contains(7) << "\n";
    // um.erase(2);
    // um.levelOrder();
    // um.erase(3);
    // um.levelOrder();
    // //um.clear();
    // um.levelOrder();

    // cout<<"erase\n";
    // um.erase(1);
    // um.levelOrder();
    // cout<<um[6]<<"\n";

    int ch;
    std::cin>>ch;
    int key;
    int value; 
    vector<int> t1;
    pair<bool, int>p;
    while(ch != 0)
    {
        switch (ch)
        {
        case 1:
            cout<<boolalpha<<um.empty()<<"\n";
            break;
        case 2:
            cout<<um.size()<<"\n";
            break;
        case 3:
            std::cin>>key;
            cout<<boolalpha<<um.contains(key)<<"\n";
            break;
        case 4:
            std::cin>>key;
            std::cin>>value;
            cout<<boolalpha<<um.insert(key, value)<<"\n";
            break;
        case 5:
            std::cin>>key;
            cout<<boolalpha<<um.erase(key)<<"\n";
            break;
        case 6:
            std::cin>>key;
            cout<<um[key]<<"\n";
            break;
        case 7:
            um.clear();
            break;
        case 8:
            t1 = um.keys();
            for (int i = 0; i < t1.size(); i++)
            {
                cout<<t1[i]<<"\n";
            }
            cout<<"\n";
            break;
        case 9:
            std::cin>>key;
            p = um.lower_bound(key);
            cout<<p.first<<"\n";
            cout<<p.second<<"\n";
            break;
        case 10:
            p = um.upper_bound(key);
            cout<<p.first<<"\n";
            cout<<p.second<<"\n";
            break;
        default:
            break;
        }
        std::cin>>ch;
    }
    // um.levelOrder();
}

