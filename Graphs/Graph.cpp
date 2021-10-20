#include "Graph.h"

// ==============================================================
// Private Functions Start

// Utility function to get the edges stored in the vector
void Graph::getEdges(vector<Edge> &edges) {
    for (int u = 0; u < V; ++u) {
        for (const auto &p : g[u]) {
            int v = p.first, w = p.second;
            edges.push_back(Edge(u, v, w));
        }
    }
}

// Utility function to print an edge
void Graph::printEdge(int u, int v) {
    if (directed) {
        cout << u << " --> " << v;
    } else {
        cout << u << " <--> " << v;
    }
    if (weighted) {
        cout << " : " << g[u][v];
    }
}

// Utility function to print the edges along with their types
void Graph::printEdgeTypesUtil(int u, vector<int> &color, vector<int> &tIn, vector<int> &tOut, int &time, map<pair<int, int>, string> &result) {
    tIn[u] = ++time;
    color[u] = 1;  // Grey colored
    for (const auto &p : g[u]) {
        int v = p.first;
        if (color[v] == 0) {
            result[make_pair(u, v)] = "Tree Edge";
            printEdgeTypesUtil(v, color, tIn, tOut, time, result);
        } else if (color[v] == 1) {
            result[make_pair(u, v)] = "Back Edge";
        } else {
            if (tIn[u] < tIn[v]) {
                result[make_pair(u, v)] = "Forward Edge";
            } else {
                result[make_pair(u, v)] = "Cross Edge";
            }
        }
    }
    color[u] = 2;
    tOut[u] = ++time;
}

// Utility function to perform DFS
void Graph::DFSUtil(int u, vector<bool> &visited) {
    cout << u << " ";
    visited[u] = true;
    for (const auto &p : g[u]) {
        int v = p.first;
        if (!visited[v]) {
            DFSUtil(v, visited);
        }
    }
}

// Utility function to perform BFS
void Graph::BFSUtil(int u, vector<bool> &visited) {
    visited[u] = true;
    queue<int> q;
    q.push(u);
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        cout << curr << " ";
        for (const auto &p : g[curr]) {
            int v = p.first;
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

// Utility function to print Topological Sort Order using DFS
void Graph::DFSTopologicalSortUtil(int u, vector<bool> &visited, stack<int> &result) {
    visited[u] = true;
    for (const auto &p : g[u]) {
        int v = p.first;
        if (!visited[v]) {
            DFSTopologicalSortUtil(v, visited, result);
        }
    }
    result.push(u);
}

// Utility function to print all the Topological Sort Orders
void Graph::allTopologicalSortUtil(vector<int> &result, vector<bool> &visited, vector<int> &indegree) {
    bool flag = false;
    for (int u = 0; u < V; ++u) {
        if (indegree[u] == 0 && !visited[u]) {
            for (const auto &p : g[u]) {
                int v = p.first;
                --indegree[v];
            }
            result.push_back(u);
            visited[u] = true;
            allTopologicalSortUtil(result, visited, indegree);
            visited[u] = false;
            result.pop_back();
            for (const auto &p : g[u]) {
                int v = p.first;
                ++indegree[v];
            }
            flag = true;
        }
    }
    if (!flag) {
        for (const auto &i : result) {
            cout << i << " ";
        }
        cout << endl;
    }
}

// Utility function to print the shortest Distance and shortest path from a vertex to all the other vertices
void Graph::printShortestPathDistance(int u, const vector<int> &distance, const vector<int> &parent) {
    cout << "The shortest distance of all the vertices from vertex " << u << " is:" << endl;
    for (int v = 0; v < V; ++v) {
        if (v != u) {
            cout << "Vertex " << v << ":" << endl;
            if (distance[v] == INT_MAX) {
                cout << "The vertex " << v << " is not reachable from the vertex " << u;
            } else {
                cout << "Shortest distance: " << distance[v] << endl;
                cout << "The shortest path is: ";
                int curr = v;
                vector<int> path;
                while (curr != -1) {
                    path.push_back(curr);
                    curr = parent[curr];
                }
                for (int i = path.size() - 1; i >= 0; --i) {
                    cout << path[i] << " ";
                }
            }
            cout << endl;
        }
    }
}

// Utility function to perform the find operation on Disjoint Sets
int Graph::find(int u, vector<int> &parent) {
    if (parent[u] == u) {
        return u;
    }
    return parent[u] = find(parent[u], parent);
}

// Utility function to perform the union operation on Disjoint Sets
void Graph::unionSet(int u, int v, vector<int> &parent, vector<int> &rank) {
    u = find(u, parent);
    v = find(v, parent);
    if (u != v) {
        if (rank[u] < rank[v]) {
            swap(u, v);
        }
        parent[v] = u;
        if (rank[v] == rank[u]) {
            ++rank[u];
        }
    }
}

// Utility function to print all the Articulation points
void Graph::printArticulationPointsUtil(int u, vector<bool> &visited, vector<int> &tIn, vector<int> &low, int &time, int p = -1) {
    visited[u] = true;
    tIn[u] = low[u] = time++;
    int children = 0;
    for (const auto &t : g[u]) {
        int v = t.first;
        if (v == p) {
            continue;
        } else if (visited[v]) {
            low[u] = min(low[u], tIn[v]);
        } else {
            printArticulationPointsUtil(v, visited, tIn, low, time, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= tIn[u] && p != -1) {
                cout << u << " ";
            }
            ++children;
        }
    }
    if (p == -1 && children > 1) {
        cout << u << " ";
    }
}

// Utility function to print all the Bridges
void Graph::printBridgesUtil(int u, vector<bool> &visited, vector<int> &tIn, vector<int> &low, int &time, vector<pair<int, int>> &result, int p = -1) {
    visited[u] = true;
    tIn[u] = low[u] = time++;
    for (auto const &t : g[u]) {
        int v = t.first;
        if (v == p) {
            continue;
        } else if (visited[v]) {
            low[u] = min(low[u], tIn[v]);
        } else {
            printBridgesUtil(v, visited, tIn, low, time, result, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > tIn[u]) {
                result.push_back(make_pair(u, v));
            }
        }
    }
}

// Utility function to get the reversed graph
void Graph::getReversedGraph(vector<map<int, int>> &gr) {
    gr.assign(V, map<int, int>());
    for (int u = 0; u < V; ++u) {
        for (const auto &p : g[u]) {
            int v = p.first, w = p.second;
            gr[v][u] = w;
        }
    }
}

// Utility function to print all the Strongly Connected Components(SCCs)
void Graph::printSCCsUtil(const vector<map<int, int>> &gr, int u, vector<bool> &visited, vector<int> &component) {
    visited[u] = true;
    component.push_back(u);
    for (const auto &p : gr[u]) {
        int v = p.first;
        if (!visited[v]) {
            printSCCsUtil(gr, v, visited, component);
        }
    }
}

// Utility function to print all the Biconnected Components of the graph
void Graph::printBiconnectedComponentsUtil(int u, vector<bool> &visited, vector<int> &tIn, vector<int> &low, int &time, stack<Edge> &result, int p = -1) {
    tIn[u] = low[u] = time++;
    visited[u] = true;
    int children = 0;
    for (const auto &t : g[u]) {
        int v = t.first;
        if (!visited[v]) {
            ++children;
            result.push(Edge(u, v, g[u][v]));
            printBiconnectedComponentsUtil(v, visited, tIn, low, time, result, u);
            low[u] = min(low[u], low[v]);
            if ((p == -1 && children > 1) || (p != -1 && low[v] >= tIn[u])) {
                while (result.top().u != u || result.top().v != v) {
                    printEdge(result.top().u, result.top().v);
                    cout << endl;
                    result.pop();
                }
                printEdge(result.top().u, result.top().v);
                cout << endl
                     << endl;
                result.pop();
            }
        } else if (p != v && tIn[v] < low[u]) {
            low[u] = tIn[v];
            result.push(Edge(u, v, g[u][v]));
        }
    }
}

// Utility function to check if the graph is Bipartite or not
bool Graph::isBipartiteUtil(int u, vector<int> &color, const vector<map<int, int>> &g) {
    queue<int> q;
    q.push(u);
    color[u] = 1;
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        for (const auto &p : g[curr]) {
            int v = p.first;
            if (v == curr) {
                return false;
            }
            if (color[v] == -1) {
                color[v] = 1 - color[curr];
                q.push(v);
            } else if (color[v] == color[curr]) {
                return false;
            }
        }
    }
    return true;
}

// Private Functions End
// ==============================================================

// ==============================================================
// Public Functions Start

// Constructors
Graph::Graph()
    : Graph(0, false, {}) {
    cout << "Enter the number of vertices of the Graph: ";
    cin >> V;
    g.assign(V, map<int, int>());
    cout << "Is the graph directed (Y/N): ";
    char isDirected = '\0';
    cin >> isDirected;
    isDirected = tolower(isDirected);
    directed = (isDirected == 'y');
    cout << "Is the graph weighted (Y/N): ";
    char isWeighted = '\0';
    cin >> isWeighted;
    isWeighted = tolower(isWeighted);
    weighted = (isWeighted == 'y');
    cout << "Enter the number of edges of the graph: ";
    cin >> E;
    for (int i = 0; i < E; ++i) {
        int u = 0, v = 0, w = 1;
        if (weighted) {
            cout << "Enter the source, sink and weight of Edge " << i + 1 << " separated by spaces: ";
            cin >> u >> v >> w;
        } else {
            cout << "Enter the source and sink of Edge " << i + 1 << " separated by spaces: ";
            cin >> u >> v;
        }
        g[u][v] = w;
        if (!directed) {
            g[v][u] = w;
        }
    }
}

Graph::Graph(int V, bool directed, initializer_list<initializer_list<int>> list)
    : V{V}, E{0}, directed{directed}, weighted{false}, g{} {
    E = list.size();
    weighted = ((*(list.begin())).size() == 3);
    g.assign(V, map<int, int>());
    for (const auto &i : list) {
        int u = 0, v = 0, w = 1;
        auto it = i.begin();
        if (weighted) {
            u = *it;
            v = *(it + 1);
            w = *(it + 2);
        } else {
            u = *it;
            v = *(it + 1);
        }
        g[u][v] = w;
        if (!directed) {
            g[v][u] = w;
        }
    }
}

// Destructor
Graph::~Graph() {
}

// Function to add an edge to the graph
void Graph::addEdge(int u, int v, int w = 1) {
    g[u][v] = w;
    if (!directed) {
        g[v][u] = w;
    }
}

// Function to delete an edge from the graph
void Graph::deleteEdge(int u, int v) {
    if (g[u].count(v) != 0) {
        g[u].erase(v);
        if (!directed) {
            g[v].erase(u);
        }
    }
}

// Function to delete vertex from the graph
void Graph::deleteVertex(int u) {
    if (u >= V) {
        return;
    }
    g[u].clear();
    for (int i = 0; i < V; ++i) {
        if (i != u && g[i].count(u) != 0) {
            g[i].erase(u);
        }
    }
}

// Function to print all the edges
void Graph::printEdges() {
    cout << "The Edges are: " << endl;
    for (int u = 0; u < V; ++u) {
        for (const auto &p : g[u]) {
            int v = p.first;
            if (directed || u < v) {
                printEdge(u, v);
                cout << endl;
            }
        }
    }
}

// Function to print all the edges along with their types
void Graph::printEdgeTypes() {
    vector<int> color(V, 0);
    vector<int> tIn(V, 0);
    vector<int> tOut(V, 0);
    map<pair<int, int>, string> result;
    int time = 0;
    cout << "The Edges are: " << endl;
    for (int u = 0; u < V; ++u) {
        if (color[u] == 0) {
            printEdgeTypesUtil(u, color, tIn, tOut, time, result);
        }
    }
    for (const auto &p : result) {
        int u = p.first.first, v = p.first.second;
        if (directed || u < v) {
            printEdge(u, v);
            cout << " : " << p.second << endl;
        }
    }
}

// Function to perform DFS from a given starting vertex
void Graph::DFS(int u) {
    cout << "DFS starting with " << u << ": ";
    vector<bool> visited(V, false);
    DFSUtil(u, visited);
    cout << endl;
}

// Function to perform clTabCtrlDFS from 0 vertex
void Graph::DFS() {
    cout << "DFS: ";
    vector<bool> visited(V, false);
    for (int u = 0; u < V; ++u) {
        if (!visited[u]) {
            DFSUtil(u, visited);
        }
    }
    cout << endl;
}

// Function to perform BFS from a given starting vertex
void Graph::BFS(int u) {
    cout << "BFS starting with " << u << ": ";
    vector<bool> visited(V, false);
    BFSUtil(u, visited);
    cout << endl;
}

// Function to perform BFS from 0 vertex
void Graph::BFS() {
    cout << "BFS: ";
    vector<bool> visited(V, false);
    for (int u = 0; u < V; ++u) {
        if (!visited[u]) {
            BFSUtil(u, visited);
        }
    }
    cout << endl;
}

// Function to evaluate in-degree of all the vertices and store it in a vector
void Graph::evaluateIndegree(vector<int> &indegree) {
    for (int u = 0; u < V; ++u) {
        for (const auto &p : g[u]) {
            int v = p.first;
            ++indegree[v];
        }
    }
}

// Function to print Topological Sort Order found using Kahn's Algorithm
void Graph::KahnsTopologicalSort() {
    if (!directed) {
        cout << "The Graph is not directed..." << endl;
        return;
    }
    vector<int> indegree(V, 0);
    evaluateIndegree(indegree);
    queue<int> q;
    for (int u = 0; u < V; ++u) {
        if (indegree[u] == 0) {
            q.push(u);
        }
    }
    int count = 0;
    vector<int> result;
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        ++count;
        result.push_back(curr);
        for (const auto &p : g[curr]) {
            int v = p.first;
            if (--indegree[v] == 0) {
                q.push(v);
            }
        }
    }
    if (count == V) {
        cout << "Kahn's Topological Sort Order: ";
        for (const auto &i : result) {
            cout << i << " ";
        }
        cout << endl;
    } else {
        cout << "The Graph contains Cycle..." << endl;
    }
}

// Function to print Topological Sort Order found using DFS
void Graph::DFSTopologicalSort() {
    if (!directed) {
        cout << "The Graph is not directed..." << endl;
    }
    vector<bool> visited(V, false);
    stack<int> result;
    for (int u = 0; u < V; ++u) {
        if (!visited[u]) {
            DFSTopologicalSortUtil(u, visited, result);
        }
    }
    while (!result.empty()) {
        cout << result.top() << " ";
        result.pop();
    }
    cout << endl;
}

// Function to print all Topological Sort Orders
void Graph::allTopologicalSort() {
    if (!directed) {
        cout << "The graph is not directed..." << endl;
    }
    vector<bool> visited(V, false);
    vector<int> indegree(V, 0);
    evaluateIndegree(indegree);
    vector<int> result;
    cout << "All Topological Sort Orders:" << endl;
    allTopologicalSortUtil(result, visited, indegree);
}

// Function to print Hamiltonian Path in the graph if it exists
void Graph::printHamiltonianPath() {
    if (!directed) {
        cout << "The graph is not directed..." << endl;
        return;
    }
    vector<int> indegree(V, 0);
    evaluateIndegree(indegree);
    queue<int> q;
    for (int u = 0; u < V; ++u) {
        if (indegree[u] == 0) {
            q.push(u);
        }
    }
    int count = 0;
    vector<int> result;
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        ++count;
        result.push_back(curr);
        for (const auto &p : g[curr]) {
            int v = p.first;
            if (--indegree[v] == 0) {
                q.push(v);
            }
        }
    }
    if (count == V) {
        bool hasPath = true;
        for (int i = 0; i < result.size() - 1; ++i) {
            int u = result[i], v = result[i + 1];
            if (g[u].count(v) == 0) {
                hasPath = false;
                break;
            }
        }
        if (hasPath) {
            cout << "Hamiltonian Path: ";
            for (const auto &i : result) {
                cout << i << " ";
            }
            cout << endl;
        } else {
            cout << "No Hamiltonian Path exists..." << endl;
        }
    } else {
        cout << "Graph contains a cycle..." << endl;
    }
}

// Shortest Path Finding Algorithms
void Graph::shortestPathUnweighted(int u) {
    vector<int> distance(V, INT_MAX);
    vector<int> parent(V, -1);
    vector<bool> visited(V, false);
    distance[u] = 0;
    visited[u] = true;
    queue<int> q;
    q.push(u);
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        for (const auto &p : g[curr]) {
            int v = p.first;
            if (!visited[v]) {
                distance[v] = distance[curr] + 1;
                parent[v] = curr;
                visited[v] = true;
                q.push(v);
            }
        }
    }
    printShortestPathDistance(u, distance, parent);
}

void Graph::Dijkstra(int u) {
    vector<int> distance(V, INT_MAX);
    vector<int> parent(V, -1);
    vector<bool> visited(V, false);
    distance[u] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(0, u));
    int count = 0;
    while (!pq.empty() && count < V) {
        pair<int, int> top = pq.top();
        pq.pop();
        int curr = top.second;
        if (visited[curr]) {
            continue;
        }
        ++count;
        visited[curr] = true;
        for (const auto &p : g[curr]) {
            int v = p.first, w = p.second;
            int newDistance = distance[curr] + w;
            if (newDistance < distance[v]) {
                distance[v] = newDistance;
                parent[v] = curr;
                pq.push(make_pair(newDistance, v));
            }
        }
    }
    printShortestPathDistance(u, distance, parent);
}

void Graph::BellmanFord(int u) {
    vector<Edge> edges;
    getEdges(edges);
    vector<int> distance(V, INT_MAX);
    vector<int> parent(V, -1);
    distance[u] = 0;
    int x = 0;
    for (int i = 0; i < V; ++i) {
        x = -1;
        for (const auto &e : edges) {
            if (distance[e.u] != INT_MAX && distance[e.v] > distance[e.u] + e.w) {
                distance[e.v] = max(distance[e.u] + e.w, -INT_MAX);
                parent[e.v] = e.u;
                x = e.v;
            }
        }
    }
    cout << endl;
    if (x == -1) {
        printShortestPathDistance(u, distance, parent);
    } else {
        for (int i = 0; i < V; ++i) {
            x = parent[x];
        }
        vector<int> cycle;
        for (int curr = x;; curr = parent[curr]) {
            cycle.push_back(curr);
            if (curr == x && cycle.size() > 1) {
                break;
            }
        }
        cout << "Negative Weight Cycle: ";
        for (int i = cycle.size() - 1; i >= 0; --i) {
            cout << cycle[i] << " ";
        }
        cout << endl;
    }
}

void Graph::spfa(int u) {
    vector<int> distance(V, INT_MAX);
    vector<int> parent(V, -1);
    vector<int> count(V, 0);
    vector<bool> inQueue(V, false);
    distance[u] = 0;
    queue<int> q;
    q.push(u);
    inQueue[u] = true;
    bool flag = true;
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        inQueue[curr] = false;
        for (const auto &p : g[curr]) {
            int v = p.first, w = p.second;
            int newDistance = distance[curr] + w;
            if (newDistance < distance[v]) {
                distance[v] = newDistance;
                parent[v] = curr;
                if (!inQueue[v]) {
                    q.push(v);
                    inQueue[v] = true;
                    ++count[v];
                    if (count[v] > V) {
                        flag = false;
                        break;
                    }
                }
            }
        }
        if (!flag) {
            break;
        }
    }
    if (!flag) {
        cout << "The graph contains Negative Weight Cycle..." << endl;
    } else {
        printShortestPathDistance(u, distance, parent);
    }
}

void Graph::shortestPathDAG(int u) {
    if (!directed) {
        cout << "The Graph is not directed..." << endl;
        return;
    }
    vector<int> indegree(V, 0);
    evaluateIndegree(indegree);
    queue<int> q;
    for (int u = 0; u < V; ++u) {
        if (indegree[u] == 0) {
            q.push(u);
        }
    }
    vector<int> result;
    int count = 0;
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        ++count;
        result.push_back(curr);
        for (const auto &p : g[curr]) {
            int v = p.first;
            if (--indegree[v] == 0) {
                q.push(v);
            }
        }
    }
    if (count == V) {
        vector<int> distance(V, INT_MAX);
        vector<int> parent(V, -1);
        distance[u] = 0;
        for (int i = 0; i < result.size() - 1; ++i) {
            int curr = result[i];
            if (distance[curr] == INT_MAX) {
                continue;
            }
            for (const auto &p : g[curr]) {
                int v = p.first, w = p.second;
                int newDistance = distance[curr] + w;
                if (newDistance < distance[v]) {
                    distance[v] = newDistance;
                    parent[v] = curr;
                }
            }
        }
        printShortestPathDistance(u, distance, parent);
    } else {
        cout << "The Graph contains cycle..." << endl;
    }
}

void Graph::FloydWarshall() {
    vector<vector<int>> distance(V, vector<int>(V, INT_MAX));
    vector<vector<int>> parent(V, vector<int>(V, -1));
    for (int i = 0; i < V; ++i) {
        distance[i][i] = 0;
        parent[i][i] = i;
        for (const auto &p : g[i]) {
            int v = p.first, w = p.second;
            distance[i][v] = w;
            parent[i][v] = v;
        }
    }
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (distance[i][k] != INT_MAX && distance[k][j] != INT_MAX && distance[i][j] > distance[i][k] + distance[k][j]) {
                    distance[i][j] = distance[i][k] + distance[k][j];
                    parent[i][j] = parent[i][k];
                }
            }
        }
    }
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            for (int t = 0; t < V; ++t) {
                if (distance[i][t] != INT_MAX && distance[t][j] != INT_MAX && distance[t][t] < 0) {
                    distance[i][j] = INT_MIN;
                }
            }
        }
    }
    for (int i = 0; i < V; ++i) {
        cout << "Shortest Distance of all the vertices from vertex " << i << " is: " << endl;
        for (int j = 0; j < V; ++j) {
            if (j != i) {
                cout << "Vertex " << j << ": " << endl;
                if (distance[i][j] == INT_MAX) {
                    cout << "Vertex " << j << " is not reachable from vertex " << i << endl;
                } else if (distance[i][j] == INT_MIN) {
                    cout << "Vertex " << j << " is not reachable from vertex " << i << " due to presence of negative weight cycle." << endl;
                } else {
                    cout << "Shortest distance: " << distance[i][j] << endl;
                    cout << "The shortest path is: ";
                    vector<int> path;
                    int curr = i;
                    path.push_back(curr);
                    while (curr != j) {
                        curr = parent[curr][j];
                        path.push_back(curr);
                    }
                    for (const auto &p : path) {
                        cout << p << " ";
                    }
                    cout << endl;
                }
            }
        }
    }
}

// Minimum Spanning Tree Algorithms
void Graph::PrimsMST() {
    if (directed) {
        cout << "The graph is directed..." << endl;
        return;
    }
    vector<int> distance(V, INT_MAX);
    vector<int> parent(V, -1);
    vector<bool> visited(V, false);
    auto cmp = [](Edge x, Edge y) {
        if (x.w != y.w) {
            return x.w > y.w;
        } else if (x.u != y.u) {
            return x.u > y.u;
        } else {
            return x.v > y.v;
        }
    };
    priority_queue<Edge, vector<Edge>, decltype(cmp)> pq(cmp);
    distance[0] = 0;
    pq.push(Edge(0, -1, 0));
    int count = 0;
    while (!pq.empty() && count < V) {
        Edge e = pq.top();
        pq.pop();
        int u = e.u, p = e.v, w = e.w;
        if (visited[u]) {
            continue;
        }
        ++count;
        visited[u] = true;
        distance[u] = w;
        parent[u] = p;
        for (const auto &p : g[u]) {
            int v = p.first, d = p.second;
            if (!visited[v]) {
                pq.push(Edge(v, u, d));
            }
        }
    }
    cout << "The MST is: " << endl;
    int minCost = 0;
    for (int i = 1; i < V; ++i) {
        minCost += distance[i];
        cout << parent[i] << " - " << i << " : " << distance[i] << endl;
    }
    cout << "The cost of MST is: " << minCost << endl;
}

void Graph::KruskalsMST() {
    if (directed) {
        cout << "The graph is directed..." << endl;
        return;
    }
    auto cmp = [](Edge x, Edge y) {
        if (x.w != y.w) {
            return x.w > y.w;
        } else if (x.u != y.u) {
            return x.u > y.u;
        } else {
            return x.v > y.v;
        }
    };
    priority_queue<Edge, vector<Edge>, decltype(cmp)> pq(cmp);
    vector<int> parent(V);
    iota(parent.begin(), parent.end(), 0);
    vector<int> rank(V, 0);
    for (int u = 0; u < V; ++u) {
        for (const auto &p : g[u]) {
            int v = p.first, w = p.second;
            pq.push(Edge(u, v, w));
        }
    }
    int count = 0;
    vector<Edge> result;
    while (!pq.empty() && count < V - 1) {
        Edge e = pq.top();
        pq.pop();
        int u = e.u, v = e.v, w = e.w;
        int pu = find(u, parent), pv = find(v, parent);
        if (pu != pv) {
            unionSet(pu, pv, parent, rank);
            result.push_back(Edge(u, v, w));
            ++count;
        }
    }
    cout << "The MST is: " << endl;
    int minCost = 0;
    for (const auto &e : result) {
        minCost += e.w;
        cout << e.u << " - " << e.v << " : " << e.w << endl;
    }
    cout << "The cost of MST is: " << minCost << endl;
}

// Function to print the Articulation Points in the graph
void Graph::printArticulationPoints() {
    cout << "Articulation points are: ";
    vector<int> tIn(V, 0), low(V, 0);
    vector<bool> visited(V, false);
    int time = 0;
    for (int u = 0; u < V; ++u) {
        if (!visited[u]) {
            printArticulationPointsUtil(u, visited, tIn, low, time);
        }
    }
    cout << endl;
}

// Function to print Bridges in the graph
void Graph::printBridges() {
    cout << "The Bridges are: " << endl;
    vector<int> tIn(V, 0), low(V, 0);
    vector<bool> visited(V, false);
    int time = 0;
    vector<pair<int, int>> result;
    for (int u = 0; u < V; ++u) {
        if (!visited[u]) {
            printBridgesUtil(u, visited, tIn, low, time, result);
        }
    }
    for (const auto &p : result) {
        int u = p.first, v = p.second;
        printEdge(u, v);
        cout << endl;
    }
}

// Function to print Strongly Connected Components(SCCs)
void Graph::printSCCs() {
    cout << "Strongly Connected Components are: " << endl;
    if (!directed) {
        vector<bool> visited(V, false);
        for (int u = 0; u < V; ++u) {
            if (!visited[u]) {
                DFSUtil(u, visited);
                cout << endl;
            }
        }
        return;
    }
    vector<bool> visited(V, false);
    stack<int> result;
    for (int u = 0; u < V; ++u) {
        if (!visited[u]) {
            DFSTopologicalSortUtil(u, visited, result);
        }
    }
    vector<map<int, int>> gr;
    getReversedGraph(gr);
    visited.assign(V, false);
    while (!result.empty()) {
        int u = result.top();
        result.pop();
        if (!visited[u]) {
            vector<int> component;
            printSCCsUtil(gr, u, visited, component);
            for (const auto &i : component) {
                cout << i << " ";
            }
            cout << endl;
        }
    }
}

// Function to print Biconnected Components
void Graph::printBiconnectedComponents() {
    cout << "Biconnected Components are: " << endl;
    stack<Edge> result;
    vector<int> tIn(V, 0), low(V, 0);
    vector<bool> visited(V, false);
    int time = 0;
    for (int u = 0; u < V; ++u) {
        if (!visited[u]) {
            printBiconnectedComponentsUtil(u, visited, tIn, low, time, result);
            while (!result.empty()) {
                printEdge(result.top().u, result.top().v);
                cout << endl;
                result.pop();
            }
            cout << endl;
        }
    }
}

// Function to check if the graph is Bipartite or not
bool Graph::isBipartite() {
    vector<map<int, int>> gcpy;
    if (directed) {
        gcpy.assign(V, map<int, int>());
        for (int u = 0; u < V; ++u) {
            for (const auto &p : g[u]) {
                int v = p.first, w = p.second;
                gcpy[u][v] = w;
                gcpy[v][u] = w;
            }
        }
    }
    vector<int> color(V, -1);
    for (int u = 0; u < V; ++u) {
        if (color[u] == -1) {
            if (!directed && !isBipartiteUtil(u, color, g)) {
                return false;
            } else if (directed && !isBipartiteUtil(u, color, gcpy)) {
                return false;
            }
        }
    }
    return true;
}

// Public Functions End
// ==============================================================
