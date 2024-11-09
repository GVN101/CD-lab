#include <stdio.h> // Include the standard input-output library for using printf and scanf functions
#include <string.h> // Include the string library for string manipulation functions
#include <ctype.h> // Include the ctype library for character type functions (e.g., isupper)

int n, r, p; // Global variables: n for number of productions, r for result index, p for printed productions count
char productions[30][30], nl, input, result[30], already_printed[10]; // Arrays for productions, result, and already printed symbols

// Function to check if a character has already been printed
int already_printed_result(char c) {
    for(int i = 0; i < p; i++) { // Loop through already printed characters
        if(already_printed[i] == c) // If the character is found
            return 1; // Return 1 (true)
    }
    return 0; // Return 0 (false) if not found
}

// Function to add a character to the result if it is not already present
void add_to_result(char c) {
    for(int i = 0; i < r; i++) { // Loop through the current result
        if(result[i] == c) // If the character is already in the result
            return; // Do nothing and return
    }
    result[r++] = c; // Add the character to the result and increment the result index
}

// Function to compute the FIRST set of a given non-terminal character
void first(char c) {
    if(!isupper(c)) { // If the character is not an uppercase letter (i.e., a terminal)
        add_to_result(c); // Add it to the result
        return; // Return from the function
    }
    for(int i = 0; i < n; i++) { // Loop through all productions
        if(productions[i][0] == c) { // If the production starts with the character c
            if(productions[i][2] == c) // If the production leads to itself (left recursion)
                continue; // Skip this production
            else if(!isupper(productions[i][2])) // If the next character is a terminal
                add_to_result(productions[i][2]); // Add it to the result
            else // If the next character is a non-terminal
                first(productions[i][2]); // Recursively call first on that non-terminal
        }
    } 
}

// Function to compute the FOLLOW set of a given non-terminal character
void follow(char c) {
    if(productions[0][0] == c) // If c is the start symbol
        add_to_result('$'); // Add the end-of-input symbol to the FOLLOW set
    for(int i = 0; i < n; i++) { // Loop through all productions
        for(int j = 2; j < strlen(productions[i]); j++) { // Loop through the production string starting from the third character
            if(productions[i][j] == c) { // If the character c is found in the production
                if(productions[i][j + 1] == '\0') // If c is the last character in the production
                    follow(productions[i][0]); // Call follow on the left-hand side of the production
                else if (productions[i][j + 1] == c) // If the next character is the same as c (left recursion)
                    continue; // Skip this iteration
                else if(!isupper(productions[i][j + 1]) && productions[i][j] != '#') // If the next character is a terminal and not epsilon
                    add_to_result(productions[i][j + 1]); // Add it to the FOLLOW set
                else // If the next character is a non-terminal
                    first(productions[i][j + 1]); // Call first on the next character
            }
        }
    }
}

// Main function
int main() {
    printf("Enter the number of productions: "); // Prompt user for the number of productions
    scanf("%d", &n); // Read the number of productions from user input
    printf("Enter the productions: \n\n"); // Prompt user to enter the productions
    for(int i = 0; i < n; i++) { // Loop to read each production
        scanf("%s%c", productions[i], &nl); // Read the production string
    }
    printf("\n"); // Print a newline for formatting
    p = 0; // Initialize the printed productions count
    for(int i = 0; i < n; i++) { // Loop through each production to compute FIRST sets
        input = productions[i][0]; // Get the left-hand side non-terminal
        if(!already_printed_result(input)) { // If it has not been printed yet
            r = 0; // Reset the result index
            first(input); // Compute the FIRST set for the non-terminal
            printf("First of %c: ", input); // Print the FIRST set header
            for(int i = 0; i < r; i++) { // Loop through the result array
                printf("%c ", result[i]); // Print each character in the FIRST set
            }
            already_printed[p++] = input; // Mark this non-terminal as printed
            printf("\n"); // Print a newline for formatting
        }
    }
    p = 0; // Reset the printed productions count for FOLLOW sets
    printf("==================\n"); // Print a separator line
    strcpy(result, ""); // Clear the result array for FOLLOW sets
    for(int i = 0; i < n; i++) { // Loop through each production to compute FOLLOW sets
        input = productions[i][0]; // Get the left-hand side non-terminal
        if(!already_printed_result(input)) { // If it has not been printed yet
            r = 0; // Reset the result index
            follow(input); // Compute the FOLLOW set for the non-terminal
            printf("Follow of %c: ", input); // Print the FOLLOW set header
            for(int i = 0; i < r; i++) { // Loop through the result array
                printf("%c ", result[i]); // Print each character in the FOLLOW set
            }
            already_printed[p++] = input; // Mark this non-terminal as printed
            printf("\n"); // Print a newline for formatting
        }
    }
    return 0; // Return 0 to indicate successful execution
}
