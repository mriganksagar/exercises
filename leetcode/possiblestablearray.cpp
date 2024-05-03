// PROBLEM URL
//https://leetcode.com/problems/find-all-possible-stable-binary-arrays-i/description/
/*
You are given 3 positive integers zero, one, and limit.

A binary array 
arr is called stable if:

    The number of occurrences of 0 in arr is exactly zero.
    The number of occurrences of 1 in arr is exactly one.
    Each
    subarray
    of arr with a size greater than limit must contain both 0 and 1.

Return the total number of stable binary arrays.

Since the answer may be very large, return it modulo 109 + 7.
*/


#include<iostream>
#include<vector>
using namespace std;

/*
in this solution there are some problems

but
first lets see how i tried to solve this problem

the problem basically reduces to 
find number of permutation where in that permuation
there are no continous zeros or ones more than limit
limit is the maximum continuous zero or ones allowed

because 
if we want for any subarray of size greater than limit, to contain both 0 and 1
then it can't have continuos zero or one, more than limit times.


so if i try to find all the permuations possible with zero times of 0s and one times of 1s
then it would be fact(zero+one) /(fact(zero) * fact(one) )

if i subtract the permutations where there are more than limit times of continuos ones or zeros
then the result if the final answer


but how do i find the permutations with more than limit times of continuous ones or zeros

first 
find for 1 , subtract it then 
find for 0 , subtract it

but both of them have permuations for more than zeros 0s and more than one 1s (intersections occurs)
so we subtracted this part twice

i will add it now
*/

/*
    this solution is good but not good enough

    there is one fundamental flaw in 

    How I calculate the permutations where
    there are continuos "zero" or "one" more than limit times


    the way i am calculating is 

    lets say i have 10 zeros , 9 ones

    and i want 5 zeros together at least
    
    to find it 

    i will club them 5 zeros together and think them as a single character now  (00000)
    and i have now 5 zeros left, 9 ones left

    we have total characters

    5 zeros + 9 ones and 1 special clubbed , means 15 character

    and 9 indinstinctive same characters which is "one"
    and 5 indinstinctive zeros

    then fact(15) / fact(9) * fact(5)


    but there is one problem 
    for that lets have another example 

    i have 3 ones and 1 zero
    then if you think manually there are total 
    4 permutations possible


    0111,
    1011,
    1101,
    1110

    if you think about clubbing two ones together 
     
    you have 3 characters now 

    (11)  one times, 1 one times and 0 one times

    so by formulate you have
    3 fact divided by 1 fact times 1 fact 

    which is 6

    (11)10
    (11)01
    1(11)0
    10(11)
    0(11)1  
    01(11)

    but actually the 5th and 6th permutations are same if you only remove the paranthesis
    and so are the 1st and 3rd permuations

    
    observe that
    whenever
    11 comes together with 1
    it can be swapped 
    to cause (11)1 and 1(11) both are the same things

    
    it means that
    the times 1 is coming more than 3 times is coming twice
*/


/*

    MY Hypothesis to solve this question failed , i used an example and saw the recurrence formulae will not work

    btw the formulae was


    to find number of permutations
    for array with a zeros and b ones
    and at least ac continuous zeros and at least bc continuos ones

    after some computation same as before 
    (a+b)! / ( (a - ac +1 )! * (b-bc+1)! )

    minus
    recursion ( a, b, ac+1, bc)
    minus
    recursion (a, b, ac, bc+1);
    plus
    recursion (a, b, ac+1, bc+1)
    to compensate for reducing twice (due to earlier two steps)


    though this whole thing doesn't work , 
    it was completely wrong hypothesis

    cause
    in this example 

    (11) 11 0
    1(11)10 
    is same 
    i have thought of this case in my formulae

    but
    not about 
    (11) 0 11
    11 0 (11) these two are same as well


    so  1 comes together with (11) was creating duplicates 
    to remove it I was removing the duplicates where there are (111)

    but the case when (11) 0 11 i didn't took care of this case
    in fact if it is (11) 0 111 
    then 11 0 (11) 1 and 11 0 1 (11) all three are same 
    so it becomes quite complex to make some formuale with recurrence relation 
    hence i am dropping this 
    shit hole

    (i don't thnk anybody is reading this , so i can swear i)
    stupid fukcing porblme
*/
class SolutionOld {
public:
    long long getFactorial(int n){
        if(n<=0) return 1;
        if(factorial.size() < n+1){
            factorial.resize(n+1, -1);
        }
        if(factorial[n] == -1){
            return n* getFactorial(n-1);
        }
        return factorial[n];
    }
    vector<int> factorial;

    long long combinations(int n, int m){
        long long result = getFactorial(n)/getFactorial(m);
        result /= getFactorial(n-m);
        return result;
    }
    int numberOfStableArrays(int zero, int one, int limit) {
        long long totalPermutations = getFactorial(zero+one);
        totalPermutations /= getFactorial(zero);
        totalPermutations /= getFactorial(one);
        // with limit times zero
        long long withContinuosZero = 0;
        if( zero > limit){
            withContinuosZero = getFactorial(zero+one-limit);
            withContinuosZero /= getFactorial(zero-limit-1);
            withContinuosZero /= getFactorial(one);
        }
        long long withContinuosOne = 0;
        if(one>limit){
            withContinuosOne = getFactorial(zero+one-limit);
            withContinuosOne /= getFactorial(one-limit-1);
            withContinuosOne /= getFactorial(zero);
        }
        long long withOneZeroBoth = 0;
        if(zero>limit and one>limit){
            withOneZeroBoth = getFactorial(zero+one -2*limit);
            withOneZeroBoth /= getFactorial(zero-limit-1);
            withOneZeroBoth /= getFactorial(one-limit -1);
        }
        totalPermutations = totalPermutations - withContinuosOne - withContinuosZero + withOneZeroBoth;
        return totalPermutations;
    }    
};


class Solution {
public:
    int mod = 1000000007;
    int limitG;
    int numberOfStableArraysH(int zero, int one, int consecutiveStart, int startCharacter, vector<vector<vector<vector<int>>>>&dp){
       
        if(consecutiveStart == 0) return 0;
        else if((startCharacter == 0 and zero == 1 and one == 0) or (startCharacter == 1 and one ==1 and zero == 0)) 
        {
            return 1;
        }

        if(dp[startCharacter][consecutiveStart][zero][one] != -1) return dp[startCharacter][consecutiveStart][zero][one];
        
        int result = 0;
        if(startCharacter == 0 and zero>0){
            result += numberOfStableArraysH(zero -1,  one, consecutiveStart-1, 0 , dp)%mod;
            result += numberOfStableArraysH(zero -1, one, limitG,  1, dp)%mod;
            result = result%mod;
        }
        else if(startCharacter == 1 and one>0){
            result += numberOfStableArraysH(zero, one-1, limitG, 0, dp)%mod;;
            result += numberOfStableArraysH(zero, one-1, consecutiveStart-1, 1, dp)%mod;
            result = result%mod;
        }
        dp[startCharacter][consecutiveStart][zero][one] = result;
        return result;
    }

    int numberOfStableArrays(int zero, int one, int limit){
        limitG = limit;
        vector<vector<vector<vector<int>>>> dp(2, 
            vector<vector<vector<int>>>(limit+1,
                vector<vector<int>>(zero+1, 
                    vector<int>(one+1, -1)
                )
            )
        );
        int result = 0;
        result += numberOfStableArraysH(zero, one, limit, 0, dp)%mod;
        result += numberOfStableArraysH(zero, one, limit, 1, dp)%mod;
        return result%mod;
    }
};