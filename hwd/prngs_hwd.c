
#if 1

#include "../xorshiftstare.h"

#if HWD_PRNG_BITS == 64

#if HAVE___UINT128_T
static uint128_v rng_state = 1u;
#else
static uint128_v rng_state = { .hi = 0u, .lo = 1u };
#endif

static inline uint64_t next (void)
{
    return RNG_NAME(&rng_state);
}

#else

static uint64_t rng_state = 1u;

static inline uint32_t next (void)
{
    return RNG_NAME(&rng_state);
}

#endif

#else

/* Sample file for hwd.c (xoroshiro128+). */

static inline uint64_t rotl(const uint64_t x, int k) {
    return (x << k) | (x >> (64 - k));
}

static uint64_t s[2] = { 1, -1ULL };

static uint64_t inline next() {
    const uint64_t s0 = s[0];
    uint64_t s1 = s[1];

    const uint64_t result_plus = s0 + s1;

    s1 ^= s0;
    s[0] = rotl(s0, 24) ^ s1 ^ (s1 << 16);
    s[1] = rotl(s1, 37);

    return result_plus;
}

#endif
