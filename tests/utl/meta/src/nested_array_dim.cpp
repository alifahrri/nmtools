#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;
namespace utl = nm::utl;

TEST_CASE("nested_array_dim" * doctest::test_suite("utl"))
{
    {
        using arg_t = utl::array<double,3>;
        constexpr auto N = meta::nested_array_dim_v<arg_t>;
        NMTOOLS_STATIC_ASSERT_EQUAL( N, 1 );
    }
    {
        using arg_t = utl::array<utl::array<double,3>,2>;
        constexpr auto N = meta::nested_array_dim_v<arg_t>;
        NMTOOLS_STATIC_ASSERT_EQUAL( N, 2 );
    }
    {
        using arg_t = utl::array<utl::array<utl::array<double,2>,3>,2>;
        constexpr auto N = meta::nested_array_dim_v<arg_t>;
        NMTOOLS_STATIC_ASSERT_EQUAL( N, 3 );
    }
}