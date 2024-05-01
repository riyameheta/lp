#include <iostream>   // Input/output stream
#include <vector>     // Vector container
#include <queue>      // Priority queue
#include <unordered_map> // Unordered map container
#include <algorithm>  // Standard algorithms

using namespace std;

// Structure to represent a node in the graph
struct GraphNode {
    int id;            // Node ID
    double heuristic;  // Heuristic value for A* algorithm
    double cost;       // Cost of reaching this node
};

// Functor to compare GraphNode objects for priority queue
struct CompareNode {
    bool operator()(const GraphNode &a, const GraphNode &b) {
        // Comparison based on total estimated cost (heuristic + actual cost)
        return a.heuristic + a.cost > b.heuristic + b.cost;
    }
};

// A* algorithm implementation
vector<int> astar(const vector<vector<GraphNode>> &graph, int start, int goal, const vector<double> &heuristic) {
    priority_queue<GraphNode, vector<GraphNode>, CompareNode> pq; // Priority queue to store nodes
    unordered_map<int, double> cost_so_far;  // Map to store cost of reaching each node
    unordered_map<int, int> came_from;       // Map to store parent node for each node in the path

    pq.push({start, heuristic[start], 0.0}); // Push start node to priority queue
    cost_so_far[start] = 0.0;                // Initialize cost of start node

    while (!pq.empty()) {  // Loop until priority queue is empty
        GraphNode current = pq.top(); // Get the node with lowest estimated total cost
        pq.pop();                     // Remove the node from priority queue

        if (current.id == goal) {  // If goal node is reached
            vector<int> path;      // Initialize path vector
            int node = goal;       // Start from goal node
            while (node != start) { // Backtrack from goal node to start node
                path.push_back(node);  // Add current node to path
                node = came_from[node]; // Move to parent node
            }
            path.push_back(start); // Add start node to path
            reverse(path.begin(), path.end()); // Reverse the path to get correct order
            return path; // Return the shortest path
        }

        // Traverse neighbors of current node
        for (const GraphNode &neighbor : graph[current.id]) {
            double new_cost = cost_so_far[current.id] + neighbor.cost; // Calculate new cost
            if (!cost_so_far.count(neighbor.id) || new_cost < cost_so_far[neighbor.id]) {
                cost_so_far[neighbor.id] = new_cost; // Update cost of reaching neighbor
                pq.push({neighbor.id, heuristic[neighbor.id], new_cost}); // Push neighbor to priority queue
                came_from[neighbor.id] = current.id; // Set parent of neighbor to current node
            }
        }
    }
    return {}; // Return empty path if goal node is not reachable
}

// Function to initialize the graph and heuristic values for the Romania map problem
void initializeRomaniaMap(vector<vector<GraphNode>> &graph, vector<double> &heuristic) {
    graph.resize(4); // Resize graph vector to 4 nodes

    // Initialize edges and costs for each node in the graph
    graph[0].push_back({1, 75, 0}); // Arad
    graph[0].push_back({2, 140, 0}); // Arad
    graph[0].push_back({3, 118, 0}); // Arad

    graph[1].push_back({0, 140, 0}); // Sibiu
    graph[1].push_back({2, 99, 0}); // Sibiu

    graph[2].push_back({0, 118, 0}); // Timisoara
    graph[2].push_back({3, 111, 0}); // Timisoara

    graph[3].push_back({0, 75, 0}); // Zerind

    // Initialize heuristic values for each node
    heuristic = {366, 253, 329, 380};
}

// Main function
int main() {
    vector<vector<GraphNode>> graph; // Graph representation
    vector<double> heuristic;        // Heuristic values
    initializeRomaniaMap(graph, heuristic); // Initialize graph and heuristic values

    int start, goal; // Variables to store start and goal nodes
    cout << "Enter the start node and the goal node: ";
    cin >> start >> goal; // Read start and goal nodes from user input

    // Call A* algorithm to find shortest path
    vector<int> path = astar(graph, start, goal, heuristic);

    // Output the result
    if (!path.empty()) {
        cout << "Path found: ";
        for (int node : path) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "Path not found" << endl;
    }

    return 0;
}
