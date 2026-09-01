#include<bits/stdc++.h>
using namespace std;

bool binarySearch(vector<vector<int>>&matrix,int target){
int left=0,row=matrix.size(),col=matrix[0].size(),right=row*col-1;
while(left<=right){
    int mid = (left+right)/2;
    int r = mid / col;
    int c = mid % col;
    if(target==matrix[r][c]) return true;
    else if(target>matrix[r][c]){
        left= mid + 1;
    }
    else{
        right= mid - 1;
    }
}
return false;
}

int main(){
    int row,col,target;

    cout<<"Enter Row:"<<endl;
    cin>>row;

    cout<<"Enter Column:"<<endl;
    cin>>col;

    vector<vector<int>> arr(row, vector<int>(col));

    cout<<"Enter Elements In Array:"<<endl;
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            cin>>arr[i][j];
        }
    }

    cout<<"Enter Target Value:"<<endl;
    cin>>target;
    cout<<endl;

    cout<<binarySearch(arr,target)<<endl;

    return 0;
}