#include <iostream>
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>
class Graph
{

private:
    enum class vertex
    {
        undiscovered,
        discovered,
        processed
    };
    int size;
    vector<vector<int>> graph;
    vector<vertex> vertexStatus;
    vector<int> ancestors;
    vector<int> parents;
    vector<int> outdegree;
    vector<int> timeStart;
    vector<int> timeEnd;
    int time = 0;

    vector<int> articulationVertices;
    vector<pair<int, int>> articulationBridges;

public:
    Graph(int n, vector<vector<int>> &connections) : graph(vector<vector<int>>(n, vector<int>())), size(n),
                                                     vertexStatus(vector<vertex>(n, vertex::undiscovered)),
                                                     timeStart(vector<int>(n, 0))
    {
        for (auto connection : connections)
        {
            graph[connection[0]].push_back(connection[1]);
            graph[connection[1]].push_back(connection[0]);
        }
    }

    void printEdges(){
        cout<<"Printing Edges of Graph"<<endl;
        cout<<"Number of vertices are "<<size<<endl;
        for(auto edge: graph){
            cout<<edge[0]<<" "<<edge[1]<<endl;
        }
        cout<<"=============================="<<endl;
    }

    vector<pair<int, int>> criticalConnections()
    {
        for (int v = 0; v < size; v++)
        {
            if (vertexStatus[v] == vertex::undiscovered)
                dfsCriticalConnectionsHelper(v, graph);
        }
        return articulationBridges;
    }

    int dfsCriticalConnectionsHelper(int v, vector<vector<int>> &graph, int parent = -1)
    {
        vertexStatus[v] = vertex::discovered;
        timeStart[v] = ++time;

        int ancestor = v;
        int outbound = 0;

        for (int neighbor : graph[v])
        {
            if (vertexStatus[neighbor] == vertex::discovered)
            {
                if (neighbor != parent and timeStart[neighbor] < timeStart[ancestor])
                    ancestor = neighbor;
            }
            else
            {
                outbound++;
                int kids_ancestor = dfsCriticalConnectionsHelper(neighbor, graph, v);
                if (timeStart[kids_ancestor] < timeStart[ancestor])
                    ancestor = kids_ancestor;
            }
        }

        if (parent == -1)
        {
            // articulated root-cut node
            if (outbound > 1)
                articulationVertices.push_back(v);
        }
        else if (ancestor == v)
        {
            // it means it is the bridge-cut node (child one)
            //  checking if the node is the leaf-node or not
            //  (leaf node can't be articulated cause it doesn't connect any node but only itself to the DFS tree)
            if (outbound > 0)
            {
                articulationVertices.push_back(v);
            }
            // check the parent of node to be articulated or not
            // if the parent is root node then it can't be articulated, otherwise it is articulated, cause
            // cutting it doesn't connect any node but the subtree to itself,
            // if there are more children to the root node then it is different case and already handled in the if clause before
            // should check for parent isn't -1 to avoid segmentation fault but can skip it as parent -1 is already checked in the if above
            if (timeStart[parent] > 1)
            {
                // means parent is not root node
                articulationVertices.push_back(parent);
            }
            // in this case it is a bridge even if the parent is a root cause we are cutting edges and not the bridges
            articulationBridges.emplace_back(v, parent);
        }
        else if (ancestor == parent and timeStart[parent] > 1)
        {
            // this will mean a parent cut node and the parent is not the root
            articulationVertices.push_back(parent);
        }
        return ancestor;
    }
};

int main()
{   
    int size;
    cout<<"Enter the number of vertices: ";
    cin>>size;
    vector<vector<int>> edges;
    edges.reserve(10);
    string s;
    cout<<"Enter the edges in format: a b "<<endl;
    while(true){
        getline(cin, s);

        if(!a.empty() and !b.empty()) break;
        edges.push_back({stoi(a),stoi(b)});
    }
    Graph graph = Graph(size, edges);
    graph.printEdges();
}
