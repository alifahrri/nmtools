#include "nmtools/array/view/broadcast_to.hpp"
#include "nmtools/testing/data/array/broadcast_to.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/constants.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define RUN_impl(...) \
nm::view::broadcast_to(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs broadcast_to fn to callable lambda
#define RUN_broadcast_to(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("broadcast_to-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_broadcast_to(case_name, ...) \
RUN_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define BROADCAST_TO_SUBCASE(case_name, array, shape, expected) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(broadcast_to, case_name); \
    auto array_ref = RUN_broadcast_to(case_name, args::array,args::shape); \
    NMTOOLS_ASSERT_EQUAL( array_ref.shape(), args::shape ); \
    NMTOOLS_ASSERT_CLOSE( array_ref, expect::expected ); \
}

TEST_CASE("broadcast_to(case1)" * doctest::test_suite("view::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case1, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case1, x_v, shape, expected );
    BROADCAST_TO_SUBCASE( case1, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case1, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case1, x_h, shape, expected );
}

TEST_CASE("broadcast_to(case2)" * doctest::test_suite("view::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case2, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case2, x_v, shape, expected );
    BROADCAST_TO_SUBCASE( case2, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case2, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case2, x_h, shape, expected );
}

TEST_CASE("broadcast_to(case3)" * doctest::test_suite("view::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case3, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case3, x_v, shape, expected );
    BROADCAST_TO_SUBCASE( case3, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case3, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case3, x_h, shape, expected );
}

TEST_CASE("broadcast_to(case4)" * doctest::test_suite("view::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case4, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case4, x_v, shape, expected );
    BROADCAST_TO_SUBCASE( case4, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case4, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case4, x_h, shape, expected );
}

TEST_CASE("broadcast_to(case5)" * doctest::test_suite("view::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case5, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case5, x_v, shape, expected );
    BROADCAST_TO_SUBCASE( case5, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case5, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case5, x_h, shape, expected );
}

TEST_CASE("broadcast_to(case6)" * doctest::test_suite("view::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case6, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case6, x_v, shape, expected );
    BROADCAST_TO_SUBCASE( case6, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case6, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case6, x_h, shape, expected );
}

TEST_CASE("broadcast_to(case7)" * doctest::test_suite("view::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case7, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case7, x_v, shape, expected );
    BROADCAST_TO_SUBCASE( case7, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case7, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case7, x_h, shape, expected );
}

TEST_CASE("broadcast_to(case8)" * doctest::test_suite("view::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case8, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case8, x_v, shape, expected );
    BROADCAST_TO_SUBCASE( case8, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case8, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case8, x_h, shape, expected );
}

TEST_CASE("broadcast_to(case9)" * doctest::test_suite("view::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case9, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case9, x_v, shape, expected );
    BROADCAST_TO_SUBCASE( case9, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case9, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case9, x_h, shape, expected );
}

TEST_CASE("broadcast_to(case10)" * doctest::test_suite("view::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case10, x, shape, expected );
}

TEST_CASE("broadcast_to(traits)"  * doctest::test_suite("view::broadcast_to"))
{
    using namespace nmtools::literals;
    namespace meta = nmtools::meta;
    SUBCASE("is_fixed_size_ndarray(1)")
    {
        int  x[3] = {1,2,3};
        auto shape = std::tuple{1_ct,2_ct,3_ct};
        auto broadcasted = view::broadcast_to(x,shape);
        using broadcasted_t = decltype(broadcasted);
        NMTOOLS_ASSERT_EQUAL( meta::is_fixed_size_ndarray_v<broadcasted_t>, true );
    }
    // this use assert
    // SUBCASE("is_fixed_size_ndarray(2)")
    // {
    //     int x[3] = {1,2,3};
    //     // cant do this here, will assert
    //     // auto shape = std::tuple{1_ct,3_ct,2_ct};
    //     auto shape = std::tuple{1,3,2};
    //     auto broadcasted = view::broadcast_to(x,shape);
    //     using broadcasted_t = decltype(broadcasted);
    //     NMTOOLS_ASSERT_EQUAL( meta::is_fixed_size_ndarray_v<broadcasted_t>, false );
    // }
}