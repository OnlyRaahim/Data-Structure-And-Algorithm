// https://leetcode.com/problems/power-of-two/submissions/2067319680/

class Solution {
public:
    bool isPowerOfTwo(int n) {
       return n > 0 &&(n &(n-1))==0; 
        
    }
};