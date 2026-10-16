#include<bits/stdc++.h>
using namespace std;

class DataStream{
    public:
    int value;
    int k;
    vector<int> nums;

    DataStream(int value,int k){
        this->value=value;
        this->k=k;
    }

    bool consecutive(int num){

        nums.push_back(num);

        if(nums.size()<k){
            return false;
        }

        for(int i=nums.size()-k; i<nums.size(); i++){
            if(nums[i]!=value){
                return false;
            }
        }

        return true;
    }
    
};

int main() {
    DataStream ds(4, 3);

    cout << boolalpha;
    cout << ds.consecutive(4) << endl; 
    cout << ds.consecutive(4) << endl; 
    cout << ds.consecutive(4) << endl; 
    cout << ds.consecutive(3) << endl; 

    return 0;
}