#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph {
    int V; 
    vector<vector<int>> adj; 

public:
    Graph(int V) : V(V), adj(V) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); 
    }

    void DFSUtil(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";

        for (int i : adj[v]) {
            if (!visited[i]) {
                DFSUtil(i, visited);
            }
        }
    }

    void DFS(int v) {
        vector<bool> visited(V, false);
        cout << "Depth First Search (DFS) starting from vertex " << v << ":\n";
        DFSUtil(v, visited);
        cout << "\n";
    }

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
    int V = 6; 

    Graph g(V);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(3, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);

    g.DFS(0);
    g.BFS(0);

    return 0;
}
