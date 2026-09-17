#include<bits/stdc++.h>
using namespace std;

class Node{
    public:

    int data;
    Node* next;

    Node(){
        data=0;
        next=nullptr;
    }
};

class LinkedList{
    public:
    Node* head;

    LinkedList(){
        head=nullptr;
    }
    
    void insert(int value){
        Node* newNode = new Node();
        newNode->data=value;
        newNode->next=NULL;

        if(head==NULL){
            head=newNode;
            return;
        }

        Node *temp = head;

        while(temp->next!=NULL){
            temp=temp->next;
        }

        temp->next=newNode;

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