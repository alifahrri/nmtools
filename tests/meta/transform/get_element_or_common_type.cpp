#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;

TEST_CASE("get_element_or_common_type" * doctest::test_suite("meta"))
{
    {
        using arg_t = nmtools_array<size_t,4>;
        using result_t = meta::get_element_or_common_type_t<arg_t>;
        using expect_t = size_t;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using arg_t = nmtools_list<size_t>;
        using result_t = meta::get_element_or_common_type_t<arg_t>;
        using expect_t = size_t;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using arg_t = nmtools_array<size_t,4>;
        using result_t = meta::get_element_or_common_type_t<arg_t>;
        using expect_t = size_t;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using arg_t = nmtools_tuple<size_t,size_t,size_t>;
        using result_t = meta::get_element_or_common_type_t<arg_t>;
        using expect_t = size_t;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
        {
        using arg_t = nmtools_tuple<size_t,int,size_t>;
        using result_t = meta::get_element_or_common_type_t<arg_t>;
        using expect_t = long int;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
}