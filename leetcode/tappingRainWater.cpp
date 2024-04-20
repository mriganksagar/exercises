#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        //checking for empty input
        if(height.size() == 0) return 0;

        stack<int>st;
        st.push(0);

        int water = 0;
        for(int i =1; i < height.size(); i++){
            while(!st.empty() and height[st.top()] <= height[i]){
                int elem = height[st.top()];
                st.pop();
            
                if(!st.empty()){
                    water+= (min(height[st.top()], height[i]) - elem)*(i-st.top() -1);
                }
            }
            st.push(i);
        }        
        return water;
    }
};