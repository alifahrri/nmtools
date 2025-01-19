#include "nmtools/array/ufuncs/logical_and.hpp"
#include "nmtools/testing/data/array/logical_and.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define LOGICAL_AND_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, logical_and, case_name); \
    using namespace args; \
    auto result = view::logical_and(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("logical_and(case1)" * doctest::test_suite("view::logical_and"))
{
    LOGICAL_AND_SUBCASE( case1,   a,   b );
    LOGICAL_AND_SUBCASE( case1, a_a, b_a );
    LOGICAL_AND_SUBCASE( case1, a_f, b_f );
    LOGICAL_AND_SUBCASE( case1, a_d, b_d );
    LOGICAL_AND_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("logical_and(case2)" * doctest::test_suite("view::logical_and"))
{
    LOGICAL_AND_SUBCASE( case2,   a, b );
    LOGICAL_AND_SUBCASE( case2, a_a, b );
    LOGICAL_AND_SUBCASE( case2, a_f, b );
    LOGICAL_AND_SUBCASE( case2, a_d, b );
    LOGICAL_AND_SUBCASE( case2, a_h, b );
}

#define REDUCE_LOGICAL_AND_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, reduce_logical_and, case_name); \
    using namespace args; \
    auto result = view::reduce_logical_and(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_logical_and(case1)" * doctest::test_suite("view::reduce_logical_and"))
{
    REDUCE_LOGICAL_AND_SUBCASE( case1,   a, axis );
    REDUCE_LOGICAL_AND_SUBCASE( case1, a_a, axis );
    REDUCE_LOGICAL_AND_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_LOGICAL_AND_SUBCASE( case1, a_d, axis );
    REDUCE_LOGICAL_AND_SUBCASE( case1, a_f, axis );
}

TEST_CASE("reduce_logical_and(case2)" * doctest::test_suite("view::reduce_logical_and"))
{
    REDUCE_LOGICAL_AND_SUBCASE( case2,   a, axis );
    REDUCE_LOGICAL_AND_SUBCASE( case2, a_a, axis );
    REDUCE_LOGICAL_AND_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_LOGICAL_AND_SUBCASE( case2, a_d, axis );
    REDUCE_LOGICAL_AND_SUBCASE( case2, a_f, axis );
}

TEST_CASE("reduce_logical_and(case3)" * doctest::test_suite("view::reduce_logical_and"))
{
    REDUCE_LOGICAL_AND_SUBCASE( case3,   a, axis );
    REDUCE_LOGICAL_AND_SUBCASE( case3, a_a, axis );
    REDUCE_LOGICAL_AND_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_LOGICAL_AND_SUBCASE( case3, a_d, axis );
    REDUCE_LOGICAL_AND_SUBCASE( case3, a_f, axis );
}

TEST_CASE("reduce_logical_and(case4)" * doctest::test_suite("view::reduce_logical_and"))
{
    REDUCE_LOGICAL_AND_SUBCASE( case4,   a, axis );
    REDUCE_LOGICAL_AND_SUBCASE( case4, a_a, axis );
    REDUCE_LOGICAL_AND_SUBCASE( case4, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_LOGICAL_AND_SUBCASE( case4, a_d, axis );
    REDUCE_LOGICAL_AND_SUBCASE( case4, a_f, axis );
}

TEST_CASE("reduce_logical_and(case5)" * doctest::test_suite("view::reduce_logical_and"))
{
    REDUCE_LOGICAL_AND_SUBCASE( case5,   a, axis );
    REDUCE_LOGICAL_AND_SUBCASE( case5, a_a, axis );
    REDUCE_LOGICAL_AND_SUBCASE( case5, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_LOGICAL_AND_SUBCASE( case5, a_d, axis );
    REDUCE_LOGICAL_AND_SUBCASE( case5, a_f, axis );
}

TEST_CASE("reduce_logical_and(case6)" * doctest::test_suite("view::reduce_logical_and"))
{
    REDUCE_LOGICAL_AND_SUBCASE( case6,   a, axis );
    REDUCE_LOGICAL_AND_SUBCASE( case6, a_a, axis );
    REDUCE_LOGICAL_AND_SUBCASE( case6, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_LOGICAL_AND_SUBCASE( case6, a_d, axis );
    REDUCE_LOGICAL_AND_SUBCASE( case6, a_f, axis );
}