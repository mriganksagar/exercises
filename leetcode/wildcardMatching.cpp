//https://leetcode.com/problems/wildcard-matching/
// this question is very similar to the regular pattern matching of the leetcode

#include<vector>
#include<string>
using namespace std;
class Solution {
public:
    bool isMatch(const string& s, const string& p, int si, int pi, vector<vector<int>>& dp){
        if(dp[si][pi] != -1) return dp[si][pi];
        if(pi == p.size()){
            if(si == s.size()) return 1;
            else return 0;
        }
        if(si <s.size() and (s[si] == p[pi] or p[pi] == '?') ){
            dp[si][pi] = isMatch(s, p, si+1, pi+1, dp);
        }
        else if(p[pi] == '*'){
            if(si < s.size()) dp[si][pi] = isMatch(s, p, si+1, pi, dp);
            if(dp[si][pi]!=1) dp[si][pi] = isMatch(s, p, si, pi+1, dp);
        }
        else dp[si][pi] = 0;
        return dp[si][pi];
    }   

    bool isMatch(string s, string p) {
        vector<vector<int>> dp(s.size()+1, vector<int>(p.size()+1, -1));
        return isMatch(s, p, 0, 0, dp);
    }
};