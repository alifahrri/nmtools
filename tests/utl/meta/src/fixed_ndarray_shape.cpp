#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;
namespace utl = nm::utl;

TEST_CASE("fixed_ndarray_shape" * doctest::test_suite("utl"))
{
    {
        using arg_t = utl::array<utl::array<float,2>,3>;
        constexpr auto result = meta::fixed_ndarray_shape_v<arg_t>;
        constexpr auto expect = utl::array<size_t,2>{3,2};
        NMTOOLS_STATIC_ASSERT_EQUAL( result.size(), expect.size() );
        for (size_t i=0; i<result.size(); i++) {
            NMTOOLS_ASSERT_EQUAL( result[i], expect[i] );
        }
    }
}