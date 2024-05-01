#include <iostream>   // Input/output stream
#include <vector>     // Vector container
#include <climits>    // Constants for integer limits
#include <algorithm>  // Standard algorithms

using namespace std;

class Solution
{
public:
    // Dijkstra's algorithm to find shortest path
    vector<int> dijkstra(int V, vector<vector<pair<int, int>>> adj, int src, vector<int> &parent)
    {
        vector<bool> visited(V, false); // Mark all nodes as unvisited
        vector<int> dist(V, INT_MAX);   // Initialize distances to infinity

        dist[src] = 0; // Distance to source vertex is 0

        // Loop through all vertices
        for (int i = 0; i < V - 1; ++i)
        {
            // Find vertex with minimum distance
            int min = INT_MAX, minIndex;
            for (int j = 0; j < V; ++j)
            {
                if (!visited[j] && dist[j] < min)
                {
                    min = dist[j];
                    minIndex = j;
                }
            }

            int u = minIndex; // Current vertex
            visited[u] = true; // Mark current vertex as visited

            // Update distances for adjacent vertices
            for (const auto &edge : adj[u])
            {
                int adjNode = edge.first; // Adjacent vertex
                int edgW = edge.second;   // Weight of edge

                // Relaxation step
                if (!visited[adjNode] && dist[u] != INT_MAX && dist[u] + edgW < dist[adjNode])
                {
                    dist[adjNode] = dist[u] + edgW; // Update distance
                    parent[adjNode] = u;            // Update parent
                }
            }
        }

        return dist; // Return array of shortest distances
    }

    // Reconstruct path from source to destination
    vector<int> reconstructPath(int src, int dest, const vector<int> &parent)
    {
        vector<int> path;
        for (int v = dest; v != src; v = parent[v])
            path.push_back(v);
        path.push_back(src);
        reverse(path.begin(), path.end()); // Reverse path to get correct order
        return path;
    }
};

int main()
{
    int V = 3; // Number of vertices

    // Adjacency list representation of graph
    vector<vector<pair<int, int>>> adj(V);
    vector<pair<int, int>> v1{{1, 1}, {2, 6}}, v2{{2, 3}, {0, 1}}, v3{{1, 3}, {0, 6}};
    adj[0] = v1;
    adj[1] = v2;
    adj[2] = v3;

    int src, dest;
    cout << "Enter source and destination vertices: ";
    cin >> src >> dest; // Read source and destination vertices from user

    Solution obj; // Create object of Solution class

    vector<int> parent(V, -1); // Parent array to store shortest path tree
    vector<int> res = obj.dijkstra(V, adj, src, parent); // Run Dijkstra's algorithm

    int totalDistance = res[dest]; // Total distance from source to destination
    vector<int> path = obj.reconstructPath(src, dest, parent); // Reconstruct shortest path

    // Output shortest path and total distance
    cout << "Shortest path from vertex " << src << " to vertex " << dest << ": ";
    for (int i = 0; i < path.size(); ++i)
    {
        cout << path[i];
        if (i != path.size() - 1)
            cout << " -> ";
    }
    cout << "\nTotal distance: " << totalDistance << endl;

    return 0;
}
