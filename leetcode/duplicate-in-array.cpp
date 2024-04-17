#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        auto umap = unordered_set<int>();
        for(auto num:nums){
            auto it = umap.find(num);
            if(it != umap.end()) return true;
            umap.insert(num);
        }
        return false;
    }
};