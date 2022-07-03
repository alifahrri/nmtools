#include "nmtools/array/array/ones.hpp"
#include "nmtools/testing/data/array/ones.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

#define RUN_ones_impl(...) \
nm::array::ones(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs ones fn to callable lambda
#define RUN_ones(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("ones-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_ones_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_ones(case_name, ...) \
RUN_ones_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ONES_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, ones, case_name); \
    using namespace args; \
    auto result = RUN_ones(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("ones(case1)" * doctest::test_suite("array::ones"))
{
    ONES_SUBCASE(case1, shape, dtype );
    ONES_SUBCASE(case1, shape_a, dtype );
    ONES_SUBCASE(case1, shape_v, dtype );
    // ONES_SUBCASE(case1, shape_f, dtype );
    ONES_SUBCASE(case1, shape_h, dtype );
    // ONES_SUBCASE(case1, shape_d, dtype );
    ONES_SUBCASE(case1, shape_ct, dtype );
}

// TODO: remove
#if 0
TEST_CASE("ones_traits(case1)" * doctest::test_suite("array::ones_traits"))
{
    {
        using shape_t = int[3];
        shape_t shape = {2,3,2};
        auto array = nm::array::ones(shape,nm::float32);
        using array_t = decltype(array);
        constexpr auto is_fixed_shape = nm::meta::is_fixed_size_ndarray_v<array_t>;
        static_assert( !is_fixed_shape );
    }
    {
        using namespace nm::literals;
        auto shape = std::tuple{2_ct,3_ct,2_ct};
        auto array = nm::array::ones(shape,nm::float32);
        using array_t = decltype(array);
        constexpr auto is_fixed_shape = nm::meta::is_fixed_size_ndarray_v<array_t>;
        static_assert( is_fixed_shape );
    }
}
#endif