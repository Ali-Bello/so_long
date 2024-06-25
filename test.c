// File: animation.c
#include "headers/so_long.h"
#include <stdlib.h>
#include <unistd.h>

#include <math.h>

int round_to_nearest_multiple(int x, int y) {
    if (y == 0) {
        return 0; // Return 0 for invalid multiple
    }
    return floor((double)x / y) * y;
}


int main()
{
	printf("%d\n", round_to_nearest_multiple(129, 64));
}

