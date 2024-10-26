#include <bits/stdc++.h>
using namespace std;
// link for patience sort algorithm 
// https://www.youtube.com/watch?v=22s1xxRvy28
int findDeckInsertIndex(vector<int>& decks, int candidate){
    if (decks.size() == 0) return 0;
    int l = 0, r = decks.size()-1;
    int optimal;
    while (l <= r){
        int m = l+ (r-l)/2;
        if(decks[m] < candidate){
            l = m+1;
        }
        else {
            r = m-1;
            optimal = m;
        }
    }
    return optimal;
}

int lengthOfLongestIncreasingSubsequence(vector<int>& nums) {
    vector<int> decks;
    for(int num: nums){
        //find position to insert
        int insertIndex = findDeckInsertIndex(nums, num);
        if(decks.size() <= insertIndex) decks.push_back(num);
        else decks[insertIndex] = num;
    }
    return decks.size();
}
