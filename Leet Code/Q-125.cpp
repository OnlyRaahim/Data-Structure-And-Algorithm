//https://leetcode.com/problems/valid-palindrome/submissions/2172135350/


class Solution {
public:
    bool isPalindrome(string s) {
        stack<char> st;
        string clean = "";

        // Keep only letters and digits, convert to lowercase
        for (char c : s) {
            if (isalnum(c)) {
                clean += tolower(c);
            }
        }

        // Push cleaned characters into stack
        for (int i = 0; i < clean.length(); i++) {
            st.push(clean[i]);
        }

        // Compare with reverse order
        for (int i = 0; i < clean.length(); i++) {
            if (clean[i] != st.top()) {
                return false;
            }
            st.pop();
        }

        return true;
    }
};
