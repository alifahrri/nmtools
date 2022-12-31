#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

#include <tuple>

namespace nm = nmtools;
namespace meta = nm::meta;

TEST_CASE("get_common_type" * doctest::test_suite("std"))
{
    {
        using arg_t = nmtools_tuple<int>;
        using result_t = meta::get_common_type_t<arg_t>;
        using expect_t = int;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using arg_t = nmtools_tuple<int,int>;
        using result_t = meta::get_common_type_t<arg_t>;
        using expect_t = int;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using arg_t = nmtools_tuple<int,size_t>;
        using result_t = meta::get_common_type_t<arg_t>;
        using expect_t = long int;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using arg_t = nmtools_tuple<float,double>;
        using result_t = meta::get_common_type_t<arg_t>;
        using expect_t = double;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
}