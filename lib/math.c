#include "math.h"

int pow(int a, int b)
{
	int output = 1;
	if(b >= 0)
		for(; b > 0; b--)
			output *= a;
	else
		for(b *= -1; b > 0; b--)
			output /= a;

	return output;
}
