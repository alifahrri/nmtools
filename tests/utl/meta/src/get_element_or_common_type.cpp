#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;
namespace utl = nm::utl;

TEST_CASE("get_element_or_common_type" * doctest::test_suite("utl"))
{
    {
        using arg_t = utl::array<int,2>;
        using result_t = meta::get_element_or_common_type_t<arg_t>;
        using expect_t = int;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using arg_t = utl::array<utl::array<utl::array<int,2>,3>,2>;
        using result_t = meta::get_element_or_common_type_t<arg_t>;
        using expect_t = int;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using arg_t = utl::tuple<int,int,int>;
        using result_t = meta::get_element_or_common_type_t<arg_t>;
        using expect_t = int;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
}