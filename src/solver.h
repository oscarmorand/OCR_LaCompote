#ifndef SOLVER_H
#define SOLVER_H

int LineOk(char nbr, int line, char** grid);

int ColumnOk(char nbr, int col, char** grid);

int SquareOk(char nbr, int line, int col, char** grid);

int Empty(int line, int col, char** grid);

int RecSolve(int line, int col, int empty, char** grid);

void Solve(char** grid);

#endif