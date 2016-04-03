/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes a bitmap image
 */
       
#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

// global variable used store the resize factor 
int n;

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }
    
    // change argv[1] to an integer
    n = atoi(argv[1]);
    
    // ensure n is greater than 1 and less than 100 
    if (n > 100 || n < 1)
    {
        printf("Please enter a value for n that is between 1 and 100, inclusive.\n");
        return 2;
    }
    
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // declare variables for original and resized fileheaders
    BITMAPFILEHEADER bf;
    BITMAPFILEHEADER bf_resized;
    
    // read infile's BITMAPFILEHEADER and copy into resized fileheader 
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    bf_resized = bf;
    
    // declare variables for original and resized infoheaders
    BITMAPINFOHEADER bi;
    BITMAPINFOHEADER bi_resized;
    
    // read infile's BITMAPINFOHEADER and copy into resized infoheader
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    bi_resized = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }
    
    // change resized infoheader to accomodate resize factor 
    bi_resized.biWidth *= n;
    bi_resized.biHeight *= n;
    
    // determine padding for orginal file and resized file
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE) ) % 4) % 4;
    int padding_resized = (4 - (bi_resized.biWidth * sizeof(RGBTRIPLE) ) % 4) % 4;
    
    // change resized infoheader to accomodate new padding 
    bi_resized.biSizeImage = ((bi_resized.biWidth * sizeof(RGBTRIPLE)) + padding_resized) * abs(bi_resized.biHeight);
    
    // change resized fileheader to accomodate new size 
    bf_resized.bfSize = 54 + bi_resized.biSizeImage;
    
    // write resized file's BITMAPFILEHEADER
    fwrite(&bf_resized, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write resized file's BITMAPINFOHEADER
    fwrite(&bi_resized, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // loop for vertical resizing, n is the global variable storing resize factor
        for (int vertical_repeat = 1; vertical_repeat <= n ; vertical_repeat++)
        {
            // loop for each pixel in a row 
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile n number of times (horizontal resize)
                for (int k = 0 ; k < n ; k++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // Add padding for outfile
            for (int l = 0; l < padding_resized; l++)
            {
                fputc(0x00, outptr);
            }   
            
            // rescans row if n is greater than 1 
            if (vertical_repeat != n)
            {
                fseek(inptr, -(bi.biWidth * sizeof(RGBTRIPLE)), SEEK_CUR);
            }
        }
        // skip over INFILE padding, if any 
        fseek(inptr, padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    return 0;
}
