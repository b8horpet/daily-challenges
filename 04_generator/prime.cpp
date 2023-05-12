#include <type_traits>
#include <utility>
#include <array>
using u64 = unsigned long long;

template<u64... nums>
constexpr bool Test(u64 num, std::integer_sequence<u64, nums...>) {
	return ((num % 2) && ... && (num % (nums*2+3)));
}

template<u64 N>
struct Num {
	static constexpr bool is_prime = Test(N,std::make_integer_sequence<u64, N/4>{});
	static constexpr u64 value = N;
};

template<>
struct Num<3> {
	static constexpr bool is_prime = true;
};

template<>
struct Num<2> {
	static constexpr bool is_prime = true;
};

template<>
struct Num<1> {
	static constexpr bool is_prime = false;
};

template<>
struct Num<0> {
	static constexpr bool is_prime = false;
};

template<u64 N>
constexpr u64 operator|(u64 a, Num<N> b) {
	return a ? a : (Num<N>::is_prime ? N : 0ull);
}

template<u64 start, u64... nums>
constexpr u64 Search(std::integer_sequence<u64, nums...>) {
	return (0ull | ... | Num<start+nums*2>{});
}

template<u64 Nth>
struct Prime {
	static constexpr u64 value = Search<Prime<Nth-1>::value+2>(std::make_integer_sequence<u64, Prime<Nth-1>::value/2>{});
};

template<>
struct Prime<0> {
	static constexpr u64 value = 2;
};

template<>
struct Prime<1> {
	static constexpr u64 value = 3;
};

template<u64... nums>
constexpr std::array<u64, sizeof...(nums)> Generate(std::integer_sequence<u64, nums...>) {
	return {Prime<nums>::value ...};
}

template<u64 N>
struct FirstPrimes {
	static constexpr std::array<u64, N> value = Generate(std::make_integer_sequence<u64, N>{});
};

#ifndef NUM_PRIMES
#error "define number of primes to generate"
#else
constexpr u64 PrimesToGenerate = NUM_PRIMES;
#endif

#include <cmath>
#include <vector>

class Primes
{
	static constexpr auto StaticPrimes = FirstPrimes<PrimesToGenerate>::value;
	static constexpr u64 SPS = StaticPrimes.size();
	static_assert(SPS > 1, "need odd prime");
	std::vector<u64> primes;
	inline bool check(u64 n) const {
		auto l = std::sqrt(n);
		for(auto p : StaticPrimes) {
			if(p>l) return true;
			if(n%p==0) return false;
		}
		for(auto p : primes) {
			if(p>l) return true;
			if(n%p==0) return false;
		}
		u64 p = StaticPrimes.back() + 2;
		if(!primes.empty()) {
			p = primes.back() + 2;
		}
		while(p<=l) {
			if(n%p==0) return false;
			p+=2;
		}
		return true;
	}
	inline u64 next(u64 p) const {
		u64 t = p + 2;
		while(!check(t)) t += 2;
		return t;
	}
	u64 compute(u64 idx) const {
		u64 v = 0;
		if(!primes.empty()) {
			v = next(primes.back());
		} else {
			v = next(StaticPrimes.back());
		}
		for(;idx-->0;) {
			v = next(v);
		}
		return v;
	}
public:
	u64 operator[](u64 index) const {
		if(index < SPS) {
			return StaticPrimes[index];
		} else if(index-SPS < primes.size()) {
			return primes[index-SPS];
		} else {
			return compute(index-SPS-primes.size());
		}
	}
	Primes(u64 limit) {
		primes.reserve(limit);
		u64 p = StaticPrimes.back();
		for(;limit-->0;) {
			p=next(p);
			primes.push_back(p);
		}
	}
};


#include <cstdio>
#include <string>

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		fprintf(stderr, "usage: %s <N>", argv[0]);
		return 1;
	}
	u64 gen = 100'000;
	if(argc>2) {
		gen = std::stoull(argv[2]);
	}
	Primes P{gen};
	u64 N = std::stoull(argv[1]);
	printf("%llu\n", P[N] );
}
