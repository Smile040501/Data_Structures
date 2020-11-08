#ifndef _GRAPH_
#define _GRAPH_

#include<iostream>
#include<vector>
#include<map>
#include<queue>
#include<stack>
#include<climits>
#include<functional>
#include<initializer_list>
#include<string>
#include<numeric>
using namespace std;

// Graph class for representing a graph
class Graph {

private:
	
	// Edge class for representing an edge
	class Edge {
		public:
			int u, v, w;		// source, sink, weight
			// Constructor
			Edge(int u, int v, int w)
			: u{u}, v{v}, w{w} {
			}
	};
	
	// Utility function to get the edges stored in the vector
	void getEdges(vector<Edge> &edges);
	// Utility function to print an edge
	void printEdge(int u, int v);
	// Utility function to print the edges along with their types
	void printEdgeTypesUtil(int u, vector<int> &color, vector<int> &tIn, vector<int> &tOut, int &time, map<pair<int, int>, string> &result);
	
	// Utility function to perform DFS
	void DFSUtil(int u, vector<bool> &visited);
	// Utility function to perform BFS
	void BFSUtil(int u, vector<bool> &visited);
	
	// Utility function to print Topological Sort Order using DFS
	void DFSTopologicalSortUtil(int u, vector<bool> &visited, stack<int> &result);
	// Utility function to print all the Topological Sort Orders
	void allTopologicalSortUtil(vector<int> &result, vector<bool> &visited, vector<int> &indegree);
	
	// Utility function to print the shortest Distance and shortest path from a vertex to all the other vertices
	void printShortestPathDistance(int u, const vector<int> &distance, const vector<int> &parent);
	
	// Utility function to perform the find operation on Disjoint Sets
	int find(int u, vector<int> &parent);
	// Utility function to perform the union operation on Disjoint Sets
	void unionSet(int u, int v, vector<int> &parent, vector<int> &rank);
	
	// Utility function to print all the Articulation points
	void printArticulationPointsUtil(int u, vector<bool> &visited, vector<int> &tIn, vector<int> &low, int &time, int p);
	// Utility function to print all the Bridges
	void printBridgesUtil(int u, vector<bool> &visited, vector<int> &tIn, vector<int> &low, int &time, vector<pair<int, int>> &result, int p);
	
	// Utility function to get the reversed graph
	void getReversedGraph(vector<map<int, int>> &gr);
	// Utility function to print all the Strongly Connected Components(SCCs)
	void printSCCsUtil(const vector<map<int, int>> &gr, int u, vector<bool> &visited, vector<int> &component);
	
	// Utility function to print all the Biconnected Components of the graph
	void printBiconnectedComponentsUtil(int u, vector<bool> &visited, vector<int> &tIn, vector<int> &low, int &time, stack<Edge> &result, int p);
	
	// Utility function to check if the graph is Bipartite or not
	bool isBipartiteUtil(int u, vector<int> &color, const vector<map<int, int>> &g);
	
public:
	int V;		//  Number of vertices
	int E;		// Number of edges
	bool directed;		// To keep track of whether the graph is directed or not
	bool weighted;	// To keep track of whether the graph is weighted or not
	vector<map<int, int>> g;		// Adjacency List of the graph
	
	// Constructors
	Graph();		// To take graph from the user
	Graph(int V, bool directed, initializer_list<initializer_list<int>> list);		// To give graph in the required format of parameters
	
	// Destructor
	~Graph();
	
	// Function to add an edge to the graph
	void addEdge(int u, int v, int w);
	// Function to delete an edge from the graph
	void deleteEdge(int u, int v);
	// Function to delete vertex from the graph
	void deleteVertex(int u);
	// Function to print all the edges
	void printEdges();
	// Function to print all the edges along with their types
	void printEdgeTypes();
	
	// Function to perform DFS from a given starting vertex
	void DFS(int u);
	// Function to perform DFS from 0 vertex
	void DFS();
	// Function to perform BFS from a given starting vertex
	void BFS(int u);
	// Function to perform BFS from 0 vertex
	void BFS();
	
	// Function to evaluate in-degree of all the vertices and store it in a vector
	void evaluateIndegree(vector<int> &indegree);
	
	// Function to print Topological Sort Order found using Kahn's Algorithm
	void KahnsTopologicalSort();
	// Function to print Topological Sort Order found using DFS
	void DFSTopologicalSort();
	// Function to print all Topological Sort Orders
	void allTopologicalSort();
	// Function to print Hamiltonian Path in the graph if it exists
	void printHamiltonianPath();
	
	// Shortest Path Finding Algorithms
	void shortestPathUnweighted(int u);			// For unweighted graph, simple BFS
	void Dijkstra(int u);			// For graph with only +ve weights
	void BellmanFord(int u);		// For graph with both +ve and -ve weights and also print Negative Weight Cycle if present
	void spfa(int u);// For graph with both +ve and -ve weights (Shortest Path Faster Algorithm)
	void shortestPathDAG(int u);		// To find shortest path in DAG
	void FloydWarshall();		// To find all pair shortest path distance
	
	// Minimum Spanning Tree Algorithms
	void PrimsMST();
	void KruskalsMST();
	
	// Function to print the Articulation Points in the graph
	void printArticulationPoints();
	// Function to print Bridges in the graph
	void printBridges();
	
	// Function to print Strongly Connected Components(SCCs)
	void printSCCs();
	
	// Function to print Biconnected Components
	void printBiconnectedComponents();
	
	// Function to check if the graph is Bipartite or not
	bool isBipartite();
};

#endif // _GRAPH_
