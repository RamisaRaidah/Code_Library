#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

const int INF = INT_MAX;

// Number of vertices (adjust as needed)
const int V = 6; 

// Performs BFS to find an augmenting path in the residual graph
// Returns true if a path exists from source 's' to sink 't'
bool bfs(int rGraph[V][V], int s, int t, int parent[]) {
    // Create a visited array and mark all vertices as not visited
    bool visited[V];
    fill(visited, visited + V, false);

    // Create a queue, enqueue source vertex and mark source vertex as visited
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    // Standard BFS Loop
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++) {
            // If v is not visited and there is residual capacity
            if (!visited[v] && rGraph[u][v] > 0) {
                // If we find a connection to the sink node, 
                // there is no need to continue BFS
                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    // We didn't reach the sink in BFS starting from source
    return false;
}

// Returns the maximum flow from s to t in the given graph
int edmondsKarp(int graph[V][V], int s, int t) {
    int u, v;

    // Create a residual graph and fill the residual graph with
    // given capacities in the original graph as residual capacities
    int rGraph[V][V]; 
    for (u = 0; u < V; u++) {
        for (v = 0; v < V; v++) {
            rGraph[u][v] = graph[u][v];
        }
    }

    int parent[V];  // This array is filled by BFS and to store path
    int max_flow = 0; 

    // Augment the flow while there is a path from source to sink
    while (bfs(rGraph, s, t, parent)) {
        
        // Find minimum residual capacity of the edges along the
        // path filled by BFS.
        int path_flow = INF;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        // Add path flow to overall flow
        max_flow += path_flow;

        // update residual capacities of the edges and reverse edges
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow; // Reduce capacity
            rGraph[v][u] += path_flow; // Add back-edge capacity
        }
    }

    return max_flow;
}

int main() {
    // Example Graph (Adjacency Matrix)
    // 0: Source, 5: Sink
    int graph[V][V] = {
        {0, 16, 13, 0, 0, 0},
        {0, 0, 10, 12, 0, 0},
        {0, 4, 0, 0, 14, 0},
        {0, 0, 9, 0, 0, 20},
        {0, 0, 0, 7, 0, 4},
        {0, 0, 0, 0, 0, 0}
    };

    cout << "The maximum possible flow is " << edmondsKarp(graph, 0, 5) << endl;

    return 0;
}