#include<iostream>
#include<vector>
using namespace std;
int main()
{
    vector<int>n={2,3,4,5};
    fill(n.begin(),n.end(),10);
    n.push_back(1);
    cout<<n.at(0)<<endl;
    vector<int>b(10,1);
    cout<<b[3];
    cout<<b.size();
    vector<int>k={5,3,7,9,12};
    for(int a:k)
    {
        cout<<a;
    }
return 0;
}