#include "nmtools/array/eye.hpp"
#include "nmtools/evaluator/hip.hpp"
#include "nmtools/testing/data/array/eye.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools::array;
namespace fn = nmtools::functional;
namespace meta = nm::meta;
namespace view = nmtools::view;

using nmtools_array;

#define EYE_SUBCASE(case_name,...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array,eye,case_name); \
    using namespace args; \
    auto ctx = na::hip::default_context(); \
    auto view = nmtools::view::eye(__VA_ARGS__); \
    auto result = ctx->eval(view); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("eye(case1)" * doctest::test_suite("array::eye"))
{
    EYE_SUBCASE( case1, N );
}

TEST_CASE("eye(case2)" * doctest::test_suite("array::eye"))
{
    EYE_SUBCASE( case2, N, M );
}

TEST_CASE("eye(case3)" * doctest::test_suite("array::eye"))
{
    EYE_SUBCASE( case3, N, M );
}

TEST_CASE("eye(case4)" * doctest::test_suite("array::eye"))
{
    EYE_SUBCASE( case4, N, M, k );
}

TEST_CASE("eye(case5)" * doctest::test_suite("array::eye"))
{
    EYE_SUBCASE( case5, N, M, k, dtype );
}