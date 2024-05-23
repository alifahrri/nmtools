#include "nmtools/array/view/ufuncs/isinf.hpp"
#include "nmtools/testing/data/array/isinf.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define ISINF_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, isinf, case_name); \
    using namespace args; \
    auto result = view::isinf(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("isinf(case1)" * doctest::test_suite("view::isinf"))
{
    ISINF_SUBCASE( case1,   a );
    ISINF_SUBCASE( case1, a_a );
    ISINF_SUBCASE( case1, a_f );
    ISINF_SUBCASE( case1, a_d );
    ISINF_SUBCASE( case1, a_h );
}