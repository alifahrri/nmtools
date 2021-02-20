#include "nmtools/array/view/reshape.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
#include "nmtools/array/index/as_tuple.hpp"
#include "testing/doctest.hpp"

#include <array>
#include <tuple>
#include <vector>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;
namespace kind = na::kind;
using namespace nm::literals;

template <typename T>
using not_array1d = meta::logical_not<meta::is_array1d<T>>;

template <typename T>
using not_array2d = meta::logical_not<meta::is_array2d<T>>;

template <typename T>
using not_fixed_size_ndarray = meta::logical_not<meta::is_fixed_size_ndarray<T>>;

template <typename T>
using not_fixed_dim_ndarray = meta::logical_not<meta::is_fixed_dim_ndarray<T>>;

template <typename T>
using is_fixed_size_array2d = meta::compose_logical_and<T,
    not_array1d, meta::is_array2d, meta::is_ndarray,
    meta::is_fixed_size_ndarray
>;

// dynamic shape but fixed dim
// @TODO: fix trait for reshape view
template <typename T>
using is_fixed_dim_dynamic_size_array2d = meta::compose_logical_and<T,
    not_array1d, meta::is_array2d, meta::is_ndarray
    // , meta::is_fixed_dim_ndarray
>;

// dynamic shape dynamic dim
template <typename T>
using is_dynamic_dim_dynamic_size_array2d = meta::compose_logical_and<T,
    meta::is_ndarray
    , not_fixed_size_ndarray
>;

template <typename T>
using is_fixed_dim_dynamic_size_ndarray = meta::compose_logical_and<T,
    not_array1d, not_array2d, meta::is_ndarray
    // , meta::is_fixed_dim_ndarray
>;

// dynamic shape dynamic dim
template <typename T>
using is_dynamic_dim_dynamic_size_ndarray = meta::compose_logical_and<T,
    meta::is_ndarray
    , not_fixed_size_ndarray
>;

NMTOOLS_TESTING_DECLARE_CASE(reshape)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        double array[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
        auto array_a = cast<double>(array);
        auto array_v = cast(array,kind::nested_vec);
        auto array_f = cast(array,kind::fixed);
        auto array_d = cast(array,kind::dynamic);
        auto array_h = cast(array,kind::hybrid);
        int newshape[2] = {12,1};
        auto newshape_ct = std::tuple{12_ct, 1_ct};
        auto newshape_a = cast<int>(newshape);
        auto newshape_v = cast(newshape,kind::nested_vec);
        auto newshape_t = index::as_tuple(newshape_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        // isclose doesn support tuple and raw yet
        int shape_[2] = {12,1};
        auto shape = cast<int>(shape_);
        double expected[12][1] = {
            {1.}, {2.}, {3.}, {4.}, {5.}, {6.}, {7.}, {8.}, {9.}, {10.}, {11.}, {12.}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        double array[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
        auto array_a = cast<double>(array);
        auto array_v = cast(array,kind::nested_vec);
        auto array_f = cast(array,kind::fixed);
        auto array_d = cast(array,kind::dynamic);
        auto array_h = cast(array,kind::hybrid);
        int newshape[2] = {3,4};
        auto newshape_ct = std::tuple{3_ct, 4_ct};
        auto newshape_a = cast<int>(newshape);
        auto newshape_v = cast(newshape,kind::nested_vec);
        auto newshape_t = index::as_tuple(newshape_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        // isclose doesn support tuple and raw yet
        int shape_[2] = {3,4};
        auto shape = cast<int>(shape_);
        double expected[3][4] = {
            {1.,  2.,  3.,  4.},
            {5.,  6.,  7.,  8.},
            {9., 10., 11., 12.}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        double array[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
        auto array_a = cast<double>(array);
        auto array_v = cast(array,kind::nested_vec);
        auto array_f = cast(array,kind::fixed);
        auto array_d = cast(array,kind::dynamic);
        auto array_h = cast(array,kind::hybrid);
        int newshape[4] = {1,2,3,2};
        auto newshape_ct = std::tuple{1_ct, 2_ct, 3_ct, 2_ct};
        auto newshape_a = cast<int>(newshape);
        auto newshape_v = cast(newshape,kind::nested_vec);
        auto newshape_t = index::as_tuple(newshape_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        // isclose doesn support tuple and raw yet
        int shape_[4] = {1,2,3,2};
        auto shape = cast<int>(shape_);
        double expected[1][2][3][2] = {
            {
                {
                    {1., 2.},
                    {3., 4.},
                    {5., 6.}
                },
                {
                    {7.,  8.},
                    {9., 10.},
                    {11.,12.}
                }
            }
        };
    }
}

#define RUN_impl(...) \
nm::view::reshape(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs reshape fn to callable lambda
#define RUN_reshape(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("reshape-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_reshape(case_name, ...) \
RUN_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define RESHAPE_SUBCASE(case_name, array, newshape, trait) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(reshape, case_name) \
    auto array_ref = RUN_reshape(case_name, args::array, args::newshape); \
    using view_t = decltype(array_ref); \
    NMTOOLS_ASSERT_EQUAL( array_ref.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( array_ref, expect::expected ); \
    STATIC_CHECK_TRAIT( trait, view_t ); \
}

TEST_CASE("reshape(raw)" * doctest::test_suite("view::reshape"))
{
    RESHAPE_SUBCASE( case1, array, newshape_a, is_fixed_dim_dynamic_size_array2d );
    RESHAPE_SUBCASE( case1, array, newshape_v, is_dynamic_dim_dynamic_size_array2d );
    RESHAPE_SUBCASE( case1, array, newshape_t, is_fixed_dim_dynamic_size_array2d );
    RESHAPE_SUBCASE( case1, array, newshape_ct, is_fixed_size_array2d );

    RESHAPE_SUBCASE( case2, array, newshape_a, is_fixed_dim_dynamic_size_array2d );
    RESHAPE_SUBCASE( case2, array, newshape_v, is_dynamic_dim_dynamic_size_array2d );
    RESHAPE_SUBCASE( case2, array, newshape_t, is_fixed_dim_dynamic_size_array2d );
    RESHAPE_SUBCASE( case2, array, newshape_ct, is_fixed_size_array2d );

    RESHAPE_SUBCASE( case3, array, newshape_a, is_fixed_dim_dynamic_size_ndarray );
    RESHAPE_SUBCASE( case3, array, newshape_v, is_dynamic_dim_dynamic_size_ndarray );
    RESHAPE_SUBCASE( case3, array, newshape_t, is_fixed_dim_dynamic_size_ndarray );
    RESHAPE_SUBCASE( case3, array, newshape_ct, meta::is_fixed_size_ndarray );
}

TEST_CASE("reshape(array)" * doctest::test_suite("view::reshape"))
{
    RESHAPE_SUBCASE( case1, array_a, newshape_a, is_fixed_dim_dynamic_size_array2d );
    RESHAPE_SUBCASE( case1, array_a, newshape_v, is_dynamic_dim_dynamic_size_array2d );
    RESHAPE_SUBCASE( case1, array_a, newshape_t, is_fixed_dim_dynamic_size_array2d );
    RESHAPE_SUBCASE( case1, array_a, newshape_ct, is_fixed_size_array2d );

    RESHAPE_SUBCASE( case2, array_a, newshape_a, is_fixed_dim_dynamic_size_array2d );
    RESHAPE_SUBCASE( case2, array_a, newshape_v, is_dynamic_dim_dynamic_size_array2d );
    RESHAPE_SUBCASE( case2, array_a, newshape_t, is_fixed_dim_dynamic_size_array2d );
    RESHAPE_SUBCASE( case2, array_a, newshape_ct, is_fixed_size_array2d );

    RESHAPE_SUBCASE( case3, array_a, newshape_a, is_fixed_dim_dynamic_size_ndarray );
    RESHAPE_SUBCASE( case3, array_a, newshape_v, is_dynamic_dim_dynamic_size_ndarray );
    RESHAPE_SUBCASE( case3, array_a, newshape_t, is_fixed_dim_dynamic_size_ndarray );
    RESHAPE_SUBCASE( case3, array_a, newshape_ct, meta::is_fixed_size_ndarray );
}

TEST_CASE("reshape(fixed_ndarray)" * doctest::test_suite("view::reshape"))
{
    RESHAPE_SUBCASE( case1, array_f, newshape_a, is_fixed_dim_dynamic_size_array2d );
    RESHAPE_SUBCASE( case1, array_f, newshape_v, is_dynamic_dim_dynamic_size_array2d );
    RESHAPE_SUBCASE( case1, array_f, newshape_t, is_fixed_dim_dynamic_size_array2d );
    RESHAPE_SUBCASE( case1, array_f, newshape_ct, is_fixed_size_array2d );

    RESHAPE_SUBCASE( case2, array_f, newshape_a, is_fixed_dim_dynamic_size_array2d );
    RESHAPE_SUBCASE( case2, array_f, newshape_v, is_dynamic_dim_dynamic_size_array2d );
    RESHAPE_SUBCASE( case2, array_f, newshape_t, is_fixed_dim_dynamic_size_array2d );
    RESHAPE_SUBCASE( case2, array_f, newshape_ct, is_fixed_size_array2d );

    RESHAPE_SUBCASE( case3, array_f, newshape_a, is_fixed_dim_dynamic_size_ndarray );
    RESHAPE_SUBCASE( case3, array_f, newshape_v, is_dynamic_dim_dynamic_size_ndarray );
    RESHAPE_SUBCASE( case3, array_f, newshape_t, is_fixed_dim_dynamic_size_ndarray );
    RESHAPE_SUBCASE( case3, array_f, newshape_ct, meta::is_fixed_size_ndarray );
}

TEST_CASE("reshape(vector)" * doctest::test_suite("view::reshape"))
{
    RESHAPE_SUBCASE( case1, array_v, newshape_a, is_fixed_dim_dynamic_size_array2d );
    RESHAPE_SUBCASE( case1, array_v, newshape_v, is_dynamic_dim_dynamic_size_array2d );
    RESHAPE_SUBCASE( case1, array_v, newshape_t, is_fixed_dim_dynamic_size_array2d );
    RESHAPE_SUBCASE( case1, array_v, newshape_ct, is_fixed_dim_dynamic_size_array2d );

    RESHAPE_SUBCASE( case2, array_v, newshape_a, is_fixed_dim_dynamic_size_array2d );
    RESHAPE_SUBCASE( case2, array_v, newshape_v, is_dynamic_dim_dynamic_size_array2d );
    RESHAPE_SUBCASE( case2, array_v, newshape_t, is_fixed_dim_dynamic_size_array2d );
    RESHAPE_SUBCASE( case2, array_v, newshape_ct, is_fixed_dim_dynamic_size_array2d );

    RESHAPE_SUBCASE( case3, array_v, newshape_a, is_fixed_dim_dynamic_size_ndarray );
    RESHAPE_SUBCASE( case3, array_v, newshape_v, is_dynamic_dim_dynamic_size_ndarray );
    RESHAPE_SUBCASE( case3, array_v, newshape_t, is_fixed_dim_dynamic_size_ndarray );
    RESHAPE_SUBCASE( case3, array_v, newshape_ct, is_fixed_dim_dynamic_size_ndarray );
}

TEST_CASE("reshape(dynamic_ndarray)" * doctest::test_suite("view::reshape"))
{
    RESHAPE_SUBCASE( case1, array_d, newshape_a, is_dynamic_dim_dynamic_size_ndarray );
    RESHAPE_SUBCASE( case1, array_d, newshape_v, is_dynamic_dim_dynamic_size_ndarray );
    RESHAPE_SUBCASE( case1, array_d, newshape_t, is_dynamic_dim_dynamic_size_ndarray );
    RESHAPE_SUBCASE( case1, array_d, newshape_ct, is_dynamic_dim_dynamic_size_ndarray );

    RESHAPE_SUBCASE( case2, array_d, newshape_a, is_dynamic_dim_dynamic_size_ndarray );
    RESHAPE_SUBCASE( case2, array_d, newshape_v, is_dynamic_dim_dynamic_size_ndarray );
    RESHAPE_SUBCASE( case2, array_d, newshape_t, is_dynamic_dim_dynamic_size_ndarray );
    RESHAPE_SUBCASE( case2, array_d, newshape_ct, is_dynamic_dim_dynamic_size_ndarray );

    RESHAPE_SUBCASE( case3, array_d, newshape_a, is_dynamic_dim_dynamic_size_ndarray );
    RESHAPE_SUBCASE( case3, array_d, newshape_v, is_dynamic_dim_dynamic_size_ndarray );
    RESHAPE_SUBCASE( case3, array_d, newshape_t, is_dynamic_dim_dynamic_size_ndarray );
    RESHAPE_SUBCASE( case3, array_d, newshape_ct, is_dynamic_dim_dynamic_size_ndarray );
}

TEST_CASE("reshape(hybrid_ndarray)" * doctest::test_suite("view::reshape"))
{
    RESHAPE_SUBCASE( case1, array_h, newshape_a, is_fixed_dim_dynamic_size_array2d );
    RESHAPE_SUBCASE( case1, array_h, newshape_v, is_dynamic_dim_dynamic_size_array2d );
    RESHAPE_SUBCASE( case1, array_h, newshape_t, is_fixed_dim_dynamic_size_array2d );
    RESHAPE_SUBCASE( case1, array_h, newshape_ct, is_fixed_dim_dynamic_size_array2d );

    RESHAPE_SUBCASE( case2, array_h, newshape_a, is_fixed_dim_dynamic_size_array2d );
    RESHAPE_SUBCASE( case2, array_h, newshape_v, is_dynamic_dim_dynamic_size_array2d );
    RESHAPE_SUBCASE( case2, array_h, newshape_t, is_fixed_dim_dynamic_size_array2d );
    RESHAPE_SUBCASE( case2, array_h, newshape_ct, is_fixed_dim_dynamic_size_array2d );

    RESHAPE_SUBCASE( case3, array_h, newshape_a, is_fixed_dim_dynamic_size_ndarray );
    RESHAPE_SUBCASE( case3, array_h, newshape_v, is_dynamic_dim_dynamic_size_ndarray );
    RESHAPE_SUBCASE( case3, array_h, newshape_t, is_fixed_dim_dynamic_size_ndarray );
    RESHAPE_SUBCASE( case3, array_h, newshape_ct, is_fixed_dim_dynamic_size_ndarray );
}