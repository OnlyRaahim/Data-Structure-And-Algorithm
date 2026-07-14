//https://leetcode.com/problems/power-of-four/submissions/2067339832/

class Solution {
public:
    bool isPowerOfFour(int n) {
         if (n <= 0)
            return false;

        while (n % 4 == 0) {
            n = n / 4;
        }
        return n==1;
    }
};
