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
};

Node *mergeList(LinkedList &list1,LinkedList&list2){
    Node* p1=list1.head;
    Node* p2=list2.head;

    Node dummy;
    Node* current=&dummy;

    while(p1!=nullptr && p2!=nullptr){
        
        if(p1->data<=p2->data){
            current->next=p1;
            p1=p1->next;
        }

        else{
            current->next=p2;
            p2=p2->next;
        }

        current=current->next;
    }

    if(p1!=nullptr){
        current->next=p1;
    }
    else{
        current->next=p2;
    }

    return dummy.next;
}

int main(){
    LinkedList list1;
    LinkedList list2;

    list1.insert(1);
    list1.insert(2);
    list1.insert(4);

    list2.insert(1);
    list2.insert(3);
    list2.insert(4);

    Node* temp=mergeList(list1,list2);

    while(temp!=NULL){
        cout<<temp->data<<" ";
        temp=temp->next;
    }

    return 0;
}