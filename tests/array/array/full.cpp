#include "nmtools/array/full.hpp"
#include "nmtools/testing/data/array/full.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

#define FULL_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, full, case_name); \
    using namespace args; \
    auto result = nmtools::full(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("full(case1)" * doctest::test_suite("array::full"))
{
    FULL_SUBCASE(case1, shape, fill_value );
    FULL_SUBCASE(case1, shape_a, fill_value );
    // TODO: fix
    // FULL_SUBCASE(case1, shape_f, fill_value );
    FULL_SUBCASE(case1, shape_h, fill_value );
    // FULL_SUBCASE(case1, shape_d, fill_value );
    FULL_SUBCASE(case1, shape_ct, fill_value );
}

// TODO: remove
#if 0
TEST_CASE("full_traits(case1)" * doctest::test_suite("array::full_traits"))
{
    {
        using shape_t = int[3];
        shape_t shape = {2,3,2};
        auto fill_value = 1;
        auto array = nmtools::full(shape,fill_value);
        using array_t = decltype(array);
        constexpr auto is_fixed_shape = nm::meta::is_fixed_size_ndarray_v<array_t>;
        static_assert( !is_fixed_shape );
    }
    {
        using namespace nm::literals;
        auto shape = std::tuple{2_ct,3_ct,2_ct};
        auto fill_value = 1;
        auto array = nmtools::full(shape,fill_value);
        using array_t = decltype(array);
        constexpr auto is_fixed_shape = nm::meta::is_fixed_size_ndarray_v<array_t>;
        static_assert( is_fixed_shape );
    }
}
#endif