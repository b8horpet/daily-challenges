all: prime sieve
.PHONY=all

prime:
	clang++ prime.cpp -std=c++20 -fbracket-depth=10000 -DNUM_PRIMES=1000 -O3 -o prime

sieve:
	clang++ sieve.cpp -std=c++20 -O3 -o sieve


clean:
	rm -f prime sieve
