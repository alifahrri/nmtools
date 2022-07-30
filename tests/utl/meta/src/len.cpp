#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;
namespace utl = nm::utl;

TEST_CASE("len" * doctest::test_suite("utl"))
{
    {
        using arg_t = utl::array<double,3>;
        constexpr auto N = meta::len_v<arg_t>;
        NMTOOLS_STATIC_ASSERT_EQUAL( N, 3 );
    }
    {
        using arg_t = utl::tuple<int,double,int>;
        constexpr auto N = meta::len_v<arg_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_index, decltype(N) );
        NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL( N, 3 );
    }
    {
        using arg_t = utl::tuple<meta::ct<1>,meta::ct<2>,meta::ct<3>>;
        constexpr auto N = meta::len_v<arg_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_index, decltype(N) );
        NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL( N, 3 );
    }
}