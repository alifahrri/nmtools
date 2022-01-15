#include "nmtools/meta/utl/transform.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;
namespace utl = nm::utl;

TEST_CASE("get_element_type" * doctest::test_suite("utl"))
{
    {
        using arg_t = utl::array<double,2>;
        using result_t = meta::get_element_type_t<arg_t>;
        using expect_t = double;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using arg_t = utl::array<utl::array<double,3>,2>;
        using result_t = meta::get_element_type_t<arg_t>;
        using expect_t = double;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using arg_t = utl::array<utl::array<utl::array<double,2>,3>,2>;
        using result_t = meta::get_element_type_t<arg_t>;
        using expect_t = double;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
}