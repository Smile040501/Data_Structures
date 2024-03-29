#include <iostream>
using namespace std;

#include "Graph.h"

// Sample Graphs

// Undirected Unweighted Graph
// g(5, false, { {0, 1}, {0, 4}, {1, 3}, {1, 4}, {2, 3}, {2, 4}, {3, 4} });

// Undirected Weighted Graph
// g(9, false, { {0, 1, 4}, {0, 7, 8}, {1, 2, 8}, {1, 7, 11}, {2, 3, 7}, {2, 5, 4}, {2, 8, 2}, {3, 4, 9}, {3, 5, 14}, {4, 5, 10}, {5, 6, 2}, {6, 7, 1}, {6, 8, 6}, {7, 8, 7} });

// Directed Unweighted Graph
// g(7, true, { {0, 1}, {0, 3}, {1, 3}, {1, 4}, {2, 0}, {2, 5}, {3, 5}, {3, 6}, {4, 6}, {6, 5} });

// Directed Graph with self-loop and parallel edges
// g(4, true, { {0, 1}, {0, 2}, {1, 2}, {2, 0}, {2, 3}, {3, 3} });

// Directed Weighted Graph
// g(8, true, { {0, 1, 8}, {0, 3, 18}, {1, 2, 20}, {1, 4, 1}, {1, 3, 7}, {2, 3, 2}, {2, 5, 7}, {2, 6, 17}, {3, 1, 1}, {4, 5, 6}, {5, 6, 10}, {6, 7, 13}, {7, 4, 23}, {7, 5, 19} });

// Directed Weighted Graph with Negative Weights but no Negative Weight Cycle
// g(7, true, { {1, 2, -5}, {1, 3, 3}, {2, 4, -7}, {2, 5, 2}, {3, 6, -14}, {4, 0, 16}, {5, 0, -33}, {6, 0, 29}, {6, 5, -17} });

// Directed Weighted Graph with Negative Weight Cycle
// g(8, true, { {0, 5, -2}, {1, 2, 4}, {1, 3, 4}, {3, 5, 4}, {3, 6, -2}, {4, 1, 3}, {4, 3, 2}, {5, 4, 1}, {5, 7, -2}, {6, 2, 3}, {6, 5, -3}, {7, 0, 2}, {7, 6, 2} });

// Directed Acyclic Graph (DAG) with no weights
// g(8, true, { {1, 0}, {1, 2}, {1, 6}, {3, 0}, {3, 4}, {4, 6}, {5, 1}, {7, 1}, {7, 4} });

// Directed Acyclic Graph (DAG) with weights
// g(7, true, { {1, 2, 5}, {1, 3, 3}, {2, 4, 7}, {2, 5, 2}, {3, 6, 14}, {4, 0, 16}, {5, 0, 33}, {6, 0, 29}, {6, 5, 17} });

// DAG with Hamiltonian Path
// g(5, true, { {0, 1}, {0, 3}, {0, 4}, {2, 1}, {2, 3}, {3, 1}, {4, 2}, {4, 3} });

// Complete Graph
// g(7, false, { {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {2, 3}, {2, 4}, {2, 5}, {2, 6}, {3, 4}, {3, 5}, {3, 6}, {4, 5}, {4, 6}, {5, 6} });

// Undirected Complete Bipartite Graph
// g(8, false, { {0, 2}, {0, 3}, {0, 6}, {1, 2}, {1, 3}, {1, 6}, {4, 2}, {4, 3}, {4, 6}, {5, 2}, {5, 3}, {5, 6}, {7, 2}, {7, 3}, {7, 6} });

// Directed Weighted Bipartite Graph
// g(10, true, { {0, 7, 17}, {1, 2, 6}, {2, 3, 11}, {3, 9, 14}, {4, 6, 10}, {4, 8, 9}, {5, 6, 7}, {5, 8, 3}, {7, 1, 13}, {9, 0, 8} });

// Null Graph
// g(6, false, {});

// Trivial Graph
// g(1, false, {});

// Undirected Connected Graph
// g(12, false, { {0, 1}, {0, 4}, {0, 5}, {1, 4}, {1, 5}, {2, 3}, {2, 5}, {2, 6}, {2, 7}, {2, 8}, {3, 7}, {3, 8}, {3, 9}, {4, 5}, {6, 8}, {7, 8}, {9, 10}, {9, 11}, {10, 11} });

// Sample Graph for printing Biconnected Components
// g(12, false, { {0, 1}, {0, 6}, {1, 2}, {1, 3}, {1, 5}, {2, 3}, {2, 4}, {3, 4}, {5, 6}, {5, 7}, {5, 8}, {7, 8}, {8, 9}, {10, 11} });

// Undirected Disconnected Graph
// g(9, false, { {0, 1}, {0, 5}, {0, 8}, {1, 4}, {1, 8}, {2, 3}, {2, 6}, {2, 7}, {3, 6}, {3, 7}, {4, 5}, {4, 8}, {5, 8} });

// Undirected Weighted Disconnected Graph
// g(9, false, { {0, 1, 3}, {0, 5, 4}, {0, 8, 5}, {1, 4, 6}, {1, 8, 7}, {2, 3, 1}, {2, 6, 2}, {2, 7, 3}, {3, 6, 4}, {3, 7, 5}, {4, 5, 8}, {4, 8, 7}, {5, 8, 6} });

// Directed Connected Graph
// g(8, true, { {0, 1}, {1, 2}, {1, 4}, {1, 5}, {2, 3}, {2, 6}, {3, 2}, {3, 7}, {4, 0}, {4, 5}, {5, 6}, {6, 5}, {7, 3}, {7, 6} });

// Directed Disconnected Graph
// g(10, true, { {0, 3}, {0, 6}, {1, 0}, {2, 4}, {3, 1}, {5, 7}, {5, 8}, {5, 9}, {6, 0}, {6, 3}, {7, 9}, {8, 7}, {8, 9} });

// Directed Weighted Disconnected Graph
// g(10, true, { {0, 3, 6}, {0, 6, 18}, {1, 0, -1}, {2, 4, 0}, {3, 1, 3}, {5, 7, -9}, {5, 8, 11}, {5, 9, 1}, {6, 0, 22}, {6, 3, -4}, {7, 9, 10}, {8, 7, 5}, {8, 9, 7} });

int main() {
    return 0;
}
