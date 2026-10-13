#include<bits/stdc++.h>
using namespace std;

class MyCircularDeque{
    public:
    vector<int> arr;
    int front;
    int rear;
    int count;
    int capacity;

    public:
    MyCircularDeque(int k){
        arr.resize(k);
        front=0;
        rear=-1;
        count=0;
        capacity=k;
    }

    bool insertFront(int value){
        if(isFull()){
            return false;
        }
        if(isEmpty()){
            front=rear=0;
        }
        else{
            front=(front-1 + capacity) % capacity;
        }

        arr[front]=value;
        count++;
        return true;
    }

    bool insertRear(int value){
        if(isFull()){
            return false;
        }
        if(isEmpty()){
            front=rear=0;
        }
        else{
            rear=(rear + 1) % capacity;
        }

        arr[rear]=value;
        count++;
        return true;
    }

    bool deleteFront(){

        if(isEmpty()){
            return false;
        }

        if(count==1){
            front=0;
            rear=-1;
        }
        else{
            front=(front + 1) % capacity;
        }
        count--;
        return true;
    }

    bool deleteRear(){

        if(isEmpty()){
            return false;
        }

        if(count==1){
            front=0;
            rear=-1;
        }
        else{
            rear=(rear-1 + capacity) % capacity;
        }
        count--;
        return true;
    }

    int getFront(){
        if(isEmpty()){
            return -1;
        }
        return arr[front];
    }

    int getRear(){
        if(isEmpty()){
            return -1;
        }
        return arr[rear];
    }
    
    bool isEmpty(){
        return count==0;
    }

    bool isFull(){
        return count==capacity;
    }
};

int main(){
    MyCircularDeque dq(5);

    cout<<dq.insertFront(10)<<endl;
    cout<<dq.insertRear(50)<<endl;
    cout<<dq.insertFront(20)<<endl;
    cout<<dq.insertRear(40)<<endl;
    cout<<dq.insertFront(30)<<endl;

    cout<<"Front: "<<dq.getFront()<<endl;
    cout<<"Rear: "<<dq.getRear()<<endl;
    
    
    cout<<"Circular Deque is Full: \n"<<dq.isFull()<<endl;
    cout<<"Circular Deque is Empty: \n"<<dq.isEmpty()<<endl;
    
    cout<<dq.insertFront(50)<<endl;
    cout<<dq.deleteFront()<<endl;

    
}