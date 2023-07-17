#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // Check invalidity
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open input file
    FILE *input = fopen(argv[1], "r");
    if (!input)
    {
        return 1;
    }

    // Parameters define
    unsigned char buffer[512];
    char filename[8];
    int num = 0;

    // Open output file
    FILE *output = NULL;

    // Read until end of card
    while (fread(buffer, sizeof(buffer), 1, input) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (output == NULL)
            {
                sprintf(filename, "%03i.jpg", num++);
                output = fopen(filename, "w");
                fwrite(&buffer, sizeof(buffer), 1, output);
            }
            else
            {
                fclose(output);
                sprintf(filename, "%03i.jpg", num++);
                output = fopen(filename, "w");
                fwrite(&buffer, sizeof(buffer), 1, output);
            }
        }
        else
        {
            if (output != NULL)
            {
                fwrite(&buffer, sizeof(buffer), 1, output);
            }
        }
    }

    fclose(input);
    fclose(output);

    return 0;
}