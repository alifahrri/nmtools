#include "nmtools/array/dynamic.hpp"
#include "nmtools/utils/isclose.hpp"
#include "nmtools/testing/doctest.hpp"
#include <array>

using nmtools::utils::isclose;
using nmtools::shape;
using nmtools::array::dynamic_matrix;

TEST_CASE("shape" * doctest::test_suite("array::dynamic_matrix"))
{
    auto mat = dynamic_matrix({
        {1,2},
        {3,4},
        {5,6},
    });
    auto exp_shape = std::array{3,2};
    CHECK( isclose(mat.shape(),exp_shape) );
    CHECK( isclose(shape(mat),exp_shape) );
}

TEST_CASE("values" * doctest::test_suite("array::dynamic_matrix"))
{
    auto mat = dynamic_matrix({
        {1,2},
        {3,4},
        {5,6},
    });
    auto expected = std::array{
        std::array{1,2},
        std::array{3,4},
        std::array{5,6},
    };
    CHECK( isclose(mat,expected) );
}