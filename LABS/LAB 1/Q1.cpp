#include<iostream>
using namespace std;

int main(){
    int row,col;
    int k=0;
    int l=0;

    cout<<"Enter Rows:"<<endl;
    cin>>row;

    cout<<"Enter Column:"<<endl;
    cin>>col;

    int arr[row][col];
    int oneDc[row * col];
    int oneDr[row * col];

    cout<<"Enter Elements:"<<endl;
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            cin>>arr[i][j];
        }
    }

    cout<<"Converting 2D Into 1D Column Major.."<<endl;
    for(int j=0; j<col; j++){
        for(int i=0; i<row; i++){
            oneDc[k]=arr[i][j];
            k++;
        }
    }

    cout<<"Converting 2D Into 1D Row Major.."<<endl;
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            oneDr[l]=arr[i][j];
            l++;
        }
    }

    cout<<"Displaying 1D Array In Column Major..."<<endl;
    for(int i=0; i<row*col; i++){
        cout<<oneDc[i]<<" ";
    }
    cout<<endl;

    cout<<"Displaying 1D Array In Row Major..."<<endl;
    for(int i=0; i<row*col; i++){
        cout<<oneDr[i]<<" ";
    }

    return 0;
}