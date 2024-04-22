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





// a very smart solution for this from leetcode by someone really smart
// the idea is that it backtracks only one level, and still works
// what is the proof behind it all
// well the idea is if there are more than one star * in the pattern
// consider this example  
// lets say there 
// s is { s0, s1, s2, s3}
// p is {p0, * , p1, * , p2 }
// and s0 s1 matches with p0 * p1
// but s0 s1 s2 also matches with p0 * p1
// then why is using the second cases redundant if we are able to get to the next wildcard *

// if we need to match s3 with * p2, and it does as well
// then we can also match s2 s3 with * p2

class Solution2 {
public:
    bool isMatch(string s, string p) {
        int si = 0;
        int pi = 0;
        int star_pi = -1;
        int star_si = -1;
        while (si < s.size()) {
            if (pi < p.size() && (p[pi] == '?' || p[pi] == s[si])) {
                ++si;
                ++pi;
            } else if (pi < p.size() && p[pi] == '*') {
                star_pi = pi++;  // '*' matches empty
                star_si = si;
            // no '*' was found or failed to match with the last '*'
            } else if (star_pi == -1) {
                return false;
            } else {
                pi = star_pi + 1; // backtrack
                si = ++star_si; // '*' match one more character
            }
        }

        // We have reached the end of s. In order to have a match, the rest of characters
        // in p must be all '*'.
        for (int i = pi; i < p.size(); ++i) {
            if (p[i] != '*') return false;
        }
        return true;
    }
};