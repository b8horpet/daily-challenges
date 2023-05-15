#include <type_traits>
#include <utility>
#include <array>
using u64 = unsigned long long;

template<u64 Val, u64... nums>
constexpr std::integer_sequence<u64, Val, nums...> concat_f(std::integer_sequence<u64, nums...>);

template<typename T, u64 Val>
using concat = decltype(concat_f<Val>(std::declval<T>()));

consteval u64 Sqrt(u64 v) {
	if(v<2) return v;
	u64 lower = 0;
	u64 upper = v/2;
	if(upper*upper <= v) return upper;
	u64 middle;
	while(lower+1 < upper)
	{
		middle = (upper+lower)/2;
		const u64 m2 = middle*middle;
		if(m2 < v) {
			lower = middle;
		} else if (m2 > v) {
			upper = middle-1;
		} else {
			return middle;
		}
	}
	if((lower+1)*(lower+1) <= v) return lower+1;
	return lower;
}

template<u64 first, u64... primes>
consteval u64 next(std::integer_sequence<u64, primes...>) {
	constexpr u64 target = first*u64{2}+u64{1};
	constexpr u64 tests[] = {primes...};
	for(u64 p=first+2; p<=target; p+=2) {
		bool check = true;
		for(u64 i=sizeof...(primes); i-->0 && tests[i]<=Sqrt(p);)
		{
			if(p % tests[i] == 0) {
				check=false;
				break;
			}
		}
		//bool check = ((p % primes) && ...);
		//bool check = (... && (p % primes));
		if(check) return p;
	}
	return 0; // should not happen
}

template<u64 N>
struct PrimeSequence {
	static constexpr u64 first = next<PrimeSequence<N-1>::first>(typename PrimeSequence<N-1>::type{});
	using type = concat<typename PrimeSequence<N-1>::type, first>;
};

template<>
struct PrimeSequence<1> {
	static constexpr u64 first = 2;
	using type = std::integer_sequence<u64, 2>;
};

template<>
struct PrimeSequence<2> {
	static constexpr u64 first = 3;
	using type = std::integer_sequence<u64, 3, 2>;
};

template<typename T, u64... idx>
constexpr T reorder(T v, std::integer_sequence<u64, idx...>) {
	return {v[sizeof...(idx)-idx-1]...};
}

template<u64... primes>
consteval std::array<u64, sizeof...(primes)> Generate(std::integer_sequence<u64, primes...>) {
	std::array<u64, sizeof...(primes)> p{primes...};
	return reorder(p,std::make_integer_sequence<u64,sizeof...(primes)>{});
}

template<u64 N>
struct FirstPrimes {
	static constexpr std::array<u64, N> value = Generate(typename PrimeSequence<N>::type{});
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
