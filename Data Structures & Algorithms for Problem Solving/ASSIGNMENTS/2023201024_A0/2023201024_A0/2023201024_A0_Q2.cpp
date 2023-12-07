#include <iostream>
using namespace std;

int main() {
    
    // taking all inputs
    int n, s, j;
    cin>>n>>s>>j;
    
    int a[n];
    int jumps[j];
    
    for(int i = 0; i < n; i++)
    {
        cin>>a[i];
    }
    
    for(int i = 0; i < j; i++)
    {
        cin>>jumps[i];
    }
    
    // start jumping in the array
    
    //initial position
    long long index = s;
    cout<<a[index]<<" ";

    for(int i = 0; i < j; i++)
    {
        index = index + jumps[i];
        cout<<a[ (index % n) ]<<" ";
    }
    cout<<"\n";
    
    return 0;
}
