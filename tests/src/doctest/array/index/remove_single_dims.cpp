#include "nmtools/array/index/remove_single_dims.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "testing/doctest.hpp"

#include <array>
#include <tuple>
#include <vector>

namespace nm = nmtools;

TEST_CASE("remove_single_dims" * doctest::test_suite("index::remove_single_dims"))
{
    {
        auto shape = std::array{1,2,3};
        auto squeezed = nm::index::remove_single_dims(shape);
        auto expected = std::array{2,3};
        NMTOOLS_ASSERT_EQUAL( squeezed, expected );
    }
    {
        auto shape = std::tuple{1,2,3};
        auto squeezed = nm::index::remove_single_dims(shape);
        auto expected = std::array{2,3};
        NMTOOLS_ASSERT_EQUAL( squeezed, expected );
    }
    {
        auto shape = std::vector{1,2,3};
        auto squeezed = nm::index::remove_single_dims(shape);
        auto expected = std::array{2,3};
        NMTOOLS_ASSERT_EQUAL( squeezed, expected );
    }
    {
        auto shape = nm::array::hybrid_ndarray({1,2,3});
        auto squeezed = nm::index::remove_single_dims(shape);
        auto expected = std::array{2,3};
        NMTOOLS_ASSERT_EQUAL( squeezed, expected );
    }
}