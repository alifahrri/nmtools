#include "nmtools/array/ufuncs/arcsinh.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/data/array/arcsinh.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nmtools;
namespace view = nm::view;

#define ARCSINH_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, arcsinh, case_name); \
    using namespace args; \
    auto result = nm::arcsinh(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("arcsinh(case1)" * doctest::test_suite("array::arcsinh"))
{
    ARCSINH_SUBCASE( case1,   a);
    ARCSINH_SUBCASE( case1, a_a);
    ARCSINH_SUBCASE( case1, a_f);
    ARCSINH_SUBCASE( case1, a_d);
    ARCSINH_SUBCASE( case1, a_h);
}
