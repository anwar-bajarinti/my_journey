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
        int space=n-row;
        while(space)
        {
            cout<<" ";
            space--;
        }
        int star=row;
        while(star)
        {
            cout<<"*";
            star--;
        }
        cout<<endl;
        row++;
    }
    return 0;
}