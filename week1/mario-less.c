#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt user for height between 1 & 8; reprompt if anything else
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    //Form left aligned pyramid, each # then new line
    for (int i = 0; i < n; i++)
    {
        for (int j = n - 1; j > i; j--)
        {
            printf(" ");
        }
        for (int k = -1; k < i; k++)
        {
            printf("#");
        }
        printf("\n");
    }

}
