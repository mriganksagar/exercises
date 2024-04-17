#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution {
public:
    Node* cloneGraph(Node* node) {
        unordered_map<Node*,Node*> umap;
        return cloneGraphHelper(node, umap);
    }

    Node* cloneGraphHelper(Node* node, unordered_map<Node*,Node*>& umap){
        auto copiednode = new Node(node->val);
        umap.insert({node, copiednode});
        for(auto neighbor: node->neighbors){
            auto iter = umap.find(neighbor);
            auto copiedneighbor = iter != umap.end() ? iter->second:cloneGraphHelper(neighbor, umap);
            copiednode->neighbors.push_back(copiedneighbor);
        }
        return copiednode;
    }

};

int main(){

}