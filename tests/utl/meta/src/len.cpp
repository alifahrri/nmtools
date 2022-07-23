#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;
namespace utl = nm::utl;

TEST_CASE("len" * doctest::test_suite("utl"))
{
    {
        using arg_t = utl::array<double,3>;
        constexpr auto N = meta::len_v<arg_t>;
        NMTOOLS_STATIC_ASSERT_EQUAL( N, 3 );
    }
}