#include <stdio.h>
#include <math.h>

int floor_to_nearest(int num, int base)
{
    return (base * floor((float)num / base));
}

int main()
{
    int num = 124;
    int base = 64;
    int result = floor_to_nearest(num, base);

    printf("floor_to_nearest(%d, %d) = %d\n", num, base, result);

    return 0;
}

