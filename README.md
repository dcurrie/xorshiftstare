# xorshiftstare
Truncated XorShift* 64-bit (and 32-bit) pseudo random number generator

Implmentation of a few variations of truncated XorShift* PRNGs based on Melissa E. O'Neill's 
[blog posts](http://www.pcg-random.org/categories/xorshift.html)
and Github [gist](https://gist.github.com/imneme/9b769cefccac1f2bd728596da3a856dd).

ME O'Neill's implementation is a C++ .hpp file. This implemetation is a translation of that to a
C  .h header file, and is limited to the 32- and 64-bit versions of the PRNGs. It can be used on 
platforms that support 64-bit arithmetic, and implements optimizations for platforms with 
128-bit arithmetic.

