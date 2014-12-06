#pragma once

#include <stdint.h>

class FibRng
{
public:
    FibRng(char *seed, int _depth = 8);
    FibRng(int _depth = 8);
    ~FibRng();

    uint32_t dice(uint32_t sides);

    void reseed(char *seed);
    void spin(void);
    void dump(void);

protected:
    void erase(void);

    static const int CHOP = 0x1FFFFFFF;
    static uint32_t tickle;

    int depth;
    uint32_t *ring;
};

