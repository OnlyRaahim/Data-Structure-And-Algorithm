#include<bits/stdc++.h>
using namespace std;

class Node{
    public:
    int data;
    Node *next;

    Node(int value){
        data=value;
        next=nullptr;
    }
};

class LinkedList{
    public:
    Node *head;

    LinkedList(){
        head=nullptr;
    }

    void insert(int value){
        Node *newNode= new Node(value);
        

        if(head==NULL){
            head=newNode;
            return;
        }

        Node* temp=head;
        while(temp->next!=NULL){
            temp=temp->next;
        }

        temp->next=newNode;
    }