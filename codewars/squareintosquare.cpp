#include<bits/stdc++.h>
class Decomp
{
  public:
  static bool decomposeHelper(long long sum, long long n, std::vector<long long> &res){
    n--;
    if(sum == 0)return true;
    else if(n==1)return false;
    long long square = (n)*(n);
    while(sum < square){
      n--;
      square = n*n;
    }
    for(long long i = n; i >0; i--){
        long long leftSum = sum - i*i;
        res.push_back(i);
        if( decomposeHelper(leftSum, i, res)){
            return true;
        };
        res.pop_back();
    }
    return false;
  }
  static std::vector<long long> decompose(long long n){
    std::vector<long long> result;
    if(decomposeHelper(n*n, n, result)){
         for(int i = 0; i < result.size()/2; i++){
             auto xx = result[i];
             result[i]= result[result.size()-1-i];
             result[result.size()-i-1] = xx; 
         }
         return result;
    }
    else return {};
  };
};