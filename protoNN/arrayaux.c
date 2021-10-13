#include <stdio.h>
#include <stdlib.h>

// arrange the N elements of ARRAY in random order
void RndShuffle(int array[], size_t n) 
{
	if (n > 1) 
    {
        for (size_t i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

void PrintIntArray(int array[], size_t n) 
{
	printf("{");
	for (size_t i = 0; i < (n-1); i++)
	{
		printf("%i,",array[i]);
	}
	printf("%i}\n",array[n-1]);
}

void PrintDoubleArray(double array[], size_t n) 
{
	printf("{");
	for (size_t i = 0; i < (n-1); i++)
	{
		printf("%f,",array[i]);
	}
	printf("%f}\n",array[n-1]);
}