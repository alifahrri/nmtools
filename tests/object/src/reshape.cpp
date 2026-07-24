#include "nmtools/array/reshape.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/data/array/reshape.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace meta = nm::meta;

#define OBJECT_RESHAPE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(reshape, case_name) \
    using namespace args; \
    auto object = nmtools::array(__VA_ARGS__); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(object) ); \
    auto result = object.reshape(newshape); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

#define RESHAPE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(reshape, case_name) \
    using namespace args; \
    auto result = nmtools::reshape(__VA_ARGS__, nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

TEST_CASE("reshape(case1)" * doctest::test_suite("array::reshape"))
{
    RESHAPE_SUBCASE(case1,   array, newshape );
    RESHAPE_SUBCASE(case1, array_a, newshape_a );
    RESHAPE_SUBCASE(case1, array_f, newshape_a );
    RESHAPE_SUBCASE(case1, array_d, newshape_v );
    RESHAPE_SUBCASE(case1, array_h, newshape_h );

    RESHAPE_SUBCASE(case1,   array, newshape_ct );
    RESHAPE_SUBCASE(case1, array_a, newshape_ct );
    RESHAPE_SUBCASE(case1, array_f, newshape_ct );
    RESHAPE_SUBCASE(case1, array_d, newshape_ct );
    RESHAPE_SUBCASE(case1, array_h, newshape_ct );

    OBJECT_RESHAPE_SUBCASE(case1,   array, nmtools::Object );
    OBJECT_RESHAPE_SUBCASE(case1, array_a, nmtools::Object );
    OBJECT_RESHAPE_SUBCASE(case1, array_f, nmtools::Object );
    OBJECT_RESHAPE_SUBCASE(case1, array_d, nmtools::Object );
    OBJECT_RESHAPE_SUBCASE(case1, array_h, nmtools::Object );
}

TEST_CASE("reshape(case2)" * doctest::test_suite("array::reshape"))
{
    RESHAPE_SUBCASE(case2,   array, newshape );
    RESHAPE_SUBCASE(case2, array_a, newshape_a );
    RESHAPE_SUBCASE(case2, array_f, newshape_a );
    RESHAPE_SUBCASE(case2, array_d, newshape_v );
    RESHAPE_SUBCASE(case2, array_h, newshape_h );

    RESHAPE_SUBCASE(case2,   array, newshape_ct );
    RESHAPE_SUBCASE(case2, array_a, newshape_ct );
    RESHAPE_SUBCASE(case2, array_f, newshape_ct );
    RESHAPE_SUBCASE(case2, array_d, newshape_ct );
    RESHAPE_SUBCASE(case2, array_h, newshape_ct );

    OBJECT_RESHAPE_SUBCASE(case2,   array, nmtools::Object );
    OBJECT_RESHAPE_SUBCASE(case2, array_a, nmtools::Object );
    OBJECT_RESHAPE_SUBCASE(case2, array_f, nmtools::Object );
    OBJECT_RESHAPE_SUBCASE(case2, array_d, nmtools::Object );
    OBJECT_RESHAPE_SUBCASE(case2, array_h, nmtools::Object );
}

TEST_CASE("reshape(case3)" * doctest::test_suite("array::reshape"))
{
    RESHAPE_SUBCASE(case3,   array, newshape );
    RESHAPE_SUBCASE(case3, array_a, newshape_a );
    RESHAPE_SUBCASE(case3, array_f, newshape_a );
    RESHAPE_SUBCASE(case3, array_d, newshape_v );
    RESHAPE_SUBCASE(case3, array_h, newshape_h );

    OBJECT_RESHAPE_SUBCASE(case3,   array, nmtools::Object );
    OBJECT_RESHAPE_SUBCASE(case3, array_a, nmtools::Object );
    OBJECT_RESHAPE_SUBCASE(case3, array_f, nmtools::Object );
    OBJECT_RESHAPE_SUBCASE(case3, array_d, nmtools::Object );
    OBJECT_RESHAPE_SUBCASE(case3, array_h, nmtools::Object );
}

TEST_CASE("reshape(case4)" * doctest::test_suite("array::reshape"))
{
    RESHAPE_SUBCASE(case4,   array, newshape );
    RESHAPE_SUBCASE(case4, array_a, newshape_a );
    RESHAPE_SUBCASE(case4, array_f, newshape_a );
    RESHAPE_SUBCASE(case4, array_d, newshape_v );
    RESHAPE_SUBCASE(case4, array_h, newshape_h );

    RESHAPE_SUBCASE(case4,   array, newshape_ct );
    RESHAPE_SUBCASE(case4, array_a, newshape_ct );
    RESHAPE_SUBCASE(case4, array_f, newshape_ct );
    RESHAPE_SUBCASE(case4, array_d, newshape_ct );
    RESHAPE_SUBCASE(case4, array_h, newshape_ct );

    OBJECT_RESHAPE_SUBCASE(case4,   array, nmtools::Object );
    OBJECT_RESHAPE_SUBCASE(case4, array_a, nmtools::Object );
    OBJECT_RESHAPE_SUBCASE(case4, array_f, nmtools::Object );
    OBJECT_RESHAPE_SUBCASE(case4, array_d, nmtools::Object );
    OBJECT_RESHAPE_SUBCASE(case4, array_h, nmtools::Object );
}

TEST_CASE("reshape(case5)" * doctest::test_suite("array::reshape"))
{
    RESHAPE_SUBCASE(case5,   array, newshape );
    RESHAPE_SUBCASE(case5, array_a, newshape_a );
    RESHAPE_SUBCASE(case5, array_f, newshape_a );
    RESHAPE_SUBCASE(case5, array_d, newshape_v );
    RESHAPE_SUBCASE(case5, array_h, newshape_h );

    RESHAPE_SUBCASE(case5,   array, newshape_ct );
    RESHAPE_SUBCASE(case5, array_a, newshape_ct );
    RESHAPE_SUBCASE(case5, array_f, newshape_ct );
    RESHAPE_SUBCASE(case5, array_d, newshape_ct );
    RESHAPE_SUBCASE(case5, array_h, newshape_ct );

    OBJECT_RESHAPE_SUBCASE(case5,   array, nmtools::Object );
    OBJECT_RESHAPE_SUBCASE(case5, array_a, nmtools::Object );
    OBJECT_RESHAPE_SUBCASE(case5, array_f, nmtools::Object );
    OBJECT_RESHAPE_SUBCASE(case5, array_d, nmtools::Object );
    OBJECT_RESHAPE_SUBCASE(case5, array_h, nmtools::Object );
}

// NOTE: currently reshape is not monadic
// TODO: support monadic error handling for reshape
#if 0
TEST_CASE("reshape(case6)" * doctest::test_suite("array::reshape"))
{
    RESHAPE_SUBCASE(case6, array, newshape );
    RESHAPE_SUBCASE(case6, array_a, newshape_a );
    RESHAPE_SUBCASE(case6, array_f, newshape_a );
    RESHAPE_SUBCASE(case6, array_d, newshape_v );
    RESHAPE_SUBCASE(case6, array_h, newshape_h );

    RESHAPE_SUBCASE(case6, array, newshape_ct );
    RESHAPE_SUBCASE(case6, array_a, newshape_ct );
    RESHAPE_SUBCASE(case6, array_f, newshape_ct );
    RESHAPE_SUBCASE(case6, array_d, newshape_ct );
    RESHAPE_SUBCASE(case6, array_h, newshape_ct );
}
#endif
