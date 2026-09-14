//https://leetcode.com/problems/sort-list/submissions/2142040043/


class Solution {
public:

    ListNode* getMiddle(ListNode* head){
        ListNode* slow= head;
        ListNode* fast= head->next;

        while(fast!=NULL && fast->next!=NULL){
            slow=slow->next;
            fast=fast->next->next;
        }

        return slow;
    }

    ListNode* merge(ListNode* left, ListNode* right){
        ListNode dummy(0);
        ListNode* current=&dummy;

        while(left!=NULL && right!=NULL){
            if(left->val<=right->val){
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

    ListNode* sortList(ListNode* head) {
        if(head==NULL || head->next==NULL){
            return head;
        }

        ListNode* middle = getMiddle(head);
        ListNode* second = middle->next;
        middle->next=NULL;
        ListNode* left=sortList(head);
        ListNode* right = sortList(second);
        
        

        return merge(left,right);
        
    }
};