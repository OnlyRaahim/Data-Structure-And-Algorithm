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

class Stack{
    public:
    Node* top;

    Stack(){
        top=NULL;
    }

    void push(int value){
        Node* newNode=new Node(value);
        newNode->next=top;
        top=newNode;
    }

    void pop(){
        if (top==NULL){
            cout<<"Stack Underflow!!"<<endl;
            return;
        }

        Node* temp = top;
        top=top->next;
        delete temp;
    }

    int peek(){
        if(top==NULL){
            cout<<"Stack Is Empty!!"<<endl;
            return -1;
        }
        return top->data;
    }

    bool isEmpty(){
        return top==NULL;
    }

    void display(){
        Node* temp=top;

        while(temp!=NULL){
            cout<<temp->data<<" ";
            temp=temp->next;
        }
        cout<<endl;
    }

    ~Stack(){
        while(top!=NULL){
            pop();
        }
    }

};

int main(){
    Stack s;

    s.push(10);
    s.push(20);
    s.push(30);
    s.push(40);
    

    cout<<"Before Popping "<<endl;
    s.display();


    s.pop();
    cout<<"After popping"<<endl;
    s.display();


}