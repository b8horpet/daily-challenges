#include "arrays.h"
#include <type_traits>

constexpr std::array<int, 0> a0{};
constexpr std::array<int, 1> a1{7};
constexpr std::array<int, 5> a2{1,2,3,4,5};
constexpr std::array<int, 5> a3{5,3,2,1,4};
constexpr std::array<int, 5> a4{2,2,1,2,1};

constexpr std::array<int, 4> e2{2,3,4,5};
constexpr std::array<int, 4> e3{5,3,2,4};
constexpr std::array<int, 4> e4{2,2,2,1};

static_assert(a0 == remove_smallest(a0), "wat");
static_assert(a0 == remove_smallest(a1), "wat");
static_assert(e2 == remove_smallest(a2), "wat");
static_assert(e3 == remove_smallest(a3), "wat");
static_assert(e4 == remove_smallest(a4), "wat");

using A0 = std::integer_sequence<int>;
using A1 = std::integer_sequence<int,7>;
using A2 = std::integer_sequence<int,1,2,3,4,5>;
using A3 = std::integer_sequence<int,5,3,2,1,4>;
using A4 = std::integer_sequence<int,2,2,1,2,1>;

using E2 = std::integer_sequence<int,2,3,4,5>;
using E3 = std::integer_sequence<int,5,3,2,4>;
using E4 = std::integer_sequence<int,2,2,2,1>;

static_assert(std::is_same_v<A0, remove_smallest_t<A0>>, "wut");
static_assert(std::is_same_v<A0, remove_smallest_t<A1>>, "wut");
static_assert(std::is_same_v<E2, remove_smallest_t<A2>>, "wut");
static_assert(std::is_same_v<E3, remove_smallest_t<A3>>, "wut");
static_assert(std::is_same_v<E4, remove_smallest_t<A4>>, "wut");

int main() {}
