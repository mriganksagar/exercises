#include<bits/stdc++.h>
using namespace std;

// the intuition for the solution is :
// if there is a 0 in array, the product of subarray containing zero would also be zero
// so if logically we can separate all subarrays breaking whenever a zero comes
// and on those subarrays we can find the overall product of subarray 
// it would be either positive or negative
// if positive then it is max product of that subarray
// if negative then there would be two candidates at maximum, 
// one is exclude the left most negative number in subarray and elements before it
// second is exclude right most negative number in subarray and elements after it
// now this could be done by sliding window approach 
// so we use sliding windows approach and reset the product whenever a zero comes in array ..

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        // check non empty vector, no need
        int l = 0, r = 0;
        int product = 1;
        int maximumProduct = INT_MIN;

        while(l < nums.size()){
            // cout<<"the max is now "<<maximumProduct<<endl;
            while(r < nums.size() and nums[r] !=0 ){
                // cout<<"r and l are "<<r<<" "<<l<<endl;
                product *= nums[r++];
                maximumProduct = max(product, maximumProduct);
            }
            if(r < nums.size()) maximumProduct = max(maximumProduct, 0);
            // cout<<"breaking while first "<<endl;
            while(l < r-1){
                // cout<<"r and l are "<<r<<" "<<l<<endl;
                product /= nums[l++];
                maximumProduct = max(product, maximumProduct);
            }
            r++;
            l = r;
            product = 1;
        }
        return maximumProduct;
    }
};