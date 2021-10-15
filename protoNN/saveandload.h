#ifndef SAVEANDLOAD_H
#define SAVEANDLOAD_H

void PutFloatFP(float x, FILE* fp);

void Save(NN* nNp, char* path);

NN* Load(char* path);

#endif