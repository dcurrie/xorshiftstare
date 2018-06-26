TESTU01_DIR=/Users/e/dev/random/TestU01

LD_LIBRARY_PATH:=$(TESTU01_DIR)/install/lib:"$(LD_LIBRARY_PATH)"
export LD_LIBRARY_PATH

INC = -I$(TESTU01_DIR)/install/include
LIBS = -L$(TESTU01_DIR)/install/lib -lprobdist -lmylib -ltestu01

CEXES = xorshift128stare64a xorshift128stare64b xorshift128stare64c xorshift128stare64d
CEXES32 = xorshift64stare32a xorshift64stare32b xorshift64stare32c xorshift64stare32d

all: $(CEXES) $(CEXES32)

xorshift128stare64a: xorshiftstare.c ../xorshiftstare.h
	cc -std=c99 -O3 -Wall -DRNG_NAME=$@ -DTESTU01=1 $(INC) xorshiftstare.c $(LIBS) -o $@
xorshift128stare64b: xorshiftstare.c ../xorshiftstare.h
	cc -std=c99 -O3 -Wall -DRNG_NAME=$@ -DTESTU01=1 $(INC) xorshiftstare.c $(LIBS) -o $@
xorshift128stare64c: xorshiftstare.c ../xorshiftstare.h
	cc -std=c99 -O3 -Wall -DRNG_NAME=$@ -DTESTU01=1 $(INC) xorshiftstare.c $(LIBS) -o $@
xorshift128stare64d: xorshiftstare.c ../xorshiftstare.h
	cc -std=c99 -O3 -Wall -DRNG_NAME=$@ -DTESTU01=1 $(INC) xorshiftstare.c $(LIBS) -o $@

xorshift64stare32a: xorshiftstare32.c ../xorshiftstare.h
	cc -std=c99 -O3 -Wall -DRNG_NAME=$@ -DTESTU01=1 $(INC) xorshiftstare32.c $(LIBS) -o $@
xorshift64stare32b: xorshiftstare32.c ../xorshiftstare.h
	cc -std=c99 -O3 -Wall -DRNG_NAME=$@ -DTESTU01=1 $(INC) xorshiftstare32.c $(LIBS) -o $@
xorshift64stare32c: xorshiftstare32.c ../xorshiftstare.h
	cc -std=c99 -O3 -Wall -DRNG_NAME=$@ -DTESTU01=1 $(INC) xorshiftstare32.c $(LIBS) -o $@
xorshift64stare32d: xorshiftstare32.c ../xorshiftstare.h
	cc -std=c99 -O3 -Wall -DRNG_NAME=$@ -DTESTU01=1 $(INC) xorshiftstare32.c $(LIBS) -o $@

test64:
	./xorshift128stare64a -s        > output/xorshift128stare64a.txt
	./xorshift128stare64b -s        > output/xorshift128stare64b.txt
	./xorshift128stare64c -s        > output/xorshift128stare64c.txt
	./xorshift128stare64d -s        > output/xorshift128stare64d.txt
	./xorshift128stare64a -s -r    >> output/xorshift128stare64a.txt
	./xorshift128stare64b -s -r    >> output/xorshift128stare64b.txt
	./xorshift128stare64c -s -r    >> output/xorshift128stare64c.txt
	./xorshift128stare64d -s -r    >> output/xorshift128stare64d.txt
	./xorshift128stare64a -s -h    >> output/xorshift128stare64a.txt
	./xorshift128stare64b -s -h    >> output/xorshift128stare64b.txt
	./xorshift128stare64c -s -h    >> output/xorshift128stare64c.txt
	./xorshift128stare64d -s -h    >> output/xorshift128stare64d.txt
	./xorshift128stare64a -s -h -r >> output/xorshift128stare64a.txt
	./xorshift128stare64b -s -h -r >> output/xorshift128stare64b.txt
	./xorshift128stare64c -s -h -r >> output/xorshift128stare64c.txt
	./xorshift128stare64d -s -h -r >> output/xorshift128stare64d.txt
	./xorshift128stare64a -m       >> output/xorshift128stare64a.txt
	./xorshift128stare64b -m       >> output/xorshift128stare64b.txt
	./xorshift128stare64c -m       >> output/xorshift128stare64c.txt
	./xorshift128stare64d -m       >> output/xorshift128stare64d.txt
	./xorshift128stare64a -m -r    >> output/xorshift128stare64a.txt
	./xorshift128stare64b -m -r    >> output/xorshift128stare64b.txt
	./xorshift128stare64c -m -r    >> output/xorshift128stare64c.txt
	./xorshift128stare64d -m -r    >> output/xorshift128stare64d.txt
	./xorshift128stare64a -m -h    >> output/xorshift128stare64a.txt
	./xorshift128stare64b -m -h    >> output/xorshift128stare64b.txt
	./xorshift128stare64c -m -h    >> output/xorshift128stare64c.txt
	./xorshift128stare64d -m -h    >> output/xorshift128stare64d.txt
	./xorshift128stare64a -m -h -r >> output/xorshift128stare64a.txt
	./xorshift128stare64b -m -h -r >> output/xorshift128stare64b.txt
	./xorshift128stare64c -m -h -r >> output/xorshift128stare64c.txt
	./xorshift128stare64d -m -h -r >> output/xorshift128stare64d.txt
	./xorshift128stare64a -b       >> output/xorshift128stare64a.txt
	./xorshift128stare64b -b       >> output/xorshift128stare64b.txt
	./xorshift128stare64c -b       >> output/xorshift128stare64c.txt
	./xorshift128stare64d -b       >> output/xorshift128stare64d.txt
	./xorshift128stare64a -b -r    >> output/xorshift128stare64a.txt
	./xorshift128stare64b -b -r    >> output/xorshift128stare64b.txt
	./xorshift128stare64c -b -r    >> output/xorshift128stare64c.txt
	./xorshift128stare64d -b -r    >> output/xorshift128stare64d.txt
	./xorshift128stare64a -b -h    >> output/xorshift128stare64a.txt
	./xorshift128stare64b -b -h    >> output/xorshift128stare64b.txt
	./xorshift128stare64c -b -h    >> output/xorshift128stare64c.txt
	./xorshift128stare64d -b -h    >> output/xorshift128stare64d.txt
	./xorshift128stare64a -b -h -r >> output/xorshift128stare64a.txt
	./xorshift128stare64b -b -h -r >> output/xorshift128stare64b.txt
	./xorshift128stare64c -b -h -r >> output/xorshift128stare64c.txt
	./xorshift128stare64d -b -h -r >> output/xorshift128stare64d.txt

test32:
	./xorshift64stare32a -s        > output/xorshift64stare32a.txt
	./xorshift64stare32b -s        > output/xorshift64stare32b.txt
	./xorshift64stare32c -s        > output/xorshift64stare32c.txt
	./xorshift64stare32d -s        > output/xorshift64stare32d.txt
	./xorshift64stare32a -s -r    >> output/xorshift64stare32a.txt
	./xorshift64stare32b -s -r    >> output/xorshift64stare32b.txt
	./xorshift64stare32c -s -r    >> output/xorshift64stare32c.txt
	./xorshift64stare32d -s -r    >> output/xorshift64stare32d.txt
	./xorshift64stare32a -m       >> output/xorshift64stare32a.txt
	./xorshift64stare32b -m       >> output/xorshift64stare32b.txt
	./xorshift64stare32c -m       >> output/xorshift64stare32c.txt
	./xorshift64stare32d -m       >> output/xorshift64stare32d.txt
	./xorshift64stare32a -m -r    >> output/xorshift64stare32a.txt
	./xorshift64stare32b -m -r    >> output/xorshift64stare32b.txt
	./xorshift64stare32c -m -r    >> output/xorshift64stare32c.txt
	./xorshift64stare32d -m -r    >> output/xorshift64stare32d.txt
	./xorshift64stare32a -b       >> output/xorshift64stare32a.txt
	./xorshift64stare32b -b       >> output/xorshift64stare32b.txt
	./xorshift64stare32c -b       >> output/xorshift64stare32c.txt
	./xorshift64stare32d -b       >> output/xorshift64stare32d.txt
	./xorshift64stare32a -b -r    >> output/xorshift64stare32a.txt
	./xorshift64stare32b -b -r    >> output/xorshift64stare32b.txt
	./xorshift64stare32c -b -r    >> output/xorshift64stare32c.txt
	./xorshift64stare32d -b -r    >> output/xorshift64stare32d.txt

clean:
	rm -f xorshift128* xorshift64*
