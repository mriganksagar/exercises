#include<bits/stdc++.h>
using namespace std;

class Solution {
private: 
    enum class vertex {undiscovered, discovered, processed};
    vector<vertex> vertexStatus;
    vector<int> timeStart;
    int time = 0;
    vector<vector<int>> articulationBridges;

    void initialise_state_for_articulation(int size){
        vertexStatus = vector<vertex>(size, vertex::undiscovered);
        timeStart = vector<int>(size, 0);
    }
public:

    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        //prepare graph
        vector<vector<int>> graph(n, vector<int>());
        for(auto connection: connections){
            graph[connection[0]].push_back(connection[1]);
            graph[connection[1]].push_back(connection[0]);
        }
        // preparing statuses
        initialise_state_for_articulation(n);
        
        for(int v = 0; v < n; v++){
            if(vertexStatus[v] == vertex::undiscovered){
                vertexStatus[v] = vertex::discovered;
                dfsCriticalConnectionsHelper(v, graph);
            }
        }
        return articulationBridges;
    }

    int dfsCriticalConnectionsHelper(int v, vector<vector<int>>& graph, int parent = -1){
        timeStart[v] = ++time;
        int ancestor = v;
        int outbound = 0;
        for(int neighbor: graph[v]){        
            if(vertexStatus[neighbor] == vertex::discovered){
                if(neighbor != parent and timeStart[neighbor] < timeStart[ancestor]) ancestor = neighbor;
            }
            else {
                outbound++;
                vertexStatus[neighbor] = vertex::discovered;
                int kids_ancestor = dfsCriticalConnectionsHelper(neighbor, graph, v);
                if(timeStart[kids_ancestor] < timeStart[ancestor]) ancestor = kids_ancestor;
            }
        }
        if(ancestor == v and parent != -1){
            articulationBridges.push_back({v, parent});
        }
        return ancestor;
    }
};
