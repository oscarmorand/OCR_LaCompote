#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>

void print_grid(int n, char** grid)
{
    int i,j;
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(j%3 == 0)
                printf("  ");
            printf("%hhu ", grid[i][j]);
        }
        printf("\n");
        if((i+1)%3 == 0)
                printf("\n");
    }
}

char** init_grid(size_t n)
{
    char** grid = (char**)malloc(n * sizeof(char*));
    for (size_t i = 0; i < n; i++)
    {
        grid[i] = (char*)calloc(n, sizeof(char));
    }
    return grid;
}

void free_grid(size_t n, char** grid) 
{
    for (size_t i = 0; i < n; i++)
        free(grid[i]);
    free(grid);
}

char** Load(size_t n, char *fileName)
{
    FILE *filePtr = NULL;

    //Open file
    filePtr = fopen (fileName, "r");
    if(filePtr == NULL) {
        errx(1,"solver/parser.c/Load() : cannot open file\n");
    }

    char** grid = init_grid(n);

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
                    printf("%i,%i ", i, j);
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

    return grid;
}

void outFormatPath(char* fileName, char* outFileName) 
{
    char format[] = ".result";

    strcpy(outFileName, fileName);
    strcat(outFileName,format);
}

void Save(char *fileName, char** grid) 
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