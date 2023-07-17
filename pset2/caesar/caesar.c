#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
//Get key
    if (argc == 2)
    {
        int a = strlen(argv[1]);
        int count_digit = 0;

        for (int b = 0; argv[1][b]; b++)
        {
            if (isdigit(argv[1][b]))
            {
                count_digit++;
            }
        }

        if (argc != 2 || count_digit != a)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
//Get plaintext
    string plaintext = get_string("plaintext: ");
//Encipher
    int k = atoi(argv[1]);
    int Ci = 0;
    int Pi = 0;

    char alphabet[26];
    alphabet[0] = 'A';
    alphabet[1] = 'B';
    alphabet[2] = 'C';
    alphabet[3] = 'D';
    alphabet[4] = 'E';
    alphabet[5] = 'F';
    alphabet[6] = 'G';
    alphabet[7] = 'H';
    alphabet[8] = 'I';
    alphabet[9] = 'J';
    alphabet[10] = 'K';
    alphabet[11] = 'L';
    alphabet[12] = 'M';
    alphabet[13] = 'N';
    alphabet[14] = 'O';
    alphabet[15] = 'P';
    alphabet[16] = 'Q';
    alphabet[17] = 'R';
    alphabet[18] = 'S';
    alphabet[19] = 'T';
    alphabet[20] = 'U';
    alphabet[21] = 'V';
    alphabet[22] = 'W';
    alphabet[23] = 'X';
    alphabet[24] = 'Y';
    alphabet[25] = 'Z';

    printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (plaintext[i] >= 65 && plaintext[i] <= 90)
        {
            Pi = plaintext[i] -= 65;
            Ci = (Pi + k) % 26;
            printf("%c", alphabet[Ci]);
            Ci = 0;
            Pi = 0;
        }
        else if (plaintext[i] >= 97 && plaintext[i] <= 122)
        {
            Pi = plaintext[i] -= 97;
            Ci = (Pi + k) % 26;
            printf("%c", tolower(alphabet[Ci]));
            Ci = 0;
            Pi = 0;
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
    return 0;
}