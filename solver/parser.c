#include <stdio.h>
#include <stdlib.h>
#include <err.h>

void Parse(char *fileName, int grid[][9])
{
    FILE *filePtr = NULL;

    //Open file
    filePtr = fopen (fileName, "r");
    if(filePtr == NULL) {
        errx(2,"solver/parser.c : cannot open file\n");
    }

    //Fill grid
    int c, value, i = 0, j = 0;
    for(int column = 0; column < 11; column ++) {
        j = 0;
        if (column != 3 && column != 7) {
            for(int line = 0; line < 11; line ++) {
                c = fgetc(filePtr);
                if(line != 3 && line != 7) {
                    value = 0;
                    if (c >= (int)'0' && c <= (int)'9')
                        value = c - (int)'0';
                    grid[i][j] = value;
                    j = j + 1;
                }
            }
            i = i + 1;
        }

        //pass \n at the end of the line
        fgetc(filePtr);
        fgetc(filePtr);
    }

    //Close file
    int closeReturn = fclose(filePtr);
    if(closeReturn == (int) EOF)
        errx(3,"solver/parser.c : error in closing the file");
}