#include <stdlib.h>

#include "main.h"

/*
*converting binary to unsigned int
*/

unsigned int binary_to_uint (const char *b)
{
       	unsigned int total, pow;
	int num;

	if (b == NULL)
		return (0);

	for (num = 0; b[num]; num++)
	{
		if (b[num] != '0' && b[num] != '1')
			return (0);
	}

	for (pow = 1, total = 0, num--; num >= 0; num--, pow *= 2)
	{
		if (b[num] == '1')
			total += pow;
	}

	return (total);
}
