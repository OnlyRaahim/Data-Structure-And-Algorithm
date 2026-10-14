#include<bits/stdc++.h>
using namespace std;

int main(){
    string s;
    stack<char> st;

    cout<<"Enter String: "<<endl;
    cin>>s;

    for(int i=0; i<s.length(); i++){
        st.push(s[i]);
    }

    bool isPalindrome=true;

    for(int i=0; i<s.length(); i++){
        if(s[i]!=st.top()){
            isPalindrome=false;
            break;
        }
        st.pop();
    }

    if(isPalindrome){
        cout<<"String is Palindrome "<<endl;
    }
    else{
        cout<<"String is not Palindrome "<<endl;
    }

    return 0;
}