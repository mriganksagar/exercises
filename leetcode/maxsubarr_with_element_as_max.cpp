#include <vector>
#include <stack>
#include <unordered_map>
#include <iostream>
using namespace std;

// Problem Statement
// Given an array
// for every element ai find the maximum length of subarray that would contain this element value as the maximum value
// return an result array where element ei represent the length for ai

void rightElementWithGreaterValue(const vector<int> &nums, vector<int> &result)
{
    stack<int> st;
    result.clear();
    result.resize(nums.size());
    for (int i = nums.size() - 1; i >= 0; i--)
    {
        while (!st.empty() and nums[st.top()] < nums[i])
        {
            st.pop();
        }
        if (st.empty())
            result[i] = nums.size();
        else
            result[i] = st.top();
        st.push(i);
    }
}

vector<int> maxSubArrayWithElementAsMax(const vector<int> &nums)
{
    vector<int> rightGreater;
    // evaluate right greater element index
    rightElementWithGreaterValue(nums, rightGreater);

    stack<int> st;
    int leftGreaterIndex;

    vector<int> result;
    result.resize(nums.size());

    for (int i = 0; i < nums.size(); i++)
    {
        while (!st.empty() and nums[st.top()] < nums[i])
        {
            st.pop();
        }
        if (st.empty())
            leftGreaterIndex = -1;
        else
            leftGreaterIndex = st.top();
        st.push(i);
        result[i] = rightGreater[i] - leftGreaterIndex - 1;
    }
    //if there are douplicates then use unorderedMap to find the best outcome of all duplicates
    unordered_map<int, int> umap;
    for(int i = 0; i < nums.size(); i++){
        if(umap[nums[i]]) umap[nums[i]] = max(umap[nums[i]], result[i]);
        else umap[nums[i]] = result[i];
    }
    for(int& val: result){
        val = max(val, umap[val]);
    }
    /////////////////////////////////////////////////////
    return result;
}

int main()
{
    auto result = maxSubArrayWithElementAsMax({1,2,1});
    if(result == vector<int>{1,3,1}) cout<<"well done";
}