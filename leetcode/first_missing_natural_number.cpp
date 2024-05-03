#include<vector>
using namespace std;
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        for(int i = 0; i < nums.size();i++){
            while(nums[i] != i+1 and nums[i]>0 and nums[i]<=nums.size()){
                if(nums[nums[i]-1] == nums[i]) break;
                int x = nums[nums[i]-1];
                nums[nums[i]-1] = nums[i];
                nums[i] = x;
            }
        }
        for(int i = 0; i < nums.size(); i++){
            if(nums[i] != i+1) return i+1;
        }
        return nums.size()+1;
    }
};

// it was tricky to not use space at all and manipulate the array given