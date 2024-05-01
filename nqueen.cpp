#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool isSafe(int row, int col, const vector<int>& placement) {
    for (int i = 0; i < row; ++i) {
        if (placement[i] == col || abs(row - i) == abs(col - placement[i])) {
            return false;
        }
    }
    return true;
}

void backtrack(int n, int row, vector<int>& placement, vector<vector<string>>& solutions) {
    if (row == n) {
        vector<string> solution(n, string(n, ' X '));
        for (int i = 0; i < n; ++i) {
            solution[i][placement[i]] = 'Q';
        }
        solutions.push_back(solution);
        return;
    }

    for (int col = 0; col < n; ++col) {
        if (isSafe(row, col, placement)) {
            placement[row] = col;
            backtrack(n, row + 1, placement, solutions);
        }
    }
}

vector<vector<string>> solveNQueensBacktracking(int n) {
    vector<vector<string>> solutions;
    vector<int> placement(n);
    backtrack(n, 0, placement, solutions);
    return solutions;
}

// vector<vector<string>> solveNQueensBranchAndBound(int n) {
//     vector<vector<string>> solutions;
//     vector<int> placement(n, -1);
//     priority_queue<pair<int, vector<int>>> pq;

//     pq.push({0, placement});

//     while (!pq.empty()) {
//         int row = -pq.top().first;
//         vector<int> placement = pq.top().second;
//         pq.pop();

//         if (row == n) {
//             vector<string> solution(n, string(n, '.'));
//             for (int i = 0; i < n; ++i) {
//                 solution[i][placement[i]] = 'Q';
//             }
//             solutions.push_back(solution);
//             continue;
//         }

//         for (int col = 0; col < n; ++col) {
//             if (isSafe(row, col, placement)) {
//                 placement[row] = col;
//                 pq.push({-(row + 1), placement});
//                 placement[row] = -1;
//             }
//         }
//     }

//     return solutions;
// }

int main() {
    int n;
    cout << "Enter the size of the chessboard (N): ";
    cin >> n;

    int choice;
    cout << "Choose the algorithm to solve N-Queens problem:" << endl;
    cout << "1. Backtracking" << endl;
    cout << "2. Branch and Bound" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    vector<vector<string>> solutions;
    switch (choice) {
        case 1:
            solutions = solveNQueensBacktracking(n);
            break;
        case 2:
            // solutions = solveNQueensBranchAndBound(n);
            break;
        default:
            cout << "Invalid choice. Exiting..." << endl;
            return 1;
    }

    cout << "Number of solutions: " << solutions.size() << endl;
    for (const auto& solution : solutions) {
        for (const string& row : solution) {
            cout << row << endl;
        }
        cout << endl;
    }

    return 0;
}
