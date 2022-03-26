#include "nmtools/array/view/atleast_3d.hpp"
#include "nmtools/testing/data/array/atleast_3d.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

#define RUN_atleast_3d_impl(...) \
nm::view::atleast_3d(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs atleast_3d fn to callable lambda
#define RUN_atleast_3d(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("atleast_3d-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_atleast_3d_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_atleast_3d(case_name, ...) \
RUN_atleast_3d_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ATLEAST_3D_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, atleast_3d, case_name); \
    using namespace args; \
    auto result = RUN_atleast_3d(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.dim(), expect::dim ); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("atleast_3d(case1)" * doctest::test_suite("view::atleast_3d"))
{
    ATLEAST_3D_SUBCASE( case1, a );
}

TEST_CASE("atleast_3d(case2)" * doctest::test_suite("view::atleast_3d"))
{
    ATLEAST_3D_SUBCASE( case2, a );
    ATLEAST_3D_SUBCASE( case2, a_a );
    ATLEAST_3D_SUBCASE( case2, a_v );
    ATLEAST_3D_SUBCASE( case2, a_f );
    ATLEAST_3D_SUBCASE( case2, a_d );
    ATLEAST_3D_SUBCASE( case2, a_h );
}

TEST_CASE("atleast_3d(case3)" * doctest::test_suite("view::atleast_3d"))
{
    ATLEAST_3D_SUBCASE( case3, a );
    ATLEAST_3D_SUBCASE( case3, a_a );
    ATLEAST_3D_SUBCASE( case3, a_v );
    ATLEAST_3D_SUBCASE( case3, a_f );
    ATLEAST_3D_SUBCASE( case3, a_d );
    ATLEAST_3D_SUBCASE( case3, a_h );
}

TEST_CASE("atleast_3d(case4)" * doctest::test_suite("view::atleast_3d"))
{
    ATLEAST_3D_SUBCASE( case4, a );
    ATLEAST_3D_SUBCASE( case4, a_a );
    ATLEAST_3D_SUBCASE( case4, a_v );
    ATLEAST_3D_SUBCASE( case4, a_f );
    ATLEAST_3D_SUBCASE( case4, a_d );
    ATLEAST_3D_SUBCASE( case4, a_h );
}

TEST_CASE("atleast_3d(case5)" * doctest::test_suite("view::atleast_3d"))
{
    ATLEAST_3D_SUBCASE( case5, a );
    ATLEAST_3D_SUBCASE( case5, a_a );
    ATLEAST_3D_SUBCASE( case5, a_v );
    ATLEAST_3D_SUBCASE( case5, a_f );
    ATLEAST_3D_SUBCASE( case5, a_d );
    ATLEAST_3D_SUBCASE( case5, a_h );
}

namespace view = nm::view;
namespace meta = nm::meta;

TEST_CASE("atleast_3d(traits)" * doctest::test_suite("view::atleast_3d"))
{
    SUBCASE("fixed_ndarray(int)")
    {
        int a = 1;
        auto array = view::atleast_3d(a);
        using array_t = decltype(array);
        constexpr auto is_fixed = meta::is_fixed_size_ndarray_v<array_t>;
        NMTOOLS_STATIC_ASSERT_EQUAL( is_fixed, true );
    }
    SUBCASE("!fixed_ndarray(std::vector)")
    {
        auto a = std::vector{1};
        auto array = view::atleast_3d(a);
        using array_t = decltype(array);
        constexpr auto is_fixed = meta::is_fixed_size_ndarray_v<array_t>;
        NMTOOLS_STATIC_ASSERT_EQUAL( is_fixed, false );
    }
}