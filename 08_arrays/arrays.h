#include <utility>
#include <array>
#include <algorithm>

template<typename T, std::size_t N>
constexpr std::array<T,N-1> remove_smallest(const std::array<T,N>& a) {
  std::size_t idx = 0;
  for(std::size_t i=1; i<N; ++i) {
    if(a[i] < a[idx]) idx = i;
  }
  std::array<T,N-1> result{};
  std::generate_n(result.begin(), idx, [&a, i=0]()mutable{return a[i++];});
  std::generate_n(result.begin()+idx,N-idx-1, [&a, i=idx+1]()mutable{return a[i++];});
  return result;
}

template<typename T>
constexpr std::array<T,0> remove_smallest(const std::array<T,0>& a) {
  return a;
}

namespace tmp {

template<typename T, std::size_t N>
struct concat {
  template<std::size_t... ns>
  static constexpr std::integer_sequence<std::size_t, ns..., N> helper(std::integer_sequence<std::size_t, ns...>);
  using type = decltype(helper(T{}));
};

template<std::size_t N, std::size_t I>
struct removed_indices {
  using type = typename concat<typename removed_indices<N-1,I>::type, N-1>::type;
};

template<std::size_t N>
struct removed_indices<N,N-1> {
  using type = typename removed_indices<N-1,N-1>::type;
};

template<std::size_t I>
struct removed_indices<0,I> {
  using type = std::integer_sequence<std::size_t>;
};

template<std::size_t N, typename T, T... ns>
constexpr T get(std::integer_sequence<T, ns...>) {
  static_assert(N<sizeof...(ns), "indexing error");
  T a[sizeof...(ns)] = {ns...};
  return a[N];
}

template<typename T, T... ns>
constexpr std::size_t size(std::integer_sequence<T, ns...>) {
  return sizeof...(ns);
}

template<typename T>
struct remove_smallest {
  using value_type = typename T::value_type;
  template<value_type... ns>
  static constexpr std::size_t smallest_index(std::integer_sequence<value_type,ns...>) {
    std::size_t idx=0;
    value_type a[sizeof...(ns)] = {ns...};
    for(std::size_t i=1; i<sizeof...(ns); ++i) {
      if(a[i]<a[idx]) idx=i;
    }
    return idx;
  }
  template<std::size_t... is>
  static constexpr auto helper(std::integer_sequence<std::size_t, is...>)
  -> std::integer_sequence<value_type, get<is>(T{})...>;
  using type = decltype(
    helper(
        typename removed_indices<
          size( T{} ),
	  smallest_index( T{} )
        >::type{}
    )
  );
};

}

template<typename T>
using remove_smallest_t = typename tmp::remove_smallest<T>::type;

