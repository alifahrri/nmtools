#include "nmtools/utl.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace utl = nm::utl;
namespace meta = nm::meta;

TEST_CASE("bounded_dim" * doctest::test_suite("meta"))
{
    {
        using array_t = utl::array<double,3>;
        constexpr auto bounded_dim = meta::bounded_dim_v<array_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, decltype(bounded_dim) );
        NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL( bounded_dim, 1 );
    }
    {
        using array_t = utl::array<utl::array<double,2>,3>;
        constexpr auto bounded_dim = meta::bounded_dim_v<array_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, decltype(bounded_dim) );
        NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL( bounded_dim, 2 );
    }
    {
        using array_t = utl::vector<double>;
        constexpr auto bounded_dim = meta::bounded_dim_v<array_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, decltype(bounded_dim) );
        NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL( bounded_dim, 1 );
    }
    {
        using array_t = utl::vector<utl::vector<double>>;
        constexpr auto bounded_dim = meta::bounded_dim_v<array_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, decltype(bounded_dim) );
    }
    {
        using array_t = utl::tuple<meta::ct<2>,meta::ct<3>,meta::ct<2>>;
        constexpr auto bounded_dim = meta::bounded_dim_v<array_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, decltype(bounded_dim) );
        NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL( bounded_dim, 1 );
    }
}