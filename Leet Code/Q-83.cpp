//https://leetcode.com/problems/remove-duplicates-from-sorted-list/submissions/2132136653/

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* current = head;

        while(current!=NULL && current->next!=NULL){
            if(current->val==current->next->val){
                current->next=current->next->next;
            }
            else{
            current=current->next;
            }
        }
        return head;
    }
};