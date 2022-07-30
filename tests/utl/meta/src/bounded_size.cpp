#include "nmtools/utl.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace utl = nm::utl;
namespace meta = nm::meta;

TEST_CASE("bounded_size" * doctest::test_suite("meta"))
{
    {
        using array_t = utl::array<double,3>;
        constexpr auto bounded_size = meta::bounded_size_v<array_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, decltype(bounded_size) );
        NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL( bounded_size, 3 );
    }
    {
        using array_t = utl::array<utl::array<double,2>,3>;
        constexpr auto bounded_size = meta::bounded_size_v<array_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, decltype(bounded_size) );
        NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL( bounded_size, 6 );
    }
    {
        using array_t = utl::vector<double>;
        constexpr auto bounded_size = meta::bounded_size_v<array_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, decltype(bounded_size) );
    }
    {
        using array_t = utl::vector<utl::vector<double>>;
        constexpr auto bounded_size = meta::bounded_size_v<array_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, decltype(bounded_size) );
    }
}