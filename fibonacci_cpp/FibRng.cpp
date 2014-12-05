#include "FibRng.h"
#include <stdio.h>
#include <string.h>

// A constructor for Fibonacci Psuedo Random Number Generator.
// depth - The number of cells to use. Valid values are 2...Are_you_crazy?
FibRng::FibRng(char *seed, int _depth)
{
	depth = _depth;
	ring = new uint32_t[depth + 2];
	erase();
	reseed(seed);
}

FibRng::~FibRng()
{
	delete [] ring;
}

void FibRng::erase(void)
{
	for (int i = 0; i < depth; i++)
	{
		ring[i] = 0;
	}
}

void FibRng::reseed(char *seed)
{
	int seed_len = strlen(seed);

	for (int i = 0; i < 1024; i++)
	{
		unsigned int t = seed[i % seed_len];
		unsigned int x = i % depth;

		ring[x] += t;
		spin();
	}
}

void FibRng::spin(void)
{
	// Copy over the 'end' values.
	ring[depth]     = ring[0];
	ring[depth + 1] = ring[1];

	// Spin the wheel!
	for (int i = 0; i < depth; i++)
	{
		ring[i] = ring[i+1] + (ring[i+2] >> 1);
	}
}

void FibRng::dump(void)
{
	for (int i = 0; i < depth; i++)
	{
		printf("%u\n", ring[i]);
	}
}

