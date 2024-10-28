// https://leetcode.com/problems/target-sum/
// few things to note
// due to the restraints on nums that sum(nums) <= 1000
// it was possible to compute this solution 
// because for a number ni we need target t + ni and t - ni , from previous table,
// for that target (t` lets say) from previous table we need again t` +- number(i-1) from again previous table
// which goes on forever
// but due to limitation that sum of nums < 1000
// we know that we can never get target > 1000 by any way of adding or subtracting numbers hence i can simply return zero 
// which i did in the safe dp ( really useful abstraction )

// another important note: 
// because if target is negative and we want number of ways to acheive that, we can do so by finding -ve of target (which will be positive number)


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