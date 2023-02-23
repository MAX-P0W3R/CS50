#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
    // Prompt use for input
    string text = get_string("Text: ");
    printf("%s\n", text);

    // Count number of letters in text; exclude punctuation
    int letters = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') ||
                (text[i] >= 'A' && text[i] <= 'Z'))
                letters++;
    }
    printf("%i letters\n", letters);

    // Print number of words
    int words = 1;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == ' ')
        words++;
    }
    printf("%i words\n", words);

    // Print number sentences; sequences that end with => '.', '!', '?'
    int sentences = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        sentences++;

    }
    printf("%i sentences\n", sentences);

    // Apply Coleman-Liau index
    float calculation = (0.0588 * letters / words * 100) - (0.296 * sentences / words * 100) - 15.8;
    int index = round(calculation);

    if (index < 1)
    {
        printf("Before Grade 1\n");
        return 0;
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
        return 0;
    }
    else
    {
        printf("Grade %i\n", index);
    }
}
