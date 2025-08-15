#include<iostream>
#include<math.h>
using namespace std;
int main()
{
    int n;
    cout<<"ennter a==";
    cin>>n;
    int i=0;
    int binary=0;
    while(n!=0)
    {
        int bit=n&1;
        binary=(bit*pow(10,i))+binary;
        i++;
        n=n>>1;

    }
    cout<<"result ...."<<binary<<endl;
    return 0;
}