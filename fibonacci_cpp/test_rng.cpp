//Run some very rudimentary tests on this random number generator.

#include "FibRng.h"
#include <stdio.h>

void main(int argc, char * argv[])
{
    FibRng gen("test");
    uint32_t bins[6] = { 0, 0, 0, 0, 0, 0 };

    for (int i = 0; i < 10000000; i++)
    {
        bins[gen.dice(6)]++;
    }

    for (int i = 0; i < 6; i++)
    {
        printf("Bin %d = %u \n", i+1, bins[i]);
    }

    //gen.dump();
    printf("Done\n");
}
