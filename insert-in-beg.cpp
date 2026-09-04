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
    Node *head;

    LinkedList(){
        head=NULL;
    }

    void insert(int value){
        Node* newNode= new Node();
        newNode->data=value;
        newNode->next=NULL;

        if(head==NULL){
            head=newNode;
            return;
        }

        newNode->next=head;
        head=newNode;

    }
};

int main (){
    LinkedList list;
    list.insert(10);
    list.insert(20);
    list.insert(30);
    list.insert(40);

    Node* temp=list.head;

    while(temp!=NULL){
        cout<<temp->data<<"->";
        temp=temp->next;
    }
    return 0;
}