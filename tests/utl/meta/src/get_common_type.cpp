#include "nmtools/meta/utl/transform.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;
namespace utl = nm::utl;

TEST_CASE("get_common_type" * doctest::test_suite("utl"))
{
    {
        using arg_t = utl::tuple<int>;
        using result_t = meta::get_common_type_t<arg_t>;
        using expect_t = int;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using arg_t = utl::tuple<int,int>;
        using result_t = meta::get_common_type_t<arg_t>;
        using expect_t = int;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        // using arg_t = utl::tuple<int,size_t>;
        using arg_t = utl::tuple<int,unsigned long>;
        using result_t = meta::get_common_type_t<arg_t>;
        using expect_t = long int;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using arg_t = utl::tuple<float,double>;
        using result_t = meta::get_common_type_t<arg_t>;
        using expect_t = double;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
}