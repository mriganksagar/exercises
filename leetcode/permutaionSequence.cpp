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