# include <cs50.h>
# include <stdio.h>

int main(void)
// Ask your mom's name
{
    string answer = get_string("What's your name? ");
    printf("Hello, %s\n", answer);
}
