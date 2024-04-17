#include <vector>
#include <utility>
std::pair<int, int> longest_mountain_pass(const std::vector<int>& mountains, int limit) {
    if(!mountains.size()) return {0,0};
    // Your code goes here
    int l = 0, e =0;
    int energy = 0;
    int start_index = l;
    int max_length = 0;
    while(e < mountains.size()){
        if(e-l > max_length){
            max_length = e-l;
            start_index = l;
        }
        if(e == mountains.size()-1) break;
        int next = mountains[e+1];
        int current = mountains[e];
        if(current >= next){
            e++;
            continue;
        }
        else {
            if(next - current + energy <= limit){
                e++;
                energy += next - current;
            }
            else{
                l++;
                if(mountains[l-1] < mountains[l])
                    energy -= mountains[l] - mountains[l-1];
            }
        }
    }
    return {max_length+1, start_index};
}