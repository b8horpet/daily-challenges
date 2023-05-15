all: prime sieve
.PHONY=all

prime:
	clang++ prime.cpp -std=c++20 -fbracket-depth=10000 -ftemplate-depth=10000 -DNUM_PRIMES=6000 -O3 -o prime -march=native

sieve:
	clang++ sieve.cpp -std=c++20 -O3 -o sieve -march=native #-DUSE_BOOL_VECTOR


clean:
	rm -f prime sieve
