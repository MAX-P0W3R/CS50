#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // Program takes one, non-negative argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        printf("Success\n");
    }
    // Define key
    string key = argv[1];

    // argv[] is a digit
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isdigit(argv[1][i]))
        {
        printf("Usage: ./caesar key\n");
        return 1;
        }
    }
    printf("%s\n", key);

    // Prompt user for plaintext input
    string plaintext = get_string("Plaintext: ");

    // Convert key to integer
    int k = atoi(key);
    printf("Ciphertext: ");

    // Get ciphertext
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (isupper(plaintext[i]))
        {
            printf("%c", (((plaintext[i] - 65) + k) % 26) + 65);
        }
        else if (islower(plaintext[i]))
        {
            printf("%c", (((plaintext[i] - 97) + k) % 26) + 97);
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
}
