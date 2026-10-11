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

class CircularQueue{
    public:
    Node* front;
    Node* rear;

    CircularQueue(){
        front=rear=NULL;
    }

    bool isEmpty(){
        return front==NULL;
    }

    void enqueue(int value){
        Node* newNode=new Node(value);

        if(front==NULL){
            front=rear=newNode;
            rear->next=front;
            return;
        }
        else{
            rear->next=newNode;
            rear=newNode;
            rear->next=front;
        }
    }

    void dequeue(){

        if(isEmpty()){
            cout<<"Queue is Empty!!"<<endl;
            return;
        }
        
        if(front==rear){
            delete front;
            front=rear=NULL;
        }
        else{
            Node* temp=front;
            front=front->next;
            rear->next=front;
            delete temp;
        }
    }

    int peek(){
        if(isEmpty()){
            cout<<"Queue Is Empty!!"<<endl;
            return -1;
        }
        return front->data;
    }

    void display(){
        
        if(isEmpty()){
            cout<<"Queue Is Empty!!"<<endl;
            return;
        }
        Node* temp=front;
        do{
            cout<<temp->data<<" ";
            temp=temp->next;
        }while(temp!=front);

        cout<<endl;
    }
};

int main() {
    CircularQueue q;

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);

    cout << "Circular Queue: ";
    q.display();

    cout << "Front: " << q.peek() << endl;

    q.dequeue();
    cout << "After Dequeue: ";
    q.display();

    q.enqueue(50);
    cout << "After Enqueue: ";
    q.display();
    
    return 0;
}