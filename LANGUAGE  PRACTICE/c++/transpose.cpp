#include<iostream>
#include<vector>
using namespace std;
int main()
{ 
    vector<vector<int>>mat({1,2,3},{4,5,6},{7,8,9});
    vector<int>temp;
     vector<vector<int>>result;
     for(int i=mat.size();i>=0;i--)
     {
        for(int j=0;j<3;j++)
        {
            temp.push_back(mat[i][j]);
        }
        result.push_back(temp);
     }
     for(auto it: result)
     {
        for(auto i:it)
        {
            cout<<i;
        }
     }

    return 0;
}