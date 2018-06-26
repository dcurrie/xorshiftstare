/** @file xorshiftstare.h
 *
 * @brief 32- and 64-bit pseudo random number generators based on ME O'Neill's Truncated Xorshift*
 *
 * @par
 * @copyright Copyright © 2018 Doug Currie, Londonderry, NH, USA
 * 
 * @par License
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * @par
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 * 
 * @par
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 */

/* Implmentation of a few variations of truncated XorShift* PRNGs
 * based on Melissa E. O'Neill's blog posts
 * http://www.pcg-random.org/categories/xorshift.html
 * and Github gist https://gist.github.com/imneme/9b769cefccac1f2bd728596da3a856dd
 */

/* ME O'Neill's implementation is C++ .hpp. This one translates it to C header file, and
 * is limited to the 32- and 64-bit versions. It can be used on platforms that support
 * 64-bit arithmetic, and implements optimizations for platforms with 128-bit arithmetic.
 */

#ifndef XORSHIFTSTARE_H
#define XORSHIFTSTARE_H

#include <stdint.h>

// Define the type uint128_v

#ifndef HAVE___UINT128_T
#if ((__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6) || __clang_major__ >= 9) && defined(__x86_64__))
#define HAVE___UINT128_T 1
typedef unsigned __int128 uint128_t;
#endif
#endif

#if HAVE___UINT128_T

typedef uint128_t uint128_v;

#else

typedef struct uint128_s
{
    uint64_t lo;
    uint64_t hi;
} uint128_v;

#endif

// Implement the helper inline functions

#if HAVE___UINT128_T

//#define UINT128_C(h,l) (((uint128_v )h << 64) + ((uint128_v )l))

static inline uint128_v xor128(const uint128_v x, const uint128_v y)
{
    return x ^ y;
}

static inline uint128_v shr128(const uint128_v x, const int s)
{
    return x >> s;
}

static inline uint128_v shl128(const uint128_v x, const int s)
{
    return x << s;
}

static inline uint64_t fracmult_128_64(uint128_v u, uint64_t v)
{
    return ((u * (uint128_v )v) >> 64);
}

// the seed function

static inline void xorshiftstare_64_seed (uint128_v *rng_state_p, uint128_v seed)
{
    *rng_state_p = seed;
}

static inline void xorshiftstare_64_seed_64 (uint128_v *rng_state_p, uint64_t seed)
{
    *rng_state_p = (uint128_v )seed;
}

#else

static inline uint128_v xor128(const uint128_v x, const uint128_v y)
{
    uint128_v result;
    result.lo = x.lo ^ y.lo;
    result.hi = x.hi ^ y.hi;
    return result;
}

static inline uint128_v shr128(const uint128_v x, const unsigned int s)
{
    uint128_v result;
    if (s >= 64)
    {
        result.hi = 0u;
        result.lo = x.hi >> (s - 64);
    }
    else
    {
        result.lo = x.lo >> s;
        result.hi = x.hi >> s;
        result.lo |= x.hi << (64 - s);
    }
    return result;
}

static inline uint128_v shl128(const uint128_v x, const unsigned int s)
{
    uint128_v result;
    if (s >= 64)
    {
        result.lo = 0u;
        result.hi = x.lo << (s - 64);
    }
    else
    {
        result.lo = x.lo << s;
        result.hi = x.hi << s;
        result.hi |= x.lo >> (64 - s);
    }
    return result;
}

static inline uint64_t lo32(const uint64_t x)
{
    return (x & 0xffffffffu);
}

static inline uint64_t hi32(const uint64_t x)
{
    return (x >> 32);
}

static inline uint64_t fracmult_128_64(uint128_v u, uint64_t v)
{
    uint128_v result;

#if defined(_MSC_VER) && defined(_M_AMD64)
    result.lo = _umul128(u.lo, v, &result.hi);
#else
    const uint64_t ul = lo32(u.lo);
    const uint64_t uh = hi32(u.lo);
    const uint64_t vl = lo32(v);
    const uint64_t vh = hi32(v);

    uint64_t t  = (ul * vl);

    //const uint64_t ll = lo32(t);

    t = (uh * vl) + hi32(t);

    const uint64_t lh = lo32(t) + (ul * vh);
    const uint64_t hl = hi32(t);

    result.hi = ((uh * vh) + hl) + hi32(lh);
    //result.lo = (lh << 32) + ll; // or v * v
#endif
    // now result.hi is (u.lo * v) >> 64
    // add in (u.hi * v)
    return (result.hi + (u.hi * v));
}

// the seed functions

static inline void xorshiftstare_64_seed (uint128_v *rng_state_p, uint128_v seed)
{
    rng_state_p->lo = seed.lo;
    rng_state_p->hi = seed.hi;
}

static inline void xorshiftstare_64_seed_64 (uint128_v *rng_state_p, uint64_t seed)
{
    rng_state_p->lo = seed;
    rng_state_p->hi = 0u;
}

#endif

static inline void xorshiftstare_32_seed (uint64_t *rng_state_p, uint64_t seed)
{
    *rng_state_p = seed;
}



// the generic versions of Truncated XorShift*

static inline uint64_t xorshiftstare_64 (uint128_v *rng_state_p
                                       , const uint64_t multiplier
                                       , const unsigned int a
                                       , const unsigned int b
                                       , const unsigned int c)
{
    uint128_v state = *rng_state_p;

    uint64_t result = fracmult_128_64(state, multiplier);

    state = xor128(state, shr128(state, a));
    state = xor128(state, shl128(state, b));
    state = xor128(state, shr128(state, c));

    *rng_state_p = state;

    return result;
}

static inline uint32_t xorshiftstare_32 (uint64_t *rng_state_p
                                       , const uint64_t multiplier
                                       , const unsigned int a
                                       , const unsigned int b
                                       , const unsigned int c)
{
    uint64_t state = *rng_state_p;

    uint32_t result = (state * multiplier) >> 32;

    state ^= state >> a;
    state ^= state << b;
    state ^= state >> c;

    *rng_state_p = state;

    return result;
}


// Specific tested variants of Truncated XorShift* from ME O'Neill's blog

// - 128 state bits, uint64_t output, period 2^128 - 1

static inline uint64_t xorshift128stare64a (uint128_v *rng_state_p)
{
    return xorshiftstare_64(rng_state_p, 0xd1251494eac238a5ULL, 24u, 69u, 35u);
}

static inline uint64_t xorshift128stare64b (uint128_v *rng_state_p)
{
    return xorshiftstare_64(rng_state_p, 0xfa5c5324af636dbdULL, 26u, 61u, 37u);
}

static inline uint64_t xorshift128stare64c (uint128_v *rng_state_p)
{
    return xorshiftstare_64(rng_state_p, 0xe1ee58bdbc73a745ULL, 45u, 61u, 11u);
}

static inline uint64_t xorshift128stare64d (uint128_v *rng_state_p)
{
    return xorshiftstare_64(rng_state_p, 0xf391092cc4e7515dULL, 41u, 63u, 1u);
}

#define MEO_SEED 0xc1f651c67c62c6e0uLL

static inline void xorshiftstare_64_init (uint128_v *rng_state_p)
{
    xorshiftstare_64_seed_64(rng_state_p, MEO_SEED);
}

// - 64 state bits, uint32_t output, period 2^64 - 1

static inline uint32_t xorshift64stare32a (uint64_t *rng_state_p)
{
    return xorshiftstare_32(rng_state_p, 0xd989bcacc137dcd5ULL, 11u, 31u, 18u);
}

static inline uint32_t xorshift64stare32b (uint64_t *rng_state_p)
{
    return xorshiftstare_32(rng_state_p, 0xd70ca3edf74bcc9dULL, 11u, 29u, 14u);
}

static inline uint32_t xorshift64stare32c (uint64_t *rng_state_p)
{
    return xorshiftstare_32(rng_state_p, 0x623c3040816c3dcdULL, 13u, 35u, 30u);
}

static inline uint32_t xorshift64stare32d (uint64_t *rng_state_p)
{
    return xorshiftstare_32(rng_state_p, 0x8971baedb6f2fcf5ULL, 21u, 35u, 4u);
}

static inline void xorshiftstare_32_init (uint64_t *rng_state_p)
{
    xorshiftstare_32_seed(rng_state_p, MEO_SEED);
}

#endif
