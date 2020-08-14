class Solution {
public:    
    bool isCharInStr(char c, string s) {
        size_t found = s.find(c);
        return found != string::npos;
    }
    
    int lengthOfLongestSubstring(string s) {
        size_t n = s.length();
        size_t len = 0;
        size_t i = 0;
        size_t j = 0;
        while (i < n && j < n) {
            // If character after (i, j) window is not in window,
            if (!isCharInStr(s[j], s.substr(i, j - i))) {
                j++;
                len = (j - i) > len ? (j - i) : len;
            } else {
                i++;
            }
        }
        
        return len;
    }
    
};