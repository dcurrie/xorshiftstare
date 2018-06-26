/** @file xorshiftstare.c
 *
 * @brief This is a test file for xorshiftstare.h -- you only need to include xorshiftstare.h
 */

#include "../xorshiftstare.h"

/* ************************ testing code below ************************** */

#ifdef TESTU01

#ifndef RNG_NAME
#define RNG_NAME xorshift128stare64a
#endif

#define STRN(x) #x
#define STRX(x) STRN(x)
#define NAME()  STRX(RNG_NAME)

#if HAVE___UINT128_T
static uint128_v rng_state = 1u;
#else
static uint128_v rng_state = { .hi = 0u, .lo = 1u };
#endif

static uint64_t next (void)
{
    return RNG_NAME(&rng_state);
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include <unif01.h>
#include <bbattery.h>
#include <TestU01.h>

// unif01.h includes gdef.h which defines these, but we need other stuff from inttypes.h
#undef PRIdLEAST64
#undef PRIuLEAST64
#include <inttypes.h>


inline uint32_t rev32(uint32_t v)
{
    // https://graphics.stanford.edu/~seander/bithacks.html
    // swap odd and even bits
    v = ((v >> 1) & 0x55555555) | ((v & 0x55555555) << 1);
    // swap consecutive pairs
    v = ((v >> 2) & 0x33333333) | ((v & 0x33333333) << 2);
    // swap nibbles ...
    v = ((v >> 4) & 0x0F0F0F0F) | ((v & 0x0F0F0F0F) << 4);
    // swap bytes
    v = ((v >> 8) & 0x00FF00FF) | ((v & 0x00FF00FF) << 8);
    // swap 2-byte-long pairs
    v = ( v >> 16             ) | ( v               << 16);
    return v;
}

/* Note that this function returns a 32-bit number. */
unsigned long next_32lo (void *unused0, void *unused1)
{
    return (uint32_t )next();
}

/* Note that this function returns a 32-bit number. */
unsigned long next_32lorev (void *unused0, void *unused1)
{
    return rev32((uint32_t )next());
}

/* Note that this function returns a 32-bit number. */
unsigned long next_32hirev (void *unused0, void *unused1)
{
    return rev32((uint32_t )((uint64_t )next() >> 32));
}

/* Note that this function returns a 32-bit number. */
unsigned long next_32hi (void *unused0, void *unused1)
{
    return (uint32_t )((uint64_t )next() >> 32);
} 

#define NORM_64 ( ( 1./4 ) / ( 1LL << 62 ) )

double next_01 (void *unused0, void *unused1)
{
    return next() * NORM_64;
}

//void write_state_64 (void *unused) 
//{
//    printf( "%llu\n", (unsigned long long)rng_state);
//}

void write_128 (uint128_v r) 
{
#if HAVE___UINT128_T
    printf("0x%016" PRIx64 "_%016" PRIx64 "", (unsigned long long)(r >> 64), (unsigned long long)(r));
#else
    printf("0x%016" PRIx64 "_%016" PRIx64 "", (unsigned long long)(r.hi), (unsigned long long)(r.lo));
#endif
    printf("\n");
}

void write_state_128 (void *unused) 
{
    write_128(rng_state);
}

int main(int argc, char *argv[] )
{
    unif01_Gen gen;
    gen.GetU01 = next_01;
    gen.Write = write_state_128;

    if (argc <= 1)
    {
usage:
        fprintf(stderr, "%s [-v] [-r] [-s|m|b|l] [-k] [seeds...]\n", argv[0]);
        exit(1);
    }

    // Config options for TestU01
    swrite_Basic = FALSE;  // Turn of TestU01 verbosity by default
                           // reenable by -v option.

    // Config options for generator output
    bool reverseBits = false;
    bool highBits = false;

    // Config options for tests
    bool testSmallCrush = false;
    bool testCrush = false;
    bool testBigCrush = false;
    bool testLinComp = false;
    bool testSkip = false;

    // Handle command-line option switches
    while (1)
    {
        --argc;
        ++argv;
        if ((argc == 0) || (argv[0][0] != '-'))
            break;
        if ((argv[0][1]=='\0') || (argv[0][2]!='\0'))
            goto usage;
        switch(argv[0][1])
        {
            case 'r':
                reverseBits = true;
                break;      
            case 'h':
                highBits = true;
                break;      
            case 's':
                testSmallCrush = true;
                break;
            case 'm':
                testCrush = true;
                break;
            case 'b':
                testBigCrush = true;
                break;
            case 'l':
                testLinComp = true;
                break;
            case 'v':
                swrite_Basic = TRUE;
                break;
            case 'k':
                testSkip = true;
                break;
            default:
                goto usage;
        }
    }

    if (argc > 1)
    {
#if HAVE___UINT128_T
        rng_state = ((uint128_v )strtoull(argv[0], NULL, 0) << 64) | strtoull(argv[1], NULL, 0);
#else
        rng_state.hi = strtoull(argv[0], NULL, 0);
        rng_state.lo = strtoull(argv[1], NULL, 0);
#endif
    }
    else if (argc > 0)
    {
#if HAVE___UINT128_T
        rng_state = strtoull(argv[0], NULL, 0);
#else
        rng_state.hi = 0u;
        rng_state.lo = strtoull(argv[0], NULL, 0);
#endif
    }
    else
    {
        // punt, use default
    }

    if (highBits)
    {
        if (reverseBits)
        {
            gen.GetBits = next_32hirev;
            gen.name = NAME() " high32 reversed";
        }
        else
        {
            gen.GetBits = next_32hi;
            gen.name = NAME() " high32";
        }
    }
    else
    {
        if (reverseBits)
        {
            gen.GetBits = next_32lorev;
            gen.name = NAME() " low32 reversed";
        }
        else
        {
            gen.GetBits = next_32lo;
            gen.name = NAME() " low32";
        }
    }

#if HAVE___UINT128_T
    printf("Using __uint128_t\n");
#else
    printf("Using emulated uint128_v\n");
#endif

#if 0
    for (int i = 0; i < 10; i++)
    {
        printf("0x%016" PRIx64 "\n", (uint64_t )next_32lo(NULL, NULL));
        //printf("0x%016" PRIx64 "\n", (uint64_t )next_32lorev(NULL, NULL));
    }
#endif

    if (swrite_Basic)
    {
        // verbose
        printf("0x%016" PRIx64 "\n", (uint64_t )next());
    }

    if (testSmallCrush)
    {
        bbattery_SmallCrush(&gen);
        fflush(stdout);
    }
    if (testCrush)
    {
        bbattery_Crush(&gen);
        fflush(stdout);
    }
    if (testBigCrush)
    {
        bbattery_BigCrush(&gen);
        fflush(stdout);
    }
    if (testLinComp)
    {
        static int sizes[] = {250, 500, 1000, 5000, 25000, 50000, 75000};
        scomp_Res* res = scomp_CreateRes();
        swrite_Basic = TRUE;
        for (int i = 0; i < sizeof(sizes)/sizeof(int); i++)
            scomp_LinearComp(&gen, res, 1, sizes[i], 0, 1);
        scomp_DeleteRes(res);
        fflush(stdout);
    }
    if (testSkip)
    {
        // TODO

        // hack to unit test stuff

#if HAVE___UINT128_T
#else
        uint128_v x, y, z, r;

        printf("Unit testing...\n");
        x = (uint128_v ){ .hi = 1u, .lo = 2u };
        y = (uint128_v ){ .hi = 2u, .lo = 4u };
        z = (uint128_v ){ .hi = 0u, .lo = 0x8000000000000001u };
        r = shl128(x, 1);
        assert(r.hi == y.hi && r.lo == y.lo);
        r = shr128(x, 1);
        assert(r.hi == z.hi && r.lo == z.lo);
        r = xor128(x, y);
        assert(r.hi == 3u && r.lo == 6u);
        r = xor128(z, z);
        assert(r.hi == 0 && r.lo == 0);

        uint64_t p = fracmult_128_64(x, 2);
        assert(p == y.hi);
        p = fracmult_128_64(z, 2);
        assert(p == 1);
        z.hi = 3;
        p = fracmult_128_64(z, 2);
        assert(p == 7);

        r = shl128(x, 69);
        //printf("%llu\n", r.hi);
        assert(r.hi == 64 && r.lo == 0);
        z.hi = 64;
        r = shr128(z, 69);
        assert(r.hi == 0 && r.lo == 2);
        
#endif

    }

    return 0;
}
#endif
