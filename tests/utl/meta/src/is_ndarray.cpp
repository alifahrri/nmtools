#include "nmtools/meta.hpp"
#include "nmtools/utl.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;
namespace utl = nm::utl;

TEST_CASE("is_ndarray" * doctest::test_suite("utl"))
{
    {
        using arg_t = utl::array<double,3>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, arg_t );
    }
    {
        using arg_t = utl::maybe<int>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_ndarray, arg_t );
    }
    {
        using arg_t = utl::maybe<utl::array<int,3>>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_ndarray, arg_t );
    }
    {
        using arg_t = utl::tuple<int,int,int>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_ndarray, arg_t );
    }
    {
        using arg_t = utl::array<utl::array<double,3>,2>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, arg_t );
    }
    {
        using arg_t = utl::vector<double>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, arg_t );
    }
    {
        using arg_t = utl::vector<utl::vector<double>>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_ndarray, arg_t );
    }
    {
        using arg_t = utl::either<utl::vector<double>,utl::vector<int>>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_ndarray, arg_t );
    }
}