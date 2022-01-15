#include "nmtools/meta/utl/transform.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;
namespace utl = nm::utl;

TEST_CASE("get_either_type" * doctest::test_suite("utl"))
{
    {
        using arg_t = utl::either<int,double>;
        using result_t = meta::get_either_left_t<arg_t>;
        using expect_t = int;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using arg_t = utl::either<int,double>;
        using result_t = meta::get_either_right_t<arg_t>;
        using expect_t = double;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
}