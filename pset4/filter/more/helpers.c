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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3];

        Gx[0][0] = -1,  Gx[0][1] =  0,  Gx[0][2] =  1,
        Gx[1][0] = -2,  Gx[1][1] =  0,  Gx[1][2] =  2,
        Gx[2][0] = -1,  Gx[2][1] =  0,  Gx[2][2] =  1;

    int Gy[3][3];

        Gy[0][0] = -1,  Gy[0][1] = -2,  Gy[0][2] = -1,
        Gy[1][0] =  0,  Gy[1][1] =  0,  Gy[1][2] =  0,
        Gy[2][0] =  1,  Gy[2][1] =  2,  Gy[2][2] =  1;

    float Gx_R[height][width];
    float Gx_G[height][width];
    float Gx_B[height][width];

    float Gy_R[height][width];
    float Gy_G[height][width];
    float Gy_B[height][width];

    float final_R[height][width];
    float final_G[height][width];
    float final_B[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < height; w++)
        {
            Gx_R[h][w] = 0;
            Gx_G[h][w] = 0;
            Gx_B[h][w] = 0;

            Gy_R[h][w] = 0;
            Gy_G[h][w] = 0;
            Gy_B[h][w] = 0;

            final_R[h][w] = 0;
            final_G[h][w] = 0;
            final_B[h][w] = 0;
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
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
                    //Gx
                    Gx_R[h][w] =  (   (Gx[0][0] * 0) + (Gx[0][1] * 0)                   + (Gx[0][2] * 0)
                                    + (Gx[1][0] * 0) + (Gx[1][1] * image[B][b].rgbtRed) + (Gx[1][2] * image[B][c].rgbtRed)
                                    + (Gx[2][0] * 0) + (Gx[2][1] * image[C][b].rgbtRed) + (Gx[2][2] * image[C][c].rgbtRed)
                                  );

                    Gx_G[h][w] =  (   (Gx[0][0] * 0) + (Gx[0][1] * 0)                     + (Gx[0][2] * 0)
                                    + (Gx[1][0] * 0) + (Gx[1][1] * image[B][b].rgbtGreen) + (Gx[1][2] * image[B][c].rgbtGreen)
                                    + (Gx[2][0] * 0) + (Gx[2][1] * image[C][b].rgbtGreen) + (Gx[2][2] * image[C][c].rgbtGreen)
                                  );

                    Gx_B[h][w] =  (   (Gx[0][0] * 0) + (Gx[0][1] * 0)                    + (Gx[0][2] * 0)
                                    + (Gx[1][0] * 0) + (Gx[1][1] * image[B][b].rgbtBlue) + (Gx[1][2] * image[B][c].rgbtBlue)
                                    + (Gx[2][0] * 0) + (Gx[2][1] * image[C][b].rgbtBlue) + (Gx[2][2] * image[C][c].rgbtBlue)
                                  );
                    //Gy
                    Gy_R[h][w] =  (   (Gy[0][0] * 0) + (Gy[0][1] * 0)                   + (Gy[0][2] * 0)
                                    + (Gy[1][0] * 0) + (Gy[1][1] * image[B][b].rgbtRed) + (Gy[1][2] * image[B][c].rgbtRed)
                                    + (Gy[2][0] * 0) + (Gy[2][1] * image[C][b].rgbtRed) + (Gy[2][2] * image[C][c].rgbtRed)
                                  );

                    Gy_G[h][w] =  (   (Gy[0][0] * 0) + (Gy[0][1] * 0)                     + (Gy[0][2] * 0)
                                    + (Gy[1][0] * 0) + (Gy[1][1] * image[B][b].rgbtGreen) + (Gy[1][2] * image[B][c].rgbtGreen)
                                    + (Gy[2][0] * 0) + (Gy[2][1] * image[C][b].rgbtGreen) + (Gy[2][2] * image[C][c].rgbtGreen)
                                  );

                    Gy_B[h][w] =  (   (Gy[0][0] * 0) + (Gy[0][1] * 0)                    + (Gy[0][2] * 0)
                                    + (Gy[1][0] * 0) + (Gy[1][1] * image[B][b].rgbtBlue) + (Gy[1][2] * image[B][c].rgbtBlue)
                                    + (Gy[2][0] * 0) + (Gy[2][1] * image[C][b].rgbtBlue) + (Gy[2][2] * image[C][c].rgbtBlue)
                                  );
                }
                else if (w == width - 1) //top-right corner
                {
                    //Gx
                    Gx_R[h][w] =  (   (Gx[0][0] * 0)                   + (Gx[0][1] * 0)                   + (Gx[0][2] * 0)
                                    + (Gx[1][0] * image[B][a].rgbtRed) + (Gx[1][1] * image[B][b].rgbtRed) + (Gx[1][2] * 0)
                                    + (Gx[2][0] * image[C][a].rgbtRed) + (Gx[2][1] * image[C][b].rgbtRed) + (Gx[2][2] * 0)
                                  );

                    Gx_G[h][w] =  (   (Gx[0][0] * 0)                     + (Gx[0][1] * 0)                     + (Gx[0][2] * 0)
                                    + (Gx[1][0] * image[B][a].rgbtGreen) + (Gx[1][1] * image[B][b].rgbtGreen) + (Gx[1][2] * 0)
                                    + (Gx[2][0] * image[C][a].rgbtGreen) + (Gx[2][1] * image[C][b].rgbtGreen) + (Gx[2][2] * 0)
                                  );

                    Gx_B[h][w] =  (   (Gx[0][0] * 0)                    + (Gx[0][1] * 0)                    + (Gx[0][2] * 0)
                                    + (Gx[1][0] * image[B][a].rgbtBlue) + (Gx[1][1] * image[B][b].rgbtBlue) + (Gx[1][2] * 0)
                                    + (Gx[2][0] * image[C][a].rgbtBlue) + (Gx[2][1] * image[C][b].rgbtBlue) + (Gx[2][2] * 0)
                                  );
                    //Gy
                    Gy_R[h][w] =  (   (Gy[0][0] * 0)                   + (Gy[0][1] * 0)                   + (Gy[0][2] * 0)
                                    + (Gy[1][0] * image[B][a].rgbtRed) + (Gy[1][1] * image[B][b].rgbtRed) + (Gy[1][2] * 0)
                                    + (Gy[2][0] * image[C][a].rgbtRed) + (Gy[2][1] * image[C][b].rgbtRed) + (Gy[2][2] * 0)
                                  );

                    Gy_G[h][w] =  (   (Gy[0][0] * 0)                     + (Gy[0][1] * 0)                     + (Gy[0][2] * 0)
                                    + (Gy[1][0] * image[B][a].rgbtGreen) + (Gy[1][1] * image[B][b].rgbtGreen) + (Gy[1][2] * 0)
                                    + (Gy[2][0] * image[C][a].rgbtGreen) + (Gy[2][1] * image[C][b].rgbtGreen) + (Gy[2][2] * 0)
                                  );

                    Gy_B[h][w] =  (   (Gy[0][0] * 0)                    + (Gy[0][1] * 0)                    + (Gy[0][2] * 0)
                                    + (Gy[1][0] * image[B][a].rgbtBlue) + (Gy[1][1] * image[B][b].rgbtBlue) + (Gy[1][2] * 0)
                                    + (Gy[2][0] * image[C][a].rgbtBlue) + (Gy[2][1] * image[C][b].rgbtBlue) + (Gy[2][2] * 0)
                                  );
                }
                else //top edge
                {
                    //Gx
                    Gx_R[h][w] =  (   (Gx[0][0] * 0)                   + (Gx[0][1] * 0)                   + (Gx[0][2] * 0)
                                    + (Gx[1][0] * image[B][a].rgbtRed) + (Gx[1][1] * image[B][b].rgbtRed) + (Gx[1][2] * image[B][c].rgbtRed)
                                    + (Gx[2][0] * image[C][a].rgbtRed) + (Gx[2][1] * image[C][b].rgbtRed) + (Gx[2][2] * image[C][c].rgbtRed)
                                  );

                    Gx_G[h][w] =  (   (Gx[0][0] * 0)                     + (Gx[0][1] * 0)                     + (Gx[0][2] * 0)
                                    + (Gx[1][0] * image[B][a].rgbtGreen) + (Gx[1][1] * image[B][b].rgbtGreen) + (Gx[1][2] * image[B][c].rgbtGreen)
                                    + (Gx[2][0] * image[C][a].rgbtGreen) + (Gx[2][1] * image[C][b].rgbtGreen) + (Gx[2][2] * image[C][c].rgbtGreen)
                                  );

                    Gx_B[h][w] =  (   (Gx[0][0] * 0)                    + (Gx[0][1] * 0)                    + (Gx[0][2] * 0)
                                    + (Gx[1][0] * image[B][a].rgbtBlue) + (Gx[1][1] * image[B][b].rgbtBlue) + (Gx[1][2] * image[B][c].rgbtBlue)
                                    + (Gx[2][0] * image[C][a].rgbtBlue) + (Gx[2][1] * image[C][b].rgbtBlue) + (Gx[2][2] * image[C][c].rgbtBlue)
                                  );
                    //Gy
                    Gy_R[h][w] =  (   (Gy[0][0] * 0)                   + (Gy[0][1] * 0)                   + (Gy[0][2] * 0)
                                    + (Gy[1][0] * image[B][a].rgbtRed) + (Gy[1][1] * image[B][b].rgbtRed) + (Gy[1][2] * image[B][c].rgbtRed)
                                    + (Gy[2][0] * image[C][a].rgbtRed) + (Gy[2][1] * image[C][b].rgbtRed) + (Gy[2][2] * image[C][c].rgbtRed)
                                  );

                    Gy_G[h][w] =  (   (Gy[0][0] * 0)                     + (Gy[0][1] * 0)                     + (Gy[0][2] * 0)
                                    + (Gy[1][0] * image[B][a].rgbtGreen) + (Gy[1][1] * image[B][b].rgbtGreen) + (Gy[1][2] * image[B][c].rgbtGreen)
                                    + (Gy[2][0] * image[C][a].rgbtGreen) + (Gy[2][1] * image[C][b].rgbtGreen) + (Gy[2][2] * image[C][c].rgbtGreen)
                                  );

                    Gy_B[h][w] =  (   (Gy[0][0] * 0)                    + (Gy[0][1] * 0)                    + (Gy[0][2] * 0)
                                    + (Gy[1][0] * image[B][a].rgbtBlue) + (Gy[1][1] * image[B][b].rgbtBlue) + (Gy[1][2] * image[B][c].rgbtBlue)
                                    + (Gy[2][0] * image[C][a].rgbtBlue) + (Gy[2][1] * image[C][b].rgbtBlue) + (Gy[2][2] * image[C][c].rgbtBlue)
                                  );
                }
            }
            else if (h == height - 1)
            {
                if (w == 0) //bottom-left corner
                {
                    //Gx
                    Gx_R[h][w] =  (   (Gx[0][0] * 0) + (Gx[0][1] * image[A][b].rgbtRed) + (Gx[0][2] * image[A][c].rgbtRed)
                                    + (Gx[1][0] * 0) + (Gx[1][1] * image[B][b].rgbtRed) + (Gx[1][2] * image[B][c].rgbtRed)
                                    + (Gx[2][0] * 0) + (Gx[2][1] * 0)                   + (Gx[2][2] * 0)
                                  );

                    Gx_G[h][w] =  (   (Gx[0][0] * 0) + (Gx[0][1] * image[A][b].rgbtGreen) + (Gx[0][2] * image[A][c].rgbtGreen)
                                    + (Gx[1][0] * 0) + (Gx[1][1] * image[B][b].rgbtGreen) + (Gx[1][2] * image[B][c].rgbtGreen)
                                    + (Gx[2][0] * 0) + (Gx[2][1] * 0)                     + (Gx[2][2] * 0)
                                  );

                    Gx_B[h][w] =  (   (Gx[0][0] * 0) + (Gx[0][1] * image[A][b].rgbtBlue) + (Gx[0][2] * image[A][c].rgbtBlue)
                                    + (Gx[1][0] * 0) + (Gx[1][1] * image[B][b].rgbtBlue) + (Gx[1][2] * image[B][c].rgbtBlue)
                                    + (Gx[2][0] * 0) + (Gx[2][1] * 0)                    + (Gx[2][2] * 0)
                                  );
                    //Gy
                    Gy_R[h][w] =  (   (Gy[0][0] * 0) + (Gy[0][1] * image[A][b].rgbtRed) + (Gy[0][2] * image[A][c].rgbtRed)
                                    + (Gy[1][0] * 0) + (Gy[1][1] * image[B][b].rgbtRed) + (Gy[1][2] * image[B][c].rgbtRed)
                                    + (Gy[2][0] * 0) + (Gy[2][1] * 0)                   + (Gy[2][2] * 0)
                                  );

                    Gy_G[h][w] =  (   (Gy[0][0] * 0) + (Gy[0][1] * image[A][b].rgbtGreen) + (Gy[0][2] * image[A][c].rgbtGreen)
                                    + (Gy[1][0] * 0) + (Gy[1][1] * image[B][b].rgbtGreen) + (Gy[1][2] * image[B][c].rgbtGreen)
                                    + (Gy[2][0] * 0) + (Gy[2][1] * 0)                     + (Gy[2][2] * 0)
                                  );

                    Gy_B[h][w] =  (   (Gy[0][0] * 0) + (Gy[0][1] * image[A][b].rgbtBlue) + (Gy[0][2] * image[A][c].rgbtBlue)
                                    + (Gy[1][0] * 0) + (Gy[1][1] * image[B][b].rgbtBlue) + (Gy[1][2] * image[B][c].rgbtBlue)
                                    + (Gy[2][0] * 0) + (Gy[2][1] * 0)                    + (Gy[2][2] * 0)
                                  );
                }
                else if (w == width - 1) //bottom-right corner
                {
                //Gx
                Gx_R[h][w] =  (   (Gx[0][0] * image[A][a].rgbtRed) + (Gx[0][1] * image[A][b].rgbtRed) + (Gx[0][2] * 0)
                                + (Gx[1][0] * image[B][a].rgbtRed) + (Gx[1][1] * image[B][b].rgbtRed) + (Gx[1][2] * 0)
                                + (Gx[2][0] * 0)                   + (Gx[2][1] * 0)                   + (Gx[2][2] * 0)
                              );

                Gx_G[h][w] =  (   (Gx[0][0] * image[A][a].rgbtGreen) + (Gx[0][1] * image[A][b].rgbtGreen) + (Gx[0][2] * 0)
                                + (Gx[1][0] * image[B][a].rgbtGreen) + (Gx[1][1] * image[B][b].rgbtGreen) + (Gx[1][2] * 0)
                                + (Gx[2][0] * 0)                     + (Gx[2][1] * 0)                     + (Gx[2][2] * 0)
                              );

                Gx_B[h][w] =  (   (Gx[0][0] * image[A][a].rgbtBlue) + (Gx[0][1] * image[A][b].rgbtBlue) + (Gx[0][2] * 0)
                                + (Gx[1][0] * image[B][a].rgbtBlue) + (Gx[1][1] * image[B][b].rgbtBlue) + (Gx[1][2] * 0)
                                + (Gx[2][0] * 0)                    + (Gx[2][1] * 0)                    + (Gx[2][2] * 0)
                              );
                //Gy
                Gy_R[h][w] =  (   (Gy[0][0] * image[A][a].rgbtRed) + (Gy[0][1] * image[A][b].rgbtRed) + (Gy[0][2] * 0)
                                + (Gy[1][0] * image[B][a].rgbtRed) + (Gy[1][1] * image[B][b].rgbtRed) + (Gy[1][2] * 0)
                                + (Gx[2][0] * 0)                   + (Gx[2][1] * 0)                   + (Gx[2][2] * 0)
                              );

                Gy_G[h][w] =  (   (Gy[0][0] * image[A][a].rgbtGreen) + (Gy[0][1] * image[A][b].rgbtGreen) + (Gy[0][2] * 0)
                                + (Gy[1][0] * image[B][a].rgbtGreen) + (Gy[1][1] * image[B][b].rgbtGreen) + (Gy[1][2] * 0)
                                + (Gx[2][0] * 0)                     + (Gx[2][1] * 0)                     + (Gx[2][2] * 0)
                              );

                Gy_B[h][w] =  (   (Gy[0][0] * image[A][a].rgbtBlue) + (Gy[0][1] * image[A][b].rgbtBlue) + (Gy[0][2] * 0)
                                + (Gy[1][0] * image[B][a].rgbtBlue) + (Gy[1][1] * image[B][b].rgbtBlue) + (Gy[1][2] * 0)
                                + (Gx[2][0] * 0)                    + (Gx[2][1] * 0)                    + (Gx[2][2] * 0)
                              );
                }
                else //bottom edge
                {
                //Gx
                Gx_R[h][w] =  (   (Gx[0][0] * image[A][a].rgbtRed) + (Gx[0][1] * image[A][b].rgbtRed) + (Gx[0][2] * image[A][c].rgbtRed)
                                + (Gx[1][0] * image[B][a].rgbtRed) + (Gx[1][1] * image[B][b].rgbtRed) + (Gx[1][2] * image[B][c].rgbtRed)
                                + (Gx[2][0] * 0)                   + (Gx[2][1] * 0)                   + (Gx[2][2] * 0)
                              );

                Gx_G[h][w] =  (   (Gx[0][0] * image[A][a].rgbtGreen) + (Gx[0][1] * image[A][b].rgbtGreen) + (Gx[0][2] * image[A][c].rgbtGreen)
                                + (Gx[1][0] * image[B][a].rgbtGreen) + (Gx[1][1] * image[B][b].rgbtGreen) + (Gx[1][2] * image[B][c].rgbtGreen)
                                + (Gx[2][0] * 0)                     + (Gx[2][1] * 0)                     + (Gx[2][2] * 0)
                              );

                Gx_B[h][w] =  (   (Gx[0][0] * image[A][a].rgbtBlue) + (Gx[0][1] * image[A][b].rgbtBlue) + (Gx[0][2] * image[A][c].rgbtBlue)
                                + (Gx[1][0] * image[B][a].rgbtBlue) + (Gx[1][1] * image[B][b].rgbtBlue) + (Gx[1][2] * image[B][c].rgbtBlue)
                                + (Gx[2][0] * 0)                    + (Gx[2][1] * 0)                    + (Gx[2][2] * 0)
                              );
                //Gy
                Gy_R[h][w] =  (   (Gy[0][0] * image[A][a].rgbtRed) + (Gy[0][1] * image[A][b].rgbtRed) + (Gy[0][2] * image[A][c].rgbtRed)
                                + (Gy[1][0] * image[B][a].rgbtRed) + (Gy[1][1] * image[B][b].rgbtRed) + (Gy[1][2] * image[B][c].rgbtRed)
                                + (Gx[2][0] * 0)                   + (Gx[2][1] * 0)                   + (Gx[2][2] * 0)
                              );

                Gy_G[h][w] =  (   (Gy[0][0] * image[A][a].rgbtGreen) + (Gy[0][1] * image[A][b].rgbtGreen) + (Gy[0][2] * image[A][c].rgbtGreen)
                                + (Gy[1][0] * image[B][a].rgbtGreen) + (Gy[1][1] * image[B][b].rgbtGreen) + (Gy[1][2] * image[B][c].rgbtGreen)
                                + (Gx[2][0] * 0)                     + (Gx[2][1] * 0)                     + (Gx[2][2] * 0)
                              );

                Gy_B[h][w] =  (   (Gy[0][0] * image[A][a].rgbtBlue) + (Gy[0][1] * image[A][b].rgbtBlue) + (Gy[0][2] * image[A][c].rgbtBlue)
                                + (Gy[1][0] * image[B][a].rgbtBlue) + (Gy[1][1] * image[B][b].rgbtBlue) + (Gy[1][2] * image[B][c].rgbtBlue)
                                + (Gx[2][0] * 0)                    + (Gx[2][1] * 0)                    + (Gx[2][2] * 0)
                              );
                }
            }
            else if (w == 0) //left edge
            {
                //Gx
                Gx_R[h][w] =  (   (Gx[0][0] * 0) + (Gx[0][1] * image[A][b].rgbtRed) + (Gx[0][2] * image[A][c].rgbtRed)
                                + (Gx[1][0] * 0) + (Gx[1][1] * image[B][b].rgbtRed) + (Gx[1][2] * image[B][c].rgbtRed)
                                + (Gx[2][0] * 0) + (Gx[2][1] * image[C][b].rgbtRed) + (Gx[2][2] * image[C][c].rgbtRed)
                              );

                Gx_G[h][w] =  (   (Gx[0][0] * 0) + (Gx[0][1] * image[A][b].rgbtGreen) + (Gx[0][2] * image[A][c].rgbtGreen)
                                + (Gx[1][0] * 0) + (Gx[1][1] * image[B][b].rgbtGreen) + (Gx[1][2] * image[B][c].rgbtGreen)
                                + (Gx[2][0] * 0) + (Gx[2][1] * image[C][b].rgbtGreen) + (Gx[2][2] * image[C][c].rgbtGreen)
                              );

                Gx_B[h][w] =  (   (Gx[0][0] * 0) + (Gx[0][1] * image[A][b].rgbtBlue) + (Gx[0][2] * image[A][c].rgbtBlue)
                                + (Gx[1][0] * 0) + (Gx[1][1] * image[B][b].rgbtBlue) + (Gx[1][2] * image[B][c].rgbtBlue)
                                + (Gx[2][0] * 0) + (Gx[2][1] * image[C][b].rgbtBlue) + (Gx[2][2] * image[C][c].rgbtBlue)
                              );
                //Gy
                Gy_R[h][w] =  (   (Gy[0][0] * 0) + (Gy[0][1] * image[A][b].rgbtRed) + (Gy[0][2] * image[A][c].rgbtRed)
                                + (Gy[1][0] * 0) + (Gy[1][1] * image[B][b].rgbtRed) + (Gy[1][2] * image[B][c].rgbtRed)
                                + (Gy[2][0] * 0) + (Gy[2][1] * image[C][b].rgbtRed) + (Gy[2][2] * image[C][c].rgbtRed)
                              );

                Gy_G[h][w] =  (   (Gy[0][0] * 0) + (Gy[0][1] * image[A][b].rgbtGreen) + (Gy[0][2] * image[A][c].rgbtGreen)
                                + (Gy[1][0] * 0) + (Gy[1][1] * image[B][b].rgbtGreen) + (Gy[1][2] * image[B][c].rgbtGreen)
                                + (Gy[2][0] * 0) + (Gy[2][1] * image[C][b].rgbtGreen) + (Gy[2][2] * image[C][c].rgbtGreen)
                              );

                Gy_B[h][w] =  (   (Gy[0][0] * 0) + (Gy[0][1] * image[A][b].rgbtBlue) + (Gy[0][2] * image[A][c].rgbtBlue)
                                + (Gy[1][0] * 0) + (Gy[1][1] * image[B][b].rgbtBlue) + (Gy[1][2] * image[B][c].rgbtBlue)
                                + (Gy[2][0] * 0) + (Gy[2][1] * image[C][b].rgbtBlue) + (Gy[2][2] * image[C][c].rgbtBlue)
                              );
            }
            else if (w == width - 1) //right edge
            {
                //Gx
                Gx_R[h][w] =  (   (Gx[0][0] * image[A][a].rgbtRed) + (Gx[0][1] * image[A][b].rgbtRed) + (Gx[0][2] * 0)
                                + (Gx[1][0] * image[B][a].rgbtRed) + (Gx[1][1] * image[B][b].rgbtRed) + (Gx[1][2] * 0)
                                + (Gx[2][0] * image[C][a].rgbtRed) + (Gx[2][1] * image[C][b].rgbtRed) + (Gx[2][2] * 0)
                              );

                Gx_G[h][w] =  (   (Gx[0][0] * image[A][a].rgbtGreen) + (Gx[0][1] * image[A][b].rgbtGreen) + (Gx[0][2] * 0)
                                + (Gx[1][0] * image[B][a].rgbtGreen) + (Gx[1][1] * image[B][b].rgbtGreen) + (Gx[1][2] * 0)
                                + (Gx[2][0] * image[C][a].rgbtGreen) + (Gx[2][1] * image[C][b].rgbtGreen) + (Gx[2][2] * 0)
                              );

                Gx_B[h][w] =  (   (Gx[0][0] * image[A][a].rgbtBlue) + (Gx[0][1] * image[A][b].rgbtBlue) + (Gx[0][2] * 0)
                                + (Gx[1][0] * image[B][a].rgbtBlue) + (Gx[1][1] * image[B][b].rgbtBlue) + (Gx[1][2] * 0)
                                + (Gx[2][0] * image[C][a].rgbtBlue) + (Gx[2][1] * image[C][b].rgbtBlue) + (Gx[2][2] * 0)
                              );
                //Gy
                Gy_R[h][w] =  (   (Gy[0][0] * image[A][a].rgbtRed) + (Gy[0][1] * image[A][b].rgbtRed) + (Gy[0][2] * 0)
                                + (Gy[1][0] * image[B][a].rgbtRed) + (Gy[1][1] * image[B][b].rgbtRed) + (Gy[1][2] * 0)
                                + (Gy[2][0] * image[C][a].rgbtRed) + (Gy[2][1] * image[C][b].rgbtRed) + (Gy[2][2] * 0)
                              );

                Gy_G[h][w] =  (   (Gy[0][0] * image[A][a].rgbtGreen) + (Gy[0][1] * image[A][b].rgbtGreen) + (Gy[0][2] * 0)
                                + (Gy[1][0] * image[B][a].rgbtGreen) + (Gy[1][1] * image[B][b].rgbtGreen) + (Gy[1][2] * 0)
                                + (Gy[2][0] * image[C][a].rgbtGreen) + (Gy[2][1] * image[C][b].rgbtGreen) + (Gy[2][2] * 0)
                              );

                Gy_B[h][w] =  (   (Gy[0][0] * image[A][a].rgbtBlue) + (Gy[0][1] * image[A][b].rgbtBlue) + (Gy[0][2] * 0)
                                + (Gy[1][0] * image[B][a].rgbtBlue) + (Gy[1][1] * image[B][b].rgbtBlue) + (Gy[1][2] * 0)
                                + (Gy[2][0] * image[C][a].rgbtBlue) + (Gy[2][1] * image[C][b].rgbtBlue) + (Gy[2][2] * 0)
                              );
            }
            else //middle pieces
            {
                //Gx
                Gx_R[h][w] =  (   (Gx[0][0] * image[A][a].rgbtRed) + (Gx[0][1] * image[A][b].rgbtRed) + (Gx[0][2] * image[A][c].rgbtRed)
                                + (Gx[1][0] * image[B][a].rgbtRed) + (Gx[1][1] * image[B][b].rgbtRed) + (Gx[1][2] * image[B][c].rgbtRed)
                                + (Gx[2][0] * image[C][a].rgbtRed) + (Gx[2][1] * image[C][b].rgbtRed) + (Gx[2][2] * image[C][c].rgbtRed)
                              );

                Gx_G[h][w] =  (   (Gx[0][0] * image[A][a].rgbtGreen) + (Gx[0][1] * image[A][b].rgbtGreen) + (Gx[0][2] * image[A][c].rgbtGreen)
                                + (Gx[1][0] * image[B][a].rgbtGreen) + (Gx[1][1] * image[B][b].rgbtGreen) + (Gx[1][2] * image[B][c].rgbtGreen)
                                + (Gx[2][0] * image[C][a].rgbtGreen) + (Gx[2][1] * image[C][b].rgbtGreen) + (Gx[2][2] * image[C][c].rgbtGreen)
                              );

                Gx_B[h][w] =  (   (Gx[0][0] * image[A][a].rgbtBlue) + (Gx[0][1] * image[A][b].rgbtBlue) + (Gx[0][2] * image[A][c].rgbtBlue)
                                + (Gx[1][0] * image[B][a].rgbtBlue) + (Gx[1][1] * image[B][b].rgbtBlue) + (Gx[1][2] * image[B][c].rgbtBlue)
                                + (Gx[2][0] * image[C][a].rgbtBlue) + (Gx[2][1] * image[C][b].rgbtBlue) + (Gx[2][2] * image[C][c].rgbtBlue)
                              );
                //Gy
                Gy_R[h][w] =  (   (Gy[0][0] * image[A][a].rgbtRed) + (Gy[0][1] * image[A][b].rgbtRed) + (Gy[0][2] * image[A][c].rgbtRed)
                                + (Gy[1][0] * image[B][a].rgbtRed) + (Gy[1][1] * image[B][b].rgbtRed) + (Gy[1][2] * image[B][c].rgbtRed)
                                + (Gy[2][0] * image[C][a].rgbtRed) + (Gy[2][1] * image[C][b].rgbtRed) + (Gy[2][2] * image[C][c].rgbtRed)
                              );

                Gy_G[h][w] =  (   (Gy[0][0] * image[A][a].rgbtGreen) + (Gy[0][1] * image[A][b].rgbtGreen) + (Gy[0][2] * image[A][c].rgbtGreen)
                                + (Gy[1][0] * image[B][a].rgbtGreen) + (Gy[1][1] * image[B][b].rgbtGreen) + (Gy[1][2] * image[B][c].rgbtGreen)
                                + (Gy[2][0] * image[C][a].rgbtGreen) + (Gy[2][1] * image[C][b].rgbtGreen) + (Gy[2][2] * image[C][c].rgbtGreen)
                              );

                Gy_B[h][w] =  (   (Gy[0][0] * image[A][a].rgbtBlue) + (Gy[0][1] * image[A][b].rgbtBlue) + (Gy[0][2] * image[A][c].rgbtBlue)
                                + (Gy[1][0] * image[B][a].rgbtBlue) + (Gy[1][1] * image[B][b].rgbtBlue) + (Gy[1][2] * image[B][c].rgbtBlue)
                                + (Gy[2][0] * image[C][a].rgbtBlue) + (Gy[2][1] * image[C][b].rgbtBlue) + (Gy[2][2] * image[C][c].rgbtBlue)
                              );
            }
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float Gx_Rp = 0;
            float Gx_Gp = 0;
            float Gx_Bp = 0;

            float Gy_Rp = 0;
            float Gy_Gp = 0;
            float Gy_Bp = 0;

            Gx_Rp = pow(Gx_R[h][w], 2);
            Gx_Gp = pow(Gx_G[h][w], 2);
            Gx_Bp = pow(Gx_B[h][w], 2);

            Gy_Rp = pow(Gy_R[h][w], 2);
            Gy_Gp = pow(Gy_G[h][w], 2);
            Gy_Bp = pow(Gy_B[h][w], 2);

            final_R[h][w] = sqrt(Gx_Rp + Gy_Rp);
            final_G[h][w] = sqrt(Gx_Gp + Gy_Gp);
            final_B[h][w] = sqrt(Gx_Bp + Gy_Bp);

            if (final_R[h][w] > 255)
            {
                final_R[h][w] = 255;
            }

            if (final_G[h][w] > 255)
            {
                final_G[h][w] = 255;
            }

            if (final_B[h][w] > 255)
            {
                final_B[h][w] = 255;
            }
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w].rgbtRed = round(final_R[h][w]);
            image[h][w].rgbtGreen = round(final_G[h][w]);
            image[h][w].rgbtBlue = round(final_B[h][w]);
        }
    }
}