//Run some very rudimentary tests on this random number generator.

#include "FibRng.h"
#include <stdio.h>
#include <time.h>
#include <string.h>

void main(int argc, char * argv[])
{
    printf("Test Fibonacci Pseudo RNG, Version = %s\n\n", FibRng::VERSION);
    clock_t t1, t2;

    // 0 - A simple bin test.
    printf("Starting Bin Test.\n");
    t1 = clock();

    FibRng gen;
    uint32_t bins[6] = { 0, 0, 0, 0, 0, 0 };

    for (int i = 0; i < 100000000; i++)
    {
        bins[gen.dice(6)]++;
    }

    t2 = clock();

    for (int i = 0; i < 6; i++)
    {
        printf("Bin %d = %u \n", i+1, bins[i]);
    }

    printf("\nRegister Dump\n");
    gen.dump();
    printf("Done Bin Test. Ellapsed = %dms\n", t2 - t1);

    // Tests ported from Ruby to make sure incompatibilities do not creep in.

    // ----------------------------------------------------------------------
    // 1 - Test for compatible values.
    // ----------------------------------------------------------------------
    printf("\n\nStarting Value Test 1.\n");

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
        printf("Equal, no errors detected.\n\n");
    else
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

    printf("\nRegister Dump\n");
    test.dump();
    printf("Done Value Test 1.\n");

    // ----------------------------------------------------------------------
    // 2 - Reseed and retest.
    // ----------------------------------------------------------------------
    printf("\n\nStarting Value Test 2.\n");
    test.reseed("%s*08^_Tg{NnirtZ-94)q9z2l+~bB5");
    errors = 0;

    for (int i = 0; i < 80; i++)
    {
        result[i] = test.byte();

        if (expected[i] != result[i])
            errors++;
    }

    if (errors == 0)
        printf("Equal, no errors detected.\n");
    else
        printf("Different %d times\n", errors);

    printf("\nRegister Dump\n");
    test.dump();
    printf("Done Value Test 2.\n");

    // ----------------------------------------------------------------------
    // 3 - Test for compatible float values.
    // ----------------------------------------------------------------------
    printf("\n\nStarting Value Test 3.\n");

    double expected2[32] =
    {
        0.466758593916893, 0.8060004059225321,
        0.8063845634460449, 0.8676037490367889,
        0.350975576788187, 0.2556227296590805,
        0.4873242452740669, 0.07484667748212814,
        0.2968141995370388, 0.5417192056775093,
        0.4288134817034006, 0.26460993848741055,
        0.13613684102892876, 0.27074786089360714,
        0.11685592867434025, 0.814235333353281,
        0.6137734726071358, 0.9152738898992538,
        0.6325213424861431, 0.22782298550009727,
        0.6877559795975685, 0.9354030545800924,
        0.18385234475135803, 0.5579136144369841,
        0.7501311469823122, 0.04208622872829437,
        0.31922253780066967, 0.6471036206930876,
        0.4305369835346937, 0.2239683922380209,
        0.9770196247845888, 0.3727417625486851
    };

    double result2[32];

    test.reseed("%s*08^_Tg{NnirtZ-94)q9z2l+~bB5");
    errors = 0;

    for (int i = 0; i < 32; i++)
    {
        result2[i] = test.real();

        if (expected2[i] != result2[i])
            errors++;
    }

    if (errors == 0)
        printf("Equal, no errors detected.\n");
    else
        printf("Different %d times\n", errors);

    printf("\nRegister Dump\n");
    test.dump();
    printf("Done Value Test 3.\n");

    // ----------------------------------------------------------------------
    // 4 - Test for better floating point.
    // ----------------------------------------------------------------------
    printf("\n\nStarting Value Test 4.\n");

    double expected3[32] =
    {
        0.46675859541818576, 0.8063845650620829,
        0.3509755772643215, 0.48732424541347974,
        0.29681420054606944, 0.428813482196275,
        0.13613684153323594, 0.11685593019097174,
        0.6137734743119663, 0.6325213429104964,
        0.6877559813398925, 0.18385234579055312,
        0.7501311470607039, 0.31922253900599407,
        0.43053698395186735, 0.9770196254788744,
        0.105776653432334, 0.17992045162625886,
        0.7068137351637119, 0.09374992924495854,
        0.4741257221497737, 0.2717329622804037,
        0.6427948478921109, 0.048162101812947195,
        0.649627174383166, 0.27438020721066836,
        0.9478733559036244, 0.6199505789910625,
        0.8043054302444751, 0.9363898295339244,
        0.6613804354420972, 0.5876014495519649
    };

    test.reseed("%s*08^_Tg{NnirtZ-94)q9z2l+~bB5");
    errors = 0;

    for (int i = 0; i < 32; i++)
    {
        result2[i] = test.dbl();

        if (expected3[i] != result2[i])
            errors++;
    }

    if (errors == 0)
        printf("Equal, no errors detected.\n");
    else
        printf("Different %d times\n", errors);

    printf("\nRegister Dump\n");
    test.dump();
    printf("Done Value Test 4.\n");

    // ----------------------------------------------------------------------
    // 5 - Test for some random strings.
    // ----------------------------------------------------------------------
    printf("\n\nStarting String Test 5.\n");

    test.reseed("%s*08^_Tg{NnirtZ-94)q9z2l+~bB5");
    errors = 0;

    char buffer[11];
    char *str_result_1 = ",-+Idi6~ ~";

    test.ascii(buffer, 10);

    if (strcmp(buffer, str_result_1))
        errors++;

    char *str_result_2 = "5901964804";

    test.ascii(buffer, 10, "0123456789");

    if (strcmp(buffer, str_result_2))
        errors++;

    if (errors == 0)
        printf("Equal, no errors detected.\n");
    else
        printf("Different %d times\n", errors);

    printf("\nRegister Dump\n");
    test.dump();
    printf("Done String Test 5.\n");

    printf("\n");

}
