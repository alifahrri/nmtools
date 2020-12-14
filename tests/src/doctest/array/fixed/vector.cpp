#include "nmtools/array/vector.hpp"
#include "nmtools/utils/isclose.hpp"
#include "testing/doctest.hpp"

#include <array>

namespace nm = nmtools;
using nmtools::utils::isclose;
using nmtools::array::fixed_vector;

TEST_CASE("fixed_vector" * doctest::test_suite("array::fixed_vector"))
{
    auto vec = fixed_vector{{1,2,3,4,5}};
    double expected[5] = {1,2,3,4,5};
    NMTOOLS_ASSERT_CLOSE( vec, expected );
}

TEST_CASE("fixed_vector" * doctest::test_suite("array::fixed_vector"))
{
    constexpr auto vec = fixed_vector{{1,2,3,4,5}};
    constexpr double expected[5] = {1,2,3,4,5};
    STATIC_CHECK( isclose(vec, expected) );
}

TEST_CASE("fixed_vector" * doctest::test_suite("array::fixed_vector"))
{
    auto vec = fixed_vector<double,5>{};
    vec = {1,2,3,4,5};
    double expected[5] = {1,2,3,4,5};
    NMTOOLS_ASSERT_CLOSE( vec, expected );
}