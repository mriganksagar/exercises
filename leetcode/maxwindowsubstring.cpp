#include <string>
// #include <limits>
#include <climits>
using namespace std;


class Solution {
public:
    int charCountForT[75];
    void countT(string t){
        for(int i = 0; i < 75; i++){
            charCountForT[i] = 0;
        }
        for(char c: t){
            charCountForT[c-65]++;
        }
    }

    int charCountWindow[75];
    void initialiseWindowCount(){
        for(int i =0; i < 75; i++)
            charCountWindow[i]= 0;
    }

    void incrCharInWindow(char c){
        charCountWindow[c - 65]++;
    }
    void decrCharInWindow(char c){
        charCountWindow[c - 65]--;
    }

    bool checkAllCharacterIncludedInWindow(){
        for(int i = 0; i < 75; i++){
            if(charCountWindow[i] < charCountForT[i]) return false;
        }
        return true;
    }

    string minWindow(string s, string t) {
        countT(t);
        initialiseWindowCount();
        int l =0, r = 0;
        incrCharInWindow(s[r]);
        int minsol = INT_MAX;
        int start = -1;
        while(r < s.size()){
            if(!checkAllCharacterIncludedInWindow() ){
                r++;
                incrCharInWindow(s[r]);
            }
            else{
                if(minsol > r-l+1){
                    minsol = r-l+1;
                    start = l;
                }
                decrCharInWindow(s[l]);
                l++;
            }
        }
        if(start == -1) return "";
        return s.substr(start, minsol); 
    }
    // lets rewrite the code to optimise, i don't need to checkAllCharacterIncludedInWindow everytime
    // optimisation 1:  can use a same array for both charCountForT and charCountWindow, first increase the count of array by reading t string and then decrease the count whenever character is found in the sliding window
    // and increase the count when i decrease the window
    // the array signifies for each character how many counts are still left to be included in the sliding window

    // optimisation 2: keep a single count that shows sum of count of all the characters are still left to be included in the sliding window
    // if a once, b twice, c four times is left to be included, then sum will be 1+2+4 = 7 
    // or count can say how many characters are left to be included in the sliding window
    // if a once, b twice, c four times is left to be included, then sum will be 1+1+1 = 3
    
    int charactersNotIncluded;
    int countArray[75];

    bool isValid(){
        if(charactersNotIncluded == 0) return true;
        else return false;
    }
    void countTnew(string t){
        for(int i = 0; i < 75; i++){
            countArray[i] = 0;
        }
        for(char c: t){
            countArray[c-65]++;
        }
    }

    void findCharactersNotIncluded(){
        charactersNotIncluded = 0;
        for(int i =0; i<75;i++){
            if(countArray[i] != 0){
                charactersNotIncluded++;
            }
        }
    }

    void includeCharacter(char c){
        countArray[c-65]--;
        if(countArray[c-65] == 0){
            charactersNotIncluded--;
        }
    }

    void excludeCharacter(char c){
        countArray[c-65]++;
        if(countArray[c-65] == 1){
            charactersNotIncluded++;
        }
    }
    
    string minWindowOptimised(string s, string t){
        countTnew(t);
        findCharactersNotIncluded();
        int l = 0, r =0;
        includeCharacter(s[r]);
        int start = -1;
        int minsol = INT_MAX;
        while (l <= r and r < s.size()){
            if(!isValid()) {
                r++;
                if(r < s.size()) includeCharacter(s[r]);
            }    
            else{
                if(r-l+1 < minsol) {
                    minsol = r-l+1;
                    start = l;
                }
                excludeCharacter(s[l++]);
            }
        }
        if(start == -1) return "";
        return s.substr(start, minsol);
    }
};