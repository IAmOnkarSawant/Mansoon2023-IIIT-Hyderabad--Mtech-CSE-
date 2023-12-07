#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

template <typename T>
class SkipListNode
{
public:
    T value;
    SkipListNode **next;

    SkipListNode(T num, int level)
    {
        value = num;
        next = new SkipListNode *[level + 1];
        for (int i = 0; i < level + 1; i++)
            next[i] = nullptr;
    }
};

template <typename T>
class SkipList
{
    int max_level;
    int current_level;
    SkipListNode<T> *header;

public:
    SkipList(int max_levels)
    {
        max_level = max_levels;
        current_level = 0;
        header = new SkipListNode<T>(-1, max_level);
    }

    int getRandomLevel()
    {
        int level = 0;
        while (level < max_level && rand() % 2 == 0)
            level++;
        return level;
    }

    void insert(T value)
    {
        SkipListNode<T> *update[max_level + 1];
        SkipListNode<T> *current = header;

        for (int i = current_level; i >= 0; i--)
        {
            while (current->next[i] != nullptr && current->next[i]->value < value)
                current = current->next[i];

            update[i] = current;
        }

        int new_level = getRandomLevel();

        if (new_level > current_level)
        {
            for (int i = current_level + 1; i <= new_level; i++)
                update[i] = header;
            current_level = new_level;
        }

        SkipListNode<T> *new_node = new SkipListNode<T>(value, new_level);

        for (int i = 0; i <= new_level; i++)
        {
            new_node->next[i] = update[i]->next[i];
            update[i]->next[i] = new_node;
        }
    }


    void remove(T value)
    {
        SkipListNode<T> *update[max_level + 1];
        SkipListNode<T> *current = header;

        for (int i = current_level; i >= 0; i--)
        {
            while (current->next[i] != nullptr && current->next[i]->value < value)
                current = current->next[i];
            update[i] = current;
        }

        current = current->next[0];

        while (current != nullptr && current->value == value)
        {
            for (int i = 0; i <= current_level; i++)
            {
                if (update[i]->next[i] != current)
                    break;
                update[i]->next[i] = current->next[i];
            }
            SkipListNode<T> *temp = current;
            current = current->next[0];
            delete temp;
        }

        while (current_level > 0 && header->next[current_level] == nullptr)
            current_level--;
    }


    bool search(T value)
    {
        SkipListNode<T> *current = header;

        for (int i = current_level; i >= 0; i--)
        {
            while ((current->next[i] != nullptr) && (current->next[i]->value <= value))
            {
                if ((current->next[i]->value == value))
                    return 1;
                current = current->next[i];
            }
        }
        return 0;
    }

    void display()
    {
        // cout << "Skip List:" << endl;
        for (int i = current_level; i >= 0; i--)
        {
            SkipListNode<T> *current = header->next[i];
            cout << "Level " << i << ": ";
            while (current != nullptr)
            {
                cout << current->value << " ";
                current = current->next[i];
            }
            cout << endl;
        }
    }

    int count(T value)
    {
        SkipListNode<T> *current = header;
        int count = 0;

        while (current->next[0] != nullptr)
        {
            if (current->next[0]->value < value)
            {
                current = current->next[0];
            }
            else if (current->next[0]->value == value)
            {
                while (current->next[0] != nullptr && current->next[0]->value == value)
                {
                    count++;
                    current = current->next[0];
                }
                return count;
            }
            else
            {
                break;
            }
        }

        return count;
    }

    T lower_bound(T value)
    {
        SkipListNode<T> *current = header;
        T result = T(); 

        for (int i = current_level; i >= 0; i--)
        {
            while (current->next[i] != nullptr)
            {
                if (current->next[i]->value < value)
                {
                    current = current->next[i];
                }
                else if (current->next[i]->value >= value)
                {
                    result = current->next[i]->value;
                    break; 
                }
            }
        }

        return result;
    }

    T upper_bound(T value)
    {
        SkipListNode<T> *current = header;
        T result = T(); 

        for (int i = current_level; i >= 0; i--)
        {
            while (current->next[i] != nullptr)
            {
                if (current->next[i]->value <= value)
                {
                    current = current->next[i];
                }
                else if (current->next[i]->value > value)
                {
                    result = current->next[i]->value;
                    break; 
                }
            }
        }

        return result;
    }

    T closest_element(T value)
    {
        SkipListNode<T> *current = header;
        T closest = T(); 
        if(!header)
            return closest;
        while (current->next[0] != nullptr)
        {
            if (current->next[0]->value < value)
            {
                closest = current->next[0]->value;
                current = current->next[0];
            }
            else if (current->next[0]->value == value)
            {
                //return current->next[0]->value;
                while (current->next[0] != nullptr && current->next[0]->value == value)
                {
                    current = current->next[0];
                }

                if(current == nullptr)
                    continue;
                else
                {
                    int diff1 = abs(current->next[0]->value - value);
                    int diff2 = abs(closest - value);
                    closest = diff1 > diff2 ? closest : current->next[0]->value;
                }
            }
            else
            {
                break;
            }
        }
        return closest;
    }

    

};

int main()
{
    srand(time(0));
    
    int ch;
    int ele;

    SkipList<int> *sl = new SkipList<int>(3);

    while (1)
    {
        cin >> ch;

        switch (ch)
        {
        case 0:
            return 0;
        case 1:
            delete sl;
            sl = new SkipList<int>(3);
            break;
        case 2:
            cin >> ele;
            sl->insert(ele);
            break;
        case 3:
            cin >> ele;
            sl->remove(ele);
            break;
        case 4:
            cin >> ele;
            sl->search(ele);
            break;
        case 5:
            cin >> ele;
            sl->count(ele);
            break;
        case 6:
            cin >> ele;
            sl->lower_bound(ele);
            break;
        case 7:
            cin >> ele;
            sl->upper_bound(ele);
            break;
        case 8:
            cin >> ele;
            sl->closest_element(ele);
            break;
        default:
            break;
        }
    }

    return 0;
}
