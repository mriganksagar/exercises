#include <bits/stdc++.h>
using namespace std;

class Solution{
    public:
    struct S{
        vector<int> distance;
        vector<int> edges;
        S(int size , int source): distance(size+1, INT_MAX){
            distance[source]= 0;
        }
        void relax(int from, int to, int weight){
            distance[to] = min(distance[to], distance[from] + weight);
        }
        int maxDistance(){
            return *max_element(++distance.begin(), distance.end());
        }
    };

    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        S g(n, k);
        for(int i = 1; i < n; i++){
            for(auto edge: times){
                g.relax(edge[0], edge[1], edge[2]);
            }
        }
        return g.maxDistance();
    }
};

int main(){

}