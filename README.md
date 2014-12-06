# FibonacciRng in C++

This archive contains a port of the Fibonacci Pseudo Random Number Generator
from Ruby to C++. It is still only a portion of the original, but most of
the important functional bits are now present.


## Installation

This code does not have an installation procedure. To use it, simply add the
FibRng.cpp and FibRng.h files to your project by whatever means is most
convenient. While C++ is awkward and a pain, it does seem to run about one
hundred times faster than the Ruby version, so there you go.

The file test_rng.cpp contains a very simple demo of the generator in action.

## Usage

    #include "FibRng.h"

Then in an appropriate place in the code:

    FibRng gen(depth);

Where depth is an optional integer value between 2 and are you kidding
You can also get a "random" generator of the default depth by using:

    FibRng gen(depth);

To specify a seed string use:

    FibRng gen("test");

and yes an optional depth may follow the seed value.

To get some data out here are some options:

    gen.dice(100)     # A "random" integer between 0 and 99
    gen.byte()        # A "random" integer between 0 and 255
    gen.word()        # A "random" integer between 0 and 65535
    gen.real()        # A "random" float between 0 and less than 1.

and also available

    gen.reseed("string")  # Reseed the sequence with the new value.
    gen.spin()            # Spin the generator once.

If more than one stream of numbers is required, it is best to use multiple
instances of FibonacciRng objects rather than rely on one.

## Contributing

1. Fork it
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create new Pull Request
