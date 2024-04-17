#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    // find maximum subarray sum, a sliding windows problem but an easy one
    // where i can just add element into the sum greedily and update the max sum,
    // however if the sum becomes negative i reset the sum = 0, and start same from next index
    int maxSubArraySum(vector<int> &nums)
    {
        int maxx = INT_MIN;
        int summ = 0;
        int j = 0;
        for (; j < nums.size(); j++)
        {
            summ += nums[j];
            maxx = max(maxx, summ);
            if (summ < 0)
            {
                summ = 0;
            }
        }
        return maxx;
    }

    // find maximum subarray product  , a sliding windows problem
    int maxProductSubarray(vector<int> &nums)
    {
        int i = 0, j = 0;
        int product = 1;
        int maxproduct = INT32_MIN;

        while (i < nums.size() || j < nums.size())
        {
            if (nums[i] == 0)
            {
                maxproduct = max(maxproduct, 0);
                i++;
                j++;
                continue;
            }
            while (j < nums.size() && nums[j] != 0)
            {
                product *= nums[j];
                maxproduct = max(maxproduct, product);
                j++;
            }
            while (i < j - 1)
            {
                product /= nums[i];
                maxproduct = max(maxproduct, product);
                i++;
            }
            i++;
            product = 1;
        }
        return maxproduct;
    }

    /// find minumum in rotated sorted array binary search problem

    int findMinInRotatedSortedArray(vector<int> &nums)
    {
        int a = 0, b = nums.size() - 1;
        if (nums[0] <= nums[b])
            return nums[0];
        while (a < b)
        {
            int mid = a + (b - a) / 2;
            if (nums[mid] < nums[0])
            {
                // in left
                b = mid;
            }
            else
            {
                // in right
                a = mid + 1;
            }
        }
        return nums[a];
    }

    // search binary in rotated sorted array!
    int searchInRotatedSortedArray(vector<int> &nums, int target)
    {
        int s = 0, e = nums.size() - 1;
        while (s <= e)
        {
            cout << "s is " << s << " e is " << e << endl;
            int mid = s + (e - s) / 2;
            if (nums[mid] == target)
            {
                return mid;
            }
            else if (nums[s] <= nums[mid])
            {
                if (target >= nums[s] and target < nums[mid])
                {
                    e = mid - 1;
                }
                else
                {
                    s = mid + 1;
                }
            }
            else
            {
                // if(target > nums[mid] and target <= nums[e]){
                //     s = mid+1;
                // }
                // else{
                //     e = mid-1;
                // }
                // both works
                if (target < nums[mid] or target >= nums[s])
                {
                    e = mid - 1;
                }
                else
                {
                    e = mid - 1;
                }
            }
        }
        return -1;
    }

    // three sum , find sets of triplets whose sum leads to 0
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;
        for (int i = 0; i < nums.size(); i++)
        {
            int target = -nums[i];
            for (int j = i + 1, k = nums.size() - 1; j < k;)
            {
                if (i > 0 and nums[i] == nums[i - 1])
                    continue;
                int addedjk = nums[j] + nums[k];
                if (addedjk == target)
                {
                    if (result.empty() or result.back() != vector<int>{nums[i], nums[j], nums[k]})
                    {
                        result.push_back({nums[i], nums[j], nums[k]});
                    }
                    j++;
                    k--;
                    continue;
                }
                else if (addedjk < target)
                    j++;
                else
                    k--;
            }
        }
        return result;
    }

    // max water containerquestion slinding windows kinda
    // we take extereme endpoints find water, and reduce our window cause if one wall is shorted than another,
    // decreasing windows from longer wall will always give you smaller water, so decrease from the shorter end
    int maxWaterContainer(vector<int> &height)
    {
        int s = 0, e = height.size() - 1;
        int maxvol = 0;
        while (s < e)
        {
            maxvol = max(maxvol, min(height[s], height[e]) * (e - s));
            if (height[s] < height[e])
                s++;
            else
                e--;
        }
        return maxvol;
    }
};

int main()
{
    Solution s = Solution();
}
