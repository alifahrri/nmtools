#include "nmtools/array/ufuncs/ldexp.hpp"
#include "nmtools/testing/data/array/ldexp.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace view = nm::view;

#define LDEXP_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, ldexp, case_name); \
    using namespace args; \
    auto result = view::ldexp(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("ldexp(case1)" * doctest::test_suite("view::ldexp"))
{
    LDEXP_SUBCASE( case1,   a,   b );
    LDEXP_SUBCASE( case1, a_a, b_a );
    LDEXP_SUBCASE( case1, a_f, b_f );
    LDEXP_SUBCASE( case1, a_d, b_d );
    LDEXP_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("ldexp(case2)" * doctest::test_suite("view::ldexp"))
{
    LDEXP_SUBCASE( case2,   a, b );
    LDEXP_SUBCASE( case2, a_a, b );
    LDEXP_SUBCASE( case2, a_f, b );
    LDEXP_SUBCASE( case2, a_d, b );
    LDEXP_SUBCASE( case2, a_h, b );
}