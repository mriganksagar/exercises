#include<bits/stdc++.h>
using namespace std;

// Problem link
// https://leetcode.com/problems/edit-distance/description/



// the intuition for the solution is : 
// if i match a word1 with word2, at this instance i am trying to match the characters at index a and b respectively.
// then if the characters match then the best optimal result from words1 till index a-1 and word2 till index b-1, 
// will be the optimal result for word1 till a index, and word2 till b index , as well.

// for the case when characters do not match at index a and b for word1 and word2 respectively
// either we can delete the character at word1 with some cost and check optimal of matching word1 till a-1 and word2 till b.
// or we can insert a character at word1 to match the character from word2 with some cost and add the optimal of matching word2 till a and word2 till b-1 (cause word2[b] matches with new added character)
// but interestingly this is same as removing character from word2 and then check optimal of matching word1 till a and word2 till b-1 (due to removal of character at b index in word2).
// it is same because of same cost of removing and adding , else it would be a different story.
// of we can modify the character at any word to match and add optimal from word1 till (a -1 ) and word2 till(b-1)

// and some edge cases are there when we match empty word with a non empty word . which costs adding or removing length of characters from non empty word



// METHOD 1
// here i can make the matrix n+1 times m-1, size to incorporate the semantics of empty words matched with other words
// this method is simpler to reason about due to not thinking about cases manually and relying on dp even for empty words matched with other word
int minDistance(string word1, string word2){
    vector<vector<int>> dp (word1.size()+1, vector<int>(word2.size()+1, -1));
    for(int index = 0; index <= word1.size(); index++) dp[index][0] = index;
    for(int index = 0; index <= word2.size(); index++) dp[0][index] = index;

    for(int i = 1; i <= word1.size(); i++){
        for(int j = 1; j <= word2.size(); j++){
            if(word1[i-1] == word2[j-1]) {
                dp[i][j] = dp[i-1][j-1];
            }
            else{
                dp[i][j] = min(dp[i-1][j-1], min(dp[i-1][j], dp[i][j-1])) + 1;
            }
        }
    }

    return dp[word1.size()][word2.size()];
}


// Method 2 , manually think of cases
int minEditDistance(string word1, string word2){
    vector<vector<int>> dp (word1.size(), vector<int>(word2.size(), -1));
    if( word1.size() == 0) return word2.size();
    else if(word2.size() == 0) return word1.size();

    for(int i = 0; i < word1.size(); i++){
        for(int j = 0; j < word2.size(); j++){
            if(word1[i] == word2[j]) {
                if(i == 0 and j == 0)  dp[i][j] = 0;
                else if(i == 0) dp[i][j] = j;
                else if(j == 0) dp[i][j] = i;
                else dp[i][j] = dp[i-1][j-1];
            }
            else{
                if(i == 0 and j == 0)  dp[i][j] = 1;
                else if(i == 0) dp[i][j] = dp[i][j-1]+1;
                else if(j == 0) dp[i][j] = dp[i-1][j]+1;
                else dp[i][j] = min(dp[i-1][j-1], min(dp[i-1][j], dp[i][j-1])) + 1;
            }
        }
    }

    return dp[word1.size()-1][word2.size()-1];
}

int main(){}