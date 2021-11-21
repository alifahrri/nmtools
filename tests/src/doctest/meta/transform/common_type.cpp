#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;

TEST_CASE("common_type" * doctest::test_suite("meta"))
{
    {
        using lhs_t = int;
        using result_t = meta::common_type_t<lhs_t>;
        using expect_t = int;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }

    {
        using result_t = meta::common_type_t<unsigned char, int>;
        using expect_t = int;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using result_t = meta::common_type_t<unsigned char, int, long int>;
        using expect_t = long int;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using result_t = meta::common_type_t<unsigned char, int, long int, float>;
        using expect_t = float;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using result_t = meta::common_type_t<unsigned char, int, long int, float, double>;
        using expect_t = double;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using result_t = meta::common_type_t<double, unsigned char, float, int, long int>;
        using expect_t = double;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }

    {
        using lhs_t = unsigned long;
        using rhs_t = meta::integral_constant<unsigned long, 1ul>;
        using result_t = meta::common_type_t<lhs_t,rhs_t>;
        using expect_t = unsigned long;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
}