#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing -- Green
    for (int row = 0; row < width; row++)
    {
        for (int column = 0; column < height; column++)
        {
            if (image[column][row].rgbtBlue == 0 &&
            image[column][row].rgbtGreen == 0 &&
            image[column][row].rgbtRed == 0)
            {
                // HEX #33FF6B, RGB: 51, 255, 107, HSL: 136, 80%, 60%
                image[column][row].rgbtBlue = 107;
                image[column][row].rgbtGreen = 255;
                image[column][row].rgbtRed = 51;
            }
        }
    }
}
