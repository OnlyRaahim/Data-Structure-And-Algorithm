#include<bits/stdc++.h>
using namespace std;

class Node{
    public:
    int data;
    Node* next;

    Node(int value){
        data=value;
        next=NULL;
    }
};

class Queue{
    public:
    Node* front;
    Node* rear;

    Queue(){
        front=NULL;
        rear=NULL;
    }

    void enqueue(int value){
        Node* newNode=new Node(value);

        if(front==NULL){
            front=newNode;
            rear=newNode;
            return;
        }
        else{
            rear->next=newNode;
            rear=newNode;
        }
    }

    void dequeue(){
        if(front==NULL){
            cout<<"Queue Underflow!!"<<endl;
            return;
        }
        Node* temp=front;
        front=front->next;

        if(front==NULL){
            rear=NULL;
        }
        delete temp;
    }

    int peek(){
        if(front==NULL){
            cout<<"Queue Is Empty!!"<<endl;
            return -1;
        }
        return front->data;
    }

    bool isEmpty(){
        return front==NULL;
    }

    void display(){
        Node* temp=front;
        while(temp!=NULL){
            cout<<temp->data<<" ";
            temp=temp->next;
        }
        cout<<endl;
    }

    ~Queue(){
        while(front!=NULL){
            dequeue();
        }
    }
};

int main(){
    Queue q;
    
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);

    cout<<"Before Dequeue"<<endl;
    q.display();

    q.peek();
    q.dequeue();
    cout<<"After Dequeue"<<endl;
    q.display();

    return 0;
}