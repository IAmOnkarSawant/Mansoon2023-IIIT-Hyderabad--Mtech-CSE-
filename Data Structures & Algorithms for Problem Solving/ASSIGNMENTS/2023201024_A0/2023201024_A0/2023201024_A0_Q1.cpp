#include <iostream>
using namespace std;

int main() {
    
    int t;
    cin>>t;
    
    while(t--)
    {
        string word1, word2;
        cin>>word1>>word2;  
        
        int n = word1.size();
        int m = word2.size();
        
        int word1_frequency[26] = {};       
        int word2_frequency[26] = {};       
        
        for(int i = 0; i < n; i++)
        {
            int index = (int)(word1[i] - 'a');
            word1_frequency[index]++;
        }
        
        for(int i = 0; i < m; i++)
        {
            int index = (int)(word2[i] - 'a');
            word2_frequency[index]++;
        }
        
        // assure 2 strings are angrams
        bool is_anagram = 1;
        
        for(int i = 0; i < 26; i++)
        {
            if(word1_frequency[i] != word2_frequency[i])
            {
                is_anagram = 0;
            }
        }
        
        if(is_anagram)
        {
            cout<<"YES\n";
        }
        else
        {
            cout<<"NO\n";
        }
    }
}
