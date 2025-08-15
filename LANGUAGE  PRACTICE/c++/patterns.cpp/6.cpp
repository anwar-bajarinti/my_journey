#include<iostream>
using namespace std;
int main()
{
    int n;
    cout<<"enter a n";
    cin>>n;
    int row=1;
    while(row<=n)
    {
        int space=n-row+1;
        while(space)
        {
            cout<<" ";
            space--;
        }
        int p=row;
        int count=1;
       while(p)
        {
            cout<<count++;
            p--;
        }
        int p2=row-1;
        int c2=row-1;
        while(p2)
        {
            cout<<c2--;
            p2--;
        }
        cout<<endl;
        row++;
    }
}