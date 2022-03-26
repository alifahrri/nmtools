#include "nmtools/array/index/compute_strides.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace idx = nm::index;
namespace utl = nm::utl;

TEST_CASE("compute_strides" * doctest::test_suite("index"))
{
    {
        auto shape  = utl::array{3};
        auto result = idx::compute_strides(shape);
        auto expect = utl::array{1};
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }

    {
        auto shape  = utl::array{3,2};
        auto result = idx::compute_strides(shape);
        auto expect = utl::array{2,1};
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }

    {
        auto shape  = utl::array{3,2,1};
        auto result = idx::compute_strides(shape);
        auto expect = utl::array{2,1,1};
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }

    {
        auto shape  = utl::array{3ul};
        auto result = idx::compute_strides(shape);
        auto expect = utl::array{1};
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }

    {
        auto shape  = utl::array{3ul,2ul};
        auto result = idx::compute_strides(shape);
        auto expect = utl::array{2,1};
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }

    {
        auto shape  = utl::array{3ul,2ul,1ul};
        auto result = idx::compute_strides(shape);
        auto expect = utl::array{2,1,1};
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
}
