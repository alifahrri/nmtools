#include "nmtools/utl.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace utl = nm::utl;
namespace meta = nm::meta;

TEST_CASE("fixed_dim" * doctest::test_suite("meta"))
{
    {
        using array_t = utl::array<double,3>;
        constexpr auto fixed_dim = meta::fixed_dim_v<array_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, decltype(fixed_dim) );
        NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL( fixed_dim, 1 );
    }
    {
        using array_t = utl::array<utl::array<double,2>,3>;
        constexpr auto fixed_dim = meta::fixed_dim_v<array_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, decltype(fixed_dim) );
        NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL( fixed_dim, 2 );
    }
    {
        using array_t = utl::vector<double>;
        constexpr auto fixed_dim = meta::fixed_dim_v<array_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, decltype(fixed_dim) );
        NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL( fixed_dim, 1 );
    }
    {
        using array_t = utl::vector<utl::vector<double>>;
        constexpr auto fixed_dim = meta::fixed_dim_v<array_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, decltype(fixed_dim) );
    }
}