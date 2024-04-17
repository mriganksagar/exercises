#include<bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> productExceptSelf(vector<int> &nums)
    {
        vector<int> products(nums.size(), 1);
        int leftproduct = 1;
        int rightproduct = 1;
        for (int i = 0; i < nums.size(); i++)
        {
            products[i] *= leftproduct;
            products[nums.size() - 1 - i] *= rightproduct;
            leftproduct *= nums[i];
            rightproduct *= nums[nums.size() - 1 - i];
        }
        return products;
    }
};

int main(){

}
