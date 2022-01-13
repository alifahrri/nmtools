#include "nmtools/meta/utl/traits.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;
namespace utl = nm::utl;

TEST_CASE("has_at" * doctest::test_suite("utl"))
{
    {
        using arg_t = utl::array<int,2>;
        NMTOOLS_STATIC_ASSERT_EQUAL( (meta::has_at_v<arg_t,size_t>), true );
    }
    {
        using arg_t = utl::tuple<int,double>;
        NMTOOLS_STATIC_ASSERT_EQUAL( (meta::has_at_v<arg_t,size_t>), false );
    }
    {
        using arg_t = utl::maybe<utl::array<int,2>>;
        NMTOOLS_STATIC_ASSERT_EQUAL( (meta::has_at_v<arg_t,size_t>), false );
    }
    {
        using arg_t = utl::either<utl::array<int,2>,int>;
        NMTOOLS_STATIC_ASSERT_EQUAL( (meta::has_at_v<arg_t,size_t>), false );
    }
    {
        using arg_t = utl::array<utl::array<int,3>,2>;
        NMTOOLS_STATIC_ASSERT_EQUAL( (meta::has_at_v<arg_t,size_t>), true );
    }

    {
        using arg_t = const utl::array<int,2>&;
        NMTOOLS_STATIC_ASSERT_EQUAL( (meta::has_at_v<arg_t,size_t>), true );
    }

    {
        using arg_t = utl::array<int,2>&;
        NMTOOLS_STATIC_ASSERT_EQUAL( (meta::has_at_v<arg_t,size_t>), true );
    }
}