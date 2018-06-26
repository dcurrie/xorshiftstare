

PEXES = xorshift128star64a xorshift128star64b xorshift128star64c xorshift128star64d
CEXES = xorshift128stare64a xorshift128stare64b xorshift128stare64c xorshift128stare64d
SEXES = xorshift128stars64a xorshift128stars64b xorshift128stars64c xorshift128stars64d

PEXES32 = xorshift64star32a xorshift64star32b xorshift64star32c xorshift64star32d
CEXES32 = xorshift64stare32a xorshift64stare32b xorshift64stare32c xorshift64stare32d

all: $(CEXES) $(PEXES) $(SEXES) $(PEXES32) $(CEXES32)
	 

xorshift128star64a: xorshiftstar.cpp
	c++ -std=c++11 -O3 -DRNG_NAME=$@ -o $@ xorshiftstar.cpp
xorshift128star64b: xorshiftstar.cpp
	c++ -std=c++11 -O3 -DRNG_NAME=$@ -o $@ xorshiftstar.cpp
xorshift128star64c: xorshiftstar.cpp
	c++ -std=c++11 -O3 -DRNG_NAME=$@ -o $@ xorshiftstar.cpp
xorshift128star64d: xorshiftstar.cpp
	c++ -std=c++11 -O3 -DRNG_NAME=$@ -o $@ xorshiftstar.cpp

xorshift128stare64a: xorshiftstare.c
	cc -std=c99 -O3 -DRNG_NAME=$@ -o $@ xorshiftstare.c
xorshift128stare64b: xorshiftstare.c
	cc -std=c99 -O3 -DRNG_NAME=$@ -o $@ xorshiftstare.c
xorshift128stare64c: xorshiftstare.c
	cc -std=c99 -O3 -DRNG_NAME=$@ -o $@ xorshiftstare.c
xorshift128stare64d: xorshiftstare.c
	cc -std=c99 -O3 -DRNG_NAME=$@ -o $@ xorshiftstare.c

xorshift128stars64a: xorshiftstare.c
	cc -std=c99 -O3 -DRNG_NAME=$@ -DHAVE___UINT128_T=0 -o $@ xorshiftstare.c
xorshift128stars64b: xorshiftstare.c
	cc -std=c99 -O3 -DRNG_NAME=$@ -DHAVE___UINT128_T=0 -o $@ xorshiftstare.c
xorshift128stars64c: xorshiftstare.c
	cc -std=c99 -O3 -DRNG_NAME=$@ -DHAVE___UINT128_T=0 -o $@ xorshiftstare.c
xorshift128stars64d: xorshiftstare.c
	cc -std=c99 -O3 -DRNG_NAME=$@ -DHAVE___UINT128_T=0 -o $@ xorshiftstare.c

xorshift64star32a: xorshiftstar32.cpp
	c++ -std=c++11 -O3 -DRNG_NAME=$@ -o $@ xorshiftstar32.cpp
xorshift64star32b: xorshiftstar32.cpp
	c++ -std=c++11 -O3 -DRNG_NAME=$@ -o $@ xorshiftstar32.cpp
xorshift64star32c: xorshiftstar32.cpp
	c++ -std=c++11 -O3 -DRNG_NAME=$@ -o $@ xorshiftstar32.cpp
xorshift64star32d: xorshiftstar32.cpp
	c++ -std=c++11 -O3 -DRNG_NAME=$@ -o $@ xorshiftstar32.cpp

xorshift64stare32a: xorshiftstare32.c
	cc -std=c99 -O3 -DRNG_NAME=$@ -o $@ xorshiftstare32.c
xorshift64stare32b: xorshiftstare32.c
	cc -std=c99 -O3 -DRNG_NAME=$@ -o $@ xorshiftstare32.c
xorshift64stare32c: xorshiftstare32.c
	cc -std=c99 -O3 -DRNG_NAME=$@ -o $@ xorshiftstare32.c
xorshift64stare32d: xorshiftstare32.c
	cc -std=c99 -O3 -DRNG_NAME=$@ -o $@ xorshiftstare32.c

test: all
	./xorshift128stars64a | hexdump -Cv | head -n 1000 > ts.txt
	./xorshift128stare64a | hexdump -Cv | head -n 1000 > te.txt
	./xorshift128star64a  | hexdump -Cv | head -n 1000 > tm.txt
	diff te.txt tm.txt
	diff te.txt ts.txt
	./xorshift128stars64b | hexdump -Cv | head -n 1000 > ts.txt
	./xorshift128stare64b | hexdump -Cv | head -n 1000 > te.txt
	./xorshift128star64b  | hexdump -Cv | head -n 1000 > tm.txt
	diff te.txt tm.txt
	diff te.txt ts.txt
	./xorshift128stars64c | hexdump -Cv | head -n 1000 > ts.txt
	./xorshift128stare64c | hexdump -Cv | head -n 1000 > te.txt
	./xorshift128star64c  | hexdump -Cv | head -n 1000 > tm.txt
	diff te.txt tm.txt
	diff te.txt ts.txt
	./xorshift128stars64d | hexdump -Cv | head -n 1000 > ts.txt
	./xorshift128stare64d | hexdump -Cv | head -n 1000 > te.txt
	./xorshift128star64d  | hexdump -Cv | head -n 1000 > tm.txt
	diff te.txt tm.txt
	diff te.txt ts.txt
	./xorshift64stare32a | hexdump -Cv | head -n 1000 > te.txt
	./xorshift64star32a  | hexdump -Cv | head -n 1000 > tm.txt
	diff te.txt tm.txt
	./xorshift64stare32b | hexdump -Cv | head -n 1000 > te.txt
	./xorshift64star32b  | hexdump -Cv | head -n 1000 > tm.txt
	diff te.txt tm.txt
	./xorshift64stare32c | hexdump -Cv | head -n 1000 > te.txt
	./xorshift64star32c  | hexdump -Cv | head -n 1000 > tm.txt
	diff te.txt tm.txt
	./xorshift64stare32d | hexdump -Cv | head -n 1000 > te.txt
	./xorshift64star32d  | hexdump -Cv | head -n 1000 > tm.txt
	diff te.txt tm.txt

testa: xorshift128stare64a
	./xorshift128stare64a | ../../PractRand/PractRand_0.93/RNG_test stdin64

testb: xorshift128stare64b
	./xorshift128stare64b | ../../PractRand/PractRand_0.93/RNG_test stdin64

testc: xorshift128stare64c
	./xorshift128stare64b | ../../PractRand/PractRand_0.93/RNG_test stdin64

testd: xorshift128stare64d
	./xorshift128stare64d | ../../PractRand/PractRand_0.93/RNG_test stdin64

clean:
	rm -f *.txt xorshift128* xorshift64*
