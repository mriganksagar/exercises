#include <bits/stdc++.h>
#define ulong unsigned long long
ulong mystery(ulong n){
  //create binary representation of the number n
  //find the 2's exponent number just bigger than the number itself

  ulong x = 1;
  while (x < n){
    x= x*2;
  }
  std::vector<unsigned int> v;
  while(x>0){
    v.push_back(n/x);
    n = n%x;
    x = x/2;
  }
  bool reversed = false;
  std::vector<unsigned int> ans;

  for(auto i: v){
    if(!reversed ){
        ans.push_back(i);
        if(i==1)reversed = true;
    }
    else{
        if(i == 0) {
            ans.push_back(1);
            reversed = false;
        }
        else if (i==1 ) ans.push_back(0);
    }
  }
    // compute the number now from result
    ulong resultNumber = 0;
    // ulong powerOfTwo = 1;
    for(auto i: ans){
        resultNumber *= 2;
        resultNumber += i;
    }
  return resultNumber;
}

ulong mysteryInv(ulong n){
  ulong x = 1;
  while (x < n){
    x= x*2;
  }
  std::vector<unsigned int> v;
  while(x>0){
    v.push_back(n/x);
    n = n%x;
    x = x/2;
  }
  bool reversed = false;
  std::vector<unsigned int> ans;

  for(auto i: v){
    if(!reversed ){
        ans.push_back(i);
    }
    else{
        if(i == 0)  ans.push_back(1);
        else if (i==1 ) ans.push_back(0);
    }
    if(ans[ans.size()-1]==1)reversed = true;
    else reversed=false;
  }
    // compute the number now from result
    ulong resultNumber = 0;
    // ulong powerOfTwo = 1;
    for(auto i: ans){
        resultNumber *= 2;
        resultNumber += i;
    }
  return resultNumber;
}

std::string nameOfMystery(){
  return "";
}