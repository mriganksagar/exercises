#include<bits/stdc++.h>
using namespace std;

int longestCommonSubsequence(string text1, string text2) {
    // make a 2d dp 
    vector<vector<int>> dp(text1.size(), vector<int>(text2.size(), 0));
    for(int i = 0; i < text1.size(); i++){
        for(int j = 0; j < text2.size(); j++){
            if(text1[i] == text2[j]){
                if(i == 0 or j == 0) dp[i][j] = 1;
                else dp[i][j] = dp[i-1][j-1] + 1;
            }
            else{
                int newValue;
                if(i == 0 and j == 0) newValue = 0;
                else if(i == 0){
                    newValue = dp[i][j-1];
                }
                else if(j ==0){
                    newValue = dp[i-1][j];
                }
                else newValue = max(dp[i-1][j], dp[i][j-1]);
                dp[i][j] = newValue; 
            }
        }
    }

    cout << "printing the dp "<<endl;
        
    for(auto a: dp){
        for(auto aa: a){
            cout<<aa<<" ";
        }
        cout<<endl;
    }

    return dp[text1.size()-1][text2.size()-1];
}

int main(){

}