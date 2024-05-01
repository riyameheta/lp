#include <iostream>  // Input/output stream
#include <vector>    // Vector container
#include <queue>     // Priority queue for Branch and Bound algorithm
using namespace std;

// Function to check if placing a queen at (row, col) is safe
bool isSafe(int row, int col, const vector<int>& placement) {
    for (int i = 0; i < row; ++i) {
        if (placement[i] == col || abs(row - i) == abs(col - placement[i])) {
            return false;
        }
    }
    return true;
}

// Backtracking function to find solutions to N-Queens problem
void backtrack(int n, int row, vector<int>& placement, vector<vector<string>>& solutions) {
    if (row == n) { // If all queens are placed
        // Construct the solution board and add it to solutions
        vector<string> solution(n, string(n, ' X '));
        for (int i = 0; i < n; ++i) {
            solution[i][placement[i]] = 'Q';
        }
        solutions.push_back(solution);
        return;
    }

    // Try placing a queen in each column of the current row
    for (int col = 0; col < n; ++col) {
        if (isSafe(row, col, placement)) {
            placement[row] = col;
            backtrack(n, row + 1, placement, solutions);
        }
    }
}

// Function to solve N-Queens problem using backtracking
vector<vector<string>> solveNQueensBacktracking(int n) {
    vector<vector<string>> solutions;
    vector<int> placement(n); // Vector to store column positions of queens
    backtrack(n, 0, placement, solutions); // Start backtracking from the first row
    return solutions;
}

// Main function
int main() {
    int n;
    cout << "Enter the size of the chessboard (N): ";
    cin >> n; // Read the size of the chessboard from user input

    int choice;
    cout << "Choose the algorithm to solve N-Queens problem:" << endl;
    cout << "1. Backtracking" << endl;
    cout << "2. Branch and Bound" << endl;
    cout << "Enter your choice: ";
    cin >> choice; // Read user's choice of algorithm

    vector<vector<string>> solutions; // Vector to store solutions
    switch (choice) {
        case 1:
            solutions = solveNQueensBacktracking(n); // Solve using backtracking
            break;
        case 2:
            // solutions = solveNQueensBranchAndBound(n); // Solve using Branch and Bound (commented out)
            break;
        default:
            cout << "Invalid choice. Exiting..." << endl; // Print error message for invalid choice
            return 1;
    }

    // Output the solutions
    cout << "Number of solutions: " << solutions.size() << endl;
    for (const auto& solution : solutions) {
        for (const string& row : solution) {
            cout << row << endl; // Print each row of the solution board
        }
        cout << endl;
    }

    return 0; // Exit the program
}
