#include "nmtools/array/zeros_like.hpp"
#include "nmtools/evaluator/hip.hpp"
#include "nmtools/testing/data/array/zeros_like.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace view = nm::view;
namespace meta = nm::meta;

#define ZEROS_LIKE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( array, zeros_like, case_name ); \
    using namespace args; \
    auto view = nmtools::view::zeros_like(__VA_ARGS__); \
    auto ctx = na::hip::default_context(); \
    auto result = ctx->eval(view); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("zeros_like(case1)" * doctest::test_suite("array::zeros_like"))
{
    ZEROS_LIKE_SUBCASE( case1, a );
    ZEROS_LIKE_SUBCASE( case1, a_a );
    ZEROS_LIKE_SUBCASE( case1, a_f );
    ZEROS_LIKE_SUBCASE( case1, a_h );
    ZEROS_LIKE_SUBCASE( case1, a_d );
}

TEST_CASE("zeros_like(case2)" * doctest::test_suite("array::zeros_like"))
{
    ZEROS_LIKE_SUBCASE( case2, a );
    ZEROS_LIKE_SUBCASE( case2, a_a );
    ZEROS_LIKE_SUBCASE( case2, a_f );
    ZEROS_LIKE_SUBCASE( case2, a_h );
    ZEROS_LIKE_SUBCASE( case2, a_d );
}

TEST_CASE("zeros_like(case3)" * doctest::test_suite("array::zeros_like"))
{
    ZEROS_LIKE_SUBCASE( case3, a, dtype );
    ZEROS_LIKE_SUBCASE( case3, a_a, dtype );
    ZEROS_LIKE_SUBCASE( case3, a_f, dtype );
    ZEROS_LIKE_SUBCASE( case3, a_h, dtype );
    ZEROS_LIKE_SUBCASE( case3, a_d, dtype );
}