#include <stdio.h>

int LineOk(char nbr, int line, char grid[][9]) 
{
    for(int j = 0; j < 9; j++) {
        if(grid[line][j] == nbr)
            return 0;
    }
    return 1;
}

int ColumnOk(char nbr, int col, char grid[][9]) 
{
    for(int i = 0; i < 9; i++) {
        if(grid[i][col] == nbr)
            return 0;
    }
    return 1;
}

int SquareOk(char nbr, int line, int col, char grid[][9])
{
    char y = (line / 3) * 3;
    char x = (col / 3) * 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if(grid[y+i][x+j] == nbr)
                return 0;
        }
    }
    return 1;
}

int Empty(int line, int col, char grid[][9]) 
{
    if(line >= 9 || col >= 9)
        return 0;
    return (grid[line][col] == 0);
}

int RecSolve(int line, int col, int empty, char grid[][9])
{
    if(line >= 9)
        return 0;

    char nextCol = col+ 1;
    char nextLine = line;

    if(nextCol >= 9) {                                                              // if we are at the end of the line                       
        nextLine = line + 1;                                                        // we go to the next line
        nextCol = 0;
    }

    if(empty == 0)                                                                  // if the box isn't empty
        return (RecSolve(nextLine, nextCol, Empty(nextLine,nextCol,grid), grid));   // continue recursion on next box  
    else {
        for(char nbr = 1; nbr < 10; nbr++) {

            if (LineOk (nbr, line, grid)                                            // if line, column and square are ok
            && ColumnOk(nbr, col, grid)
            && SquareOk(nbr, line, col, grid)) {

                grid[line][col] = nbr;                                              // we put the number in the box

                if(RecSolve(nextLine, nextCol, Empty(nextLine, nextCol, grid), grid) == 0) // if everything is ok 
                    return 0;                                                              // the we are ok too
                else
                    grid[line][col] = 0;                                            // else we try the next number
            }
        }                  
        return -1;                                                                  // if we have tried all numbers, then there is a problem
    }
}

void Solve(char grid[][9])
{
    RecSolve(0, 0, Empty(0, 0, grid), grid);
}