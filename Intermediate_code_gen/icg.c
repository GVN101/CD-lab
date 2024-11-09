#include<stdio.h> // Include standard input-output library for printf and scanf functions
#include<stdlib.h> // Include standard library for general functions (not used in this code)
#include<string.h> // Include string library for string manipulation functions

// Global variables
int i = 1, j = 0, no = 0, tmpch = 90; // i for indexing, j for operator count, no is unused, tmpch for temporary character (ASCII)
char str[100], left[15], right[15]; // str for input expression, left and right for operands

// Function prototypes
void findopr(); // Function to find operators in the expression
void explore(); // Function to generate intermediate code
void fleft(int); // Function to find left operand
void fright(int); // Function to find right operand

// Structure to hold operator information
struct exp {
    int pos; // Position of the operator in the expression
    char op; // Operator character
    int isUnary; // Flag to indicate if the operator is unary
} k[15]; // Array to hold up to 15 operators

// Main function
void main() {
    printf("\t\tINTERMEDIATE CODE GENERATION\n\n"); // Print header
    printf("Enter the Expression : "); // Prompt user for input
    scanf("%s", str); // Read the expression from user input
    printf("The intermediate code:\n"); // Print header for intermediate code
    findopr(); // Call function to find operators
    explore(); // Call function to generate intermediate code
}

// Function to find operators in the expression
void findopr() {
    // Loop through the expression to find parentheses
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == '(' || str[i] == ')') { // If character is '(' or ')'
            k[j].pos = i; // Store position
            k[j].isUnary = 0; // Set isUnary to 0 (not unary)
            k[j++].op = str[i]; // Store operator and increment j
        }
    }

    // Loop to find unary minus operators
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == '-' && (i == 0 || (str[i-1] == '(' || str[i-1] == '+' || str[i-1] == '-' || str[i-1] == '*' || str[i-1] == '/'))) {
            k[j].pos = i; // Store position of unary minus
            k[j].isUnary = 1; // Set isUnary to 1 (unary)
            k[j++].op = '-'; // Store operator and increment j
        }
    }
    
    // Loop to find binary operators: '/' and '*'
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == '/' || str[i] == '*') { // If character is '/' or '*'
            k[j].pos = i; // Store position
            k[j].isUnary = 0; // Set isUnary to 0 (not unary)
            k[j++].op = str[i]; // Store operator and increment j
        }
    }
    
    // Loop to find binary operator: '+'
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == '+') { // If character is '+'
            k[j].pos = i; // Store position
            k[j].isUnary = 0; // Set isUnary to 0 (not unary)
            k[j++].op = '+'; // Store operator and increment j
        }
    }
    
    // Loop to find binary operator: '-'
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == '-') {
            // Check if the '-' is a unary operator
            if (i == 0 || (str[i-1] == '(' || str[i-1] == '+' || str[i-1] == '-' || str[i-1] == '*' || str[i-1] == '/')) {
                // Unary minus detected (after '(', '+', '-', '*', or '/')
                continue; // Skip this iteration
            }
            k[j].pos = i; // Store position of binary minus
            k[j].isUnary = 0; // Set isUnary to 0 (not unary)
            k[j++].op = '-'; // Store operator and increment j
        }
    }
}

// Function to explore the operators and generate intermediate code
void explore() {
    i = 0; // Reset index for exploring operators
    while (k[i].op != '\0') { // Loop until the end of the operator array
        if (k[i].op == '(' || k[i].op == ')') { // If the operator is a parenthesis
            // Skip parentheses
            i++; // Move to the next operator
            continue; // Continue to the next iteration
        }
        if (k[i].isUnary) { // If the operator is unary
            fright(k[i].pos); // Find the right operand
            str[k[i].pos] = tmpch--; // Replace the operator with a temporary variable
            // Print intermediate code for unary operation
            printf("\t%c := %c %s\t\t", str[k[i].pos], k[i].op, right);
        }
        else { // If the operator is binary
            fleft(k[i].pos); // Find the left operand
            fright(k[i].pos); // Find the right operand
            str[k[i].pos] = tmpch--; // Replace the operator with a temporary variable
            
            // Print intermediate code for binary operation
            printf("\t%c := %s %c %s\t\t", str[k[i].pos], left, k[i].op, right);
        }
        printf("\n"); // Print a newline for formatting
        i++; // Move to the next operator
    }
    
    fright(-1); // Call fright with -1 to process any remaining right operands
}

// Function to find the left operand of an operator
void fleft(int x) {
    int w = 0, flag = 0; // Initialize index and flag
    x--; // Move to the left of the operator
    
    // Loop to find the left operand
    while (x != -1 && str[x] != '+' && str[x] != '*' && str[x] != '=' && str[x] != '\0' && str[x] != '-' && str[x] != '/' && str[x] != ':') {
        if (str[x] != '$' && flag == 0) { // If the character is not processed and it's the first operand
            left[w++] = str[x]; // Add character to left operand
            left[w] = '\0'; // Null-terminate the string
            str[x] = '$'; // Mark the operand as processed
            flag = 1; // Set flag to indicate an operand has been found
        }
        x--; // Move left
    }
}

// Function to find the right operand of an operator
void fright(int x) {
    int w = 0, flag = 0; // Initialize index and flag
    x++; // Move to the right of the operator
    
    // Loop to find the right operand
    while (x != -1 && str[x] != '+' && str[x] != '*' && str[x] != '\0' && str[x] != '=' && str[x] != '-' && str[x] != '/' && str[x] != ':') {
        if (str[x] != '$' && flag == 0) { // If the character is not processed and it's the first operand
            right[w++] = str[x]; // Add character to right operand
            right[w] = '\0'; // Null-terminate the string
            str[x] = '$'; // Mark the operand as processed
            flag = 1; // Set flag to indicate an operand has been found
        }
        x++; // Move right
    }
}
