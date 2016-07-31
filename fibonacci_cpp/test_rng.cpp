//Run some very rudimentary tests on this random number generator.

#include "FibRng.h"
#include <stdio.h>

void main(int argc, char * argv[])
{
    printf("Starting Bin Test.\n");

    FibRng gen;
    uint32_t bins[6] = { 0, 0, 0, 0, 0, 0 };

    for (int i = 0; i < 100000000; i++)
    {
        bins[gen.dice(6)]++;
    }

    for (int i = 0; i < 6; i++)
    {
        printf("Bin %d = %u \n", i+1, bins[i]);
    }

    //gen.dump();
    printf("Done Bin Test.\n");

    // Test from Ruby used to make sure incompatibilities do not creep in.
    // expected = [184, 93,   0, 240,  34, 184,   4, 220, 126, 132,
    //              13, 67, 166, 107, 165,  66,  68, 120, 102, 110,
    //             212, 99,  80, 167,   9,  56,  47, 167, 127, 195,
    //             169, 34, 184,  97, 136, 176, 214, 104, 218, 103,
    //             180, 16,  83, 204, 128,  81,  63,  56, 237, 165,
    //               0, 88, 129,  40, 152,  44, 189,  35, 205, 249,
    //              77, 94, 142,  18,  60, 248,  49, 172, 235,  83,
    //              84, 65, 181, 117,  16, 170, 222,  97, 130, 217]
    //
    // prng = FibonacciRng.new("%s*08^_Tg{NnirtZ-94)q9z2l+~bB5")
    // result = Array.new(80){ prng.byte }
    //
    // assert_equal(expected, result)

    printf("\n\nStarting Value Test.\n");

    int expected[80] =
    {
        184, 93, 0, 240, 34, 184, 4, 220, 126, 132,
        13, 67, 166, 107, 165, 66, 68, 120, 102, 110,
        212, 99, 80, 167, 9, 56, 47, 167, 127, 195,
        169, 34, 184, 97, 136, 176, 214, 104, 218, 103,
        180, 16, 83, 204, 128, 81, 63, 56, 237, 165,
        0, 88, 129, 40, 152, 44, 189, 35, 205, 249,
        77, 94, 142, 18, 60, 248, 49, 172, 235, 83,
        84, 65, 181, 117, 16, 170, 222, 97, 130, 217
    };

    int result[80];
    FibRng test("%s*08^_Tg{NnirtZ-94)q9z2l+~bB5");
    int errors = 0;

    for (int i = 0; i < 80; i++)
    {
        result[i] = test.byte();

        if (expected[i] != result[i])
            errors++;
    }

    if (errors == 0)
        printf("Equal, no errors detected.\n");
    else
    {
        printf("Different %d times\n\n", errors);

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 10; j++)
                printf("%4d", expected[10 * i + j]);

            printf("\n");

            for (int j = 0; j < 10; j++)
                printf("%4d", result[10 * i + j]);

            printf("\n\n");
        }
    }

    printf("Done Value Test.\n");

}
