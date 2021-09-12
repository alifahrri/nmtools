#include "nmtools/array/view/matmul.hpp"
#include "nmtools/testing/data/array/matmul.hpp"
#include "nmtools/testing/doctest.hpp"

#define RUN_split_impl(...) \
nmtools::view::detail::split(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs split fn to callable lambda
#define RUN_split(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("split-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_split_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_split(case_name, ...) \
RUN_split_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SPLIT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, split, case_name); \
    using namespace args; \
    auto result = RUN_split(case_name, __VA_ARGS__); \
    auto lhs = std::get<0>(result); \
    auto rhs = std::get<1>(result); \
    NMTOOLS_ASSERT_EQUAL( lhs, expect::lhs ); \
    NMTOOLS_ASSERT_EQUAL( rhs, expect::rhs ); \
}

TEST_CASE("split(case1)" * doctest::test_suite("view::detail::split"))
{
    SPLIT_SUBCASE( case1, shape, N );
    SPLIT_SUBCASE( case1, shape_a, N );
    SPLIT_SUBCASE( case1, shape_v, N );
    SPLIT_SUBCASE( case1, shape_f, N );
    SPLIT_SUBCASE( case1, shape_h, N );
}

TEST_CASE("split(case2)" * doctest::test_suite("view::detail::split"))
{
    SPLIT_SUBCASE( case2, shape, N );
    SPLIT_SUBCASE( case2, shape_a, N );
    SPLIT_SUBCASE( case2, shape_v, N );
    SPLIT_SUBCASE( case2, shape_f, N );
    SPLIT_SUBCASE( case2, shape_h, N );
}

TEST_CASE("split(case3)" * doctest::test_suite("view::detail::split"))
{
    SPLIT_SUBCASE( case3, shape, N );
    SPLIT_SUBCASE( case3, shape_a, N );
    SPLIT_SUBCASE( case3, shape_v, N );
    SPLIT_SUBCASE( case3, shape_f, N );
    SPLIT_SUBCASE( case3, shape_h, N );
}

TEST_CASE("split(case4)" * doctest::test_suite("view::detail::split"))
{
    SPLIT_SUBCASE( case4, shape, N );
    SPLIT_SUBCASE( case4, shape_a, N );
    SPLIT_SUBCASE( case4, shape_v, N );
    SPLIT_SUBCASE( case4, shape_f, N );
    SPLIT_SUBCASE( case4, shape_h, N );
}

TEST_CASE("split(case5)" * doctest::test_suite("view::detail::split"))
{
    SPLIT_SUBCASE( case5, shape, N );
    SPLIT_SUBCASE( case5, shape_a, N );
    SPLIT_SUBCASE( case5, shape_v, N );
    SPLIT_SUBCASE( case5, shape_f, N );
    SPLIT_SUBCASE( case5, shape_h, N );
}

TEST_CASE("split(case6)" * doctest::test_suite("view::detail::split"))
{
    SPLIT_SUBCASE( case6, shape, N );
    SPLIT_SUBCASE( case6, shape_a, N );
    SPLIT_SUBCASE( case6, shape_v, N );
    SPLIT_SUBCASE( case6, shape_f, N );
    SPLIT_SUBCASE( case6, shape_h, N );
}

#define RUN_shape_matmul_impl(...) \
nmtools::view::detail::shape_matmul(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs shape_matmul fn to callable lambda
#define RUN_shape_matmul(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("shape_matmul-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_shape_matmul_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_shape_matmul(case_name, ...) \
RUN_shape_matmul_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SHAPE_MATMUL_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, shape_matmul, case_name); \
    using namespace args; \
    auto result = RUN_shape_matmul(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("shape_matmul(case1)" * doctest::test_suite("view::detail::shape_matmul"))
{
    SHAPE_MATMUL_SUBCASE( case1, lshape, rshape );
    SHAPE_MATMUL_SUBCASE( case1, lshape_a, rshape_a );
    SHAPE_MATMUL_SUBCASE( case1, lshape_v, rshape_v );
    SHAPE_MATMUL_SUBCASE( case1, lshape_f, rshape_f );
    SHAPE_MATMUL_SUBCASE( case1, lshape_h, rshape_h );
    // SHAPE_MATMUL_SUBCASE( case1, lshape_d, rshape_d );
}

TEST_CASE("shape_matmul(case2)" * doctest::test_suite("view::detail::shape_matmul"))
{
    SHAPE_MATMUL_SUBCASE( case2, lshape, rshape );
    SHAPE_MATMUL_SUBCASE( case2, lshape_a, rshape_a );
    SHAPE_MATMUL_SUBCASE( case2, lshape_v, rshape_v );
    SHAPE_MATMUL_SUBCASE( case2, lshape_f, rshape_f );
    SHAPE_MATMUL_SUBCASE( case2, lshape_h, rshape_h );
    // SHAPE_MATMUL_SUBCASE( case2, lshape_d, rshape_d );
}

TEST_CASE("shape_matmul(case3)" * doctest::test_suite("view::detail::shape_matmul"))
{
    SHAPE_MATMUL_SUBCASE( case3, lshape, rshape );
    SHAPE_MATMUL_SUBCASE( case3, lshape_a, rshape_a );
    SHAPE_MATMUL_SUBCASE( case3, lshape_v, rshape_v );
    SHAPE_MATMUL_SUBCASE( case3, lshape_f, rshape_f );
    SHAPE_MATMUL_SUBCASE( case3, lshape_h, rshape_h );
    // SHAPE_MATMUL_SUBCASE( case3, lshape_d, rshape_d );
}

TEST_CASE("shape_matmul(case4)" * doctest::test_suite("view::detail::shape_matmul"))
{
    SHAPE_MATMUL_SUBCASE( case4, lshape, rshape );
    SHAPE_MATMUL_SUBCASE( case4, lshape_a, rshape_a );
    SHAPE_MATMUL_SUBCASE( case4, lshape_v, rshape_v );
    SHAPE_MATMUL_SUBCASE( case4, lshape_f, rshape_f );
    SHAPE_MATMUL_SUBCASE( case4, lshape_h, rshape_h );
    // SHAPE_MATMUL_SUBCASE( case4, lshape_d, rshape_d );
}

TEST_CASE("shape_matmul(case5)" * doctest::test_suite("view::detail::shape_matmul"))
{
    SHAPE_MATMUL_SUBCASE( case5, lshape, rshape );
    SHAPE_MATMUL_SUBCASE( case5, lshape_a, rshape_a );
    SHAPE_MATMUL_SUBCASE( case5, lshape_v, rshape_v );
    SHAPE_MATMUL_SUBCASE( case5, lshape_f, rshape_f );
    SHAPE_MATMUL_SUBCASE( case5, lshape_h, rshape_h );
    // SHAPE_MATMUL_SUBCASE( case5, lshape_d, rshape_d );
}

TEST_CASE("shape_matmul(case6)" * doctest::test_suite("view::detail::shape_matmul"))
{
    SHAPE_MATMUL_SUBCASE( case6, lshape, rshape );
    SHAPE_MATMUL_SUBCASE( case6, lshape_a, rshape_a );
    SHAPE_MATMUL_SUBCASE( case6, lshape_v, rshape_v );
    SHAPE_MATMUL_SUBCASE( case6, lshape_f, rshape_f );
    SHAPE_MATMUL_SUBCASE( case6, lshape_h, rshape_h );
    // SHAPE_MATMUL_SUBCASE( case6, lshape_d, rshape_d );
}

TEST_CASE("shape_matmul(case7)" * doctest::test_suite("view::detail::shape_matmul"))
{
    SHAPE_MATMUL_SUBCASE( case7, lshape, rshape );
    SHAPE_MATMUL_SUBCASE( case7, lshape_a, rshape_a );
    SHAPE_MATMUL_SUBCASE( case7, lshape_v, rshape_v );
    SHAPE_MATMUL_SUBCASE( case7, lshape_f, rshape_f );
    SHAPE_MATMUL_SUBCASE( case7, lshape_h, rshape_h );
    // SHAPE_MATMUL_SUBCASE( case7, lshape_d, rshape_d );
}

TEST_CASE("shape_matmul(case8)" * doctest::test_suite("view::detail::shape_matmul"))
{
    SHAPE_MATMUL_SUBCASE( case8, lshape, rshape );
    SHAPE_MATMUL_SUBCASE( case8, lshape_a, rshape_a );
    SHAPE_MATMUL_SUBCASE( case8, lshape_v, rshape_v );
    SHAPE_MATMUL_SUBCASE( case8, lshape_f, rshape_f );
    SHAPE_MATMUL_SUBCASE( case8, lshape_h, rshape_h );
    // SHAPE_MATMUL_SUBCASE( case8, lshape_d, rshape_d );
}

TEST_CASE("shape_matmul(case9)" * doctest::test_suite("view::detail::shape_matmul"))
{
    SHAPE_MATMUL_SUBCASE( case9, lshape, rshape );
    SHAPE_MATMUL_SUBCASE( case9, lshape_a, rshape_a );
    SHAPE_MATMUL_SUBCASE( case9, lshape_v, rshape_v );
    SHAPE_MATMUL_SUBCASE( case9, lshape_f, rshape_f );
    SHAPE_MATMUL_SUBCASE( case9, lshape_h, rshape_h );
    // SHAPE_MATMUL_SUBCASE( case9, lshape_d, rshape_d );
}

#define RUN_index_matmul_impl(...) \
nmtools::view::detail::matmul(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs matmul fn to callable lambda
#define RUN_index_matmul(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("index-matmul-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_index_matmul_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_index_matmul(case_name, ...) \
RUN_matmul_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define INDEX_MATMUL_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(index, matmul, case_name); \
    using namespace args; \
    auto result = RUN_index_matmul(case_name, __VA_ARGS__); \
    auto left   = std::get<0>(result); \
    auto right  = std::get<1>(result); \
    NMTOOLS_ASSERT_EQUAL( left, expect::left ); \
    NMTOOLS_ASSERT_EQUAL( right, expect::right ); \
}

TEST_CASE("matmul(case1)" * doctest::test_suite("view::detail::matmul"))
{
    INDEX_MATMUL_SUBCASE(case1, indices, lshape, rshape, shape);
    INDEX_MATMUL_SUBCASE(case1, indices_a, lshape_a, rshape_a, shape_a);
    INDEX_MATMUL_SUBCASE(case1, indices_f, lshape_f, rshape_f, shape_f);
    INDEX_MATMUL_SUBCASE(case1, indices_h, lshape_h, rshape_h, shape_h);
    INDEX_MATMUL_SUBCASE(case1, indices_v, lshape_v, rshape_v, shape_v);
}

TEST_CASE("matmul(case2)" * doctest::test_suite("view::detail::matmul"))
{
    INDEX_MATMUL_SUBCASE(case2, indices, lshape, rshape, shape);
    INDEX_MATMUL_SUBCASE(case2, indices_a, lshape_a, rshape_a, shape_a);
    INDEX_MATMUL_SUBCASE(case2, indices_f, lshape_f, rshape_f, shape_f);
    INDEX_MATMUL_SUBCASE(case2, indices_h, lshape_h, rshape_h, shape_h);
    INDEX_MATMUL_SUBCASE(case2, indices_v, lshape_v, rshape_v, shape_v);
}

TEST_CASE("matmul(case3)" * doctest::test_suite("view::detail::matmul"))
{
    INDEX_MATMUL_SUBCASE(case3, indices, lshape, rshape, shape);
    INDEX_MATMUL_SUBCASE(case3, indices_a, lshape_a, rshape_a, shape_a);
    INDEX_MATMUL_SUBCASE(case3, indices_f, lshape_f, rshape_f, shape_f);
    // NOT supported yet, calculating indices for slicing requires fixed index array
    // TODO: suppor index matmul with dynamic index array
    // INDEX_MATMUL_SUBCASE(case3, indices_h, lshape_h, rshape_h, shape_h);
    // INDEX_MATMUL_SUBCASE(case3, indices_v, lshape_v, rshape_v, shape_v);
}

TEST_CASE("matmul(case4)" * doctest::test_suite("view::detail::matmul"))
{
    INDEX_MATMUL_SUBCASE(case4, indices, lshape, rshape, shape);
    INDEX_MATMUL_SUBCASE(case4, indices_a, lshape_a, rshape_a, shape_a);
    INDEX_MATMUL_SUBCASE(case4, indices_f, lshape_f, rshape_f, shape_f);
    // NOT supported yet, calculating indices for slicing requires fixed index array
    // TODO: suppor index matmul with dynamic index array
    // INDEX_MATMUL_SUBCASE(case4, indices_h, lshape_h, rshape_h, shape_h);
    // INDEX_MATMUL_SUBCASE(case4, indices_v, lshape_v, rshape_v, shape_v);
}

TEST_CASE("matmul(case5)" * doctest::test_suite("view::detail::matmul"))
{
    INDEX_MATMUL_SUBCASE(case5, indices, lshape, rshape, shape);
    INDEX_MATMUL_SUBCASE(case5, indices_a, lshape_a, rshape_a, shape_a);
    INDEX_MATMUL_SUBCASE(case5, indices_f, lshape_f, rshape_f, shape_f);
    // NOT supported yet, calculating indices for slicing requires fixed index array
    // TODO: suppor index matmul with dynamic index array
    // INDEX_MATMUL_SUBCASE(case5, indices_h, lshape_h, rshape_h, shape_h);
    // INDEX_MATMUL_SUBCASE(case5, indices_v, lshape_v, rshape_v, shape_v);
}

#define RUN_matmul_impl(...) \
nmtools::view::matmul(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs matmul fn to callable lambda
#define RUN_matmul(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("matmul-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_matmul_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_matmul(case_name, ...) \
RUN_matmul_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define MATMUL_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, matmul, case_name); \
    using namespace args; \
    auto result = RUN_matmul(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("matmul(case1)" * doctest::test_suite("view::matmul"))
{
    MATMUL_SUBCASE( case1, lhs, rhs );
    MATMUL_SUBCASE( case1, lhs_a, rhs_a );
    MATMUL_SUBCASE( case1, lhs_f, rhs_f );
    MATMUL_SUBCASE( case1, lhs_h, rhs_h );
    // TODO: support slice for dynamic ndarray
    // MATMUL_SUBCASE( case1, lhs_d, rhs_d );
}

TEST_CASE("matmul(case2)" * doctest::test_suite("view::matmul"))
{
    MATMUL_SUBCASE( case2, lhs, rhs );
    MATMUL_SUBCASE( case2, lhs_a, rhs_a );
    MATMUL_SUBCASE( case2, lhs_f, rhs_f );
    MATMUL_SUBCASE( case2, lhs_h, rhs_h );
    // TODO: support slice for dynamic ndarray
    // MATMUL_SUBCASE( case2, lhs_d, rhs_d );
}

TEST_CASE("matmul(case3)" * doctest::test_suite("view::matmul"))
{
    MATMUL_SUBCASE( case3, lhs, rhs );
    MATMUL_SUBCASE( case3, lhs_a, rhs_a );
    MATMUL_SUBCASE( case3, lhs_f, rhs_f );
    MATMUL_SUBCASE( case3, lhs_h, rhs_h );
    // TODO: support slice for dynamic ndarray
    // MATMUL_SUBCASE( case3, lhs_d, rhs_d );
}

TEST_CASE("matmul(case4)" * doctest::test_suite("view::matmul"))
{
    MATMUL_SUBCASE( case4, lhs, rhs );
    MATMUL_SUBCASE( case4, lhs_a, rhs_a );
    MATMUL_SUBCASE( case4, lhs_f, rhs_f );
    MATMUL_SUBCASE( case4, lhs_h, rhs_h );
    // TODO: support slice for dynamic ndarray
    // MATMUL_SUBCASE( case4, lhs_d, rhs_d );
}

TEST_CASE("matmul(case5)" * doctest::test_suite("view::matmul"))
{
    MATMUL_SUBCASE( case5, lhs, rhs );
    MATMUL_SUBCASE( case5, lhs_a, rhs_a );
    MATMUL_SUBCASE( case5, lhs_f, rhs_f );
    MATMUL_SUBCASE( case5, lhs_h, rhs_h );
    // TODO: support slice for dynamic ndarray
    // MATMUL_SUBCASE( case5, lhs_d, rhs_d );
}

TEST_CASE("matmul(case6)" * doctest::test_suite("view::matmul"))
{
    MATMUL_SUBCASE( case6, lhs, rhs );
    MATMUL_SUBCASE( case6, lhs_a, rhs_a );
    MATMUL_SUBCASE( case6, lhs_f, rhs_f );
    MATMUL_SUBCASE( case6, lhs_h, rhs_h );
    // TODO: support slice for dynamic ndarray
    // MATMUL_SUBCASE( case6, lhs_d, rhs_d );
}

TEST_CASE("matmul(view_at)" * doctest::test_suite("view::matmul"))
{
    {
        using namespace nmtools::testing::data::array::matmul::case1::args;
        auto result = nmtools::view::matmul(lhs,rhs);
        auto at00   = result.view_at(0,0);
        using at00_t = decltype(at00);
        using elem_t = nmtools::meta::get_element_type_t<at00_t>;
        static_assert( std::is_same_v<elem_t,int> );
        NMTOOLS_ASSERT_EQUAL(at00, 20);
    }
    {
        using namespace nmtools::testing::data::array::matmul::case3::args;
        auto result = nmtools::view::matmul(lhs,rhs);
        auto at000  = result.view_at(0,0,0);
        using at000_t = decltype(at000);
        using elem_t  = nmtools::meta::get_element_type_t<at000_t>;
        static_assert( std::is_same_v<elem_t,int> );
        NMTOOLS_ASSERT_EQUAL(at000, 20);
    }
}