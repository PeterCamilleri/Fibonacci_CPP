#include "FibRng.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

// The tickle variable protects against rapid fire creation of
// generators with the default seed.
uint64_t FibRng::tickle = 0;

const char  *FibRng::VERSION = "1.1.0";

// Set up some operational constants.
const char *FibRng::ASCII_7 =
    "\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2A\x2B\x2C\x2D\x2E\x2F"
    "\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3A\x3B\x3C\x3D\x3E\x3F"
    "\x40\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4A\x4B\x4C\x4D\x4E\x4F"
    "\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5A\x5B\x5C\x5D\x5E\x5F"
    "\x60\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6A\x6B\x6C\x6D\x6E\x6F"
    "\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7A\x7B\x7C\x7D\x7E";

const double FibRng::BASE = CHOP + 1.0;
const double FibRng::DBL  = BASE * BASE;
const char  *FibRng::spice = "StringLeonardo Pisano";

// A constructor for Fibonacci Psuedo Random Number Generator.
// This takes up to three parms. Versions with fewer parms follow
// that use sensible default values where needed.
// Parms:
// init - The amount of initial churning done. Valid values are 1..1000000
// seed - A seed string.
// depth - The number of cells to use. Valid values are 2..256. Default = 8
FibRng::FibRng(int init, const char *seed, int depth) : init(init), depth(depth)
{
    ring = new uint32_t[depth + 2];
    reseed(seed);
}

// Build with the default init value of 32 * depth + 768.
// seed - A seed string.
// depth - The number of cells to use. Valid values are 2..256. Default = 8
FibRng::FibRng(const char *seed, int depth) : depth(depth)
{
    default_init();
    ring = new uint32_t[depth + 2];
    reseed(seed);
}

// Build with a random seed and a default init value of 32 * depth + 768.
// depth - The number of cells to use. Valid values are 2..256. Default = 8
FibRng::FibRng(int depth) : depth(depth)
{
    default_init();
    ring = new uint32_t[depth + 2];
    default_seed();
}

// Build with a random seed.
// init - The amount of initial churning done. Valid values are 1..1000000
// depth - The number of cells to use. Valid values are 2..256. Default = 8
FibRng::FibRng(int init, int depth) : init(init), depth(depth)
{
    ring = new uint32_t[depth + 2];
    default_seed();
}

void FibRng::default_init(void)
{
    init = 32 * depth + 768;
}

void FibRng::default_seed(void)
{
    char seed_buffer[80];
    sprintf_s(seed_buffer, 80, "%lld", time(NULL) + tickle);
    tickle++;
    do_seed(seed_buffer, strlen(seed_buffer));
}

// Restart the generator with a new seed.
void FibRng::reseed(const char *seed)
{
    int len = strlen(seed) + strlen(spice) + 1;
    char *buffer = new char[len];

    strcpy_s(buffer, len, seed);
    strcat_s(buffer, len, spice);

    do_seed(buffer, len-1);

    delete [] buffer;
}

// Reseed the generator with a new value.
void FibRng::do_seed(char *seed, int seed_len)
{
    erase();

    for (int i = 0; i < init; i++)
    {
        unsigned int t = seed[i % seed_len];
        unsigned int x = i % depth;

        ring[x] += t;
        spin();
    }
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

// Generate a random byte value.
uint8_t FibRng::byte(void)
{
    spin();
    return ring[0] & 0xFF;
}

// Generate a random 16 bit value.
uint16_t FibRng::word(void)
{
    spin();
    return ring[0] & 0xFFFF;
}

// Generate a quick floating point value in 0.0 <= x < 1.0
double FibRng::real(void)
{
    spin();
    return ring[0] / BASE;
}

// Generate a better floating point value in 0.0 <= x < 1.0
double FibRng::dbl(void)
{
    spin();
    double part_one = ring[0] * BASE;
    spin();
    return (part_one + ring[0]) / DBL;
}

// Fill a buffer with randomized ASCII text.
void FibRng::ascii(char *buffer, uint32_t len, const char *set)
{
    uint32_t set_len = strlen(set);

    for (uint32_t i = 0; i < len; i++)
        buffer[i] = set[dice(set_len)];

    buffer[len] = 0;
}

// Scramble the eggs some more.
void FibRng::spin(void)
{
    // Copy over the 'end' values.
    ring[depth]   = ring[0];
    ring[depth+1] = ring[1];

    // Spin the wheel!
    for (int i = 0; i < depth; i++)
    {
        uint32_t ri2 = ring[i+2];
        ring[i] = (ring[i+1] + ((ri2 >> 1) | ((ri2 & 1) ? TOP : 0))) & CHOP;
    }
}

// Dump the internal state for test purposes.
void FibRng::dump(void)
{
    for (int i = 0; i < depth; i++)
        printf("%08X  ", ring[i]);

    printf("\n");
}

// Erase the generator's internal state.
void FibRng::erase(void)
{
    for (int i = 0; i < depth; i++)
        ring[i] = 0;
}
