#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> dp;
    int safedp(int i, int j){
        if(j < 0) return dp[i][-j];
        else if(j > 1000) return 0;
        else return dp[i][j];
    }

    int findTargetSumWays(vector<int>& nums, int target) {
        this->dp.resize(nums.size() + 1, vector<int>(1000+1, 0));
        // selecting zero elements can lead to sum zero, 1 way to get it. hence; value = 1;
        dp[0][0] = 1;
        for(int i = 1; i <= nums.size(); i++){
            for(int j = 0; j <= 1000; j++){
                dp[i][j] = safedp(i-1,j-nums[i-1]) + safedp(i-1, j+nums[i-1]);
            }
        }
        return safedp(nums.size(), target);
    }
};