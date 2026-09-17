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

    void deleteFromMiddle(int afterValue){
        if(head==NULL){
            cout<<"List Is Empty!!"<<endl;
            return;
        }
        Node* temp=head;
        while(temp!=NULL && temp->data!=afterValue){
            temp=temp->next;
        }
        if(temp==NULL){
            cout<<"After Value Not Found!!"<<endl;
            return;
        }
        else{
            if(temp->next==NULL){
                cout<<"No Node After This Value!!"<<endl;
                return;
            }
            else{
                Node* toDelete = temp->next;
                temp->next= toDelete->next;
                delete toDelete;
            }

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
    list.deleteFromMiddle(20);
    list.display();

    return 0;
}