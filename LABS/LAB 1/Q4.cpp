#include<iostream>
using namespace std;

int binarySearch(int size,int arr[],int target){
    int left=0;
    int right=size-1;

    while(left<=right){
        int mid=(left+right)/2;
        if(arr[mid]==target) return mid;
        else if(arr[mid]<target){
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
int arr[]={-1,0,3,5,9,12};
int size=6;

cout<<"Enter Target Value: "<<endl;
cin>>target;

int result=binarySearch(size,arr,target);

if(result != -1){
    cout<<"Target found at Index: "<<result<<endl;
}
else {
    cout<<result<<endl;
}

    return 0;
}