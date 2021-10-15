#ifndef CUT_H
#define CUT_H

void apply_cut(int** hough, int xLen, int yLen); // apply cut
int** normalize(int** raw, int xLen, int yLen);// raw matrix -> coordinates containing matrix
int** get_lines(int** norm, int xLen, int yLen, int nbc); // normalized matrix -> coordinates containing matrix

#endif