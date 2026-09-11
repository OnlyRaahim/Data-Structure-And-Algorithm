#include<bits/stdc++.h>
using namespace std;

class Node{
    public:
    int data;
    Node *next;

    Node(){
        data=0;
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
        Node *newNode= new Node();
        newNode->data=value;
        newNode->next=nullptr;

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

    void display(){
        Node* temp=head;
        while(temp!=NULL){
            cout<<temp->data<<" ";
            temp=temp->next;
        }
    }
};

void removeDuplicate(LinkedList& list){
    Node* current=list.head;

    while(current!=NULL && current->next!=NULL){
        if(current->data==current->next->data){
            current->next=current->next->next;
        }
        else{
        current=current->next;
        }
    }
    
}

int main(){
    LinkedList list;
    

    list.insert(1);
    list.insert(1);
    list.insert(1);
    list.insert(2);
    list.insert(2);
    list.insert(4);

    cout<<"Before Removing Duplicates!!"<<endl;
    list.display();

    removeDuplicate(list);
    cout<<"\nAfter Removing Duplicates!!"<<endl;
    list.display();
    
    return 0;
}