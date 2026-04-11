#include "nmtools/array/var.hpp"
#include "nmtools/core/context/object.hpp"
#include "nmtools/testing/data/array/var.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#define VAR_SUBCASE_NUM(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, var, case_name); \
    using namespace args; \
    auto result = nmtools::var(__VA_ARGS__, nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_num, decltype(result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define VAR_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, var, case_name); \
    using namespace args; \
    auto result = nmtools::var(__VA_ARGS__, nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("var(case1)" * doctest::test_suite("array::var"))
{
    VAR_SUBCASE( case1, array, axis );
    VAR_SUBCASE( case1, array_a, axis_a );
    VAR_SUBCASE( case1, array_f, axis_f );
    VAR_SUBCASE( case1, array_h, axis );
    VAR_SUBCASE( case1, array_d, axis );
}

TEST_CASE("var(case2)" * doctest::test_suite("array::var"))
{
    VAR_SUBCASE( case2, array, axis );
    VAR_SUBCASE( case2, array_a, axis_a );
    VAR_SUBCASE( case2, array_f, axis_f );
    VAR_SUBCASE( case2, array_h, axis );
    VAR_SUBCASE( case2, array_d, axis );
}

TEST_CASE("var(case6)" * doctest::test_suite("array::var"))
{
    VAR_SUBCASE( case6,   array, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case6, array_a, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case6, array_f, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case6, array_h, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case6, array_d, axis, nm::None, ddof, keepdims );
}