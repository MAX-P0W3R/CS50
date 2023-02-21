// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch
// a => 6; e => 3, i => 1; o => 0
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string replace(string input);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./no-vowels word\n");
        return 1;
    }
    string word = argv[1];

    string result = replace(word);

    printf("%s\n", result);
}

string replace(string input)
{
    string output = input;

    for (int i = 0; i < strlen(input); i++)
    {
        char c = tolower(input[i]);
        switch (c)
        {
            case 'a':
                output[i] = '6';
                break;

            case 'e':
                output[i] = '3';
                break;

            case 'i':
                output[i] = '1';
                break;

            case 'o':
                output[i] = '0';
                break;

            default:
                output[i] = input[i];
                break;
        }
    }
    return output;
}
