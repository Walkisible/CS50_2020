#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

int main(void)
{
//Get the text input from user
    string text = get_string("Text: ");

//Letters counting
    int count_letters = 0;
    int count_blank = 0;
    int count_digit = 0;
    int count_punct = 0;
    int tmp_letters = 0;

    tmp_letters = strlen(text);

    for (int a = 0; text[a]; a++)
    {
        if (isblank(text[a]))
        {
            count_blank++;
        }
    }
    for (int b = 0; text[b]; b++)
    {
        if (isdigit(text[b]))
        {
            count_digit++;
        }
    }
    for (int c = 0; text[c]; c++)
    {
        if (ispunct(text[c]))
        {
            count_punct++;
        }
    }
    count_letters = tmp_letters - count_blank - count_digit - count_punct;

//Words counting
    int count_words = 0;

    for (int d = 0; text[d] != '\0'; d++)
    {
        if (text[d] == ' ' && text[d + 1] != ' ')
        {
            count_words++;
        }
    }
    count_words += 1;

//Sentences counting
    int count_sentences = 0;

    for (int e = 0; text[e] != '\0'; e++)
    {
        if (text[e] == '.' || text[e] == '!' || text[e] == '?')
        {
            count_sentences++;
        }
    }

//Coleman-Liau index
    float L = 0;
    float S = 0;;
    float index = 0;
    float x = count_letters;
    float y = count_words;
    float z = count_sentences;

    L = 100 * (x / y);
    S = 100 * (z / y);

    index = (0.0588 * L) - (0.296 * S) - 15.8;
    int grade = round(index);

//Grade claasification
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
    return 0;
}