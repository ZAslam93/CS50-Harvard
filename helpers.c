#include "helpers.h"
// Including header math.h for rounding functionality
#include <math.h>

// Convert image to grayscale --function incomplete--
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int greyvalue = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Computing the shade of grey for each pixel
            int b = round(image[i][j].rgbtBlue / 3);
            int g = round(image[i][j].rgbtGreen / 3);
            int r = round(image[i][j].rgbtRed / 3);
            greyvalue = (b + g + r);
            // Setting each pixel to equal shade
            image[i][j].rgbtBlue = greyvalue;
            image[i][j].rgbtGreen = greyvalue;
            image[i][j].rgbtRed = greyvalue;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
