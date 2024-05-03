#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include<algorithm>
using namespace std;
class Solution {
public:
    vector<int> digitAssignedToChar;
    vector <bool> digitsAvailable;
    int maxDigits;

    int getDigit(char c){
        if(c-65 < 0 or c-65 > 25) cout<<"invalid index"<<endl;
        return digitAssignedToChar[c-65];
    }
    void assignDigit(char c, int digit){
        // cout<<"asigning digit to c : "<<digit<< " to "<<c<<endl;
        digitAssignedToChar[c-65] = digit;
        digitsAvailable[digit] = false;
    }

    void unassignDigit(char c, int digit){
        // cout<<"unassigning digit to c: "<<digit<<" to "<<c<<endl;
        digitAssignedToChar[c-65] = -1;
        digitsAvailable[digit] = true;
    }

    void init(const vector<string>& words, const string& result){
        digitAssignedToChar.resize(26, -1);
        digitsAvailable.resize(10, true);

        // finding the digits in right side, and left side of the equation
        maxDigits = result.size();
        for(const auto& word: words){
            maxDigits = max(maxDigits, (int)word.size());
        }
    }

    int getDigitFromCharacterFromRightInWord(string word, int index){
        //index starts from 0
        if((int)word.size() -1 -index < 0 )
            return 0;
        else return getDigit(word[word.size() -1 -index]);
    }

    char getCharFromRightInWord(string word, int index){
        return word[word.size()-1-index];
    }

    bool isSolvableH(const vector<string>& words, int wordsIndex, const string& result, int sum = 0, int indexR = 0){
        while(wordsIndex < words.size()){
            string word = words[wordsIndex];
            int digit = getDigitFromCharacterFromRightInWord(word, indexR);
            if(digit == -1){
                for(int digit = 0; digit<10; digit++){
                    if(digitsAvailable[digit]){
                        //ican'tassing zero if rindex is wordfirst index
                        if(indexR == word.size()-1 and digit==0 and indexR!=0) continue; 
                        char c = getCharFromRightInWord(word, indexR);
                        assignDigit(c, digit);
                        if (isSolvableH(words, wordsIndex, result, sum, indexR)) return true;
                        unassignDigit(c, digit);
                    }
                }
                return false;
            }
            if(digit == 0 and indexR == word.size()-1 and indexR!=0) return false;
            sum+=digit;
            wordsIndex++;
        }
        int digit = sum%10;
        int carry = sum/10;
        int digitRightSide = getDigitFromCharacterFromRightInWord(result, indexR);
        if(digitRightSide == -1){
            // assign a digit
            // if digit we want it to assign is available then it is ok
            if(digitsAvailable[digit]){
                if(indexR == result.size()-1 and digit == 0 and indexR!=0){
                    return false;
                }
                assignDigit(getCharFromRightInWord(result, indexR), digit);
                if(isSolvableH(words, wordsIndex, result, sum, indexR)) return true;
                unassignDigit(getCharFromRightInWord(result, indexR), digit);
            }
            return false;
        }
        else if(digit != digitRightSide) return false;
        else if(digit == 0 and indexR == result.size()-1 and indexR!=0) return false;
        else if(indexR+1 == maxDigits and carry == 0) return true;
        
        return isSolvableH(words, 0, result, carry, indexR+1);
    }
    bool isSolvable(vector<string>& words, string result) {
        init(words, result);
        return isSolvableH(words, 0, result);
    }
};