//https://leetcode.com/problems/binary-search/submissions/2123876603/

class Solution {
public:
    int search(vector<int>& nums, int target) {
        
        int size=nums.size();
        int left=0;
        int right=size-1;

        while(left<=right){
            int mid=(left+right)/2;
            if(nums[mid]==target) return mid;
            else if(nums[mid]>target){
                right=mid-1;
            }
            else{
                left=mid+1;
            }
        }

        return -1;
    }

};