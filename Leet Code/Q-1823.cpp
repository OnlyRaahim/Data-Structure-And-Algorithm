//https://leetcode.com/problems/find-the-winner-of-the-circular-game/submissions/2171621862/

class Solution {
public:
    int findTheWinner(int n, int k) {
        if (n == 1) {
            return 1;
        }

        return (findTheWinner(n - 1, k) + k - 1) % n + 1;
    }
};