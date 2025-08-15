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
        int firnum=n-row+1;
        int p1=1;
        while(firnum)
        {
            cout<<p1++;
            firnum--;
        }
        int star=(row-1)*2;
        while(star)
        {
            cout<<"*";
            star--;
        }
        int secnum=n-row+1;
        while(secnum)
        {
            cout<<secnum--;
        }
        cout<<endl;
        row++;
     }
    return 0;
}
