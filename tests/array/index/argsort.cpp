#include "nmtools/testing/doctest.hpp"

NMTOOLS_TESTING_DECLARE_CASE(index, argsort)
{
    using namespace literals;
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int array[4] = {0,1,2,3};
        NMTOOLS_CAST_ARRAYS(array);
        inline auto array_ct = nmtools_tuple{0_ct,1_ct,2_ct,3_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[4] = {0,1,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int array[4] = {1,0,2,3};
        NMTOOLS_CAST_ARRAYS(array);
        inline auto array_ct = nmtools_tuple{1_ct,0_ct,2_ct,3_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[4] = {1,0,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int array[4] = {2,1,0,3};
        NMTOOLS_CAST_ARRAYS(array);
        inline auto array_ct = nmtools_tuple{2_ct,1_ct,0_ct,3_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[4] = {2,1,0,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int array[4] = {1,2,3,4};
        NMTOOLS_CAST_ARRAYS(array);
        inline auto array_ct = nmtools_tuple{1_ct,2_ct,3_ct,4_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[4] = {0,1,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int array[4] = {2,1,3,4};
        NMTOOLS_CAST_ARRAYS(array);
        inline auto array_ct = nmtools_tuple{2_ct,1_ct,3_ct,4_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[4] = {1,0,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int array[4] = {3,2,1,4};
        NMTOOLS_CAST_ARRAYS(array);
        inline auto array_ct = nmtools_tuple{3_ct,2_ct,1_ct,4_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result[4] = {2,1,0,3};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(index, constexpr_argsort)
{
    using namespace literals;
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline int array[4] = {0,1,2,3};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array);
        constexpr inline auto array_ct = nmtools_tuple{0_ct,1_ct,2_ct,3_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline int result[4] = {0,1,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline int array[4] = {1,0,2,3};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array);
        constexpr inline auto array_ct = nmtools_tuple{1_ct,0_ct,2_ct,3_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline int result[4] = {1,0,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline int array[4] = {2,1,0,3};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array);
        constexpr inline auto array_ct = nmtools_tuple{2_ct,1_ct,0_ct,3_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline int result[4] = {2,1,0,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline int array[4] = {1,2,3,4};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array);
        constexpr inline auto array_ct = nmtools_tuple{1_ct,2_ct,3_ct,4_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline int result[4] = {0,1,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        constexpr inline int array[4] = {2,1,3,4};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array);
        constexpr inline auto array_ct = nmtools_tuple{2_ct,1_ct,3_ct,4_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline int result[4] = {1,0,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        constexpr inline int array[4] = {3,2,1,4};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array);
        constexpr inline auto array_ct = nmtools_tuple{3_ct,2_ct,1_ct,4_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        constexpr inline int result[4] = {2,1,0,3};
    }
}

#include "nmtools/array/index/argsort.hpp"
#include "nmtools/testing/doctest.hpp"

#define RUN_impl(...) \
nmtools::index::argsort(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nmtools::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs argsort fn to callable lambda
#define RUN_argsort(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("index::argsort-") + #case_name; \
    auto name  = nmtools::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_argsort(case_name, ...) \
RUN_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ARGSORT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(index, argsort, case_name); \
    using namespace args; \
    auto result = RUN_argsort(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

#define CONSTEXPR_ARGSORT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(index, constexpr_argsort, case_name); \
    using namespace args; \
    constexpr auto result = RUN_impl(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("argsort(case1)" * doctest::test_suite("index::argsort"))
{
    ARGSORT_SUBCASE( case1, array );
    ARGSORT_SUBCASE( case1, array_a );
    ARGSORT_SUBCASE( case1, array_f );
    ARGSORT_SUBCASE( case1, array_h );
    ARGSORT_SUBCASE( case1, array_ct );
    #ifndef NMTOOLS_TESTING_DISABLE_DYNAMIC_ALLOCATION
    ARGSORT_SUBCASE( case1, array_v );
    #endif // NMTOOLS_TESTING_DISABLE_DYNAMIC_ALLOCATION
}

TEST_CASE("argsort(case2)" * doctest::test_suite("index::argsort"))
{
    ARGSORT_SUBCASE( case2, array );
    ARGSORT_SUBCASE( case2, array_a );
    #ifndef NMTOOLS_TESTING_DISABLE_DYNAMIC_ALLOCATION
    ARGSORT_SUBCASE( case2, array_v );
    #endif
    ARGSORT_SUBCASE( case2, array_f );
    ARGSORT_SUBCASE( case2, array_h );
    ARGSORT_SUBCASE( case2, array_ct );
}

TEST_CASE("argsort(case3)" * doctest::test_suite("index::argsort"))
{
    ARGSORT_SUBCASE( case3, array );
    ARGSORT_SUBCASE( case3, array_a );
    #ifndef NMTOOLS_TESTING_DISABLE_DYNAMIC_ALLOCATION
    ARGSORT_SUBCASE( case3, array_v );
    #endif
    ARGSORT_SUBCASE( case3, array_f );
    ARGSORT_SUBCASE( case3, array_h );
    ARGSORT_SUBCASE( case3, array_ct );
}

TEST_CASE("argsort(case4)" * doctest::test_suite("index::argsort"))
{
    ARGSORT_SUBCASE( case4, array );
    ARGSORT_SUBCASE( case4, array_a );
    #ifndef NMTOOLS_TESTING_DISABLE_DYNAMIC_ALLOCATION
    ARGSORT_SUBCASE( case4, array_v );
    #endif
    ARGSORT_SUBCASE( case4, array_f );
    ARGSORT_SUBCASE( case4, array_h );
    ARGSORT_SUBCASE( case4, array_ct );
}

TEST_CASE("argsort(case5)" * doctest::test_suite("index::argsort"))
{
    ARGSORT_SUBCASE( case5, array );
    ARGSORT_SUBCASE( case5, array_a );
    #ifndef NMTOOLS_TESTING_DISABLE_DYNAMIC_ALLOCATION
    ARGSORT_SUBCASE( case5, array_v );
    #endif
    ARGSORT_SUBCASE( case5, array_f );
    ARGSORT_SUBCASE( case5, array_h );
    ARGSORT_SUBCASE( case5, array_ct );
}

TEST_CASE("argsort(case6)" * doctest::test_suite("index::argsort"))
{
    ARGSORT_SUBCASE( case6, array );
    ARGSORT_SUBCASE( case6, array_a );
    #ifndef NMTOOLS_TESTING_DISABLE_DYNAMIC_ALLOCATION
    ARGSORT_SUBCASE( case6, array_v );
    #endif
    ARGSORT_SUBCASE( case6, array_f );
    ARGSORT_SUBCASE( case6, array_h );
    ARGSORT_SUBCASE( case6, array_ct );
}

TEST_CASE("argsort(case1)" * doctest::test_suite("index::constexpr_argsort"))
{
    // somehow doesn't work on clang 🤷, works fine on gcc
    // note: non-constexpr function 'operator()<int const (&)[3], const int &>' cannot be used in a constant expression
    // TODO: fix constexpr clang, seems like something to do with at customization point
    CONSTEXPR_ARGSORT_SUBCASE( case1, array );
    CONSTEXPR_ARGSORT_SUBCASE( case1, array_a );
    CONSTEXPR_ARGSORT_SUBCASE( case1, array_f );
    CONSTEXPR_ARGSORT_SUBCASE( case1, array_h );
    CONSTEXPR_ARGSORT_SUBCASE( case1, array_ct );
}

TEST_CASE("argsort(case2)" * doctest::test_suite("index::constexpr_argsort"))
{
    CONSTEXPR_ARGSORT_SUBCASE( case2, array );
    CONSTEXPR_ARGSORT_SUBCASE( case2, array_a );
    CONSTEXPR_ARGSORT_SUBCASE( case2, array_f );
    CONSTEXPR_ARGSORT_SUBCASE( case2, array_h );
    CONSTEXPR_ARGSORT_SUBCASE( case2, array_ct );
}

TEST_CASE("argsort(case3)" * doctest::test_suite("index::constexpr_argsort"))
{
    CONSTEXPR_ARGSORT_SUBCASE( case3, array );
    CONSTEXPR_ARGSORT_SUBCASE( case3, array_a );
    CONSTEXPR_ARGSORT_SUBCASE( case3, array_f );
    CONSTEXPR_ARGSORT_SUBCASE( case3, array_h );
    CONSTEXPR_ARGSORT_SUBCASE( case3, array_ct );
}

TEST_CASE("argsort(case4)" * doctest::test_suite("index::constexpr_argsort"))
{
    #ifndef __clang__
    CONSTEXPR_ARGSORT_SUBCASE( case4, array );
    CONSTEXPR_ARGSORT_SUBCASE( case4, array_a );
    CONSTEXPR_ARGSORT_SUBCASE( case4, array_f );
    CONSTEXPR_ARGSORT_SUBCASE( case4, array_h );
    CONSTEXPR_ARGSORT_SUBCASE( case4, array_ct );
    #endif // __clang__
}

TEST_CASE("argsort(case5)" * doctest::test_suite("index::constexpr_argsort"))
{
    #ifndef __clang__
    CONSTEXPR_ARGSORT_SUBCASE( case5, array );
    CONSTEXPR_ARGSORT_SUBCASE( case5, array_a );
    CONSTEXPR_ARGSORT_SUBCASE( case5, array_f );
    CONSTEXPR_ARGSORT_SUBCASE( case5, array_h );
    CONSTEXPR_ARGSORT_SUBCASE( case5, array_ct );
    #endif // __clang__
}

TEST_CASE("argsort(case6)" * doctest::test_suite("index::constexpr_argsort"))
{
    #ifndef __clang__
    CONSTEXPR_ARGSORT_SUBCASE( case6, array );
    CONSTEXPR_ARGSORT_SUBCASE( case6, array_a );
    CONSTEXPR_ARGSORT_SUBCASE( case6, array_f );
    CONSTEXPR_ARGSORT_SUBCASE( case6, array_h );
    CONSTEXPR_ARGSORT_SUBCASE( case6, array_ct );
    #endif // __clang__
}