#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace meta = nm::meta;

TEST_CASE("is_index" * doctest::test_suite("meta::traits"))
{
    {
        using arg_t = int;
        STATIC_CHECK_TRAIT( meta::is_index, arg_t );
    }
    {
        using arg_t = double;
        STATIC_CHECK_TRAIT_FALSE( meta::is_index, arg_t );
    }
    {
        using arg_t = std::integral_constant<int,1>;
        STATIC_CHECK_TRAIT( meta::is_index, arg_t );
    }
}