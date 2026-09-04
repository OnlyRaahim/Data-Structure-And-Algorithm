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

        if(value==25){
            Node *temp=head;

            while(temp != NULL && temp->data != 20){
                temp=temp->next;
            }

            if(temp==NULL){
                return;
            }

            newNode->next=temp->next;
            temp->next=newNode;
            return;
        }

        Node *temp = head;

        while(temp->next!=NULL){
            temp=temp->next;
        }

        temp->next=newNode;
    }
};

int main (){
    LinkedList list;
    list.insert(10);
    list.insert(20);
    list.insert(30);
    list.insert(40);
    list.insert(25);

    Node* temp=list.head;

    while(temp!=NULL){
        cout<<temp->data<<"->";
        temp=temp->next;
    }
    return 0;
}