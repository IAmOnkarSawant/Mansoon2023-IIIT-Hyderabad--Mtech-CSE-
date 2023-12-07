#include <iostream>
#include <vector>
using namespace std;

class Trie
{
    Trie *child[26];
    bool eos;

public:
    Trie()
    {
        eos = 0;
        for (int i = 0; i < 26; i++)
        {
            child[i] = NULL;
        }
    }

    void insert(string word)
    {
        int n = word.size();
        Trie *t = this;
        for (int i = 0; i < n; i++)
        {
            if (t->child[(int)word[i]-'a'] != NULL)
            {
                t = t->child[(int)word[i]-'a'];
            }
            else
            {
                Trie *obj = new Trie();
                t->child[(int)word[i]-'a'] = obj;
                t = t->child[(int)word[i]-'a'];
            }
        }
        t->eos = 1;
    }

    bool search(string word)
    {
        if (word == "")
            return 1;
        int n = word.size();
        Trie *t = this;
        for (int i = 0; i < n; i++)
        {
            if (t->child[(int)word[i]-'a'] != NULL)
            {
                t = t->child[(int)word[i]-'a'];
            }
            else
            {
                return 0;
            }
        }
        if (t->eos == 1)
        {
            return 1;
        }
        return 0;
    }

    void dfs(Trie *t, string s, vector<string> &result)
    {
        bool count = 0;
        for (int i = 0; i < 26; i++)
        {
            if (t->child[i] != NULL)
            {
                count = 1;
                break;
            }
        }

        if (t->eos == 1)
        {
            result.push_back(s);
            if (count == 0)
                return;
        }

        for (int i = 0; i < 26; i++)
        {
            if (t->child[i] != NULL)
            {
                string temp = s;
                temp.push_back((char)i+'a');
                dfs(t->child[i], temp, result);
            }
        }
    }

    vector<string> startsWith(string prefix)
    {
        int n = prefix.size();
        Trie *t = this;
        for (int i = 0; i < n; i++)
        {
            if (t->child[(int)prefix[i]-'a'] != NULL)
            {
                t = t->child[(int)prefix[i]-'a'];
            }
            else
            {
                return vector<string>();
            }
        }
        vector<string> result;
        dfs(t, prefix, result);
        return result;
    }

    int ld(string word1, string word2)
    {
        int m = word1.size();
        int n = word2.size();

        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for (int i = 0; i <= m; i++)
        {
            for (int j = 0; j <= n; j++)
            {
                if (i == 0)
                {
                    dp[i][j] = j;
                }
                else if (j == 0)
                {
                    dp[i][j] = i;
                }
                else if (word1[i - 1] == word2[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else
                {
                    dp[i][j] = 1 + min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1]));
                }
            }
        }

        return dp[m][n];
    }

    void autoHelp(Trie *node, string w1, string current, vector<string> &result)
    {
        if (node->eos && ld(w1, current) <= 3)
        {
            result.push_back(current);
        }

        if ((current.size() > (w1.size() + 3)))
        {
            return;
        }

        for (int i = 0; i < 26; i++)
        {
            if (node->child[i] != NULL)
            {
                string temp = current;
                temp.push_back((char)i+'a');
                autoHelp(node->child[i], w1, temp, result);
            }
        }
    }

    vector<string> autocorrect(string w1)
    {
        vector<string> result;
        autoHelp(this, w1, "", result);
        return result;
    }
};

int main()
{
    int n, q;
    cin >> n >> q;
    Trie *root = new Trie();
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        root->insert(s);
    }

    while (q--)
    {
        int a;
        string s;
        cin >> a >> s;
        if (a == 1)
        {
            cout << root->search(s) << "\n";
        }
        else if (a == 2)
        {
            vector<string> ans = root->startsWith(s);
            cout<<ans.size()<<"\n";
            for (const string &word : ans)
            {
                cout << word << "\n";
            }
        }
        else
        {
            vector<string> ans = root->autocorrect(s);
            cout << ans.size() << "\n";
            for (const string &word : ans)
            {
                cout << word << "\n";
            }
        }
    }

    delete root;

    return 0;
}
