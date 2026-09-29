#include<bits/stdc++.h>
using namespace std;

class Node{
    public:

    int data;
    Node* next;
    Node* prev;

    Node(int value){
        data=value;
        next=prev=nullptr;
    }
};

class LinkedList{
    public:
    Node* head;
    Node* tail;

    LinkedList(){
        head=tail=nullptr;
    }
    
    void insert(int value){
        Node* newNode = new Node(value);
        
        if(head==NULL){
            head=tail=newNode;
            return;
        }
        else{
            newNode->prev=tail;
            tail->next=newNode;
            tail=newNode;
        }
    }

    void insertAtSpecificPos(int pos,int newValue){
        Node* newNode=new Node(newValue);

        if(head==NULL){
            cout<<"List Is Empty!! "<<endl;
        }

        if(pos==1){
            newNode->next=head;
            head->prev=newNode;
            head=newNode;
            return;
        }

        Node* temp=head;
        for(int i=1; i<pos-1 && temp!=NULL; i++){
            temp=temp->next;
        }

        if(temp==NULL){
            cout<<"Position Out Of Bound!!"<<endl;
            delete newNode;
            return;
        }
        newNode->next=temp->next;
        newNode->prev=temp;
        temp->next=newNode;
        temp->next->prev=newNode;
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

    list.insertAtSpecificPos(3,25);

    list.display();
    return 0;
}
