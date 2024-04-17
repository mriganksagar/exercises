#include<bits/stdc++.h>

class Solution {
public:
    int maxProfit(std::vector<int>& prices) {
        int maxprofit = 0;
        int size = prices.size();

        int maxright = 0;
        for(int i = size -1; i>=0; i--){
            maxprofit = std::max(maxprofit, maxright - prices[i]);
            maxright = std::max(maxright, prices[i]);
        }
        return maxprofit;
    }
};
