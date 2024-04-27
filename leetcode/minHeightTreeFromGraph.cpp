//https://leetcode.com/problems/minimum-height-trees
// given a graph with no cycle, obviously it can be thought of as a tree, now give the list of nodes which when thought of as root nodes and the tree is made, the height of such tree is minimum.
#include<vector>
#include<iostream>
#include<cmath>
#include<queue>
#include<unordered_set>
using namespace std;


class Solution {
public:
    vector<int> height;
    void findHeightForEachNode(const vector<vector<int>>& tree, int parent = -1, int current = 0){
        int maxHeight = 0;
        for(auto child: tree[current]){
            if(child != parent){
                findHeightForEachNode(tree, current, child);
                maxHeight = max(maxHeight, height[child]);
            }
        }
        height[current] = maxHeight+1;
    }

    void findMinHeightTreesHelper(const vector<vector<int>>& tree, vector<int>& result, int radius = 0, int parent = -1, int current = 0 ){
        for(auto child: tree[current]){
            if(child==parent) continue;
            int otherChildHeight = 0;
            for(auto otherChild: tree[current]){
                if(otherChild != parent and otherChild != child and height[otherChild] > otherChildHeight) otherChildHeight = height[otherChild];
            }
            int radiusForChild = max(radius, otherChildHeight)+1;
            findMinHeightTreesHelper(tree, result, radiusForChild, current, child);
        }

        int max1 = 0;
        int max2 = 0;
        for(auto child: tree[current]){
            if(child != parent){
                if(height[child] > max1){
                    max2 = max1;
                    max1 = height[child];
                }
                else if(height[child] > max2){
                    max2 = height[child];
                }
            }
        }
        max2 = max(max2, radius);
        if(max1 == max2 or max1 == max2+1 or max1+1 == max2){
            result.push_back(current);
        }
    }

    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        // lets create a graph// tree
        vector<vector<int>> tree(n, vector<int>());
        for( auto& edge: edges){
            tree[edge[0]].push_back(edge[1]);
            tree[edge[1]].push_back(edge[0]);
        }
        height.resize(n, -1);
        // first find the height of every node , by constructing the tree from a random node , node 1 lets say
        findHeightForEachNode(tree);
        vector<int> result;
        findMinHeightTreesHelper(tree, result);
        return result;
    }

    // this method is slow
    // i can do better i remove all the leaf nodes at a time, and reduce the degrees (the number of node a node is connected to ) and continue to do so for the new nodes 

    // my solution was failing for the case where there is only single node
    // thats why put the if (n == 1 ) condition in the start so commenting this
    // though i can avoid it if i just add a node to the leaf node if its degree <= 1 instead of degree == 1 (as done before) 
    vector<int> findMinHeightTreesNew(int n, vector<vector<int>>& edges){
        // if(n == 1) return {0};
        vector<vector<int>> graph(n, vector<int>() );
        for(auto edge:edges){
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        vector<int> degrees(n,0);
        for(auto edge: edges){
            degrees[edge[0]]++;
            degrees[edge[1]]++;
        }
        int nodesInTree = n;
        unordered_set<int> leafnodes;
        for(int node = 0; node < n; node++){
            if(degrees[node] <= 1){
                leafnodes.insert(node);
            }
        }

        while(nodesInTree>2){
            unordered_set<int> nextLeafnodes;
            for(auto leafnode: leafnodes){
                nodesInTree--;
                for(auto neighbour: graph[leafnode]) {
                    if(degrees[neighbour] == 0) continue;
                    degrees[neighbour]--;
                    if(degrees[neighbour] == 1) nextLeafnodes.insert(neighbour);
                }
                degrees[leafnode] = 0;
            }
            leafnodes = nextLeafnodes;
        }            
        return vector<int>(leafnodes.begin(), leafnodes.end());
    }
};

// using queue instead of unordered map (not much difference in performance though)
class Solution2 {
public:
 vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges){
        if(n == 1) return {0};
        if(n == 2) return {0,1};
        vector<vector<int>> graph(n, vector<int>() );
        for(auto edge:edges){
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        vector<int> degrees(n,0);
        for(auto edge: edges){
            degrees[edge[0]]++;
            degrees[edge[1]]++;
        }
        int nodesInTree = n;
        // unordered_set<int> leafnodes;
        queue<int> leafnodes;
        for(int node = 0; node < n; node++){
            if(degrees[node] <= 1){
                leafnodes.push(node);
            }
        }
        leafnodes.push(-1);
        while(true ){
            int leafnode = leafnodes.front();
            leafnodes.pop();
            if(leafnode == -1){
                if(nodesInTree <= 2) break;
                else {
                    leafnodes.push(-1);
                    continue;
                }
            }
            nodesInTree--;
            for(auto neighbour: graph[leafnode]) {
                if(degrees[neighbour] == 0) continue;
                degrees[neighbour]--;
                if(degrees[neighbour] == 1) leafnodes.push(neighbour);
            }
            degrees[leafnode] = 0;
        }          
        vector<int> result;
        while(!leafnodes.empty()) {
            result.push_back(leafnodes.front());
            leafnodes.pop();
        }
        return result;
    }
};