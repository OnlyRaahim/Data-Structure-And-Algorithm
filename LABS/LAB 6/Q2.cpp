#include<bits/stdc++.h>
using namespace std;

int main(){
    int arr[]= {1, 12, 5, 111, 200, 1000, 10};
    int n= 7;
    int k = 50;

    for(int i=1; i<n; i++){
        int key=arr[i];
        int j=i-1;

        while(j>=0 && arr[j]>key){
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=key;
    }

    int count=0;

    for(int i=0; i<n; i++){
        if(k>=arr[i]){
            k-=arr[i];
            count++;
        }
        else{
            break;
        }       
    }

    cout<<"Maximum Toys: "<<count<<endl;
    return 0;
}