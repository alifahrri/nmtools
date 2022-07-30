#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;
namespace utl = nm::utl;

TEST_CASE("replace_element_type" * doctest::test_suite("utl"))
{
    {
        using arg_t = utl::array<int,2>;
        using result_t = meta::replace_element_type_t<arg_t,double>;
        using expect_t = utl::array<double,2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using arg_t = utl::vector<int>;
        using result_t = meta::replace_element_type_t<arg_t,double>;
        using expect_t = utl::vector<double>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
}