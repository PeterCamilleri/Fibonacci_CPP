#pragma once

#include <stdint.h>

class FibRng
{
public:
    static const char *VERSION;
    static const char *ASCII_7;

    static const int DEPTH = 8;

    explicit FibRng(int init, const char *seed, int depth = DEPTH);
    explicit FibRng(          const char *seed, int depth = DEPTH);
    explicit FibRng(int init,                   int depth);
    explicit FibRng(                            int depth = DEPTH);

    ~FibRng();

    uint32_t dice(uint32_t sides);
    uint8_t  byte(void);
    uint16_t word(void);
    double   real(void);
    double   dbl(void);
    void     ascii(char *buffer, uint32_t len, const char *set = ASCII_7);

    void reseed(const char *seed);
    void spin(void);
    void dump(void);

private:
    static const int CHOP = 0x1FFFFFFF;
    static const int TOP  = 0x10000000;
    static const double BASE;
    static const double DBL;
    static const char *spice;
    static uint64_t tickle;

    void erase(void);
    void default_init(void);
    void default_seed(void);
    void do_seed(char *seed, int seed_len);

    int depth;
    int init;
    uint32_t *ring;
};

