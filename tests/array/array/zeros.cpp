#include "nmtools/array/zeros.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/data/array/zeros.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

#define ZEROS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, zeros, case_name); \
    using namespace args; \
    auto result = nmtools::zeros(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("zeros(case1)" * doctest::test_suite("array::zeros"))
{
    ZEROS_SUBCASE(case1, shape, dtype );
    ZEROS_SUBCASE(case1, shape_a, dtype );
    ZEROS_SUBCASE(case1, shape_v, dtype );
    // ZEROS_SUBCASE(case1, shape_f, dtype );
    ZEROS_SUBCASE(case1, shape_h, dtype );
    // ZEROS_SUBCASE(case1, shape_d, dtype );
    ZEROS_SUBCASE(case1, shape_ct, dtype );
}

// TODO: remove
#if 0
TEST_CASE("zeros_traits(case1)" * doctest::test_suite("array::zeros_traits"))
{
    {
        using shape_t = int[3];
        shape_t shape = {2,3,2};
        auto array = nmtools::zeros(shape,nm::float32);
        using array_t = decltype(array);
        constexpr auto is_fixed_shape = nm::meta::is_fixed_size_ndarray_v<array_t>;
        static_assert( !is_fixed_shape );
    }
    {
        using namespace nm::literals;
        auto shape = std::tuple{2_ct,3_ct,2_ct};
        auto array = nmtools::zeros(shape,nm::float32);
        using array_t = decltype(array);
        constexpr auto is_fixed_shape = nm::meta::is_fixed_size_ndarray_v<array_t>;
        static_assert( is_fixed_shape );
    }
}
#endif