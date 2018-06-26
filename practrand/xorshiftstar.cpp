#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cinttypes>

#include "xorshift.hpp"

#ifndef RNG_NAME
#define RNG_NAME xorshift128star64a
#endif


int main()
{
    freopen(NULL, "wb", stdout);  // Only necessary on Windows, but harmless.

    constexpr size_t BUFFER_SIZE = 1024 * 1024 / sizeof(uint64_t);
    static uint64_t buffer[BUFFER_SIZE];

    RNG_NAME rng;

    fprintf(stderr, "S: 0x%016" PRIx64 "_%016" PRIx64 "\n", (uint64_t )(rng.get_state()>>64), (uint64_t )rng.get_state());

    while (1) {
        for (size_t i = 0; i < BUFFER_SIZE; ++i)
            buffer[i] = rng();
        fwrite((void*) buffer, sizeof(buffer[0]), BUFFER_SIZE, stdout);
    }
}
