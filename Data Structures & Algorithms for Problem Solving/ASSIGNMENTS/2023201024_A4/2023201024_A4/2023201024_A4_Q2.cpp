#include <iostream>
#include <string>

using namespace std;

class RopeNode
{
public:
    string data;
    int len;
    int height;
    RopeNode *left;
    RopeNode *right;

    RopeNode(string str)
    {
        data = str;
        len = str.length();
        height = 1;
        left = nullptr;
        right = nullptr;
    }
};

class Rope
{
    RopeNode *root;
    int chunkSize;

    int max(int a, int b)
    {
        if (a > b)
        {
            return a;
        }
        else
        {
            return b;
        }
    }

    int getBalanceFactor(RopeNode *node)
    {
        if (node == nullptr)
            return 0;
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        return leftHeight - rightHeight;
    }

    int getHeight(RopeNode *node)
    {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    void updateHeight(RopeNode *node)
    {
        if (node != nullptr)
        {
            int leftHeight = getHeight(node->left);
            int rightHeight = getHeight(node->right);
            node->height = 1 + max(leftHeight, rightHeight);
        }
    }

    RopeNode *rotateLeft(RopeNode *x)
    {
        RopeNode *y = x->right;
        x->right = y->left;
        y->left = x;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    RopeNode *rotateRight(RopeNode *y)
    {
        RopeNode *x = y->left;
        y->left = x->right;
        x->right = y;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    void clearRecursively(RopeNode *node)
    {
        if (node == nullptr)
        {
            return;
        }

        clearRecursively(node->left);
        clearRecursively(node->right);
        delete node;
    }

    string treeToString(const RopeNode *node) const
    {
        if (node == nullptr)
        {
            return "";
        }

        string left = treeToString(node->left);
        string right = treeToString(node->right);

        return left + node->data + right;
    }

    RopeNode *concatTrees(RopeNode *tree1, RopeNode *tree2)
    {
        if (tree1 == nullptr)
        {
            return tree2;
        }
        else if (tree2 == nullptr)
        {
            return tree1;
        }

        int balance = getHeight(tree1->left) - getHeight(tree2->right);

        if (balance > 1)
        {
            if (getHeight(tree1->left->right) > getHeight(tree1->left->left))
            {
                tree1->left = rotateLeft(tree1->left);
            }
            return rotateRight(tree1);
        }
        else if (balance < -1)
        {
            if (getHeight(tree2->right->left) > getHeight(tree2->right->right))
            {
                tree2->right = rotateRight(tree2->right);
            }
            return rotateLeft(tree2);
        }
        else
        {
            tree1->right = concatTrees(tree1->right, tree2);
            int leftHeight = getHeight(tree1->left);
            int rightHeight = getHeight(tree1->right);
            tree1->height = 1 + max(leftHeight, rightHeight);
            tree1->len = (tree1->left != nullptr ? tree1->left->len : 0) + (tree1->right != nullptr ? tree1->right->len : 0);
            return tree1;
        }
    }

    char getNodeCharAt(RopeNode *node, int index)
    {
        if (node == nullptr || index < 0 || index >= node->len)
        {
            return '\0';
        }

        int leftLen = (node->left != nullptr) ? node->left->len : 0;

        if (index < leftLen)
        {
            return getNodeCharAt(node->left, index);
        }
        else if (index < leftLen + node->data.length())
        {
            return node->data[index - leftLen];
        }
        else
        {
            return getNodeCharAt(node->right, index - leftLen - node->data.length());
        }
    }

    void splitNode(RopeNode *node, int index, RopeNode *&left, RopeNode *&right)
    {
        if (node == nullptr)
        {
            left = nullptr;
            right = nullptr;
            return;
        }

        int leftLen = (node->left != nullptr) ? node->left->len : 0;
        if (index <= leftLen)
        {
            splitNode(node->left, index, left, node->left);
            right = node;
        }
        else
        {
            splitNode(node->right, index - leftLen - 1, node->right, right);
            left = node;
        }
        updateHeight(node);
    }

public:
    Rope(string content = "", int chunkSize = 5)
    {
        this->chunkSize = chunkSize;
        if (content.empty())
        {
            root = nullptr;
        }
        else
        {
            root = buildRope(content, 0, content.size() - 1);
        }
    }

    ~Rope()
    {
        clearRecursively(root);
        root = nullptr;
    }

    RopeNode *buildRope(string content, int start, int end)
    {
        if (start > end)
        {
            return nullptr;
        }

        int len = end - start + 1;
        if (len < chunkSize)
        {
            return new RopeNode(content.substr(start, len));
        }

        int mid = start + chunkSize - 1;
        if (mid > end)
        {
            mid = end;
        }

        if (start > mid)
        {
            return buildRope(content, mid + 1, end);
        }
        else if (mid >= start && mid <= end)
        {
            string concatenatedStr = content.substr(start, len);
            return new RopeNode(concatenatedStr);
        }
        return nullptr;
    }

    bool empty()
    {
        return (root == nullptr);
    }

    int size()
    {
        if (root == nullptr)
        {
            return 0;
        }
        return root->len;
    }

    void clear()
    {
        clearRecursively(root);
        root = nullptr;
    }

    string to_string() const
    {
        return treeToString(root);
    }

    Rope *concat(Rope *r2)
    {
        Rope *result = new Rope();

        if (r2 != nullptr)
        {
            result->root = concatTrees(root, r2->root);
        }
        else
        {
            result->root = root;
        }

        return result;
    }

    char charAt(int index)
    {
        if (index < 0 || index >= size())
        {
            return '\0';
        }

        char result = getNodeCharAt(root, index);
        return result;
    }

    Rope *subrope(int first, int last)
    {
        if (first < 0 || first >= size() || last < 0 || last >= size() || first > last)
        {
            return new Rope();
        }

        Rope *result = new Rope();
        RopeNode *newRoot = nullptr;
        RopeNode *rightSubtree = nullptr;

        splitNode(root, first, root, newRoot);
        splitNode(newRoot, last - first + 1, newRoot, rightSubtree);
        result->root = rightSubtree;

        root = concatTrees(root, newRoot);

        return result;
    }

    Rope *push_back(string s)
    {
        Rope *newRope = new Rope(s);
        Rope *result = this->concat(newRope);
        delete newRope;
        return result;
    }
};

int main()
{
    Rope rope;
    while (true)
    {
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 0:
        {
            return 0;
        }

        case 1:
        {
            string content;
            cin.ignore();
            getline(cin, content);
            rope = Rope(content);
            break;
        }

        case 2:
        {
            cout << (rope.empty() ? "true" : "false") << endl;
            break;
        }
        case 3:
        {
            cout << rope.size() << endl;
            break;
        }

        case 4:
        {
            rope.clear();
            cout << endl;
            break;
        }
        case 5:
        {
            int index;
            string insertStr;
            cin >> index;
            cin.ignore();
            getline(cin, insertStr);
            break;
        }

        case 6:
        {
            int first, last;
            cin >> first >> last;
            break;
        }

        case 7:
        {
            int i;
            cin >> i;
            char c = rope.charAt(i);
            cout << c << endl;
            break;
        }

        case 8:
        {
            int start, end;
            cin >> start >> end;
            Rope *concated = rope.subrope(start, end);
            break;
        }

        case 9:
        {
            string cc;
            cin.ignore();
            getline(cin, cc);
            Rope *rcc = new Rope(cc);
            Rope *concated = rope.concat(rcc);
            break;
        }

        case 10:
        {
            string s;
            cin.ignore();
            getline(cin, s);
            rope = *rope.push_back(s);
            break;
        }

        case 11:
        {
            cout << rope.to_string() << endl;
            break;
        }

        case 12:
        {
            int si;
            cin >> si;
            break;
        }

        default:
            cout << "Invalid choice. Please select a valid option." << endl;
        }
    }
}
