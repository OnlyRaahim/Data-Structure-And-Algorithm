#include<iostream>
using namespace std;

int main(){
    int students,subjects;

    cout<<"Enter Number Of Students:"<<endl;
    cin>>students;

    cout<<"Enter Number Of Subjects:"<<endl;
    cin>>subjects;

    string names[students];
    double grades[students][subjects];

    for(int i=0; i<students; i++){
        cout<<"\nEnter Name Of Student "<<i+1<<":"<<endl;
        cin>>names[i];
        cout<<endl;

        cout<<"Enter Grades Of "<<names[i]<<":"<<endl;
        cout<<"Enter -1 If "<<names[i]<<" Has Not Taken The Subject!! "<<endl;
        cout<<endl;

        for(int j=0; j<subjects; j++){
            cout<<"Enter Grades Of Subject "<<j+1<<":"<<endl;
            cin>>grades[i][j];
        }
    }

    for(int i=0; i<students; i++){
        double total=0;
        int count=0;

        for(int j=0; j<subjects; j++){
            if(grades[i][j] != -1){
                total+=grades[i][j];
                count++;
            }
        }

        double gpa=total/count;
        cout<<endl;
        cout<<names[i]<<" GPA is: "<<gpa<<endl;
    }

}