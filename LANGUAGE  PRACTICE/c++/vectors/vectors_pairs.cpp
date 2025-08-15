#include<iostream>
#include<vector>
using namespace std;

int main()
{
    vector<pair<int, string>> temp;

    // Hardcoded pair
    temp.push_back(make_pair(1, "anwar"));
    cout << temp[0].first << " ";
    cout << temp[0].second << endl;

    // Input a new pair from the user
    int id;
    string name;

    cout << "Enter id and name: ";
    cin >> id >> name;

    // Add user input to the vector
    temp.push_back(make_pair(id, name));

    // Display the newly added pair
    cout << "You entered: " << temp[1].first << " " << temp[1].second << endl;

    return 0;
}
