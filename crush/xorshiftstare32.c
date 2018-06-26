/** @file xorshiftstare.c
 *
 * @brief This is a test file for xorshiftstare.h -- you only need to include xorshiftstare.h
 */

#include "../xorshiftstare.h"

/* ************************ testing code below ************************** */

#ifdef TESTU01

#ifndef RNG_NAME
#define RNG_NAME xorshift64stare32a
#endif

#define STRN(x) #x
#define STRX(x) STRN(x)
#define NAME()  STRX(RNG_NAME)

static uint64_t rng_state = 1u;

static uint32_t next (void)
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

#if 0

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

#endif

#define NORM_32 ( ( 1./4 ) / ( 1LL << 30 ) )

double next_01 (void *unused0, void *unused1)
{
    return next() * NORM_32;
}

void write_state_64 (void *unused) 
{
    printf( "%llu\n", (unsigned long long)rng_state);
}

int main(int argc, char *argv[] )
{
    unif01_Gen gen;
    gen.GetU01 = next_01;
    gen.Write = write_state_64;

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
#if 0
    bool highBits = false;
#endif

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
#if 0
            case 'h':
                highBits = true;
                break;      
#endif
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

    if (argc > 0)
    {
        rng_state = strtoull(argv[0], NULL, 0);
    }
    else
    {
        // punt, use default
    }

#if 0
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
#endif
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

#if 0
    for (int i = 0; i < 10; i++)
    {
        //printf("0x%016" PRIx64 "\n", (uint64_t )next_32lo(NULL, NULL));
        printf("%" PRIu64 "\n", (uint64_t )rng_state);
        printf("%lu\n", (*gen.GetBits)(NULL, NULL));
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
    }

    return 0;
}
#endif
