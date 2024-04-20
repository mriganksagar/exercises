#include <bits/stdc++.h>
using namespace std;

//bessie the cow who wants to wander , the problem
class Graph
{
private:
    template <typename T1, typename T2>
    size_t hash_int_pair(const pair<T1, T2> &p)
    {
        string s = to_string(p.first) + to_string(p.second);
        return hash<string>{}(s);
    }
    typedef unordered_set<pair<int, int>, decltype(&hash_int_pair<int, int>)> PairSet;

    enum status
    {
        undiscovered,
        discovered,
        processed
    };
    int size;
    // int number_of_edges;
    vector<vector<int>> adjacency_list;

    void dfs_scc(int vertex, vector<int> &scc, vector<status> &vertex_status, vector<int> &low_time, stack<int> &current_component, int &time, int &component_number)
    {
        vertex_status[vertex] = status::discovered;
        int entry_time = low_time[vertex] = ++time;
        current_component.push(vertex);
        for (int kid : adjacency_list[vertex])
        {
            if (vertex_status[kid] == status::undiscovered)
            {
                dfs_scc(kid, scc, vertex_status, low_time, current_component, time, component_number);
            }
            // in fact i dont' need to check any if, just check if kid scc is -1 and update lowtime
            if (scc[kid] == -1)
            {
                low_time[vertex] = min(low_time[vertex], low_time[kid]);
            }
        }
        if (low_time[vertex] == entry_time)
        {
            component_number++;
            while (current_component.top() != vertex)
            {
                scc[current_component.top()] = component_number;
                current_component.pop();
            }
            scc[current_component.top()] = component_number;
            current_component.pop();
        }
        vertex_status[vertex] = status::processed;
    }

    void dfs_condenser(int vertex, vector<int> &scc, vector<status> &vertex_status, PairSet &edges)
    {
        vertex_status[vertex] = status::discovered;
        for (auto kid : adjacency_list[vertex])
        {
            if (vertex_status[kid] == status::undiscovered)
            {
                dfs_condenser(kid, scc, vertex_status, edges);
            }
            if (scc[kid] != scc[vertex])
            {
                edges.emplace(vertex, kid);
            }
        }
    }

    void dfs_topological(int vertex, vector<status>&discovered, stack<int>& st){
        discovered[vertex] = status::discovered;
        for(auto x: adjacency_list[vertex]){
            if(discovered[x] == status::undiscovered){
                dfs_topological(x, discovered, st);
            }
        }
        st.push(vertex);
    }

public:
    Graph(const vector<pair<int, int>> &edges, int vertices_number) : size(vertices_number), adjacency_list(vector<vector<int>>(vertices_number))
    {
        for (auto p : edges)
        {
            adjacency_list[p.first].emplace_back(p.second);
        }
    }

    vector<vector<int>> getAdjacencyList(){
        return adjacency_list;
    }
    vector<int> topologicalSort(){
        // it only works for dag, no way to check if graph is not dag upon calling this method
        vector<status> discovered(size, status::undiscovered);
        stack<int> st;
        vector<int> sorted_vertices;
        sorted_vertices.reserve(size);
        for(int v = 0; v < size; v++){
            if(discovered[v] == status::undiscovered){
                dfs_topological(v, discovered, st);
                while(!st.empty()){
                    sorted_vertices.push_back(st.top());
                    st.pop();
                }
            }
        }
        return sorted_vertices;
    }

    tuple<vector<int>, int, vector<int>, vector<pair<int,int>>  > strongDAG(vector<int>& components_weight)
    {
        vector<int> scc(size, -1);
        vector<int> low_time(size);
        vector<status> vertex_status(size, status::undiscovered);
        stack<int> current_component;

        int time = 0;
        int component_number = -1; // first component will be number 0
        for (int i = 0; i < size; i++)
        {
            if (vertex_status[i] == status::undiscovered)
            {
                dfs_scc(i, scc, vertex_status, low_time, current_component, time, component_number);
            }
        }
        // clear structures not to be used anymore
        low_time.clear();
        // count number of vertices in scc condensed dag and their weight
        int number_of_components = 0;
        components_weight.reserve(size / 10);
        for (int i = 0; i < size; i++)
        {
            int comp = scc[i];
            if (components_weight.size() < comp+1)
            {
                components_weight.resize(comp+1, -1);
            }
            if (components_weight[comp] == -1)
            {
                number_of_components++;
                components_weight[comp] = 1;
            }
            else
            {
                components_weight[comp]++;
            }
        }
        // find edges of scc condensed dag
        PairSet scc_condensed_edges_set;
        vertex_status = vector<status>(size, status::undiscovered);
        for (int i = 0; i < size; i++)
        {
            if (vertex_status[i] == status::undiscovered)
            {
                dfs_condenser(i, scc, vertex_status, scc_condensed_edges_set);
            }
        }
        vector<pair<int, int>> scc_condensed_edges(scc_condensed_edges_set.begin(), scc_condensed_edges_set.end());
        return make_tuple(scc,number_of_components, components_weight, scc_condensed_edges);
    }
};

Graph *makeGraph(vector<pair<int, int>> &edges, int vertices_number, int edges_number)
{
    return new Graph(edges, vertices_number);
}

Graph *takeGraphInput(Graph *(*callback)(vector<pair<int, int>> &edges, int vertices_number, int edges_number))
{
    int number_of_vertices, number_of_edges;
    // cout << "vertices and edges: " << endl;
    cin >> number_of_vertices >> number_of_edges;
    number_of_vertices++; //due to starting from 1
    vector<pair<int, int>> edges;
    int v, u;
    for (int i = 0; i < number_of_edges; i++)
    {
        cin >> v >> u;
        edges.emplace_back(v, u);
    }
    return callback(edges, number_of_vertices, number_of_edges);
}

int main()
{
    Graph *graph = takeGraphInput(makeGraph);
    vector<int> components_weight;
    int rootvertex = 1;
    // cout<<"Give: the root vertex"<<endl;
    // cin>>rootvertex;
    auto scctuple = graph->strongDAG(components_weight);
    auto scc = get<0>(scctuple);
    int scc_size = get<1>(scctuple);
    auto scc_weight = get<2>(scctuple);
    auto scc_edges = get<3>(scctuple);

    vector<pair<int, int>> scc_edges_r;
    scc_edges_r.reserve(scc_edges.size());
    for(auto p : scc_edges){
        scc_edges_r.emplace_back(p.second, p.first);
    }

    Graph *dag = new Graph(scc_edges, scc_size);
    Graph *dag_r = new Graph(scc_edges_r, scc_size);

    auto top_sorted_dag = dag->topologicalSort();
    auto top_sorted_dag_r = dag_r->topologicalSort();
    
    vector<int> dp_top_sort_dag(scc_size,-1);
    vector<int> dp_top_sort_dag_r(scc_size,-1);
class Solution {
public:
    int largestComponentSize(vector<int>& nums){

    }

};


int main()
{  

}
    for(int i=0; i < scc_size; i++){   
        auto x= top_sorted_dag[i];
        for(auto y: adjacency_list_r[x]){
            if(dp_top_sort_dag[y]!= -1){
                dp_top_sort_dag[x] = max(dp_top_sort_dag[x], dp_top_sort_dag[y] + scc_weight[x]);
            }
        }
        x = top_sorted_dag_r[i];
        for(auto y: adjacency_list[x]){
            if(dp_top_sort_dag_r[y]!= -1){
                dp_top_sort_dag_r[x] = max(dp_top_sort_dag_r[x], dp_top_sort_dag_r[y] + scc_weight[x]);
            }
        }
    }

    int max_can_be_visited = 0;
    for(auto p : scc_edges_r){
        if(dp_top_sort_dag[p.first] != -1 and dp_top_sort_dag_r[p.second] != -1){
            max_can_be_visited = max(max_can_be_visited, dp_top_sort_dag[p.first]+dp_top_sort_dag_r[p.second]);
        }
    }
    return max_can_be_visited;
}