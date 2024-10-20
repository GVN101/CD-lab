// #include <stdio.h>
// #include <string.h>
// char input_string[26], action[20], stack[30], act[10];
// int input_length, j=0,i=0;
// void check();
// int main()
// {
//   puts("GRAMMAR is: \n\nE->E+E\nE->E*E\nE->(E)\nE->id");
//   puts("Enter the string: ");
//   gets(input_string);
//   printf("\n");
//   input_length = strlen(input_string);
//   strcpy(action, "SHIFT ->");
//   puts("Stack\tinput\taction");
//   for(i=0;j<input_length;i++,j++)
//   {
//     if(input_string[j] == 'i' && input_string[j+1] == 'd')
//     {
//         stack[i] = input_string[j];
//         stack[i+1] = input_string[j+1];
//         stack[i+2] = '\0';
//         input_string[j] = ' ';
//         input_string[j+1] = ' ';
//         printf("\n$%s\t%s\t%s id", stack, input_string, action); 
//         check();
//     }
//     else
//     {
//         stack[i] = input_string[j];
//         stack[i+1] = '\0';
//         input_string[j] = ' ';
//         printf("\n$%s\t%s\t%s %c", stack, input_string, action, stack[i]);
//         check();
//     }
//   }
//   return 0;
// }

// void check()
// {
//     strcpy(act, "REDUCE TO E");
//     for(int k=0;k< input_length;k++)
//     {
//         if(stack[k]=='i' && stack[k+1] == 'd')
//         {
//             stack[k] = 'E';
//             stack[k+1] = '\0';
//             printf("\n$%s\t%s\t%s", stack, input_string, act);
//             j++;
//         }
//     }
//     for(int k=0;k< input_length;k++)
//     {
//         if(stack[k]=='E' && stack[k+1] == '+' && stack[k+2] == 'E')
//         {
//             stack[k] = 'E';
//             stack[k+1] = '\0';
//             stack[k+2] = '\0';
//             printf("\n$%s\t%s\t%s", stack, input_string, act);
//             i-=2;
//         }
//     }
//     for(int k=0;k< input_length;k++)
//     {
//         if(stack[k]=='E' && stack[k+1] == '*' && stack[k+2] == 'E')
//         {
//             stack[k] = 'E';
//             stack[k+1] = '\0';
//             stack[k+2] = '\0';
//             printf("\n$%s\t%s\t%s", stack, input_string, act);
//             i-=2;
//         }
//     }
//     for(int k=0;k< input_length;k++)
//     {
//         if(stack[k] == '(' && stack[k+1] == 'E' && stack[k+2] == ')')
//         {
//             stack[k] = 'E';
//             stack[k+1] = '\0';
//             stack[k+2] = '\0';
//             printf("\n$%s\t%s\t%s", stack, input_string, act);
//             i-=2;
//         }
//     }
// }

#include <stdio.h>
#include <string.h>

char input_string[26], action[20], stack[30], act[10]; // Declare global variables
int input_length, j=0, i=0; // Initialize variables

void check(); // Function prototype

int main()
{
  // Display the grammar rules
  puts("GRAMMAR is: \n\nE->E+E\nE->E*E\nE->(E)\nE->id");

  // Prompt the user to enter a string
  puts("Enter the string: ");

  // Read the input string from the user
  gets(input_string);
  printf("\n");

  // Calculate the length of the input string
  input_length = strlen(input_string);

  // Initialize the action as SHIFT
  strcpy(action, "SHIFT ->");

  // Display the headers for the stack, input, and action columns
  puts("Stack\tinput\taction");

  // Loop through the input string
  for(i=0; j<input_length; i++, j++)
  {
    // Check if the current and next characters form an 'id'
    if(input_string[j] == 'i' && input_string[j+1] == 'd')
    {
        // Update the stack with the 'id' and update the input string
        stack[i] = input_string[j];
        stack[i+1] = input_string[j+1];
        stack[i+2] = '\0';
        input_string[j] = ' ';
        input_string[j+1] = ' ';
        
        // Display the stack, input, and action after shifting 'id'
        printf("\n$%s\t%s\t%s id", stack, input_string, action); 
        check(); // Call the check function
    }
    else
    {
        // Update the stack with the current character and update the input string
        stack[i] = input_string[j];
        stack[i+1] = '\0';
        input_string[j] = ' ';
        
        // Display the stack, input, and action after shifting a character
        printf("\n$%s\t%s\t%s %c", stack, input_string, action, stack[i]);
        check(); // Call the check function
    }
  }

  return 0; // Exit the program
}

void check()
{
    // Set the action as REDUCE TO E
    strcpy(act, "REDUCE TO E");

    // Check for 'id' in the stack
    for(int k=0; k < input_length; k++)
    {
        if(stack[k] == 'i' && stack[k+1] == 'd')
        {
            stack[k] = 'E';
            stack[k+1] = '\0';
            printf("\n$%s\t%s\t%s", stack, input_string, act);
            j++;
        }
    }

    // Check for E+E pattern in the stack
    for(int k=0; k < input_length; k++)
    {
        if(stack[k] == 'E' && stack[k+1] == '+' && stack[k+2] == 'E')
        {
            stack[k] = 'E';
            stack[k+1] = '\0';
            stack[k+2] = '\0';
            printf("\n$%s\t%s\t%s", stack, input_string, act);
            i -= 2;
        }
    }

    // Check for E*E pattern in the stack
    for(int k=0; k < input_length; k++)
    {
        if(stack[k] == 'E' && stack[k+1] == '*' && stack[k+2] == 'E')
        {
            stack[k] = 'E';
            stack[k+1] = '\0';
            stack[k+2] = '\0';
            printf("\n$%s\t%s\t%s", stack, input_string, act);
            i -= 2;
        }
    }

    // Check for (E) pattern in the stack
    for(int k=0; k < input_length; k++)
    {
        if(stack[k] == '(' && stack[k+1] == 'E' && stack[k+2] == ')')
        {
            stack[k] = 'E';
            stack[k+1] = '\0';
            stack[k+2] = '\0';
            printf("\n$%s\t%s\t%s", stack, input_string, act);
            i -= 2;
        }
    }
}