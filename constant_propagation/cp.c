/**
 * The program takes input expressions, folds them to constants if possible, and outputs the optimized
 * code.
 * 
 * @return The program is returning 0, which indicates successful execution.
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Function prototypes
void input(); // to get the expression from the users (format: + 1 2 3)
void constant(); // fold expressions to constants
void output();
void change(int p, char *res);

int n; // Global variable to store the maximum number of expressions

// Structure to represent an expression
struct expr {
    char op[2], op1[5], op2[5], res[5]; // Operator, operands, result, and a flag
    int flag; // Flag to indicate if the expression is optimized
} arr[10]; // Array of expressions

int main() {
    input(); // Get input expressions from the user
    constant(); // Fold expressions to constants
    output(); // Display the optimized code
    return 0;
}

// Function to input expressions
void input() {
    printf("Enter the maximum number of expressions: ");
    scanf("%d", &n); // Read the maximum number of expressions
    printf("Enter the input: \n");
    for (int i = 0; i < n; i++) {
        scanf("%s", arr[i].op); // Read operator
        scanf("%s", arr[i].op1); // Read first operand
        scanf("%s", arr[i].op2); // Read second operand
        scanf("%s", arr[i].res); // Read result
        arr[i].flag = 0; // Initialize flag
    }
}

// Function to fold expressions to constants
void constant() {
    int op1, op2, res;
    char op, res1[5];
    for (int i = 0; i < n; i++) {
        if ((isdigit(arr[i].op1[0]) && isdigit(arr[i].op2[0])) || strcmp(arr[i].op, "=") == 0) {
            op1 = atoi(arr[i].op1); // Convert first operand to integer
            op2 = atoi(arr[i].op2); // Convert second operand to integer
            op = arr[i].op[0]; // Get operator

            switch (op) {
                case '+': res = op1 + op2; break;
                case '-': res = op1 - op2; break;
                case '*': res = op1 * op2; break;
                case '/': res = op1 / op2; break;
                case '=': res = op1; break;
            }

            sprintf(res1, "%d", res); // Convert result to string
            arr[i].flag = 1; // Mark expression as optimized
            change(i, res1); // Update other expressions with the new result
        }
    }
}

// Function to output the optimized code
void output() {
    printf("\n Optimized code is: ");
    for (int i = 0; i < n; i++) {
        if (arr[i].flag == 0) {
            printf("\n%s %s %s %s ", arr[i].op1, arr[i].op, arr[i].op2, arr[i].res); // Print the expression
        }
    }
}

// Function to update other expressions with the new result
void change(int p, char *res) {
    for (int i = p + 1; i < n; i++) {
        if (strcmp(arr[p].res, arr[i].op1) == 0)
            strcpy(arr[i].op1, res); // Update first operand
        else if (strcmp(arr[p].res, arr[i].op2) == 0)
            strcpy(arr[i].op2, res); // Update second operand
    }
}