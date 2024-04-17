#include <stack>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:

    bool isOperator(string s){
        string tokens[4] = {"*", "/","-", "+" };
        for(int i = 0; i < 4; i++){
            if(s == tokens[i]) return true;
        }
        return false;
    }
    void evaluate (stack<int>& st, string op){
        int n1 = st.top();
        st.pop();
        int n2 = st.top();
        st.pop();
        if(op == "*") st.push(n1*n2);
        else if(op == "/") st.push(n2/n1);
        else if(op == "+") st.push(n1+n2);
        else if (op == "-") st.push(n2-n1);
    }

    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        for(auto token: tokens){
            if(isOperator(token)){
                evaluate(st, token);
            }
            else st.push(stoi(token));
        }
        // for a valid expression there would be only a single element in the stack
        if(st.size() == 1) return st.top();
        return 0;
    }
};