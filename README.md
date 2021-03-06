# FibonacciRng in C++

This archive contains a port of the Fibonacci Pseudo Random Number Generator
from Ruby to C++. It is only a subset of the original. Notably absent is
support for the hashing functionality of the Ruby implementation.

While C++ is awkward and a pain, it does seem to run about one hundred times
faster than the Ruby version, so there you go.

## Installation

While this code comes packaged with all of the paraphernalia associated with
Visual Studio 2013, in the end, it consists of two simple source files:
FibRng.cpp and FibRng.h. Thus there is no formal installation procedure
beyond obtaining the source files and copying them to the required folders.

## Usage

To incorporate this software one need only add the cpp file to the project or
make file and add the following line to files that use its facilities:

    include "FibRng.h"

The Visual Studio project is useful in one respect though. It includes a few
rudimentary tests for performance and correctness of operation. This is found
in the file test_rng.cpp.

The next required step is to create instances of generators. This process
requires up to three parameters, supported by four constructors with optional
inputs to give seven possible ways to specify a new FibRng instance.

### Parameters:

##### init
This integer specifies the amount of effort expended during the initial
construction of the generator. There is normally little need to specify
this value as the default value does a good job of cooking the data for
an adequate number of iterations. Valid init values are 1..1,000,000.

##### seed
This string (a char * actually) is used to seed the random number generator.
The longer, and more unpredictable the string, the better a job it will do
in creating random (or at least unpredictable) starting conditions. The
default seed is a system derived value based on the current time and a
tickle counter.

##### depth
The integer depth determines the amount of data used to represent the internal
state of the generator. The default value (8) yields 232 bits of internal state.
This is adequate for casual use, but not nearly enough for more rigorous
applications. Valid depth values are 2..256.

### Constructors

The following four constructors are available:

```c++
explicit FibRng(int init, const char *seed, int depth = DEPTH);
explicit FibRng(          const char *seed, int depth = DEPTH);
explicit FibRng(int init,                   int depth);
explicit FibRng(                            int depth = DEPTH);
```
Note that three of these functions have an optional parameter while one does
not. This yields a total of seven ways to create a FibRng generator.
It is not possible to specify an init value with default seed
and depth values. This is because this arrangement is confused with the more
useful option of specifying a depth value with default init and seed values.

However, all is not lost. To emulate the missing option, simply use:

```c++
FibRng(init_value, FibRng::DEPTH);
```

### Data Generation

Once the generator is created, it must be put to work cranking out data. There
are a number of options for doing this:

```c++
// A "random" integer between 0 and sides-1.
uint32_t dice(uint32_t sides);

// A "random" integer between 0 and 255.
uint8_t byte(void);

// A "random" integer between 0 and 65535.
uint16_t word(void);

// A quick "random" float between 0 and 1.
double real(void);

// A better "random" float between 0 and 1.
double dbl(void);

// gen.ascii(b,l)   -- Fill buffer b with l random printable ASCII characters.
// gen.ascii(b,l,s) -- Fill buffer b with l random characters from string s.
void ascii(char *buffer, uint32_t len, const char *set = ASCII_7);
```

and also available

```c++
void reseed(const char *seed); // Reseed the sequence with the new value.
void spin(void);               // Spin the generator once.
void dump(void);               // A debug register dump.
```

If more than one stream of numbers is required, it is best to use multiple
instances of FibRng objects rather than rely on one.

## Contributing

#### Plan A

1. Fork it (https://github.com/PeterCamilleri/Fibonacci_CPP/fork)
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create new Pull Request

#### Plan B

Go to the GitHub repository and raise an issue calling attention to some
aspect that could use some TLC or a suggestion or an idea.

## License

The gem is available as open source under the terms of the
[MIT License](./LICENSE.txt).

## Code of Conduct

Everyone interacting in the counted_cache project’s codebases, issue trackers,
chat rooms and mailing lists is expected to follow the
[code of conduct](./CODE_OF_CONDUCT.md).
