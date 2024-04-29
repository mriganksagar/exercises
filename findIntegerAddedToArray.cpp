// https://leetcode.com/problems/find-the-integer-added-to-array-ii/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:
    bool canbeDone(const vector<int>&nums1, const vector<int>& nums2, int index, int difference){
        int forgive = 2 - index;

        int a = index, b = 0;
        while(b < nums2.size()){
            if(nums2[b] - nums1[a] != difference){
                if(forgive == 0) return false;
                forgive--;
                a++;
                continue;
            }
            a++;
            b++;
        }
        return true;
    }

    int minimumAddedInteger(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        int mindiff = INT_MAX;
        for(int i = 0; i <= 2; i++){
            int difference = nums2[0] - nums1[i];
            if(canbeDone(nums1, nums2, i, difference)) mindiff = min(mindiff,  difference);
        }
        return mindiff;
    }
};