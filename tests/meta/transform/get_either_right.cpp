#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;

TEST_CASE("get_either_right" * doctest::test_suite("meta"))
{
    {
        using either_t = nmtools_either<int,float>;
        using result_t = meta::get_either_right_t<either_t>;
        using expect_t = float;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using either_t = nmtools_either<const int,const float>;
        using result_t = meta::get_either_right_t<either_t>;
        using expect_t = const float;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using either_t = nmtools_either<int*,float*>;
        using result_t = meta::get_either_right_t<either_t>;
        using expect_t = float*;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using either_t = nmtools_either<const int*,const float*>;
        using result_t = meta::get_either_right_t<either_t>;
        using expect_t = const float*;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
}