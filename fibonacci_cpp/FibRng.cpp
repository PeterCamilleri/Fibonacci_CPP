#include "FibRng.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

// The tickle variable protects against rapid fire creation of
// generators with the default seed.
uint32_t FibRng::tickle = 0;

// A constructor for Fibonacci Psuedo Random Number Generator.
// seed - A seed string.
// depth - The number of cells to use. Valid values are 2...Are_you_crazy?
FibRng::FibRng(char *seed, int _depth)
{
    depth = _depth;
    ring = new uint32_t[depth + 2];
    reseed(seed);
}

// A constructor for Fibonacci Psuedo Random Number Generator with default seed.
// depth - The number of cells to use. Valid values are 2...Are_you_crazy?
FibRng::FibRng(int _depth)
{
    char seed_buffer[80];

    sprintf_s(seed_buffer, 80, "%d", time(NULL) + tickle);

    tickle++;
    depth = _depth;
    ring = new uint32_t[depth + 2];
    reseed(seed_buffer);
}

// Time to pack up and go home!
FibRng::~FibRng()
{
    delete [] ring;
}

// Roll a dice with the specified number of sides.
uint32_t FibRng::dice(uint32_t sides)
{
    uint32_t limit = ((CHOP + 1) / sides) * sides;

    do
    {
        spin();
    } while (ring[0] >= limit);
        
    return ring[0] % sides;
}

// Reseed the generator with a new value.
void FibRng::reseed(char *seed)
{
    int seed_len = strlen(seed);

    erase();

    for (int i = 0; i < 1024; i++)
    {
        unsigned int t = seed[i % seed_len];
        unsigned int x = i % depth;

        ring[x] += t;
        spin();
    }
}

// Scramble the eggs some more.
void FibRng::spin(void)
{
    // Copy over the 'end' values.
    ring[depth]     = ring[0];
    ring[depth + 1] = ring[1];

    // Spin the wheel!
    for (int i = 0; i < depth; i++)
    {
        ring[i] = (ring[i+1] + (ring[i+2] >> 1)) & CHOP;
    }
}

// Dump the internal state for test purposes.
void FibRng::dump(void)
{
    for (int i = 0; i < depth; i++)
    {
        printf("%u ", ring[i]);
    }

    printf("\n");
}

// Erase the generator's internal state.
void FibRng::erase(void)
{
    for (int i = 0; i < depth; i++)
    {
        ring[i] = 0;
    }
}
