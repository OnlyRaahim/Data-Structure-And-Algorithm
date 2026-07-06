//https://leetcode.com/problems/reverse-string/submissions/2058443364/

class Solution {
public:
    void reverseString(vector<char>& s) {
        int start=0;
        int end=s.size()-1;

        while(start<end){
            swap(s[start],s[end]);
            start++;
            end--;
        }
        
    }
};