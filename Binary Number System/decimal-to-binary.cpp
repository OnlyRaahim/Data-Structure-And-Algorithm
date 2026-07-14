#include<iostream>
using namespace std;

int decimal_to_binary(int decimalNum){
    int ans=0,pow=1,rem;

    while(decimalNum>0){
        rem=decimalNum%2;
        decimalNum/=2;
        ans+=(rem*pow);
        pow*=10;
    }

    return ans;
}

int main(){
   
    int decimalNum=50;
    cout<<decimal_to_binary(decimalNum)<<endl;
    
    return 0;
}