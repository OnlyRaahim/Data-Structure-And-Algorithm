#include<bits/stdc++.h>
using namespace std;

class ProductOfNumber{
    private:
    vector<int> nums;

    public:
    ProductOfNumber(){}

    void addnum(int num){
        nums.push_back(num);
    }

    int getProduct(int k){
        int product=1;

        for(int i=nums.size()-k; i<nums.size(); i++){
            product*=nums[i];
        }
        return product;
    }
};

int main(){
    ProductOfNumber p;
    p.addnum(1);
    p.addnum(2);
    p.addnum(3);
    p.addnum(4);

    cout<<p.getProduct(2)<<endl;
    cout<<p.getProduct(3)<<endl;
    cout<<p.getProduct(4)<<endl;

    return 0;
}