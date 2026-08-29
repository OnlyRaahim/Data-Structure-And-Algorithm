//using vector

#include<iostream>
#include<vector>
using namespace std;

int binarySearch(vector<int>&nums,int target){
    int left=0;
    int right=nums.size()-1;

    while(left<=right){
        int mid=(left+right)/2;
        if(nums[mid]==target) return mid;
        else if(nums[mid]<target){
            left=mid+1;
        }
        else{
            right=mid-1;
        }
    }

    return -1;
}

int main(){
int target;
vector<int> nums = {-1,0,3,5,9,12};


cout<<"Enter Target Value: "<<endl;
cin>>target;

int result=binarySearch(nums,target);

if(result != -1){
    cout<<"Target found at Index: "<<result<<endl;
}
else {
    cout<<result<<endl;
}
    return 0;
}