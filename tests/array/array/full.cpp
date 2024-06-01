#include "nmtools/array/array/full.hpp"
#include "nmtools/testing/data/array/full.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

#define RUN_full_impl(...) \
nm::array::full(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs full fn to callable lambda
#define RUN_full(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("full-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_full_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_full(case_name, ...) \
RUN_full_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define FULL_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, full, case_name); \
    using namespace args; \
    auto result = RUN_full(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("full(case1)" * doctest::test_suite("array::full"))
{
    FULL_SUBCASE(case1, shape, fill_value );
    FULL_SUBCASE(case1, shape_a, fill_value );
    // TODO: fix
    // FULL_SUBCASE(case1, shape_f, fill_value );
    FULL_SUBCASE(case1, shape_h, fill_value );
    // FULL_SUBCASE(case1, shape_d, fill_value );
    FULL_SUBCASE(case1, shape_ct, fill_value );
}

// TODO: remove
#if 0
TEST_CASE("full_traits(case1)" * doctest::test_suite("array::full_traits"))
{
    {
        using shape_t = int[3];
        shape_t shape = {2,3,2};
        auto fill_value = 1;
        auto array = nm::array::full(shape,fill_value);
        using array_t = decltype(array);
        constexpr auto is_fixed_shape = nm::meta::is_fixed_size_ndarray_v<array_t>;
        static_assert( !is_fixed_shape );
    }
    {
        using namespace nm::literals;
        auto shape = std::tuple{2_ct,3_ct,2_ct};
        auto fill_value = 1;
        auto array = nm::array::full(shape,fill_value);
        using array_t = decltype(array);
        constexpr auto is_fixed_shape = nm::meta::is_fixed_size_ndarray_v<array_t>;
        static_assert( is_fixed_shape );
    }
}
#endif