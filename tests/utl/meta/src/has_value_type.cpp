#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;
namespace utl = nm::utl;

TEST_CASE("has_value_type" * doctest::test_suite("utl"))
{
    {
        using arg_t = utl::array<int,2>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::has_value_type, arg_t );
    }
    {
        using arg_t = utl::tuple<int,int>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::has_value_type, arg_t );
    }
    {
        using arg_t = utl::vector<int>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::has_value_type, arg_t );
    }
}