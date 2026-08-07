#include "nmtools/utl/expected.hpp"
#include "nmtools/utl/string.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm  = nmtools;
namespace utl = nmtools::utl;

TEST_CASE("expected" * doctest::test_suite("utl"))
{
    {
        using expected = utl::expected<int,utl::string>;

        auto e1 = expected();
        CHECK( e1.has_value() );
        CHECK( e1.value() == 0 );
        CHECK( (bool)e1 );
        CHECK( *e1 == 0 );
        CHECK( nm::has_value(e1) );
        CHECK( nm::unwrap(e1) == 0 );

        auto e2 = expected(utl::unexpected(utl::string("fail")));
        CHECK( !e2.has_value() );
        CHECK( e2.error() == "fail" );
        CHECK( !nm::has_value(e2) );
        CHECK( nm::unwrap_error(e2) == "fail" );

        auto e3 = expected(expected::unexpected_type("fail"));
        CHECK( !e3.has_value() );
        CHECK( e3.error() == "fail" );
        CHECK( !nm::has_value(e3) );
        CHECK( nm::unwrap_error(e3) == "fail" );

        CHECK( nm::is_expected_v<expected> );
        CHECK( nm::has_error_type_v<expected> );
        CHECK( nm::has_unexpected_type_v<expected> );
        CHECK( nm::is_same_v<nm::get_error_type_t<expected>, utl::string> );
        CHECK( nm::is_same_v<nm::get_unexpected_type_t<expected>, utl::unexpected<utl::string>> );
    }
    {
        using expected = utl::expected<float,int>;

        auto e1 = expected();
        CHECK( e1.has_value() );
        CHECK( e1.value() == 0 );
        CHECK( nm::has_value(e1) );
        CHECK( nm::unwrap(e1) == 0 );

        auto e2 = expected(utl::unexpected(-1));
        CHECK( !e2.has_value() );
        CHECK( e2.error() == -1 );
        CHECK( !nm::has_value(e2) );
        CHECK( nm::unwrap_error(e2) == -1 );

        expected e3 = utl::unexpected(-1);
        CHECK( !e3.has_value() );
        CHECK( e3.error() == -1 );
        CHECK( !nm::has_value(e3) );
        CHECK( nm::unwrap_error(e3) == -1 );

        CHECK( nm::is_expected_v<expected> );
        CHECK( nm::has_error_type_v<expected> );
        CHECK( nm::has_unexpected_type_v<expected> );
        CHECK( nm::is_same_v<nm::get_error_type_t<expected>, int> );
        CHECK( nm::is_same_v<nm::get_unexpected_type_t<expected>, utl::unexpected<int>> );
    }
}