// this problem falls in 0/1 knapsack dp category
// https://leetcode.com/problems/partition-equal-subset-sum/

#include <bits/stdc++.h>
using namespace std;


// the intuition behind :
// as we want to know if it can be separated into two subsets of equal sum
// this problem can be reduced to 
// is there any subset of array whose sum is exact equal to half of totalsum
// then it can bee seen as a knapsack problem , where elements should add up to total target
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        // no need to check for empty array ( given non empty )
        // if sum of nums elements is odd then return false, 
        int sumOfNums = 0;
        for(int num: nums) sumOfNums+=num;
        if(sumOfNums %2 == 1) return false;

        int requiredSum = sumOfNums/2;        
        vector<vector<bool>> dp(nums.size()+1, vector<bool>(requiredSum + 1, false));
        
        // taking no elements to return sum 0, is possible
        dp[0][0] = true;

        for(int i =1; i <= nums.size(); i++){
            for(int j = 0 ; j <= requiredSum; j++){
                dp[i][j] = (j >= nums[i-1] and dp[i-1][j - nums[i-1]]) or dp[i-1][j];
            }
        }

        return dp[nums.size()][requiredSum];
    }
};



int main(){
    Solution* sol = new Solution();
    vector<int> nums = {1,5,11,6};
    cout<<"sup mf"<<endl;
    bool ans = sol->canPartition(nums);
    cout << ans <<endl;
}

