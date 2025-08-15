#include<iostream>
#include<vector>
using namespace std;

int main()
{
    vector<vector<int>> v;
    int n;

    cout << "Enter number of vectors: ";
    cin >> n;

    for(int i = 0; i < n; i++)
    {
        cout << "Enter elements for vector " << i << " (end with -1): ";
        vector<int> temp; // Temporary vector for each row

        int d;
        while (true) {
            cin >> d;
            if (d == -1) break;
            temp.push_back(d);
        }

        v.push_back(temp); // Add the filled row to the main vector
    }

    // Printing the 2D vector
    cout << "\n2D Vector contents:\n";
    for(int i = 0; i < v.size(); i++)
    {
        for(int j = 0; j < v[i].size(); j++)
        {
            cout << v[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
