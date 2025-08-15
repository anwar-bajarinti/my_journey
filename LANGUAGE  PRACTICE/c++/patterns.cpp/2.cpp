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
        int space=row;
        while(space)
        {
            cout<<" ";
            space--;
        }
        int star=n-row;
        while(star)
        {
            cout<<"*";
            star--;
        }
        cout<<endl;
        row++;
    }
}