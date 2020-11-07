#include "nmtools/array/dynamic.hpp"
#include "nmtools/utility/helper.hpp"
#include "testing/doctest.hpp"
#include <array>

using nmtools::helper::isclose;
using nmtools::array_shape;
using nmtools::array::dynamic_matrix;

TEST_CASE("dynamic_matrix" * doctest::test_suite("array::dynamic_matrix"))
{
    auto mat = dynamic_matrix<double>{3,2};
    mat = {
        {1,2},
        {3,4},
        {5,6},
    };
    auto expected = std::array{
        std::array{1,2},
        std::array{3,4},
        std::array{5,6},
    };
    CHECK( isclose(mat,expected) );
}