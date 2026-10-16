
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, k;
    cout << "Enter number of friends: ";
    cin >> n;

    cout << "Enter k: ";
    cin >> k;

    vector<int> v;

    for (int i = 1; i <= n; i++) {
        v.push_back(i);
    }

    int index = 0;

    while (v.size() > 1) {
        index = (index + k - 1) % v.size();

        cout << "Friend " << v[index] << " is eliminated." << endl;

        v.erase(v.begin() + index);
    }

    cout << "Winner is Friend " << v[0] << endl;

    return 0;
}
