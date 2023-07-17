#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average = 0;
    float f_average = 0;

    float blue = 0;
    float green = 0;
    float red = 0;

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            average = 0;
            f_average = 0;

            blue = image[h][w].rgbtBlue;
            green = image[h][w].rgbtGreen;
            red = image[h][w].rgbtRed;

            f_average = (blue + green + red) / 3;
            average = round(f_average);

            image[h][w].rgbtBlue = average;
            image[h][w].rgbtGreen = average;
            image[h][w].rgbtRed = average;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float originalBlue = 0;
    float originalGreen = 0;
    float originalRed = 0;

    float sepiaBlue = 0;
    float sepiaGreen = 0;
    float sepiaRed = 0;

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            originalBlue = image[h][w].rgbtBlue;
            originalGreen = image[h][w].rgbtGreen;
            originalRed = image[h][w].rgbtRed;

            sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;
            sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;
            sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue;

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            image[h][w].rgbtBlue = round(sepiaBlue);
            image[h][w].rgbtGreen = round(sepiaGreen);
            image[h][w].rgbtRed = round(sepiaRed);
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width / 2; w++)
        {
            RGBTRIPLE temp = image[h][w];
            image[h][w] = image[h][width - (w + 1)];
            image[h][width - (w + 1)] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int tmp_Red[height][width];
    int tmp_Green[height][width];
    int tmp_Blue[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < height; w++)
        {
            tmp_Red[h][w] = 0;
            tmp_Green[h][w] = 0;
            tmp_Blue[h][w] = 0;
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //find average color value
            float sumRed = 0;
            float sumGreen = 0;
            float sumBlue = 0;

            float n = 0;

            float avgRed = 0;
            float avgGreen = 0;
            float avgBlue = 0;
            //height direction
            int A = h - 1;
            int B = h;
            int C = h + 1;
            //width direction
            int a = w - 1;
            int b = w;
            int c = w + 1;

            if (h == 0)
            {
                if (w == 0) //top-left corner
                {
                    n = 4;
                    sumRed =    (     image[B][b].rgbtRed + image[B][c].rgbtRed
                                    + image[C][b].rgbtRed + image[C][c].rgbtRed
                                );
                    sumGreen =  (     image[B][b].rgbtGreen + image[B][c].rgbtGreen
                                    + image[C][b].rgbtGreen + image[C][c].rgbtGreen
                                );

                    sumBlue =   (     image[B][b].rgbtBlue + image[B][c].rgbtBlue
                                    + image[C][b].rgbtBlue + image[C][c].rgbtBlue
                                );
                }
                else if (w == width - 1) //top-right corner
                {
                    n = 4;
                    sumRed =    (     image[B][a].rgbtRed + image[B][b].rgbtRed
                                    + image[C][a].rgbtRed + image[C][b].rgbtRed
                                );
                    sumGreen =  (     image[B][a].rgbtGreen + image[B][b].rgbtGreen
                                    + image[C][a].rgbtGreen + image[C][b].rgbtGreen
                                );

                    sumBlue =   (     image[B][a].rgbtBlue + image[B][b].rgbtBlue
                                    + image[C][a].rgbtBlue + image[C][b].rgbtBlue
                                );
                }
                else //top edge
                {
                    n = 6;
                    sumRed =    (     image[B][a].rgbtRed + image[B][b].rgbtRed + image[B][c].rgbtRed
                                    + image[C][a].rgbtRed + image[C][b].rgbtRed + image[C][c].rgbtRed
                                );
                    sumGreen =  (     image[B][a].rgbtGreen + image[B][b].rgbtGreen + image[B][c].rgbtGreen
                                    + image[C][a].rgbtGreen + image[C][b].rgbtGreen + image[C][c].rgbtGreen
                                );

                    sumBlue =   (     image[B][a].rgbtBlue + image[B][b].rgbtBlue + image[B][c].rgbtBlue
                                    + image[C][a].rgbtBlue + image[C][b].rgbtBlue + image[C][c].rgbtBlue
                                );
                }
            }
            else if (h == height - 1)
            {
                if (w == 0) //bottom-left corner
                {
                    n = 4;
                    sumRed =    (     image[A][b].rgbtRed + image[A][c].rgbtRed
                                    + image[B][b].rgbtRed + image[B][c].rgbtRed
                                );
                    sumGreen =  (     image[A][b].rgbtGreen + image[A][c].rgbtGreen
                                    + image[B][b].rgbtGreen + image[B][c].rgbtGreen
                                );

                    sumBlue =   (     image[A][b].rgbtBlue + image[A][c].rgbtBlue
                                    + image[B][b].rgbtBlue + image[B][c].rgbtBlue
                                );
                }
                else if (w == width - 1) //bottom-right corner
                {
                    n = 4;
                    sumRed =    (     image[A][a].rgbtRed + image[A][b].rgbtRed
                                    + image[B][a].rgbtRed + image[B][b].rgbtRed
                                );
                    sumGreen =  (     image[A][a].rgbtGreen + image[A][b].rgbtGreen
                                    + image[B][a].rgbtGreen + image[B][b].rgbtGreen
                                );

                    sumBlue =   (     image[A][a].rgbtBlue + image[A][b].rgbtBlue
                                    + image[B][a].rgbtBlue + image[B][b].rgbtBlue
                                );
                }
                else //bottom edge
                {
                    n = 6;
                    sumRed =    (     image[A][a].rgbtRed + image[A][b].rgbtRed + image[A][c].rgbtRed
                                    + image[B][a].rgbtRed + image[B][b].rgbtRed + image[B][c].rgbtRed
                                );
                    sumGreen =  (     image[A][a].rgbtGreen + image[A][b].rgbtGreen + image[A][c].rgbtGreen
                                    + image[B][a].rgbtGreen + image[B][b].rgbtGreen + image[B][c].rgbtGreen
                                );

                    sumBlue =   (     image[A][a].rgbtBlue + image[A][b].rgbtBlue + image[A][c].rgbtBlue
                                    + image[B][a].rgbtBlue + image[B][b].rgbtBlue + image[B][c].rgbtBlue
                                );
                }
            }
            else if (w == 0) //left edge
            {
                n = 6;
                    sumRed =    (     image[A][b].rgbtRed + image[A][c].rgbtRed
                                    + image[B][b].rgbtRed + image[B][c].rgbtRed
                                    + image[C][b].rgbtRed + image[C][c].rgbtRed
                                );
                    sumGreen =  (     image[A][b].rgbtGreen + image[A][c].rgbtGreen
                                    + image[B][b].rgbtGreen + image[B][c].rgbtGreen
                                    + image[C][b].rgbtGreen + image[C][c].rgbtGreen
                                );

                    sumBlue =   (     image[A][b].rgbtBlue + image[A][c].rgbtBlue
                                    + image[B][b].rgbtBlue + image[B][c].rgbtBlue
                                    + image[C][b].rgbtBlue + image[C][c].rgbtBlue
                                );
            }
            else if (w == width - 1) //right edge
            {
                n = 6;
                    sumRed =    (     image[A][a].rgbtRed + image[A][b].rgbtRed
                                    + image[B][a].rgbtRed + image[B][b].rgbtRed
                                    + image[C][a].rgbtRed + image[C][b].rgbtRed
                                );
                    sumGreen =  (     image[A][a].rgbtGreen + image[A][b].rgbtGreen
                                    + image[B][a].rgbtGreen + image[B][b].rgbtGreen
                                    + image[C][a].rgbtGreen + image[C][b].rgbtGreen
                                );

                    sumBlue =   (     image[A][a].rgbtBlue + image[A][b].rgbtBlue
                                    + image[B][a].rgbtBlue + image[B][b].rgbtBlue
                                    + image[C][a].rgbtBlue + image[C][b].rgbtBlue
                                );
            }
            else //middle pieces
            {
                n = 9;
                sumRed =    (     image[A][a].rgbtRed + image[A][b].rgbtRed + image[A][c].rgbtRed
                                + image[B][a].rgbtRed + image[B][b].rgbtRed + image[B][c].rgbtRed
                                + image[C][a].rgbtRed + image[C][b].rgbtRed + image[C][c].rgbtRed
                            );

                sumGreen =  (     image[A][a].rgbtGreen + image[A][b].rgbtGreen + image[A][c].rgbtGreen
                                + image[B][a].rgbtGreen + image[B][b].rgbtGreen + image[B][c].rgbtGreen
                                + image[C][a].rgbtGreen + image[C][b].rgbtGreen + image[C][c].rgbtGreen
                            );

                sumBlue =   (     image[A][a].rgbtBlue + image[A][b].rgbtBlue + image[A][c].rgbtBlue
                                + image[B][a].rgbtBlue + image[B][b].rgbtBlue + image[B][c].rgbtBlue
                                + image[C][a].rgbtBlue + image[C][b].rgbtBlue + image[C][c].rgbtBlue
                            );
            }

            avgRed = sumRed / n;
            avgGreen = sumGreen / n;
            avgBlue = sumBlue / n;

            tmp_Red[h][w] = round(avgRed);
            tmp_Green[h][w] = round(avgGreen);
            tmp_Blue[h][w] = round(avgBlue);
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < height; w++)
        {
            image[h][w].rgbtRed = tmp_Red[h][w];
            image[h][w].rgbtGreen = tmp_Green[h][w];
            image[h][w].rgbtBlue = tmp_Blue[h][w];
        }
    }
}
