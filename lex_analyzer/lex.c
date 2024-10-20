#include <stdio.h> // Include standard input/output library
#include <ctype.h> // Include functions for testing and mapping characters
#include <string.h> // Include string handling functions

int isOperator(char ch) // Function to check if a character is an operator
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/') // Check for common operators
    {
        return 1; // Return 1 if the character is an operator
    }
    return 0; // Return 0 if the character is not an operator
}

int isSpecialSymbol(char ch) // Function to check if a character is a special symbol
{
    if (ch == '{' || ch == '}' || ch == '(' || ch == ')' || ch == ';' || ch == ':' || ch == '"' || ch == '<' || ch == '>' || ch == '#' || ch == '=') // Check for common special symbols
    {
        return 1; // Return 1 if the character is a special symbol
    }
    return 0; // Return 0 if the character is not a special symbol
}

int main() // Main function
{
    FILE *input; // File pointer
    input = fopen("input.txt", "r"); // Open "input.txt" file for reading
    int no_of_tokens = 1; // Initialize token counter
    int line_number = 1; // Initialize line number counter
    int i = 0; // Initialize index counter
    int isString = 0; // Flag to check if a string has started
    int flag = 0; // Flag to check whether a word is a keyword or identifier
    char word[30]; // Array to store a word
    char ch; // Variable to read each character
    char keywords[30][30] = {"int", "main", "stdio", "include", "printf", "while", "for", "return"}; // Array of keywords

    printf("LineNo:\t\tTokenNo:\t\tToken\t\tLexeme\n"); // Print header for output

    while ((ch = fgetc(input)) != EOF) // Loop through each character in the file
    {
        i = 0; // Reset index counter
        if (isOperator(ch)) // Check if the character is an operator
        {
            if (ch == '/') // Check for comments
            {
                char next = fgetc(input); // Read the next character
                if (next == '/') // Single line comment
                {
                    while ((ch = fgetc(input)) != '\n' && ch != EOF)
                    {
                        // Skip characters in the comment
                    }
                }
                else if (next == '*') // Multiline comment
                {
                    while (1)
                    {
                        ch = fgetc(input);
                        if (ch == '*' && fgetc(input) == '/')
                        {
                            break;
                        }
                        if (ch == '\n')
                        {
                            line_number++; // Increment line number
                        }
                    }
                }
            }
            else
            {
                ungetc(ch, input); // Put the character back into the stream
                printf("%d\t\t%d\t\tOperator\t\t%c \n", line_number, no_of_tokens, ch); // Print operator token
                no_of_tokens++; // Increment token counter
            }
        }
        else if (isSpecialSymbol(ch)) // Check if the character is a special symbol
        {
            if (ch == '"') // Check for string
            {
                isString = (1 + isString) % 2; // Toggle isString flag
            }
            printf("%d\t\t%d\t\tSpecial Symbol\t\t%c \n", line_number, no_of_tokens, ch); // Print special symbol token
            no_of_tokens++; // Increment token counter
        }
        else if (isdigit(ch)) // Check if the character is a digit
        {
            printf("%d\t\t%d\t\tdigit\t\t\t%c \n", line_number, no_of_tokens, ch); // Print digit token
            no_of_tokens++; // Increment token counter
        }
        else if (isalpha(ch)) // Check if the character is an alphabet
        {
            word[i] = ch; // Store the character in the word array
            while (isalnum(ch) && ch != ' ' && !isSpecialSymbol(ch)) // Read the complete word
            {
                word[i++] = ch; // Store the character in the word array
                ch = fgetc(input); // Read the next character
            }

            if (isSpecialSymbol(ch)) // Check if the character is a special symbol
            {
                ungetc(ch, input); // Put the character back into the stream
            }
            word[i] = '\0'; // Null terminate the word
            char temp[30]; // Temporary array to store keyword
            for (int i = 0; word[i] != '\0'; i++)
            {
                if (strcmp(keywords[i], word) == 0) // Check if the word is a keyword
                {
                    flag = 1; // Set flag for keyword
                    strcpy(temp, keywords[i]); // Copy keyword to temp array
                    break;
                }
            }

            if (flag) // Check if the word is a keyword
            {
                printf("%d\t\t%d\t\tKeyword\t\t\t%s\n", line_number, no_of_tokens, temp); // Print keyword token
                no_of_tokens++; // Increment token counter
                flag = 0; // Reset flag
            }
            else
            {
                if (isString) // Check if the word is part of a string
                {
                    printf("%d\t\t%d\t\tString\t\t\t%s\n", line_number, no_of_tokens, word); // Print string token
                    no_of_tokens++; // Increment token counter
                }
                else
                {
                    printf("%d\t\t%d\t\tIdentifier\t\t%s\n", line_number, no_of_tokens, word); // Print identifier token
                    no_of_tokens++; // Increment token counter
                }
            }
        }
        if (ch == '\n') // Check for new line
        {
            line_number++; // Increment line number
        }
    }

    fclose(input); // Close the file
    return 0; // Return from main function
}