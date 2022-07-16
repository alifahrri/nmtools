#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

#include <array>
#include <tuple>
#include <vector>

namespace meta = nmtools::meta;

TEST_CASE("has_template_get" * doctest::test_suite("meta"))
{
    {
        using arg_t = const std::tuple<int,int>&;
        STATIC_CHECK(( meta::has_template_get_v<arg_t,1> ));
    }
    {
        using arg_t = const std::array<int,4>&;
        STATIC_CHECK(( meta::has_template_get_v<arg_t,1> ));
    }
    // note: somehow this is true even if it is clearly out of bound access
    {
        using arg_t = const std::array<int,4>&;
        STATIC_CHECK(( meta::has_template_get_v<arg_t,4> ));
    }
    // wont compile, static assert from std::get failed
    // error: static_assert failed due to requirement '0UL < tuple_size<std::tuple<> >::value' "tuple index is in range"
    //   static_assert(__i < tuple_size<tuple<>>::value
    // {
    //     using arg_t = std::tuple<int,int,int,int>;
    //     STATIC_CHECK(( !meta::has_template_get_v<arg_t,4> ));
    // }
}