#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>

#include "../xorshiftstare.h"

// This is a hack to support testing of the non-HAVE___UINT128_T versions of the functions
#define xorshift128stars64a xorshift128stare64a
#define xorshift128stars64b xorshift128stare64b
#define xorshift128stars64c xorshift128stare64c
#define xorshift128stars64d xorshift128stare64d

#ifndef RNG_NAME
#define RNG_NAME xorshift128stare64a
#endif

static uint128_v rng_state;

static uint64_t rng()
{
    return RNG_NAME(&rng_state);
}

int main()
{
    freopen(NULL, "wb", stdout);  // Only necessary on Windows, but harmless.

    static const size_t BUFFER_SIZE = 1024 * 1024 / sizeof(uint64_t);
    static uint64_t buffer[BUFFER_SIZE];

    xorshiftstare_64_init(&rng_state);

#if HAVE___UINT128_T
    fprintf(stderr, "S: 0x%016" PRIx64 "_%016" PRIx64 "\n", (uint64_t )(rng_state>>64), (uint64_t )rng_state);
#else
    fprintf(stderr, "S: 0x%016" PRIx64 "_%016" PRIx64 "\n", rng_state.hi, rng_state.lo);
#endif

    while (1) {
        for (size_t i = 0; i < BUFFER_SIZE; ++i)
            buffer[i] = rng();
        fwrite((void*) buffer, sizeof(buffer[0]), BUFFER_SIZE, stdout);
    }
}
