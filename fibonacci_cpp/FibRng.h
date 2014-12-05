#pragma once

#include <stdint.h>

class FibRng
{
public:
	FibRng(char *seed, int _depth = 8);
	~FibRng();

	void erase(void);
	void reseed(char *seed);
	void spin(void);
	void dump(void);

protected:
	int depth;
	uint32_t *ring;
};

