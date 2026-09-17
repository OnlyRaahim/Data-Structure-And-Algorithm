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

    void deleteAtSpecificPos(int pos){
        if(head==NULL){
            cout<<"List Is Empty!!"<<endl;
            return;
        }
        if(pos<=0){
            cout<<"Invalid Position!!"<<endl;
            return;
        }
        if(pos==1){
            Node* temp=head;
            head=head->next;
            delete temp;
            return;
        }
        Node* temp=head;
        for(int i=1;i<pos-1 && temp!=NULL; i++){
            temp=temp->next;
        }
        if(temp==NULL || temp->next==NULL){
            cout<<"Position Out Of Bound!!"<<endl;
            return;
        }
        else{
            Node* toDelete=temp->next;
            temp->next=toDelete->next;
            delete toDelete;           
        }
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

    list.deleteAtSpecificPos(3);
    list.display();

    return 0;
}