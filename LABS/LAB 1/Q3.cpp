#include<bits/stdc++.h>
using namespace std;

class MedianFinder{
private:
vector<int> arr;

public:
MedianFinder(){
}

void addNum(int num){
    arr.push_back(num);
    sort(arr.begin(),arr.end());
}

double findMedian(){
    int n=arr.size();

    if(n % 2 == 1){
        return arr[n/2];
    }

    else{
        return (arr[n/2-1] + arr[n/2])/2.0;
    }
}
};

int main(){
    MedianFinder m1;
    m1.addNum(1);
    m1.addNum(2);

    cout<<"Median Is: "<<m1.findMedian()<<endl;

    return 0;
}