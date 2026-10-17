#include<bits/stdc++.h>
using namespace std;

void bubbleSort(int *arr,int n){
    
    for(int i=0; i<n-1; i++){
        bool swapped=false;

        for(int j=0; j<n-i-1; j++){
            if(arr[j]>arr[j+1]){
                int temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
                swapped=true;
            }
        }
        if(swapped==false) break;
    }

    cout<<"Sorted Array: "<<endl;
    for(int i=0; i<n; i++){
        cout<<arr[i]<<" ";
    }
}

int main(){
    int n;

    cout<<"Enter Number of Element:"<<endl;
    cin>>n;

    int arr[n];

    cout<<"Enter Elements In Array: "<<endl;
    for(int i=0; i<n; i++){
        cin>>arr[i];
    }

    bubbleSort(arr,n);
}