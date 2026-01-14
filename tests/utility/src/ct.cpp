#include "nmtools/constants.hpp"
#include "nmtools/utl/static_string.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm  = nmtools;
namespace utl = nmtools::utl;

using namespace nmtools::literals;

// TODO: fully implement
TEST_CASE("number" * doctest::test_suite("ct") * doctest::may_fail())
{
    {
        utl::static_string str;
        str = "1";
        CHECK( ct_is_number(str) );
        CHECK( !ct_is_slice(str) );
        CHECK( !ct_is_clipped_integer(str) );
        CHECK( !ct_is_ellipsis(str) );
    }
    {
        utl::static_string str;
        str = "-1";
        CHECK( ct_is_number(str) );
        CHECK( !ct_is_slice(str) );
        CHECK( !ct_is_clipped_integer(str) );
        CHECK( !ct_is_ellipsis(str) );
    }
    /***************************************************************** */
    {
        utl::static_string str;
        str = "...";
        CHECK( !ct_is_number(str) );
        CHECK( !ct_is_slice(str) );
        CHECK( !ct_is_clipped_integer(str) );
        CHECK( ct_is_ellipsis(str) );
    }
    /***************************************************************** */
    {
        utl::static_string str;
        str = "1:";
        CHECK( !ct_is_number(str) );
        CHECK( ct_is_slice(str) );
        CHECK( !ct_is_clipped_integer(str) );
        CHECK( !ct_is_ellipsis(str) );
    }
    {
        utl::static_string str;
        str = "-1:";
        CHECK( !ct_is_number(str) );
        CHECK( ct_is_slice(str) );
        CHECK( !ct_is_clipped_integer(str) );
        CHECK( !ct_is_ellipsis(str) );
    }
    {
        utl::static_string str;
        str = "::";
        CHECK( !ct_is_number(str) );
        CHECK( ct_is_slice(str) );
        CHECK( !ct_is_clipped_integer(str) );
        CHECK( !ct_is_ellipsis(str) );
    }
    /***************************************************************** */
    {
        utl::static_string str;
        str = "1:[0,9]";
        CHECK( !ct_is_number(str) );
        CHECK( !ct_is_slice(str) );
        CHECK( ct_is_clipped_integer(str) );
        CHECK( !ct_is_ellipsis(str) );
    }
    {
        auto v = "1:"_ct;
        CHECK( nm::len_v<decltype(v)> == 2 );
    }
}