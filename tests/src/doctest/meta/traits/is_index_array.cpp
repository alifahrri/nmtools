#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"
#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace meta = nm::meta;

TEST_CASE("is_index_array" * doctest::test_suite("meta::traits"))
{
    {
        using arg_t = std::array<int,3>;
        STATIC_CHECK_TRAIT( meta::is_index_array, arg_t );
    }
    {
        using arg_t = std::array<double,3>;
        STATIC_CHECK_TRAIT_FALSE( meta::is_index_array, arg_t );
    }
    {
        using arg_t = std::tuple<int,int,int>;
        STATIC_CHECK_TRAIT( meta::is_index_array, arg_t );
    }
    {
        using arg_t = std::tuple<int,double,int>;
        STATIC_CHECK_TRAIT_FALSE( meta::is_index_array, arg_t );
    }
    {
        using arg_t = std::tuple<std::integral_constant<int,3>,std::integral_constant<int,1>,std::integral_constant<int,2>>;
        STATIC_CHECK_TRAIT( meta::is_index_array, arg_t );
    }
}