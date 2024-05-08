// https://leetcode.com/problems/find-the-median-of-the-uniqueness-array/

#include<vector>
#include<unordered_map>
using namespace std;

class Solution {
public:
    void umapIncrement(unordered_map<int, int>& umap, int val){
        if(umap.find(val) == umap.end()){
            umap[val] =1;
        }
        else umap[val]++;
    }
    void umapDecrement(unordered_map<int, int>& umap, int val){
        if(umap.find(val) == umap.end()){
            return;
        }
        else if (umap[val] == 1) umap.erase(val);
        else umap[val]--;
    }

    long long findSubarraysCount(const vector<int>&nums, int x){
        // find count of subarrays with uniqueness less than x
        int l = 0, r = 0;
        unordered_map<int, int> umap;
        long long count = 0;
        while(r < nums.size()){
            umapIncrement(umap, nums[r]);
            while(umap.size() >= x){
                umapDecrement(umap, nums[l++]);
            }
            count+= r-l+1;
            r++;
        }
        return count;
    }

    // this works better because of not using hashmap (faster and more memory efficient) // to my surprise, theres a lot of difference
    long long findSubarraysCountFaster(const vector<int>&nums, int x){
        int l = 0, r = 0;
        int occuranceCount[100001];
        for(int i = 0; i<=100000; i++){
            occuranceCount[i] = 0;
        }

        long long count = 0;
        int size = 0;
        while(r < nums.size()){
            if(occuranceCount[nums[r]]++ == 0) size++;
            while(size >= x){
                if(occuranceCount[nums[l++]]-- == 1) size--;
            }
            count+= r-l+1;
            r++;
        }
        return count;
    }

    int medianOfUniquenessArray(vector<int>& nums) {
        int size = nums.size();
        int l = 1, r = size;
        long long countInLeft = ((long long)size*(size+1)/2 -1 )/2;
        int answer;
        while(l <= r){
            int mid = l + (r-l)/2;
            long long countSubarrays = findSubarraysCount(nums, mid);
            if(countSubarrays <= countInLeft){
                answer = mid;
                l = mid+1;
            }
            else{
                r = mid-1;
            }
        }    
        return answer;
    }
};