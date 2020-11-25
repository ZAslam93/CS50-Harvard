#include "helpers.h"
// Including header math.h for rounding functionality
#include <math.h>

// Convert image to grayscale --function COMPLETE--
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Initializing [greyscale]
    int greyvalue = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Computing the shade of grey for each pixel
            greyvalue = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen +
            image[i][j].rgbtRed) / 3.0);
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
    // Initializing [spBlue] [spGreen] [spRed]
    int spBlue = 0;
    int spGreen = 0;
    int spRed = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculating each pixel's sepia value using formula
            spBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen
            + .131 * image[i][j].rgbtBlue);
            spGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen
            + .168 * image[i][j].rgbtBlue);
            spRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen
            + .189 * image[i][j].rgbtBlue);

            // Setting maximum sepia value to 255
            if (spBlue > 255)
            {
                spBlue = 255;
            }
            if (spGreen > 255)
            {
                spGreen = 255;
            }
            if (spRed > 255)
            {
                spRed = 255;
            }

            // Applying sepia value to each pixel
            image[i][j].rgbtBlue = spBlue;
            image[i][j].rgbtGreen = spGreen;
            image[i][j].rgbtRed = spRed;
        }
    }
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
