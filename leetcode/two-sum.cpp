#include <bits/stdc++.h>
using namespace std;

class Solution{
public: 
    vector<int> twoSum(vector<int>& arr, int target){
        vector<int> ans;
        unordered_map<int,int> mmap;
        for(int i = 0; i < arr.size(); i++){
            int x = arr[i];
            auto it = mmap.find(target-x);
            if( it != mmap.end()){
                ans.push_back(i);
                ans.push_back(it->second);
            }
            else{
                mmap.insert({x,i});
            }
        }

        return ans;
    }
};


int main(){

}