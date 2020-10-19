#include "math.h"

int pow(int a, int b)
{
	int output = 1;
	for(; b > 0; b--)
		output *= a;

	return output;
}