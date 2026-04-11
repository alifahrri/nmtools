#include "nmtools/array/stddev.hpp"
#include "nmtools/core/context/object.hpp"
#include "nmtools/testing/data/array/stddev.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#define STD_SUBCASE_NUM(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, stddev, case_name); \
    using namespace args; \
    auto result = nmtools::std(__VA_ARGS__, nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_num, decltype(result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define OBJECT_STD_SUBCASE(case_name, a, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, stddev, case_name); \
    using namespace args; \
    auto object = nmtools::array(a,nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(object) ); \
    auto result = object.std(__VA_ARGS__); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define STD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, stddev, case_name); \
    using namespace args; \
    auto result = nmtools::std(__VA_ARGS__, nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("std(case1)" * doctest::test_suite("array::std"))
{
    STD_SUBCASE_NUM( case1, array );
    STD_SUBCASE_NUM( case1, array_a );
    STD_SUBCASE_NUM( case1, array_f );
    // TODO: fix
    // STD_SUBCASE_NUM( case1, array_h );
    // STD_SUBCASE_NUM( case1, array_d );
}

TEST_CASE("std(case6)" * doctest::test_suite("array::std"))
{
    STD_SUBCASE( case6,   array, axis, nm::None, ddof, keepdims );
    STD_SUBCASE( case6, array_a, axis, nm::None, ddof, keepdims );
    STD_SUBCASE( case6, array_f, axis, nm::None, ddof, keepdims );
    STD_SUBCASE( case6, array_h, axis, nm::None, ddof, keepdims );
    STD_SUBCASE( case6, array_d, axis, nm::None, ddof, keepdims );

    OBJECT_STD_SUBCASE( case6,   array, axis, nm::None, ddof, keepdims );
    OBJECT_STD_SUBCASE( case6, array_a, axis, nm::None, ddof, keepdims );
    OBJECT_STD_SUBCASE( case6, array_f, axis, nm::None, ddof, keepdims );
    OBJECT_STD_SUBCASE( case6, array_h, axis, nm::None, ddof, keepdims );
    OBJECT_STD_SUBCASE( case6, array_d, axis, nm::None, ddof, keepdims );
}