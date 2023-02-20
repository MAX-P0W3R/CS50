#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // TODO: Prompt for start size
    int start_size;
    do
    {
        start_size = get_int("Starting population size: ");
    }
    while (start_size < 9);

    // TODO: Prompt for end size
    int end_size;
    do
    {
        end_size = get_int("Ending population size: ");
    }
    while (end_size < start_size);

    // TODO: Calculate number of years until we reach threshold
    int year = 0;
    int n = start_size;
    int calculator = 0;

    // TODO: Print number of years
    if (start_size == end_size)
    {
        printf("Years: 0 ");
    }

    do
    {
        n = round(n + (n / 3) - (n / 4));
        year += 1;
    }
    while (n < end_size);
    printf("Years: %i\n", year);
}
