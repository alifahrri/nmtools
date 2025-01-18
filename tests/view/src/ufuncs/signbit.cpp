#include "nmtools/array/ufuncs/signbit.hpp"
#include "nmtools/testing/data/array/signbit.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define SIGNBIT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, signbit, case_name); \
    using namespace args; \
    auto result = view::signbit( __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("signbit(case1)" * doctest::test_suite("view::signbit"))
{
    SIGNBIT_SUBCASE( case1,   a );
    SIGNBIT_SUBCASE( case1, a_a );
    SIGNBIT_SUBCASE( case1, a_f );
    SIGNBIT_SUBCASE( case1, a_d );
    SIGNBIT_SUBCASE( case1, a_h );
}