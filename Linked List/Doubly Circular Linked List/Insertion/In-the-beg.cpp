#include<bits/stdc++.h>
using namespace std;

class Node{
    public:
    int data;
    Node* next;
    Node* prev;

    Node(int value){
        data=value;
        next=NULL;
        prev=NULL;
    }
};

class DoublyCircularList{
    public:
    Node* head;
    Node* tail;

    DoublyCircularList(){
        head=tail=NULL;
    }

    void insert(int value){
        Node* newNode= new Node(value);
        
        if(head==NULL){
            head=tail=newNode;
            return;
        }
        else{
            newNode->next=head;
            newNode->prev=tail;
            head->prev=newNode;
            tail->next=newNode;
            head=newNode;
        }
    }

    void display(){
        Node*temp=head;

        do{
            cout<<temp->data<<" ";
            temp=temp->next;
        }while(temp!=head);
    }
};

int main(){
    DoublyCircularList list;

    list.insert(10);
    list.insert(20);
    list.insert(30);
    list.insert(40);
    list.display();

    return 0;
}
