#include <bits/stdc++.h>
using namespace std;

int dfs(vector<int>& discovered, vector<int>& time_entry, const vector<int> & dishes, int vertex, int size, int& time){
    discovered[vertex] =1;
    time_entry[vertex] = ++time;
    
    int next = (vertex+dishes[vertex]+1)%size;
    int ans;
    if(discovered[next]==0){
        ans = dfs(discovered,time_entry, dishes, next, size, time);
    }
    else if(discovered[next]==1){
        ans = time_entry[vertex] - time_entry[next]+1;
    }
    else ans = 0; // because if that next vertext was already processed it means it has already provided its answer
    discovered[vertex] = 2;
    return ans;
}

int tastydishes(const vector<int>& dishes ){
    vector<int> discovered(dishes.size(), 0);
    vector<int> time_entry(dishes.size(), 0);
    int answers = 0;
    
    for(int i = 0; i < dishes.size(); i++){
        if(discovered[i] == 0){
            int time = 0;
            answers += dfs(discovered, time_entry, dishes,i, dishes.size(), time);
        }
    }
    return answers;
}

int main() {
    int testcases;
    cin>>testcases;
    
    for(int i =0; i < testcases; i++){
        int size;
        cin>>size;
        vector<int> dishes;
        for(int j=0; j < size; j++){
            int val;
            cin>>val;
            dishes.push_back(val);
        }
        cout<<tastydishes(dishes)<<endl;
    }
}