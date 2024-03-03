#include "all_possible_sums.h"
#include <stdio.h>
int main(int argc, char **argv)
{
    int ai[3] = {1, 2, 3};
    int bi[3] = {4, 5, 6};
    float af[3] = {1.0, 2.0, 3.0};
    float bf[3] = {1.5, 2.5, 3.5};
    TEMPLATE(sum, int)(3, ai, bi);
    printf("%d %d %d", ai[0], ai[1], ai[2]);
    TEMPLATE(sum, float)(3, af, bf);
    return 0;
}