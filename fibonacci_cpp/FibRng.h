#pragma once

#include <stdint.h>

class FibRng
{
public:
    static const int DEPTH = 8;

    FibRng(int init, char *seed, int depth = DEPTH);
    FibRng(          char *seed, int depth = DEPTH);
    FibRng(int init,             int depth);
    FibRng(                      int depth = DEPTH);

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
    static const char *spice;
    static uint32_t tickle;

    void default_init(void);
    void default_seed(void);
    void do_seed(char *seed, int seed_len);

    int depth;
    int init;
    uint32_t *ring;
};

