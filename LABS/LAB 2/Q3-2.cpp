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

    Node* getMiddle(Node* head){
        Node* slow=head;
        Node* fast=head->next;

        while(fast!=NULL && fast->next!=NULL){
            slow=slow->next;
            fast=fast->next->next;
        }

        return slow;
    }

    Node* merge(Node* left, Node* right){
        Node dummy(0);
        Node* current=&dummy;

        while(left!=NULL && right!=NULL){
            if(left->data<=right->data){
                current->next=left;
                left=left->next;
            }

            else{
                current->next=right;
                right=right->next;
            }

            current=current->next;
        }

        if(left!=NULL){
            current->next=left; 
        }

        else{
            current->next=right;
        }

        return dummy.next;
    }

    Node* mergeSort(Node* head){
        
        if(head==NULL || head->next==NULL){
            return head;
        }

        Node* middle=getMiddle(head);
        Node* second=middle->next;
        middle->next=NULL;
        Node* left=mergeSort(head);
        Node* right=mergeSort(second);
        return merge(left,right);
    }

    void sort(){
        head=mergeSort(head);
        Node*temp=head;

        while(temp!=NULL){
            cout<<temp->data<<" ";
            temp=temp->next;
        }
    }

};

int main(){
    LinkedList list1;
    

    list1.insert(6);
    list1.insert(3);
    list1.insert(1);

    list1.sort();
    
    return 0;
}    