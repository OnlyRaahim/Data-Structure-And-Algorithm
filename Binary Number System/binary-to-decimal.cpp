#include<iostream>
using namespace std;

int binaryTodecimal(int binarynum){
    int ans=0,pow=1;
    
    while(binarynum > 0){
        int rem=binarynum%10;
        ans+=rem*pow;
        binarynum/=10;
        pow*=2;
    }

    return ans;
}

int main(){
    int n=101;
    
    cout<<binaryTodecimal(n)<<endl;

    return 0;
}