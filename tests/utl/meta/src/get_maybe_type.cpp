#include "nmtools/meta/utl/transform.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;
namespace utl = nm::utl;

TEST_CASE("get_maybe_type" * doctest::test_suite("utl"))
{
    {
        using arg_t = utl::maybe<int>;
        using result_t = meta::get_maybe_type_t<arg_t>;
        using expect_t = int;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using arg_t = utl::maybe<utl::array<double,3>>;
        using result_t = meta::get_maybe_type_t<arg_t>;
        using expect_t = utl::array<double,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
}