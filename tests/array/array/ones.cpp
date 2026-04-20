#include "nmtools/array/ones.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/data/array/ones.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

#define ONES_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, ones, case_name); \
    using namespace args; \
    auto result = nmtools::ones(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("ones(case1)" * doctest::test_suite("array::ones"))
{
    ONES_SUBCASE(case1, shape, dtype );
    ONES_SUBCASE(case1, shape_a, dtype );
    ONES_SUBCASE(case1, shape_v, dtype );
    // ONES_SUBCASE(case1, shape_f, dtype );
    ONES_SUBCASE(case1, shape_h, dtype );
    // ONES_SUBCASE(case1, shape_d, dtype );
    ONES_SUBCASE(case1, shape_ct, dtype );
}

// TODO: remove
#if 0
TEST_CASE("ones_traits(case1)" * doctest::test_suite("array::ones_traits"))
{
    {
        using shape_t = int[3];
        shape_t shape = {2,3,2};
        auto array = nmtools::ones(shape,nm::float32);
        using array_t = decltype(array);
        constexpr auto is_fixed_shape = nm::meta::is_fixed_size_ndarray_v<array_t>;
        static_assert( !is_fixed_shape );
    }
    {
        using namespace nm::literals;
        auto shape = std::tuple{2_ct,3_ct,2_ct};
        auto array = nmtools::ones(shape,nm::float32);
        using array_t = decltype(array);
        constexpr auto is_fixed_shape = nm::meta::is_fixed_size_ndarray_v<array_t>;
        static_assert( is_fixed_shape );
    }
}
#endif