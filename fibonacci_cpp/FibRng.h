#pragma once

#include <stdint.h>

class FibRng
{
public:
    FibRng(char *seed, int _depth = 8);
    FibRng(int _depth = 8);
    FibRng(int _init, char *seed, int _depth = 8);
    FibRng(int _init, int _depth = 8);

    ~FibRng();

    uint32_t dice(uint32_t sides);
    uint8_t  byte(void);
    uint16_t word(void);
    double   real(void);

    void reseed(char *seed);
    void spin(void);
    void dump(void);

protected:
    void erase(void);

    static const int CHOP = 0x1FFFFFFF;
    static const int TOP  = 0x10000000;
    static const double BASE;
    static uint32_t tickle;

    int depth;
    int init;
    uint32_t *ring;
};

