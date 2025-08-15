#include<iostream>
using namespace std;
int main()
{
    int n;
    cout<<"enter n";
    cin>>n;
    int row=1;
    while(row<=n)
    {
        int space=row-1;
        while(space)
        {
            cout<<" ";
            space--;
        }
        int p=n-row+1;
        int c=row;
        while(p)
        {
            cout<<c++;
            p--;
       }
       cout<<endl;
       row++;
    }
}