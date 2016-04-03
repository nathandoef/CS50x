/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// define BYTE as an unsigned 8 bit integer
typedef uint8_t  BYTE;


int main(int argc, char* argv[])
{
    // open memory card file 
    FILE* memCard = fopen("card.raw", "r");
    if (memCard == NULL)
    {
        printf("Could not open card.raw");
        return 1;
    }
    
    // create a buffer that is 512 bytes 
    BYTE buffer[512];
    
    // define counter for file number 
    int fileNum = 0;
    
    // declare an array of characters used for the jpg title
    char title[8];
    
    // define a file pointer called image and initialize to NULL
    FILE* image = NULL;
    
    /* read memory card file 512 bytes at a time and store in buffer until the
    there are not 512 bytes left in the file */
    while ((fread (&buffer, 512, 1, memCard)) == 1 )
    {
        // check if there is a starting sequence at the beginning of a block
        if ( (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff) &&
            (buffer[3] == 0xe0 || buffer[3] == 0xe1) )
        {
            // if the image pointer is currently not open (checks if it is the first image file)
            if (image == NULL)
            {
                // create jpeg file
                sprintf (title, "%03i.jpg", fileNum);
        
                // open file pointer, image, that points to title, append so previous data is not lost 
                image = fopen(title, "a");
                if (image == NULL)
                {
                printf("Could not open %s.", title);
                return 2;
                }
            
                // write the 512 bytes stored in the buffer to the image file 
                fwrite(&buffer, 512, 1, image);
            }
            
            /* else a file is already open, is finished writing, and must be closed 
            to start writing the new image */
            else 
            {
                // close the current file image file that is open 
                fclose(image);
                image = NULL;
                
                // increment fileNum
                fileNum++;
                
                // create a new jpeg file 
                sprintf(title, "%03i.jpg", fileNum);
                
                // open file pointer, image, that points to title, append so previous data isn't lost
                image = fopen(title, "a");
                if (image == NULL)
                {
                printf("Could not open %s.", title);
                return 3;
                }
                
                // write buffer to image file
                fwrite(&buffer, 512, 1, image);
            }
        }
        
        // if its not the beginning of a jpg and an image file is not pointing to NULL 
        else if (image != NULL)
        {
            // continue writing
            fwrite(&buffer, 512, 1, image);
        }
    }
    
    // close the last image file
    fclose(image);

    //close memory card file 
    fclose(memCard);
    
    return 0;
}
