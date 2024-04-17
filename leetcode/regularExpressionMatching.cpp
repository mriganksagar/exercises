#include<string>
#include<vector>
using namespace std;

class Solution{
public:

    bool isMatch(const string& s, const string& p, int i, int j, vector<vector<int>>& memoised){
        if(memoised[i][j] != -1) return memoised[i][j];
        
        //check if pattern ended, 
        // pattern ended and as well as string then it is good , a match, but pattern ended and there is string left to match then false
        if(j==p.size()){
            if(i==s.size()){
                memoised[i][j] = 1;
                return true;
            }
            else {
                memoised[i][j] = 0;
                return false;
            }
        }
        // result is false, and we check for possible pattern match
        bool result = false;
        if(j+1 < p.size() and p[j+1] == '*'){
            // * pattern
            if(i < s.size() and (p[j] == '.' || s[i] == p[j]) ){
                result = result || isMatch(s, p, i+1, j, memoised);
            }
            result = result || isMatch(s, p, i, j+2, memoised);
        }
        else if(i < s.size() && (p[j] == '.' || s[i] == p[j])) result = result || isMatch(s,p,i+1, j+1, memoised);
        // in else there would be no pattern match and means 'false' // no need to explicitly save it to result cause it is already false
        memoised[i][j] = boolToInt(result);
        return boolToInt(result);
    }

    int boolToInt(bool b){
        if(b) return 1;
        else return 0;
    }

    bool isMatch(string s, string p){
        auto memoised = vector<vector<int>>(s.size()+1, vector<int>(p.size()+1, -1));
        return isMatch(s, p, 0, 0, memoised);
    }
};