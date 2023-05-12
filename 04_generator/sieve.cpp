#include <cmath>
#include <vector>
#include <cstdio>
#include <string>
using u64 = unsigned long long;

#ifdef USE_BOOL_VECTOR
using storage_t = bool;
#else
using storage_t = unsigned char;
static_assert(sizeof(unsigned char) == 1, "need 1 byte type");
#endif

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		fprintf(stderr, "usage: %s <N>", argv[0]);
		return 1;
	}
	u64 N = std::stoull(argv[1]);
	std::vector<storage_t> primes;
	u64 B = N*(std::log(N)+std::log(std::log(N)));
	if(N < 10) B = 40;
	primes.resize(B, 1);
	u64 p=2;
	for(u64 i=0; i<N; ++i)
	{
		for(u64 x=p-1; x<B; x+=p)
		{
			primes[x]=0;
		}
		for(p++;!primes[p-1];++p);
	}
	printf("%llu\n", p);
}
