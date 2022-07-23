#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;
namespace utl = nm::utl;

TEST_CASE("is_tuple" * doctest::test_suite("utl"))
{
    {
        using arg_t = utl::tuple<int,int,int>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_tuple, arg_t );
    }
    {
        using arg_t = utl::tuple<int,double,float>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_tuple, arg_t );
    }
    {
        using arg_t = utl::array<int,2>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_tuple, arg_t );
    }
    {
        using arg_t = utl::maybe<utl::tuple<int,int,int>>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_tuple, arg_t );
    }
    {
        using arg_t = utl::either<utl::tuple<int,int,int>,utl::array<int,3>>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_tuple, arg_t );
    }
}