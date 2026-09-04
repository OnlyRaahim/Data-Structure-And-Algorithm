// https://leetcode.com/problems/minimum-operations-to-exceed-threshold-value-i/submissions/2128773052/

class Solution {
public:
    int minOperations vector<int>& nums, int k) {
        int count=0;
        

        for(int num: nums){
            if(num<k){
                count++;
            }

        }
    
        return count;
    }
};