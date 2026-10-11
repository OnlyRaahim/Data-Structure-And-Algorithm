#include<bits/stdc++.h>
using namespace std;

class Node{
    public:
    int data;
    Node* next;
    Node* prev;

    Node(int value){
        data=value;
        next=prev=NULL;
    }
};

class Deque{
    public:
    Node* head;
    Node* tail;

    Deque(){
        head=tail=NULL;
    }

    void insertFront(int value){
        Node* newNode=new Node(value);
        if(head==NULL){
            head=tail=newNode;
        }
        else{
            newNode->next=head;
            head->prev=newNode;
            head=newNode;
        }
    }

    void insertRear(int value){
        Node* newNode= new Node(value);
        if(tail==NULL){
            head=tail=newNode;
            return;
        }
        else{
            tail->next=newNode;
            newNode->prev=tail;
            tail=newNode;
        }
    }

    void deleteFront(){
        if(head==NULL){
            cout<<"Deque is Empty!!"<<endl;
            return;
        }
        Node*temp=head;
        if(head==tail){
            head=tail=NULL;
            return;
        }
        else{
            head=head->next;
            head->prev=NULL;
        }
        delete temp;
    }

    void deleteRear(){
        if(tail==NULL){
            cout<<"Deque is Empty!!"<<endl;
            return;
        }
        Node* temp=tail;
        if(head==tail){
            head=tail=NULL;
            return;
        }
        else{
            tail=tail->prev;
            tail->next=NULL;
        }

        delete temp;
    }

    void display(){
        if(head==NULL){
            cout<<"Deque is Empty!!"<<endl;
            return;
        }
        Node*temp=head;
        cout<<"Front->";
        while(temp!=NULL){
            cout<<temp->data<<"<->";
            temp=temp->next;
        }
        cout<<"NULL\n";
    }

    ~Deque(){
        while(head!=NULL){
            Node*temp=head;
            head=head->next;
            delete temp;
        }
        tail=NULL;
    }
};

int main() {
    Deque dq;

    dq.insertFront(20);
    dq.insertFront(10);
    dq.insertRear(30);
    dq.insertRear(40);

    dq.display();

    dq.deleteFront();
    dq.display();

    dq.deleteRear();
    dq.display();

    return 0;
}