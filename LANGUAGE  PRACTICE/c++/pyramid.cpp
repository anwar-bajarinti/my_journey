#include<iostream>
#include<string>
using namespace std;
int main()
{
    int pos=0;
    string str;
    cout<<"enter a string";
getline(cin,str);
for(char c:str)
{
    int space=str.length()-pos+1;
    while(space>0)
    {
        cout<<" ";
        space--;
    }
    for(int i=0;i<pos;i++)
    {
        cout<<str[i];
    }
    cout<<c;
    for(int j=pos-1;j>=0;j--)
    {
        cout<<str[j];
    }
    cout<<endl;
    pos++;
}
    return 0;
}