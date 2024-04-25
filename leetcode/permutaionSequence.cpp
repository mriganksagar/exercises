// https://leetcode.com/problems/permutation-sequence/

// to solve this i did not use recursion and backtracking 
// cause there exists a pattern 
// lets consider the all possible result space you can divide that into n parts where n is also the numbers of number in the array or 1, 2, .. n in the case of this question
// first part will have the first element , second will have the second element and so on 
// through this we can identify the first number in the sequence, 
// to find the second number , the possible result space will reduce by factor of the previous n and same logic can be applied 
// to find the ith number , the result space reduce by factor of i+1
// the current result space can be divided into  n-i+1 parts each part will be of length n-i factorial.
// using this pattern makes it easier to find all the numbers in the resultant sequence
#include<string>
#include<vector>
using namespace std;
class Solution {
public:
    vector<bool> numberspace;

    string findAtPosition(int position){
        int count = 0;
        for(int index = 1; index < numberspace.size(); index++){
            if(!numberspace[index])count++;
            if(count == position){
                //mark it is included
                numberspace[index] = true;
                return to_string(index);
            }
        } 
        return"";
    }
    string getPermutation(int n, int k) {
        // intitalise numberspace
        numberspace.resize(n+1, false);

        string result;
        int currentFactorial = 1;
        for(int i = n; i > 1; i--) currentFactorial*=i;
        for(int i = n; i > 0; i--){
            currentFactorial /= i;
            int position = (k-1)/currentFactorial+1;
            result += findAtPosition(position);
            k = k%currentFactorial;
            if(k == 0) k = currentFactorial;
        }
        return result;
    }
};