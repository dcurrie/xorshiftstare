#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cinttypes>

#include "xorshift.hpp"

#ifndef RNG_NAME
#define RNG_NAME xorshift64star32a
#endif


int main()
{
    freopen(NULL, "wb", stdout);  // Only necessary on Windows, but harmless.

    constexpr size_t BUFFER_SIZE = 1024 * 1024 / sizeof(uint32_t);
    static uint32_t buffer[BUFFER_SIZE];

    RNG_NAME rng;

    fprintf(stderr, "S: 0x%016" PRIx64 "\n", rng.get_state());

    while (1) {
        for (size_t i = 0; i < BUFFER_SIZE; ++i)
            buffer[i] = rng();
        fwrite((void*) buffer, sizeof(buffer[0]), BUFFER_SIZE, stdout);
    }
}
