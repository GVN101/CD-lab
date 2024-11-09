#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
int main()
{
    FILE *input, *output;
    int l = 1;
    int t = 0;
    int j = 0;
    int i, flag;
    char ch, str[20];
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    char keyword[30][30] = {"int", "main", "if", "else", "do", "while"};
    fprintf(output, "Line no. \t Token no. \t\t Token \t\t Lexeme\n\n");
    
    while (!feof(input))
    {
        i = 0;
        flag = 0;
        ch = fgetc(input);
        
        // Check for single-line comments (//)
        if (ch == '/')
        {
            char nextChar = fgetc(input);
            if (nextChar == '/')
            {
                fprintf(output, "%7d\t\t %7d\t\t Comment\t Single-line comment\n", l, t);
                t++;
                while (ch != '\n' && !feof(input))
                {
                    ch=fgetc(input); // Process the rest of the line
                }
                l++; // Since it's a new line
            }
            else if (nextChar=='*')
            {
                fprintf(output, "%7d\t\t %7d\t\t Comment\t Multi-line comment start\n", l, t);
                t++;
                char prevChar = '\0';
                while (!(prevChar == '*' && ch == '/') && !feof(input)) // Look for */
                {
                    prevChar = ch;
                    ch = fgetc(input);
                    if (ch == '\n') // If there's a new line inside the comment
                        l++;
                }
                fprintf(output, "%7d\t\t %7d\t\t Comment\t Multi-line comment end\n", l, t);
                t++;
            }
            else
            {
                ungetc(nextChar, input); // Push back the character if not a comment
            }
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        {
            fprintf(output, "%7d\t\t %7d\t\t Operator\t %7c\n", l, t, ch);
            t++;
        }
        else if (ch == ';' || ch == '{' || ch == '}' || ch == '(' || ch == ')' || ch == '?' || ch == '@' || ch == '!' || ch == '%')
        {
            fprintf(output, "%7d\t\t %7d\t\t Special symbol\t %7c\n", l, t, ch);
            t++;
        }
        else if (isdigit(ch))
        {
            fprintf(output, "%7d\t\t %7d\t\t Digit\t\t %7c\n", l, t, ch);
            t++;
        }
        else if (isalpha(ch))
        {
            str[i] = ch;
            i++;
            ch = fgetc(input);
            while (isalnum(ch) && ch != ' ')
            {
                str[i] = ch;
                i++;
                ch = fgetc(input);
            }
            str[i] = '\0';
            for (j = 0; j <= 30; j++)
            {
                if (strcmp(str, keyword[j]) == 0)
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 1)
            {
                fprintf(output, "%7d\t\t %7d\t\t Keyword\t %7s\n", l, t, str);
                t++;
            }
            else
            {
                fprintf(output, "%7d\t\t %7d\t\t Identifier\t %7s\n", l, t, str);
                t++;
            }
        }
        else if (ch == '\n')
        {
            l++;
        }
    }
    fclose(input);
    fclose(output);
    return 0;
}