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
    Node* head;

    LinkedList(){
        head=nullptr;
    }
    
    void insert(int value){
        Node* newNode = new Node(value);
        
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

    void insertAtSpecificPos(int pos,int newValue){
        Node* newNode=new Node(newValue);

        if(head==NULL){
            cout<<"List Is Empty!! "<<endl;
        }

        if(pos==1){
            newNode->next=head;
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

    list.insertAtSpecificPos(6,25);
    list.display();

    return 0;
    
}
