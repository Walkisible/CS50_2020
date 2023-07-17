#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float dollars;
    do
    {
        dollars = get_float("Change owed: ");
    }
    while (dollars < 0);

    int coins = round(dollars * 100);
    int count = 0;

    while(coins >= 25)
    {
        count++;
        coins -= 25;
    }
    while(coins >= 10)
    {
        count++;
        coins -= 10;
    }
    while(coins >= 5)
    {
        count++;
        coins -= 5;
    }
    while(coins >= 1)
    {
        count++;
        coins -= 1;
    }

    printf("%i\n", count);
    return 0;
}
