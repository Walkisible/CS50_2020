#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Checkimg input
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    // Create # table
    for (int a = 1; a <= n; a++)
    {
        for (int b = n; b > a; b--)
        {
            printf(" ");
        }
        for (int c = 1; c <= a; c++ )
        {
            printf("#");
        }
        printf("  ");
        for (int d = 1; d <= a; d++)
        {
            printf("#");
        }
        printf("\n");
    }
    return 0;
}
