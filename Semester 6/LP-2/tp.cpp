#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph {
    int V; // Number of vertices
    vector<vector<int>> adj; // Adjacency list

public:
    Graph(int V) : V(V), adj(V) {}

    // Function to add an edge between vertices u and v
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // For undirected graph
    }

    // Depth First Search (DFS) recursive implementation
    void DFSUtil(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";

        for (int i : adj[v]) {
            if (!visited[i]) {
                DFSUtil(i, visited);
            }
        }
    }

    // DFS traversal starting from vertex v
    void DFS(int v) {
        vector<bool> visited(V, false);
        cout << "Depth First Search (DFS) starting from vertex " << v << ":\n";
        DFSUtil(v, visited);
        cout << "\n";
    }

    // Breadth First Search (BFS) traversal
    void BFS(int v) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[v] = true;
        q.push(v);

        cout << "Breadth First Search (BFS) starting from vertex " << v << ":\n";

        while (!q.empty()) {
            v = q.front();
            cout << v << " ";
            q.pop();

            for (int i : adj[v]) {
                if (!visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
        cout << "\n";
    }
};

int main() {
    int V = 6; // Number of vertices

    Graph g(V);

    // Adding edges to the graph
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(3, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);

    // Perform DFS and BFS traversal from vertex 0
    g.DFS(0);
    g.BFS(0);

    return 0;
}
