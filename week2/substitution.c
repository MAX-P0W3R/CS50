# This is still a work in progress -- NOT FINISHED

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool validateKey();
bool verifyKeyOnlyContainsLetters();
bool checkIfKeyContainsAllUniqueCharacters();
void convertToUppercase();

string convertToCipherText(string plaintext);
string key;

int main(int argc, string argv[])
{
    // Check for key
    if (argv[1] == NULL)
    {
        printf("You must provide a 26 digit alphabetic key containing each letter once and only once.\n");
        printf("example: vchprzgjntlskfbdqwaxeuymoi\n");
        return 1;
    }

    // Assign key to global variable and convert to uppercase
    key = argv[1];
    convertToUppercase(key);

    // Check if key validates
    if (!validateKey())
    {
        return 1;
    }

    string plaintext = get_string("plaintext: ");
    printf("Ciphertext: %s\n", convertToCipherText(plaintext));
    return 0;
}

// Iterate and convert to uppercase
void convertToUppercase()
{
    for (int i = 0; i < strlen(key); i++)
    {
        key[i] = toupper(key[i]);
    }
}

    // Verify key validity
bool validateKey()
{
    if (!verifyKeyOnlyContainsLetters()) //See line 75.
    {
        printf("Key must only contain letters.\n");
        return false;
    }
    if (strlen(key) != 26) //Makes sure the key is exactly 26 characters long.
    {
        printf("Key must contain exactly 26 characters.\n");
        return false;
    }

    if (!checkIfKeyContainsAllUniqueCharacters()) //See line 91.
    {
        printf("Key must contain each character once and only once.\n");
        return false;
    }

    //If all the tests pass, result is assigned true and returned.
    return true;
}

bool verifyKeyOnlyContainsLetters()
{
    //Loops through every character of the key and checks that they're all between the range of the uppercase alphabet.
    //(key was converted to uppercase earlier, avoid checking the lowercase letters.)
    for (int i = 0; i < strlen(key); i++)
    {
        if (!isupper(key[i]))
        {
            return false;
        }
    }
    return true;
}

bool checkIfKeyContainsAllUniqueCharacters()
{
    int containsLetter = 0;

    //Function loops through the alphabet checking each character of the key as it goes.
    for (char currentChar = 'A'; currentChar <= 'Z'; currentChar++)
    {
        for (int i = 0; i <= strlen(key); i++)
        {
            //If the key contains the current letter, it incriments the counter variable (containsLetter) and then moves on to the next letter.
            if (currentChar == key[i])
            {
                containsLetter++;
                //Break statement is essential as once it see's a character in the key it stops and moves on to the next alphabetic character, this checks for duplicate letters within the key.
                break;
            }
        }
    }

    //If the counter was successfully incremented to 26 i.e it contains each letter once and only once, result is then assigned true and returned.
    return (containsLetter == 26);
}

string convertToCipherText(string plaintext)
{
    string ciphertext = plaintext;

    for (int i = 0; i < strlen(ciphertext); i++)
    {
        //If block to ignore punctuation.

        //Checks if the plaitext is a capital letter, if so it takes off 97 (see asciichart.com) to get the index to 0 and assigns the corresponding key value to the ciphertext.
        if (isupper(plaintext[i]))
        {
            ciphertext[i] = key[plaintext[i] - 65];
        }
        //Same as previous step but for lowercase letters. Takes off 97 this time and then converts the assigned character to lowercase as the key is all uppercase characters.
        if (islower(plaintext[i]))
        {
            ciphertext[i] = key[plaintext[i] - 97];
            ciphertext[i] = tolower(ciphertext[i]);
        }
    }

    return ciphertext;
}
