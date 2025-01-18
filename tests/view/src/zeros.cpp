#include "nmtools/array/zeros.hpp"
#include "nmtools/testing/data/array/zeros.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

#define RUN_zeros_impl(...) \
nm::view::zeros(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs zeros fn to callable lambda
#define RUN_zeros(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("zeros-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_zeros_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_zeros(case_name, ...) \
RUN_zeros_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ZEROS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, zeros, case_name); \
    using namespace args; \
    auto result = RUN_zeros(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("zeros(case1)" * doctest::test_suite("view::zeros"))
{
    ZEROS_SUBCASE(case1, shape, dtype );
    ZEROS_SUBCASE(case1, shape_a, dtype );
    ZEROS_SUBCASE(case1, shape_v, dtype );
    // ZEROS_SUBCASE(case1, shape_f, dtype );
    ZEROS_SUBCASE(case1, shape_h, dtype );
    // ZEROS_SUBCASE(case1, shape_d, dtype );
    ZEROS_SUBCASE(case1, shape_ct, dtype );
}

// TODO: remove
#if 0
TEST_CASE("zeros_traits(case1)" * doctest::test_suite("view::zeros_traits"))
{
    {
        using shape_t = int[3];
        shape_t shape = {2,3,2};
        auto array = nm::view::zeros(shape,nm::float32);
        using array_t = decltype(array);
        constexpr auto is_fixed_shape = nm::meta::is_fixed_size_ndarray_v<array_t>;
        static_assert( !is_fixed_shape );
    }
    {
        using namespace nm::literals;
        auto shape = std::tuple{2_ct,3_ct,2_ct};
        auto array = nm::view::zeros(shape,nm::float32);
        using array_t = decltype(array);
        constexpr auto is_fixed_shape = nm::meta::is_fixed_size_ndarray_v<array_t>;
        static_assert( is_fixed_shape );
    }
}
#endif