#include<bits/stdc++.h>
using namespace std;

string process(string s){
    vector<char> st;
    for(int i=0; i<s.length(); i++){
        if(s[i]=='#'){
            if(!st.empty()){
                st.pop_back();
            }
        }
        else{
            st.push_back(s[i]);
        }
    }
    string result="";

    for(int i=0; i<st.size(); i++){
        result+=st[i];
    }
    return result;
    
}

int main(){
    string s,t;

    cout<<"Enter First String: "<<endl;
    cin>>s;
    
    cout<<"Enter Second String: "<<endl;
    cin>>t;
    
    string a=process(s);
    string b=process(t);

    cout<<"First String After Backspace: "<<a<<endl;
    cout<<"Second String After Backspace: "<<b<<endl;

    if(a==b){
        cout<<"Both Strings are Equal "<<endl;
    }
    else{
       cout<<"Both Strings are not Equal "<<endl; 
    }

    return 0;   
}