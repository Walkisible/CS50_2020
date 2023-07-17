#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
//card_num defines as user's input
    long card_num = get_long("Number: ");
//-----------------------------------------------------------//
//Parameters define
    int digit = 0;
    int count = 0;
    int sum = 0;
    long temp_num = card_num;
    long count_num = card_num;
//-----------------------------------------------------------//
//Finding digits of the input
    while (count_num > 0)
    {
        count++;
        digit = count_num / 10;
        count_num /= 10;
    }
//-----------------------------------------------------------//
//Luhn's algorithm
    for (int i = 1; i < count + 1; i++)
    {
        int digit_num = temp_num % 10;
        if (i % 2 == 0)
        {
            digit_num *= 2;
            if (digit_num > 9)
            {
                digit_num -= 9;
            }
        }
        sum += digit_num;
        temp_num /= 10;
    }
//-----------------------------------------------------------//
//Create the company_id
    long temp_id = card_num;
    while (temp_id > 100)
    {
        temp_id /= 10;
    }
    int company_id = temp_id;
//-----------------------------------------------------------//
//Checking card type: AMEX, MASTERCARD, VISA
    if ((sum % 10 == 0) && (count == 13) && (company_id >= 40 && company_id <= 49))
    {
        printf("VISA\n");
    }
    else if ((sum % 10 == 0) && (count == 15) && (company_id == 34 || company_id == 37))
    {
        printf("AMEX\n");
    }
    else if ((sum % 10 == 0) && (count == 16))
    {
        if (company_id >= 51 && company_id <= 55)
        {
        printf("MASTERCARD\n");
        }
        else if (company_id >= 40 && company_id <= 49)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
    return 0;
}
