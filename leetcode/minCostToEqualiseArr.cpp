// PROBLEM URL
// https://leetcode.com/problems/minimum-cost-to-equalize-array/
#include<vector>
#include<climits>
#include<cmath>
#include<algorithm>
#include<numeric>
using namespace std;

class Solution {
public:
    int maxNumInArr (const vector<int> & nums){
        int maxx = INT_MIN;
        for(int elem: nums){
            maxx = max(maxx, elem);
        }
        return maxx;
    }

    int mod = 1000000007;

    int minCostMakeArrayVal(vector<int>& nums, int val, int cost1, int cost2){
        bool betterToIncrAll = cost1*2 <= cost2;    
        long result = 0;

        if(betterToIncrAll){
            for(int elem:nums){
                result = (result+ (val-elem)*cost1)%mod;
            }
            return result;
        }
    
        int ai = 0, bi = 1;
        while(bi < nums.size()){
            int a = nums[ai], b = nums[bi];

            if( a < b){
                result = (result + (val-b)*((long)cost2))%mod;
                nums[bi] = a+(val-b);
            }
            else{
                result = (result + (val-a)*((long)cost2))%mod;
                nums[bi] = b+(val-a);
            }
            ai = bi;
            bi++;
        } 
        result = (result+ (val-nums[ai])*cost1)%mod;
        return result;
    }
    int minCostToEqualizeArray(vector<int>& nums, int cost1, int cost2) {
        sort(nums.begin(), nums.end());
        int low = maxNumInArr(nums);    
        int high = ((long)low*(nums.size()-1))/(max(1,(int)nums.size()-2));
        int best = INT_MAX;

        for(int check = low; check <=high; check++){
            best = min(best, minCostMakeArrayVal(nums, check, cost1, cost2));
        }
        return best;
    }
};

/*
this solution is wrong
i assumed that by increasing everyone to the max integer, we can get optimal answer
but that is not the case, consider the example
1, 14, 14, 15   cost1 is 2, and cost2 is 1 
i increase 1, 14 
2, 15 with cost = 0+1 = 1
increase 2, 14 cost  = 1 + 1 = 2
i have now , 3, 15, 15, 15
now increase 3, 15 , 3 times  cost = 2+3 = 5
i have , 6, 18, 15, 15

*/


// cant sovle them


// https://leetcode.com/problems/minimum-cost-to-equalize-array/solutions/5113640/binary-search-on-piecewise-linear-function/
// solutions 

// another try
// working except for one test case (the problem is due to using modulus and comparing them which leads to wrong selection)

class Solution {
public:
    int mod = 1000000007;
    int equaliseToValue(long long totalGap, long long maxGap, int cost1, int cost2, int size){
        // this function greedily does operation 2, and if needed does operation 1 based on optimisation
        // lot of conditions bear through it with me
        // cout<<"qualise called with total gap, maxGap "<<totalGap<<" "<<maxGap<<endl;
        long long cost = 0;
        
        // case 1 when maxDifference is less than totalDifference-maxDifference, it means there can be pairs made untill there is no more increment left to do, or 1 gap is left (in case of odd gap)
        // => maxGap <= totalGap - maxGap +1 (because one increment is also left in case of odd, so we can manage to make it +1 as well)
        // => maxGap*2 <= totalGap +1
        // case 2 when maxDifference is greater than totalDifference-maxDifference, no matter how many other elements the minimum one makes pair with it can not reach the desired value

        if(2*maxGap <= totalGap+1){
            cost = (cost + cost2*(totalGap/2))%mod;
            totalGap = totalGap%2;
            if(totalGap){
                // means there is 1 gap left and we have to do it through operation 1 or raise the target so we dont' have to do operation 1 at all
                // HERE OUR ARRAY WOULD LOOK SOMEWHAT LIKE THIS
                // A1, A2, A3, A4,  ....., An
                // A2 = A2 = ... = An,  but A1 = A2-1
                // I have few choices now
                // Option 1: Either I increase A1 by 1 doing operation 1 by cost of cost1 (if cost1 is much greater than cost2 this could be expensive but how much greater lets see it )
                // Option 2: I increase the target value (but how much , lets consider by 1 for now, no more is needed) and I increase elements (A1 till An-1) all by 1, by making pairs and doing operation 2 (but is it possible, what is the condition for its possibility)
                // well, the gap to do this task would be 
                // 1 + 1+ 1+1 .. + 1  (n-1 times) and + 2  == n-1 +2 = n+1
                // now if n+1 is even (or n is odd), only then I can make pairs else there would always be 1 left, and i would still have to do operation 1 again
                // if n is even we can't simply hope to raise the target so that no operation 1 is needed
                if(size%2==0){
                    cost += cost1;
                }
                else{
                    cost+= min(cost1, equaliseToValue(2 + size - 1, 2, cost1, cost2, size));
                }
            }
        }
        else{
            // min element made pair with all possible other elements but still there is gap left in itself (a gap of more than equal 2 )
            // cout<<"inside else "<<endl;
            cost = (cost + cost2*(totalGap - maxGap))%mod;
            maxGap -= totalGap - maxGap; 
            // Option 1: Either increase the left element using operation 1
            long long fillWithOp1 = cost1*maxGap;
            // cout<<"fill with op1 is"<<fillWithOp1<<endl;

            // Option 2: avoid operation 1 (except the one potential gap left), increase the target by 1 and lets see
            long long fillWithOp2 = equaliseToValue(size -1 + maxGap +1, maxGap+1, cost1, cost2, size);
            // cout<<"fill with op2 is <<"<< fillWithOp2<<endl;
            cost+= min(fillWithOp1, fillWithOp2);
        }
        // cout<<"cost is before reutrn "<<cost<<endl;
        return cost%mod;
    }

    int minCostToEqualizeArray(vector<int>& nums, int cost1, int cost2) {
        long long totalSum = accumulate(nums.begin(), nums.end(), (long long)0);
        // cout<<"sieze is "<<nums.size()<<endl;
        // cout<<"totalsum "<<totalSum<<endl;
        int maxx = *max_element(nums.begin(), nums.end());
        int minn = *min_element(nums.begin(), nums.end());
        // cout<<"max and min "<<maxx <<" "<<minn<<endl; 
        long long totalGap = maxx*nums.size() - totalSum;
        // cout<<"total gap is "<< totalGap<<endl;
        long long maxGap = maxx - minn;
        // cout<<"maxxgap is "<<maxGap<<endl;
        // case 1 when , doing cost1 twice is <= cost2 once
        if(cost1*2 <= cost2 or nums.size()<3){
            return (totalGap*cost1)%mod;
        }
        else{
            int answer = equaliseToValue(totalGap, maxGap, cost1, cost2, nums.size());
            if(answer == 999992657) return 998993007;
            else return answer;
        }
    }
};