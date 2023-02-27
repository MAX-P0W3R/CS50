#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    int length = strlen(input);

    if (length == 1)
    {
        return input[0] - '0';
    }

    char last_digit = input[length - 1]; //Start by getting the index of the last char in the string (the char before the \0).

    int converted_last_digit = last_digit - '0'; //Convert this char into its numeric value. Can you subtract some char to do this?

    input[length - 1] = '\0'; //Remove the last char from the string by moving the null terminator one position to the left.

    return converted_last_digit + 10 * convert(input); //Return this value plus 10 times the integer value of the new shortened string.

    return 1;
}
