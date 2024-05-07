#include<vector>
using namespace std;

class Solution {
public:
    vector<int> binaryRepresentation(int x){
        vector<int> representation;
        representation.reserve(32);
        for(int i = 31; i >= 0; i--){
            int y = (x>>i)&1;
            representation.push_back(y);
        }
        return representation;
    }
    long long minEnd(int n, int x) {
        vector<int> representation;
        vector<int> x_b = binaryRepresentation(x);
        vector<int> n_b = binaryRepresentation(n-1);
        int j = 31;
        for(int i = 31; i >= 0; i--){
            if(x_b[i] == 0)
                representation.push_back(n_b[j--]);
            else representation.push_back(x_b[i]);
        }    
        while(j>=0){
            representation.push_back(n_b[j--]);
        }
        long long result = 0;
        long long base = 1;
        for(int digit: representation){
            result += base*digit;
            base*=2;
        }
        return result;
    }
};