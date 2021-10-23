#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>

void Load(char *fileName, char grid[][9])
{
    FILE *filePtr = NULL;

    //Open file
    filePtr = fopen (fileName, "r");
    if(filePtr == NULL) {
        errx(1,"solver/parser.c/Load() : cannot open file\n");
    }

    //Fill grid
    char c, value;
    int i = 0, j = 0;
    for(int column = 0; column < 11; column ++) {
        j = 0;
        if (column != 3 && column != 7) {
            for(int line = 0; line < 11; line ++) {
                c = fgetc(filePtr);
                if(line != 3 && line != 7) {
                    value = 0;
                    if (c >= (char)'0' && c <= (char)'9')
                        value = c - (char)'0';
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
        errx(1,"solver/parser.c/Load() : error in closing the file");
}

void outFormatPath(char* fileName, char* outFileName) 
{
    char format[] = ".result";

    strcpy(outFileName, fileName);
    strcat(outFileName,format);
}

void Save(char *fileName, char grid[][9]) 
{
    char outFileName[100];
    outFormatPath(fileName, outFileName);

    //Open file
    FILE* fp = NULL;
    fp = fopen (outFileName, "w");
    if(fp == NULL) {
        errx(1,"solver/parser.c/Save() : cannot open file\n");
    }

    for (int i = 0; i < 9; i++)
    {
        if(i == 3 || i == 6) 
            fputc((char)'\n',fp);
        for (int j = 0; j < 9; j++)
        {
            if(j == 3 || j == 6) 
                fputc((char)' ',fp);
            char c = grid[i][j] + '0';
            fputc(c,fp);
        }
        fputc((char)'\n',fp);
    }

    //Close file
    int closeReturn = fclose(fp);
    if(closeReturn == (int) EOF) {
        errx(1,"solver/parser.c/Save() : error in closing the file");
    }
}