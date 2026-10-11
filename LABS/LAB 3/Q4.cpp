#include<bits/stdc++.h>
using namespace std;

class Node{
    public:
    int data;
    Node* next;
    Node* prev;

    Node(int value){
        data=value;
        next=prev=NULL;
    }
};

class DoublyLinkedList{
    public:
    Node* head;
    Node* tail;

    DoublyLinkedList(){
        head=tail=NULL;
    }

    void insert(int value){
        Node* newNode=new Node(value);
        if(head==NULL){
            head=tail=newNode;
            return;
        }
        else{
            tail->next=newNode;
            newNode->prev=tail;
            tail=newNode;
        }
    }

    void display(){
        Node* temp=head;
        while(temp!=NULL){
            cout<<temp->data<<" ";
            temp=temp->next;
        }
    }

    void concatenate(DoublyLinkedList& L,DoublyLinkedList& M){
        Node* temp=L.head;
        while(temp!=NULL){
            insert(temp->data);
            temp=temp->next;
        }

        temp=M.head;
        while(temp!=NULL){
            insert(temp->data);
            temp=temp->next;
        }
    }

        ~DoublyLinkedList() {
        Node* temp = head;

        while (temp != nullptr) {
            Node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
    }

    void sortDescending() {
        Node* current = head;

        while (current != nullptr) {
            Node* maxNode = current;
            Node* temp = current->next;

            while (temp != nullptr) {
                if (temp->data > maxNode->data) {
                    maxNode = temp;
                }

                temp = temp->next;
            }

            
            int value = current->data;
            current->data = maxNode->data;
            maxNode->data = value;

            current = current->next;
        }
    }


};

int main(){
    DoublyLinkedList L,M,N;

    for(int i=2; i<=10; i+=2){
        L.insert(i);
    }

    for(int i=1; i<=9; i+=2){
        M.insert(i);
    }

    cout<<"List L: "<<endl; 
    L.display();
    cout<<endl;

    cout<<"List M: "<<endl;
    M.display();
    cout<<endl;

    N.concatenate(L,M);
    cout<<"List N: "<<endl;
    N.display();
    cout<<endl;

    cout<<"Arrange In Descending Order"<<endl;
    N.sortDescending();
    N.display();

    return 0;
}