#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>

#include "../xorshiftstare.h"

#ifndef RNG_NAME
#define RNG_NAME xorshift64stare32a
#endif

static uint64_t rng_state;

static uint32_t rng()
{
    return RNG_NAME(&rng_state);
}

int main()
{
    freopen(NULL, "wb", stdout);  // Only necessary on Windows, but harmless.

    static const size_t BUFFER_SIZE = 1024 * 1024 / sizeof(uint32_t);
    static uint32_t buffer[BUFFER_SIZE];

    xorshiftstare_32_init(&rng_state);

    fprintf(stderr, "S: 0x%016" PRIx64 "\n", rng_state);

    while (1) {
        for (size_t i = 0; i < BUFFER_SIZE; ++i)
            buffer[i] = rng();
        fwrite((void*) buffer, sizeof(buffer[0]), BUFFER_SIZE, stdout);
    }
}
