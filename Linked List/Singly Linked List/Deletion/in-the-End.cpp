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
    Node* tail;

    LinkedList(){
        head=NULL;
        tail=NULL;
    }

    void insert(int value){
        Node* newNode= new Node(value);
        
        if(head==NULL){
            head=tail=newNode;
            return;
        }

        newNode->next=tail;
        tail=newNode;

    }

    void deleteFromEnd(){
        
        if(head==NULL){
            cout<<"List Is Empty!! "<<endl;
            return;
        }
        if(head==tail){
            delete head;
            head=tail=NULL;
            return;
        }
        Node* temp=head;

        while(temp->next!=tail){
            temp=temp->next;
        }
        delete tail;
        tail=temp;
        tail->next=NULL;
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
    list.deleteFromEnd();
    list.display();

    
    return 0;
}