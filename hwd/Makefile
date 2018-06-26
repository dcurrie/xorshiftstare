
# Configuration

DEFS64 = -DHWD_BITS=64 -DHWD_PRNG_BITS=64 -DHWD_DIM=8
DEFS32 = -DHWD_BITS=32 -DHWD_PRNG_BITS=32 -DHWD_DIM=8

#hwd: hwd.c prngs_hwd.c ../xorshiftstare
#	cc -O3 -std=c99 -Wall $(DEFS) hwd.c -o hwd 

CEXES = xorshift128stare64a xorshift128stare64b xorshift128stare64c xorshift128stare64d
CEXES32 = xorshift64stare32a xorshift64stare32b xorshift64stare32c xorshift64stare32d

all: $(CEXES) $(CEXES32)

xorshift128stare64a: hwd.c prngs_hwd.c ../xorshiftstare.h
	cc -std=c99 -O3 -Wall -DRNG_NAME=$@ $(DEFS64) $(INC) hwd.c $(LIBS) -o $@
xorshift128stare64b: hwd.c prngs_hwd.c ../xorshiftstare.h
	cc -std=c99 -O3 -Wall -DRNG_NAME=$@ $(DEFS64) $(INC) hwd.c $(LIBS) -o $@
xorshift128stare64c: hwd.c prngs_hwd.c ../xorshiftstare.h
	cc -std=c99 -O3 -Wall -DRNG_NAME=$@ $(DEFS64) $(INC) hwd.c $(LIBS) -o $@
xorshift128stare64d: hwd.c prngs_hwd.c ../xorshiftstare.h
	cc -std=c99 -O3 -Wall -DRNG_NAME=$@ $(DEFS64) $(INC) hwd.c $(LIBS) -o $@

xorshift64stare32a: hwd.c prngs_hwd.c ../xorshiftstare.h
	cc -std=c99 -O3 -Wall -DRNG_NAME=$@ $(DEFS32) $(INC) hwd.c $(LIBS) -o $@
xorshift64stare32b: hwd.c prngs_hwd.c ../xorshiftstare.h
	cc -std=c99 -O3 -Wall -DRNG_NAME=$@ $(DEFS32) $(INC) hwd.c $(LIBS) -o $@
xorshift64stare32c: hwd.c prngs_hwd.c ../xorshiftstare.h
	cc -std=c99 -O3 -Wall -DRNG_NAME=$@ $(DEFS32) $(INC) hwd.c $(LIBS) -o $@
xorshift64stare32d: hwd.c prngs_hwd.c ../xorshiftstare.h
	cc -std=c99 -O3 -Wall -DRNG_NAME=$@ $(DEFS32) $(INC) hwd.c $(LIBS) -o $@

clean:
	rm -f xorshift128* xorshift64*
