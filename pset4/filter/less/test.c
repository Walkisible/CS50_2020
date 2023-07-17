#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    int list[9] = {10, 40, 70, 110, 120, 130, 200, 220, 240};

    float sum =   list[0]  + list[1]    + list[2]
                + list[3]  + list[4]    + list[5]
                + list[6]  + list[7]    + list[8];

    float avg = sum / 9;
    int result = round(avg);

    printf("%f\n", sum);
    printf("%f\n", avg);
    printf("%i\n", result);
}