#include<vector>
#include<unordered_map>
using namespace std;

class Solution {
public:
    void umapIncrement(unordered_map<int, int>& umap, int val){
        // cout<<"umapincr called"<<endl;
        if(umap.find(val) == umap.end()){
            umap[val] =1;
        }
        else umap[val]++;
        // cout<<"before umap increment return"<<endl;
    }
    void umapDecrement(unordered_map<int, int>& umap, int val){
        // cout<<"umap decr called"<<endl;
        if(umap.find(val) == umap.end()){
            return;
        }
        else if (umap[val] == 1) umap.erase(val);
        else umap[val]--;
        // cout<<"before umap decrement return"<<endl;
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
        // cout<<"beforereturningsub "<<endl;
        return count;
    }

    int medianOfUniquenessArray(vector<int>& nums) {
        int size = nums.size();
        int l = 1, r = size;
        long long countInLeft = ((long long)size*(size+1)/2 -1 )/2;
        // cout<<"count if left "<<countInLeft<<endl; 
        int answer;
        while(l <= r){
            // cout<<"l and r "<<l<<" "<<r<<endl; 
            int mid = l + (r-l)/2;
            // cout<<"mid is "<<mid<<endl;
            long long countSubarrays = findSubarraysCount(nums, mid);
            // cout<<"coutn sub arrays is "<< countSubarrays<<endl;
            if(countSubarrays <= countInLeft){
                answer = mid;
                // cout<<"save answer "<<mid<<endl;
                l = mid+1;
            }
            else{
                r = mid-1;
            }
        }    
        return answer;
    }
};