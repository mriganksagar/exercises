#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
using namespace std;


// a bad code maybe i will rewrite it to improve readability and reduce code where flow is not going
// leetcode link https://leetcode.com/problems/substring-with-concatenation-of-all-words/
// i thought that by stogin the string i am getting better time but it is not really 
// because reading a string is not much different that creating a substring of lenght l1 from a string  linear complexity in both cases acc to me
// another solution i was thinking is instead of storing the words how about i create the word on the fly   instead of variable v
// io will create a vector of lenght word  to store varable v
// so i can recreate the string as i go 
// i think that wouldn't work
class Solution {
public:
    void initialiseHashMap(const vector<string>&words, unordered_map<string, int>& umap){
        for(string word:words){
            auto it = umap.find(word);
            if(it == nullptr) umap.emplace(word,1);
            else it->second++;
        }
    }
    void findValidWordArray(const string& s, int wordLength, const unordered_map<string, int>& umap, vector<pair<string, bool>>& validword){
        
        string currentWord = s.substr(0,wordLength);
        if(umap.find(currentWord)!= nullptr) validword.push_back({currentWord, true});
        else validword.push_back({currentWord, false});
        for(int i = wordLength; i < s.size(); i++){
            currentWord.erase(0,1);
            currentWord.push_back(s[i]);
            if(umap.find(currentWord)!= nullptr) validword.push_back({currentWord, true});
            else validword.push_back({currentWord, false}); 
        }
    } 

    int wordsCount;
    void initialiseCountForWords(const unordered_map<string, int>& umap){
        int count = 0;
        for(auto p: umap){
            count+=p.second;
        }
        wordsCount = count;
    }

    int incrementLeft( unordered_map<string, int>& cmap, int left, int right, const vector<pair<string, bool>>& validword, int wordLength, int&countLeft){
        
        while(left < right){
            auto leftIterator = cmap.find(validword[left].first);
            leftIterator->second++;
            countLeft++;
            left+=wordLength;
        }
        return left;
    }

    int incrementLeftTillWord(unordered_map<string, int>& cmap, int left, int right, const vector<pair<string, bool>>& validword, int wordLength, int&countLeft){
        // increment till word that is at index r , is found by the while loop
        string word = validword[right].first;
        while(validword[left].first != word){
            auto leftIterator = cmap.find(validword[left].first);
            leftIterator->second++;
            countLeft++;
            left+=wordLength;
        }
        //do it one more time
        auto leftIterator = cmap.find(validword[left].first);
        leftIterator->second++;
        countLeft++;
        left+=wordLength;
        
        return left;
    }

    vector<int> findSubstring(string s, vector<string>& words) {

        ////edge cases

        if(words.size() == 0 or words[0].size()*words.size() > s.size()){
            return {};
        }
        unordered_map<string, int> umap;
        //initialise uset
        initialiseHashMap(words, umap);
        initialiseCountForWords(umap);
        //result vector to store indices
        vector<int>result;

        int wordLength = (words.size() > 0) ? words[0].size(): 0;
        vector<pair<string,bool>> validword;
        findValidWordArray(s, wordLength, umap, validword);
    
        for(int w = 0; w < wordLength; w++){
            int countLeft = wordsCount;
            // int start = w;
            unordered_map<string, int> cmap(umap);
            int l = w, r = w; 
            while(r <= s.size() - wordLength){
                if(validword[r].second){
                    auto it = cmap.find(validword[r].first);
                    if(it->second > 0){
                        it->second--;
                        countLeft--;
                        if(countLeft == 0){
                            result.push_back(l);
                            l = incrementLeft(cmap, l, l+wordLength, validword, wordLength, countLeft);
                        }
                        r+=wordLength;
                    }
                    else{
                        l = incrementLeftTillWord(cmap, l, r, validword, wordLength, countLeft);
                    }
                }
                else{
                    l = incrementLeft(cmap, l, r, validword, wordLength, countLeft);
                    r+=wordLength;
                    l=r;
                }
            }
        }
        return result;
    }
};
