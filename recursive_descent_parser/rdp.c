// C program to Construct a recursive descent parsing for
// the following grammar
// E->TE’
// E’->+TE'/@
// T->FT’
// T’->*FT’/@
// F->(E)/id 

//where @ represents null character

#include <stdio.h>

// Global variables
char input[100]; // Array to store the input string
int i = 0; // Index to keep track of the current position in the input string

// Function prototypes
int E();
int T();
int EP();
int TP();
int F();

int main()
{
    // Prompt user to enter the input string
    printf("Enter the input string: ");
    scanf("%s", input);

    // Call the E() function to start parsing and check if the entire input string is parsed
    if (E() && input[i] == '\0')
        printf("The string is accepted!");
    else
        printf("The string is rejected!");

    return 0;
}

// Function to parse non-terminal E
int E()
{
    if (T()) // Check if T() is successful
    {
        return EP(); // Call EP() to handle E'
    }
    else
        return 0;
}

// Function to parse non-terminal T
int T()
{
    if (F()) // Check if F() is successful
    {
        return TP(); // Call TP() to handle T'
    }
    else
        return 0;
}

// Function to parse T'
int TP()
{
    if (input[i] == '*') // Check for '*'
    {
        i++; // Move to the next character
        if (F()) // Check if F() is successful
            return TP(); // Recursively call TP() for additional factors
        else
            return 0;
    }
    else
        return 1; // Return 1 to indicate successful parsing of T'
}

// Function to parse E'
int EP()
{
    if (input[i] == '+') // Check for '+'
    {
        i++; // Move to the next character
        if (T()) // Check if T() is successful
            return EP(); // Recursively call EP() for additional terms
        else
            return 0;
    }
    else
        return 1; // Return 1 to indicate successful parsing of E'
}

// Function to parse non-terminal F
int F()
{
    if (input[i] == '(') // Check for '(' to start an expression
    {
        i++; // Move to the next character
        if (E()) // Check if E() is successful
        {
            if (input[i] == ')') // Check for closing parenthesis
            {
                i++; // Move to the next character
                return 1; // Return 1 to indicate successful parsing of F
            }
            else
                return 0; // Return 0 if closing parenthesis is missing
        }
        else
            return 0; // Return 0 if E() fails
    }
    else if ((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z'))
    {
        i++; // Move to the next character
        return 1; // Return 1 to indicate successful parsing of F
    }
    else
        return 0; // Return 0 for invalid input character
}