#ifndef SOLVERALGO_H
#define SOLVERALGO_H

int LineOk(char nbr, int line, char grid[][9]);

int ColumnOk(char nbr, int col, char grid[][9]);

int SquareOk(char nbr, int line, int col, char grid[][9]);

int Empty(int line, int col, char grid[][9]);

int RecSolve(int line, int col, int empty, char grid[][9]);

void Solve(char grid[][9]);

#endif