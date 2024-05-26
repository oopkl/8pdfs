#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

// Define the 3x3 puzzle board as a 2D array
typedef vector<vector<int>> PuzzleState;

// Define the possible actions (movements)
enum Action { UP, DOWN, LEFT, RIGHT };

// Function to print the puzzle board
void printPuzzle(const PuzzleState &state) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << state[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Function to check if a state is the goal state
bool isGoalState(const PuzzleState& state, const PuzzleState& goalState) {
    return state == goalState;
}

// Function to get valid actions for a given state
vector<Action> getValidActions(const PuzzleState& state) {
    vector<Action> validActions;

    // Find the position of the empty space (0)
    int emptyRow = -1, emptyCol = -1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (state[i][j] == 0) {
                emptyRow = i;
                emptyCol = j;
            }
        }
    }

    // Check if UP action is valid
    if (emptyRow > 0) {
        validActions.push_back(UP);
    }

    // Check if DOWN action is valid
    if (emptyRow < 2) {
        validActions.push_back(DOWN);
    }

    // Check if LEFT action is valid
    if (emptyCol > 0) {
        validActions.push_back(LEFT);
    }

    // Check if RIGHT action is valid
    if (emptyCol < 2) {
        validActions.push_back(RIGHT);
    }

    return validActions;
}

// Function to apply an action and get the resulting state
PuzzleState applyAction(const PuzzleState& state, Action action) {
    PuzzleState newState = state;

    // Find the position of the empty space (0)
    int emptyRow = -1, emptyCol = -1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (state[i][j] == 0) {
                emptyRow = i;
                emptyCol = j;
            }
        }
    }

    // Apply the action to swap the empty space with an adjacent tile
    if (action == UP) {
        swap(newState[emptyRow][emptyCol], newState[emptyRow - 1][emptyCol]);
    } else if (action == DOWN) {
        swap(newState[emptyRow][emptyCol], newState[emptyRow + 1][emptyCol]);
    } else if (action == LEFT) {
        swap(newState[emptyRow][emptyCol], newState[emptyRow][emptyCol - 1]);
    } else if (action == RIGHT) {
        swap(newState[emptyRow][emptyCol], newState[emptyRow][emptyCol + 1]);
    }

    return newState;
}

// Depth-First Search function
bool dfs(PuzzleState currentState, const PuzzleState& goalState, stack<Action>& path, set<PuzzleState>& visited) {
    if (isGoalState(currentState, goalState)) {
        return true;
    }

    visited.insert(currentState);
    vector<Action> validActions = getValidActions(currentState);

    for (Action action : validActions) {
        PuzzleState nextState = applyAction(currentState, action);
        if (visited.find(nextState) == visited.end()) {
            path.push(action);
            printPuzzle(nextState); // Print the puzzle state after each change
            if (dfs(nextState, goalState, path, visited)) {
                return true;  // Solution found
            }
            path.pop(); // Backtrack
        }
    }

    return false; // No solution found
}

// Function to read a puzzle state from user input
PuzzleState readPuzzleState() {
    PuzzleState state(3, vector<int>(3)); //board with 3 rows each containing a vector of 3 integers.
    cout << "Enter the puzzle state (3x3 matrix, use 0 for the empty space):" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> state[i][j];
        }
    }
    return state;
}

int main() {
    // Read the initial state and goal state from user input
    cout << "Initial State:" << endl;
    PuzzleState initialState = readPuzzleState();
    
    cout << "Goal State:" << endl;
    PuzzleState goalState = readPuzzleState();

    // Create a stack to store the path of actions
    stack<Action> path;

    // Set to track visited states
    set<PuzzleState> visited;

    // Call DFS starting from the initial state
    bool solutionFound = dfs(initialState, goalState, path, visited);

    if (solutionFound) {
        cout << "Solution found." << endl;
    } else {
        cout << "No solution found." << endl;
    }

    return 0;
}
