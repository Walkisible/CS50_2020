#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
//Get the key
    if (argc == 2)
    {
        int count_argv = 0;
        int count_digit = 0;
        int count_same_alph = 0;
        //argv counting
        for (int a = 0; argv[1][a]; a++)
        {
            if (isalpha(argv[1][a]))
            {
                count_argv++;
            }
        }
        //argv digit checking
        for (int b = 0; argv[1][b]; b++)
        {
            if (isdigit(argv[1][b]))
            {
                count_digit++;
            }
        }
        //argv same char checking
        for (int c = 0; argv[1][c]; c++)
        {
            for (int d = c + 1; argv[1][d]; d++)
            {
                if (argv[1][c] == argv[1][d])
                {
                    count_same_alph++;
                }
            };
        }
        //Key checking
        if (count_same_alph > 0)
        {
            printf("Key must not contain repeated characters.\n");
            return 1;
        }
        if (count_digit > 0)
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
        else if (count_argv != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
//Get plaintext
    string plaintext = get_string("plaintext: ");
//Encipher
    int tmp_i = 0;

    char alphabet[26];
    alphabet[0] = argv[1][0];
    alphabet[1] = argv[1][1];
    alphabet[2] = argv[1][2];
    alphabet[3] = argv[1][3];
    alphabet[4] = argv[1][4];
    alphabet[5] = argv[1][5];
    alphabet[6] = argv[1][6];
    alphabet[7] = argv[1][7];
    alphabet[8] = argv[1][8];
    alphabet[9] = argv[1][9];
    alphabet[10] = argv[1][10];
    alphabet[11] = argv[1][11];
    alphabet[12] = argv[1][12];
    alphabet[13] = argv[1][13];
    alphabet[14] = argv[1][14];
    alphabet[15] = argv[1][15];
    alphabet[16] = argv[1][16];
    alphabet[17] = argv[1][17];
    alphabet[18] = argv[1][18];
    alphabet[19] = argv[1][19];
    alphabet[20] = argv[1][20];
    alphabet[21] = argv[1][21];
    alphabet[22] = argv[1][22];
    alphabet[23] = argv[1][23];
    alphabet[24] = argv[1][24];
    alphabet[25] = argv[1][25];

    printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (plaintext[i] >= 65 && plaintext[i] <= 90)
        {
            tmp_i = plaintext[i] - 65;
            printf("%c", toupper(alphabet[tmp_i]));
        }
        else if (plaintext[i] >= 97 && plaintext[i] <= 122)
        {
            tmp_i = plaintext[i] - 97;
            printf("%c", tolower(alphabet[tmp_i]));
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
    return 0;
}