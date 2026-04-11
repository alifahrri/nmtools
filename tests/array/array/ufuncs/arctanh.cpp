#include "nmtools/array/ufuncs/arctanh.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/data/array/arctanh.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nmtools;
namespace view = nm::view;

#define ARCTANH_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, arctanh, case_name); \
    using namespace args; \
    auto result = nm::arctanh(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("arctanh(case1)" * doctest::test_suite("array::arctanh"))
{
    ARCTANH_SUBCASE( case1,   a);
    ARCTANH_SUBCASE( case1, a_a);
    ARCTANH_SUBCASE( case1, a_f);
    ARCTANH_SUBCASE( case1, a_d);
    ARCTANH_SUBCASE( case1, a_h);
}
