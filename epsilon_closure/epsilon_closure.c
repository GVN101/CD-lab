#include <stdio.h> // Include the standard input-output library for using printf and scanf functions

// Function prototypes
void dfs(int i, int n); // Declaration of the depth-first search function
void reset_visited(int n); // Declaration of the function to reset the visited states

// Global variables
int et[100][100]; // 2D array to store epsilon transitions (up to 100 states)
int visited[100]; // Array to track whether a state has been visited during DFS

int main() {
    int number_of_states, number_of_transistions; // Variables to hold the number of states and transitions

    // Prompt user for the number of states
    printf("Enter the number of states: ");
    scanf("%d", &number_of_states); // Read the number of states from user input

    // Prompt user for the number of transitions
    printf("Enter the number of transitions: ");
    scanf("%d", &number_of_transistions); // Read the number of transitions from user input

    // Prompt user to enter the transitions
    printf("Enter the transitions: \n\n");
    int m, n; // Variables to hold the state numbers for transitions
    char symbol; // Variable to hold the transition symbol

    // Get the epsilon closure for each state
    for(int i = 0; i < number_of_transistions; i++) {
        // Read the transition in the format: state1 symbol state2
        scanf("%d %c %d", &m, &symbol, &n);
        // If the symbol is 'e' (epsilon), mark the transition in the epsilon transition table
        if(symbol == 'e')
            et[m][n] = 1; // Set the transition from state m to state n in the epsilon transition table
    }

    // Finding the epsilon closure for each state
    for(int i = 1; i <= number_of_states; i++) {
        // Print the epsilon closure for the current state
        printf("\nEpsilon closure of state %d: ", i);
        reset_visited(number_of_states); // Reset the visited array for the new DFS
        dfs(i, number_of_states); // Perform DFS starting from state i
        printf("{ "); // Start printing the closure set
        // Loop through all states to print those that are reachable
        for(int j = 1; j <= number_of_states; j++) {
            if(visited[j]) // If the state has been visited
                printf("%d ", j); // Print the state number
        }
        printf("}"); // End of the closure set
    }
    return 0; // Return 0 to indicate successful execution
}

// Depth-first search function to explore epsilon transitions
void dfs(int v, int n) {
    visited[v] = 1; // Mark the current state as visited
    // Loop through all possible states
    for(int i = 1; i <= n; i++) {
        // If there is an epsilon transition from state v to state i and state i has not been visited
        if(et[v][i] == 1 && visited[i] == 0) {
            dfs(i, n); // Recursively call DFS for state i
        }
    }
}

// Function to reset the visited array
void reset_visited(int n) {
    // Loop through all states
    for(int i = 1; i <= n; i++) {
        visited[i] = 0; // Set each state as not visited
    }
}
