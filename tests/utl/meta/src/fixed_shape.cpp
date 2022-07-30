#include "nmtools/utl.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace utl = nm::utl;
namespace meta = nm::meta;

TEST_CASE("fixed_shape" * doctest::test_suite("meta"))
{
    {
        using array_t = utl::array<double,3>;
        constexpr auto shape = meta::fixed_shape_v<array_t>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fail, decltype(shape) );
        NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL( shape, (nmtools_array{3}) );
    }
    {
        using array_t = utl::array<utl::array<double,2>,3>;
        constexpr auto shape = meta::fixed_shape_v<array_t>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fail, decltype(shape) );
        NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL( shape, (nmtools_array{3,2}) );
    }
    {
        using array_t = utl::vector<double>;
        constexpr auto shape = meta::fixed_shape_v<array_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, decltype(shape) );
    }
    {
        using array_t = utl::vector<utl::vector<double>>;
        constexpr auto shape = meta::fixed_shape_v<array_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, decltype(shape) );
    }
}