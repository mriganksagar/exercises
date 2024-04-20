#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <unordered_set>
#include <stack>
#include <boost/algorithm/string.hpp>

using namespace std;
class Graph
{
private:
    enum class vertex
    {
        undiscovered,
        discovered,
        processed
    };
    // variables needed to store graph
    int size;
    vector<vector<int>> graph;

    // data structures for storing result
    unordered_set<int> articulationVertices;
    vector<pair<int, int>> articulationBridges;
    vector<vector<pair<int, int>>> biconnectedComponents;

    // data structure and variables needed while processing
    vector<vertex> vertexStatus;
    vector<int> timeStart;
    int time = 0;
    stack<pair<int, int>> components_stack;

    void push_stack_into_biconnected_till(int parent, int v)
    {
        if (biconnectedComponents.empty() or not biconnectedComponents.back().empty())
            biconnectedComponents.emplace_back();
        while (components_stack.top() != make_pair(parent, v))
        {
            biconnectedComponents.back().push_back(components_stack.top());
            components_stack.pop();
        };
        components_stack.pop();
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
                if (neighbor != parent)
                {
                    components_stack.emplace(v, neighbor);
                    if (timeStart[neighbor] < timeStart[ancestor])
                        ancestor = neighbor;
                }
            }
            else if (vertexStatus[neighbor] == vertex::undiscovered)
            {
                outbound++;
                components_stack.emplace(v, neighbor);
                int kids_ancestor = dfsCriticalConnectionsHelper(neighbor, graph, v);
                if (timeStart[kids_ancestor] < timeStart[ancestor])
                    ancestor = kids_ancestor;
            }
            // we don't need to do anything for processed node,
            // i marked statuses processes as so i don't process a edge v to w again , when w to v comes
        }

        if (parent == -1)
        {
            // articulated root-cut node
            if (outbound > 1)
                articulationVertices.insert(v);
        }
        else if (ancestor == v)
        {
            // the bridge-cut nodes (parent and child)
            //  checking if the node is the leaf-node or not
            //  (leaf node can't be articulated cause it doesn't connect any node but only itself to the DFS tree)
            if (outbound > 0)
                articulationVertices.insert(v);
            // parent of node is also articulated, but parent shouldn't be root
            // should safe check for parent isn't -1 to avoid segmentation fault but can skip to check it as parent -1 is already checked in the if above
            if (timeStart[parent] > 1)
                articulationVertices.insert(parent);
            // in this case it is a bridge even if the parent is a root cause we are cutting edges and not the bridges
            articulationBridges.emplace_back(v, parent);
            // now to push the bi-connected components we push from components stack
            push_stack_into_biconnected_till(parent, v);
        }
        else if (ancestor == parent and timeStart[parent] > 1)
        {
            // this will mean a parent cut node and the parent is not the root
            articulationVertices.insert(parent);
        }
        vertexStatus[v] = vertex::processed;
        return ancestor;
    }

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

    void printEdges()
    {
        cout << "Printing Edges of Graph" << endl;
        cout << "Number of vertices are " << size << endl;
        for (int index = 0; index < graph.size(); index++)
        {
            for (auto v : graph[index])
            {
                cout << index << " " << v << endl;
            }
        }
        cout << "==============================" << endl;
    }

    void criticalConnections()
    {
        for (int v = 0; v < size; v++)
        {
            // resetting time
            time = 0;
            // resetting stack
            while (!components_stack.empty())
                components_stack.pop();
            if (vertexStatus[v] == vertex::undiscovered)
            {
                // pushing imaginary edge towards v into stack
                components_stack.emplace(-1, v);
                dfsCriticalConnectionsHelper(v, graph);
                push_stack_into_biconnected_till(-1, v);
            }
        }
    }

    unordered_set<int> get_articulation_vertices(bool print = false)
    {
        if (print)
        {
            cout << endl
                 << "=========================================================" << endl;
            cout << "Here are the articulation vertices" << endl;
            for (auto arti : articulationVertices)
            {
                cout << arti << endl;
            }
        }
        return articulationVertices;
    }

    vector<pair<int, int>> get_bridges(bool print = false)
    {
        if (print)
        {
            cout << endl
                 << "=========================================================" << endl;
            cout << "Here are the articulation bridges" << endl;
            for (auto bridge : articulationBridges)
            {
                cout << bridge.first << " " << bridge.second << endl;
            }
        }
        return articulationBridges;
    }

    vector<vector<pair<int, int>>> get_biconnected_components(bool print = false)
    {
        if (print)
        {
            cout << endl
                 << "=========================================================" << endl;
            cout << "Here are the biconnected components" << endl;

            for (auto biconnectedComponent : biconnectedComponents)
            {
                cout << "component -----------------------------" << endl;
                for (auto p : biconnectedComponent)
                {
                    cout << p.first << " - " << p.second << endl;
                }
            }
        }
        return biconnectedComponents;
    }
};

int main()
{
    string s;
    int size;
    cout << "Enter the number of vertices: ";
    getline(cin, s);
    boost::trim(s);
    size = stoi(s);
    vector<vector<int>> edges;
    cout << "Enter the edges in format: a b " << endl;

    while (true)
    {
        vector<string> tokens;
        getline(cin, s);
        boost::trim(s);
        boost::split(tokens, s, boost::is_any_of(" "), boost::token_compress_on);
        if (tokens.size() != 2)
            break;
        edges.push_back({stoi(tokens[0]), stoi(tokens[1])});
    }
    Graph graph = Graph(size, edges);

    graph.criticalConnections();
    graph.get_articulation_vertices(true);
    graph.get_bridges(true);
    graph.get_biconnected_components(true);
    return 0;
}
