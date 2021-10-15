#include <stdio.h>
#include <stdlib.h>

int norm_threshold = 20; //Arbitrary value 

// input : the raw Hough's Matrix
// output: the number of lines to draw
// -> Modify the raw matrix to fill it with 0 or 1 depending on the threshold
int normalize(int** raw, int xLen, int yLen)
{
    size_t nbOfDots = 0;

    for (size_t y = 0; y < yLen; y++)
    {
        for (size_t x = 0; x < xLen; x++)
        {
            raw[x][y] = raw[x][y] < norm_threshold ? 0 : 1;
            nbOfDots++;
        }
    }
    return nbOfDots;
}

// input : the normalized matrix // the number of coordinates
// output: the matrix containing the coordinates
int** get_lines(int** norm, int xLen, int yLen, int nbc)
{
    int co[2][nbc];
    int i = 0;
    for (int y = 0; y < yLen; y++)
    {
        for (int x = 0; x < xLen; x++)
        {
            if (norm[x][y] == 1)
            {
                co[0][i] = x;
                co[1][i] = y;
            }
        }
    }
    return co;
}


// input  : hough's matrix and its size
// output: the matrix containing the coordinates
void apply_cut(int** hough, int xLen, int yLen)
{
    size_t nb = normalize(hough, xLen, yLen);
    // hough has been normalized
    for (size_t y = 0; y < yLen; y++)
    {
        for (size_t x = 0; x < xLen; x++)
        {
            printf("%d", hough[x][y]);
        }
        printf("\n");
    }
}