#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"
#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace meta = nm::meta;

#if defined(NMTOOLS_DISABLE_STL)
using meta::integral_constant;
#else
using std::integral_constant;
#endif

TEST_CASE("is_index_array" * doctest::test_suite("meta::traits"))
{
    {
        using arg_t = nmtools_array<int,3>;
        STATIC_CHECK_TRAIT( meta::is_index_array, arg_t );
    }
    {
        using arg_t = nmtools_array<double,3>;
        STATIC_CHECK_TRAIT_FALSE( meta::is_index_array, arg_t );
    }
    {
        using arg_t = nmtools_tuple<int,int,int>;
        STATIC_CHECK_TRAIT( meta::is_index_array, arg_t );
    }
    {
        using arg_t = nmtools_tuple<int,double,int>;
        STATIC_CHECK_TRAIT_FALSE( meta::is_index_array, arg_t );
    }
    {
        using arg_t = nmtools_tuple<integral_constant<int,3>,integral_constant<int,1>,integral_constant<int,2>>;
        STATIC_CHECK_TRAIT( meta::is_index_array, arg_t );
    }
}