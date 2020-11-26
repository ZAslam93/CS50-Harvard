#include "helpers.h"
// Including header math.h for rounding functionality, bmp.h for RGBTRIPLE?
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
            greyvalue = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            // Setting each pixel to equal shade
            image[i][j].rgbtBlue = greyvalue;
            image[i][j].rgbtGreen = greyvalue;
            image[i][j].rgbtRed = greyvalue;
        }
    }
    return;
}

// Convert image to sepia --function COMPLETE--
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
            spBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            spGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            spRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);

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

// Reflect image horizontally --function COMPLETE--
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Initializing [temp]
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (int) round(width / 2); j++)
        {

            // Swapping pixel values using temp
            temp[i][j] = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = temp[i][j];

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Initializing [orig], [totalred/green/blue] and [counter]
    RGBTRIPLE orig[height][width];
    int totalred;
    int totalgreen;
    int totalblue;
    int counter;


    // Copying image data into orig
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            orig[i][j] = image[i][j];
        }
    }

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            // Resetting counts to 0 for each pixel
            totalred = 0;
            totalgreen = 0;
            totalblue = 0;
            counter = 0;

            // Top left
            if ((i - 1) >= 0 || (j - 1) >= 0)
            {
                totalred += orig[i - 1][j-1].rgbtRed
            }
        }
    }
    return;
}
