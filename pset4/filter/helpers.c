#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <math.h>

// Data Structure for valid pixs
typedef struct
{
    BYTE  rgbtBlue;
    BYTE  rgbtGreen;
    BYTE  rgbtRed;
    bool valid;
}
pix;

// Data Structure for valid pixs
typedef struct
{
    float red;
    float blue;
    float green;
}
edge_matrix;

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE gs;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Grayscale is the average value of red, green, and blue
            gs = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            image[i][j].rgbtBlue = gs;
            image[i][j].rgbtGreen = gs;
            image[i][j].rgbtRed = gs;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE r[2];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Coppying Left Hand Values
            r[0].rgbtBlue = image[i][j].rgbtBlue;
            r[0].rgbtGreen = image[i][j].rgbtGreen;
            r[0].rgbtRed = image[i][j].rgbtRed;

            // Copying Right Hand Values
            r[1].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            r[1].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            r[1].rgbtRed = image[i][width - 1 - j].rgbtRed;

            // Swapping Left to right
            image[i][width - 1 - j].rgbtBlue = r[0].rgbtBlue;
            image[i][width - 1 - j].rgbtGreen = r[0].rgbtGreen;
            image[i][width - 1 - j].rgbtRed = r[0].rgbtRed;

            // Swapping Right to Left
            image[i][j].rgbtBlue = r[1].rgbtBlue;
            image[i][j].rgbtGreen = r[1].rgbtGreen;
            image[i][j].rgbtRed = r[1].rgbtRed;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Temporary RGBTRIPPLe array
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // Assigning blur values to images from average surronding rgbt values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Intializing variables to find sum of rgbt values
            int valid_count;
            valid_count = 0;
            float blue = 0;
            float green = 0;
            float red = 0;


            // Double loop to find surronding rgbt values
            for (int k = -1; k < 2; k++)
            {
                for (int z = -1; z < 2; z++)
                {
                    // Using conditionals from because they look cleaner https://medium.com/swlh/cs50-pset-4-filter-8cbf734b0dbc
                    // If the box is valid then assiging rbt values to blur
                    // Check if pixel is outside rows
                    if (i + k < 0 || i + k >= height)
                    {
                        continue;
                    }
                    // Check if pixel is outside columns
                    if (j + z < 0 || j + z >= width)
                    {
                        continue;
                    }
                    {
                        blue += temp[i+k][j+z].rgbtBlue;
                        green += temp[i+k][j+z].rgbtGreen;
                        red += temp[i+k][j+z].rgbtRed;

                        valid_count++;
                    }
                }
            }

            // Assigning blur value
            image[i][j].rgbtBlue = round(blue / valid_count);
            image[i][j].rgbtGreen = round(green / valid_count);
            image[i][j].rgbtRed = round(red / valid_count);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Temporary RGBTRIPPLe array
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // Taken from https://medium.com/swlh/cs50-pset-4-filter-8cbf734b0dbc
    // Initialise Sobel arrays
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Assigning blur values to images from average surronding rgbt values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Intializing variables to find sum of rgbt values
            int valid_count;
            valid_count = 0;
            edge_matrix gx;
            edge_matrix gy;
            gx.red = 0;
            gx.blue = 0;
            gx.green = 0;
            gy.red = 0;
            gy.blue = 0;
            gy.green = 0;

            // Double loop to find surronding rgbt values
            for (int k = -1; k < 2; k++)
            {
                for (int z = -1; z < 2; z++)
                {
                    // Using conditionals from because they look cleaner https://medium.com/swlh/cs50-pset-4-filter-8cbf734b0dbc
                    // If the box is valid then assiging rbt values to blur
                    // Check if pixel is outside rows
                    if (i + k < 0 || i + k >= height)
                    {
                        continue;
                    }
                    // Check if pixel is outside columns
                    if (j + z < 0 || j + z >= width)
                    {
                        continue;
                    }
                    // Using JR matrix method from cited article
                    // Otherwise add to sums
                    gx.red += temp[i + k][j + z].rgbtRed * Gx[k + 1][z + 1];
                    gx.green += temp[i + k][j + z].rgbtGreen * Gx[k + 1][z + 1];
                    gx.blue += temp[i + k][j + z].rgbtBlue * Gx[k + 1][z + 1];
                    gy.red += temp[i + k][j + z].rgbtRed * Gy[k + 1][z + 1];
                    gy.green += temp[i + k][j + z].rgbtGreen * Gy[k + 1][z + 1];
                    gy.blue += temp[i + k][j + z].rgbtBlue * Gy[k + 1][z + 1];
                }
            }


            int red = round(sqrt(gx.red * gx.red + gy.red * gy.red));
            int green = round(sqrt(gx.green * gx.green + gy.green * gy.green));
            int blue = round(sqrt(gx.blue * gx.blue + gy.blue * gy.blue));
            // Cap at 255
            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }

            // Assign new values to pixels
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }
    return;
}
