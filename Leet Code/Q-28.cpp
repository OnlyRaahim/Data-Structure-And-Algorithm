// https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/submissions/2124133409/

class Solution {
public:
    int strStr(string haystack, string needle) {
        int s1=haystack.size();
        int s2=needle.size();

        for(int i=0; i<=s1-s2; i++){
            for (int j=0; j<s2; j++){
                if(haystack[i+j] != needle[j]){
                    break;
                }

                if(j==s2-1) return i;
            }
        }
        return -1;
    }
}; 