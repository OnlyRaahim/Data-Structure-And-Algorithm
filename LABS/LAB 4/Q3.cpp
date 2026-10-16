
#include <bits/stdc++.h>
using namespace std;

void solve(vector<int>& nums, int index) {
    if (index == nums.size()) {
        for (int x : nums) {
            cout << x << " ";
        }
        cout << endl;
        return;
    }

    for (int i = index; i < nums.size(); i++) {
        swap(nums[index], nums[i]);

        solve(nums, index + 1);

        swap(nums[index], nums[i]);
    }
}

int main() {
    vector<int> nums = {1, 2, 3};

    solve(nums, 0);

    return 0;
}
