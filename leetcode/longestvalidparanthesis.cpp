#include<stack>
#include<string>
using namespace std;
class Solution {
public:
    int longestValidParentheses(string s) {
        int maxLength = 0;
        stack<int>st;
        st.push(-1);
        for(int i = 0; i < s.size(); i++){
            if(s[i] == ')' and st.top() != -1 and s[st.top()] == '('){
                st.pop();
                maxLength = max(maxLength, i-st.top());
            }
            else st.push(i);
        }
        return maxLength;
    }
};

// https://leetcode.com/problems/longest-valid-parentheses