#include<bits/stdc++.h>
using namespace std;

class Node{
    public:
    int data;
    Node* next;

    Node(int value){
        data=value;
        next=nullptr;
    }
};

class LinkedList{
    public:
    Node *head;

    LinkedList(){
        head=NULL;
    }

    void insert(int value){
        Node* newNode= new Node(value);
        
        if(head==NULL){
            head=newNode;
            return;
        }

        newNode->next=head;
        head=newNode;

    }

    void display(){
        Node* temp=head;

        while(temp!=NULL){
            cout<<temp->data<<"->";
            temp=temp->next;
        }
        cout<<"NULL"<<endl;
    }
};

int main (){
    LinkedList list;
    list.insert(10);
    list.insert(20);
    list.insert(30);
    list.insert(40);

    list.display();

    
    return 0;
}