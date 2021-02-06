#include "nmtools/array/fixed.hpp"
#include "nmtools/utils/isclose.hpp"
#include "testing/doctest.hpp"
#include <array>

using nmtools::utils::isclose;
using nmtools::shape;
using nmtools::array::fixed_matrix;

TEST_CASE("fixed_matrix" * doctest::test_suite("array::fixed_matrix"))
{
    auto mat = fixed_matrix{{
        {1,2},
        {3,4},
        {5,6},
    }};
    auto expected = std::array{
        std::array{1,2},
        std::array{3,4},
        std::array{5,6},
    };
    CHECK( isclose(mat,expected) );
}

TEST_CASE("fixed_matrix" * doctest::test_suite("array::fixed_matrix"))
{
    constexpr auto mat = fixed_matrix{{
        {1,2},
        {3,4},
        {5,6},
    }};
    constexpr auto expected = std::array{
        std::array{1,2},
        std::array{3,4},
        std::array{5,6},
    };
    STATIC_CHECK( isclose(mat,expected) );
}

TEST_CASE("fixed_matrix" * doctest::test_suite("array::fixed_matrix"))
{
    auto mat = fixed_matrix<double,3,2>();
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