//https://leetcode.com/problems/minimum-height-trees
// given a graph with no cycle, obviously it can be thought of as a tree, now give the list of nodes which when thought of as root nodes and the tree is made, the height of such tree is minimum.
#include<vector>
#include<iostream>
#include<cmath>
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
};