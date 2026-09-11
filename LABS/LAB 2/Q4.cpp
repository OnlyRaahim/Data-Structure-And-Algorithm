#include<bits/stdc++.h>
using namespace std;

class Node{
    public:
    int data;
    Node* next;

    Node(int value){
        data=value;
        next=NULL;
    }
};

class LinkedList{
public:
Node* head;
Node* tail;

LinkedList(){
    head=NULL;
    tail=NULL;
}
void insert(int value){
    Node *newNode=new Node(value);

    if(head==NULL){
        head=newNode;
        tail=newNode;
    }
    else{
        tail->next=newNode;
        tail=newNode;
    }
}

bool isPalindrome(){
    int arr[100];
    int n=0;

    Node* temp=head;
    while(temp!=NULL){
        arr[n]=temp->data;
        n++;
        temp=temp->next;
    }

    int left=0;
    int right=n-1;

    while(left < right){
        if(arr[left]!=arr[right]){
            return false;
        }
        left++;
        right--;
    }
    return true;
}

};

int main(){
    LinkedList list;
    list.insert(1);
    list.insert(4);
    list.insert(5);
    list.insert(4);
    list.insert(1);

    if(list.isPalindrome()){
        cout<<"List is Palindrome"<<endl;
    }
    else{
        cout<<"List is Not Palindrome"<<endl;
    }
    return 0;
}
