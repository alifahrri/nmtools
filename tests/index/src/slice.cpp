#include "nmtools/index/slice.hpp"
#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/testing/data/index/slice.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/constants.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nmtools;
namespace kind = na::kind;

using nmtools_tuple;
using namespace nm::literals;

#define SHAPE_SLICE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, shape_slice, case_name); \
    using namespace args; \
    auto result = nmtools::index::shape_slice(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL_MSG_ATTRIBUTES_DOCTEST( result, expect::result, __VA_ARGS__ ); \
}

TEST_CASE("shape_slice(case1)" * doctest::test_suite("index::shape_slice") * doctest::may_fail())
{
    SHAPE_SLICE_SUBCASE(case1,   shape, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case1, shape_a, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case1, shape_v, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case1, shape_f, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case1, shape_h, slice0, slice1, slice2);

    SHAPE_SLICE_SUBCASE(case1, shape_ct, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case1, shape_cl, slice0, slice1, slice2);

    #if 0
    NMTOOLS_TESTING_USE_CASE( index, shape_slice, case1 );
    auto slices_pack = nmtools_tuple{slice0,slice1,slice2};
    auto slice = nm::at(slices_pack, nm::ct_v<0>);
    auto init = nmtools_tuple{nm::ct_v<0ul>,nm::ct_v<0ul>};
    // auto r_i = nm::get<0>(init);
    auto s_i = nm::get<1>(init);
    [[maybe_unused]] auto si = nm::at(shape,s_i);
    using slice_t = meta::remove_cvref_t<decltype(slice)>;

    static_assert( nm::len_v<decltype(shape_mx)> == 3 );
    static_assert( nm::is_mixed_index_array_v<decltype(shape_mx)> );
    static_assert( !nm::is_index_v<slice_t> );
    static_assert( nm::is_slice_all_v<slice_t> );
    static_assert( nm::is_tuple_v<slice_t> );
    static_assert( !nm::is_ellipsis_v<slice_t> );
    static_assert( !nm::is_ellipsis_v<nm::remove_cvref_t<slice_t>> );
    constexpr nm_index_t DIM = nm::len_v<decltype(shape_mx)>;
    static_assert( !(nm::is_ellipsis_v<slice_t>) && (DIM > 0) );
    #endif

    SHAPE_SLICE_SUBCASE(case1, shape_mx, slice0, slice1, slice2);

    {
        using nmtools::nullable_num;
        auto shape_na = nmtools_array{nullable_num(2),nullable_num(3),nullable_num(3)};
        static_assert( nm::meta::is_nullable_index_array_v<decltype(shape_na)> );
        static_assert( nm::meta::is_index_array_v<decltype(shape_na)> );
        // TODO: fix
        SHAPE_SLICE_SUBCASE(case1, shape_na, slice0, slice1, slice2);
    }
}

TEST_CASE("shape_slice(case2)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case2,   shape, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case2, shape_a, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case2, shape_v, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case2, shape_f, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case2, shape_h, slice0, slice1, slice2);

    SHAPE_SLICE_SUBCASE(case2, shape_ct, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case2, shape_cl, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case2, shape_mx, slice0, slice1, slice2);
}

TEST_CASE("shape_slice(case3)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case3,   shape, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case3, shape_a, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case3, shape_v, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case3, shape_f, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case3, shape_h, slice0, slice1, slice2);

    SHAPE_SLICE_SUBCASE(case3, shape_ct, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case3, shape_cl, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case3, shape_mx, slice0, slice1, slice2);
}

TEST_CASE("shape_slice(case4)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case4,   shape, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case4, shape_a, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case4, shape_v, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case4, shape_f, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case4, shape_h, slice0, slice1, slice2);

    SHAPE_SLICE_SUBCASE(case4, shape_ct, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case4, shape_cl, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case4, shape_mx, slice0, slice1, slice2);
}

TEST_CASE("shape_slice(case5)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case5,   shape, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case5, shape_a, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case5, shape_v, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case5, shape_f, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case5, shape_h, slice0, slice1, slice2);

    SHAPE_SLICE_SUBCASE(case5, shape_ct, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case5, shape_cl, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case5, shape_mx, slice0, slice1, slice2);
}

TEST_CASE("shape_slice(case6)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case6,   shape, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case6, shape_a, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case6, shape_v, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case6, shape_f, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case6, shape_h, slice0, slice1, slice2);

    SHAPE_SLICE_SUBCASE(case6, shape_ct, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case6, shape_cl, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case6, shape_mx, slice0, slice1, slice2);
}

TEST_CASE("shape_slice(case7)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case7,   shape, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case7, shape_a, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case7, shape_v, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case7, shape_f, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case7, shape_h, slice0, slice1, slice2);

    SHAPE_SLICE_SUBCASE(case7, shape_ct, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case7, shape_cl, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case7, shape_mx, slice0, slice1, slice2);
}

TEST_CASE("shape_slice(case8)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case8,   shape, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case8, shape_a, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case8, shape_v, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case8, shape_f, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case8, shape_h, slice0, slice1, slice2);

    SHAPE_SLICE_SUBCASE(case8, shape_ct, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case8, shape_cl, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case8, shape_mx, slice0, slice1, slice2);
}

TEST_CASE("shape_slice(case9)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case9,   shape, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case9, shape_a, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case9, shape_v, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case9, shape_f, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case9, shape_h, slice0, slice1, slice2);

    SHAPE_SLICE_SUBCASE(case9, shape_ct, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case9, shape_cl, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case9, shape_mx, slice0, slice1, slice2);
}

TEST_CASE("shape_slice(case10)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case10,   shape, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case10, shape_a, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case10, shape_v, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case10, shape_f, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case10, shape_h, slice0, slice1, slice2);

    SHAPE_SLICE_SUBCASE(case10, shape_ct, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case10, shape_cl, slice0, slice1, slice2);
    // SHAPE_SLICE_SUBCASE(case10, shape_mx, slice0, slice1, slice2);
}

TEST_CASE("shape_slice(case11)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case11,   shape, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case11, shape_a, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case11, shape_v, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case11, shape_f, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case11, shape_h, slice0, slice1);

    SHAPE_SLICE_SUBCASE(case11, shape_ct, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case11, shape_cl, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case11, shape_mx, slice0, slice1);
}

TEST_CASE("shape_slice(case12)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case12,   shape, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case12, shape_a, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case12, shape_v, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case12, shape_f, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case12, shape_h, slice0, slice1);

    SHAPE_SLICE_SUBCASE(case12, shape_ct, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case12, shape_cl, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case12, shape_mx, slice0, slice1);
}

TEST_CASE("shape_slice(case13)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case13,   shape, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case13, shape_a, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case13, shape_v, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case13, shape_f, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case13, shape_h, slice0, slice1);

    SHAPE_SLICE_SUBCASE(case13, shape_ct, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case13, shape_cl, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case13, shape_mx, slice0, slice1);
}

TEST_CASE("shape_slice(case14)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case14,   shape, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case14, shape_a, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case14, shape_v, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case14, shape_f, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case14, shape_h, slice0, slice1);

    SHAPE_SLICE_SUBCASE(case14, shape_ct, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case14, shape_cl, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case14, shape_mx, slice0, slice1);
}

TEST_CASE("shape_slice(case15)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case15,   shape, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case15, shape_a, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case15, shape_v, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case15, shape_f, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case15, shape_h, slice0, slice1);

    SHAPE_SLICE_SUBCASE(case15, shape_ct, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case15, shape_cl, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case15, shape_mx, slice0, slice1);
}

TEST_CASE("shape_slice(case16)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case16,   shape, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case16, shape_a, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case16, shape_v, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case16, shape_f, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case16, shape_h, slice0, slice1);

    SHAPE_SLICE_SUBCASE(case16, shape_ct, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case16, shape_cl, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case16, shape_mx, slice0, slice1);
}

TEST_CASE("shape_slice(case17)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case17,   shape, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case17, shape_a, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case17, shape_v, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case17, shape_f, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case17, shape_h, slice0, slice1);

    SHAPE_SLICE_SUBCASE(case17, shape_ct, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case17, shape_cl, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case17, shape_mx, slice0, slice1);
}

TEST_CASE("shape_slice(case18)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case18,   shape, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case18, shape_a, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case18, shape_v, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case18, shape_f, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case18, shape_h, slice0, slice1);

    SHAPE_SLICE_SUBCASE(case18, shape_ct, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case18, shape_cl, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case18, shape_mx, slice0, slice1);
}

TEST_CASE("shape_slice(case19)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case19,   shape, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case19, shape_a, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case19, shape_v, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case19, shape_f, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case19, shape_h, slice0, slice1);

    SHAPE_SLICE_SUBCASE(case19, shape_ct, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case19, shape_cl, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case19, shape_mx, slice0, slice1);
}

TEST_CASE("shape_slice(case20)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case20,   shape, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case20, shape_a, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case20, shape_v, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case20, shape_f, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case20, shape_h, slice0, slice1);

    SHAPE_SLICE_SUBCASE(case20, shape_ct, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case20, shape_cl, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case20, shape_mx, slice0, slice1);
}

TEST_CASE("shape_slice(case21)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case21,   shape, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case21, shape_a, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case21, shape_v, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case21, shape_f, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case21, shape_h, slice0, slice1);

    SHAPE_SLICE_SUBCASE(case21, shape_ct, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case21, shape_cl, slice0, slice1);
    // SHAPE_SLICE_SUBCASE(case21, shape_mx, slice0, slice1);
}

TEST_CASE("shape_slice(case22)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case22,   shape, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case22, shape_a, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case22, shape_v, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case22, shape_f, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case22, shape_h, slice0, slice1);

    SHAPE_SLICE_SUBCASE(case22, shape_ct, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case22, shape_cl, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case22, shape_mx, slice0, slice1);
}

TEST_CASE("shape_slice(case23)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case23,   shape, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case23, shape_a, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case23, shape_v, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case23, shape_f, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case23, shape_h, slice0, slice1);

    SHAPE_SLICE_SUBCASE(case23, shape_ct, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case23, shape_cl, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case23, shape_mx, slice0, slice1);
}

TEST_CASE("shape_slice(case24)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case24,   shape, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case24, shape_a, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case24, shape_v, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case24, shape_f, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case24, shape_h, slice0, slice1);

    SHAPE_SLICE_SUBCASE(case24, shape_ct, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case24, shape_cl, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case24, shape_mx, slice0, slice1);

    static_assert( nm::meta::is_index_v<decltype(nm::Last)> );
    static_assert( nm::meta::is_integral_constant_v<decltype(nm::Last)> );
}

TEST_CASE("shape_slice(case25)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case25,   shape, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case25, shape_a, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case25, shape_v, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case25, shape_f, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case25, shape_h, slice0, slice1);

    SHAPE_SLICE_SUBCASE(case25, shape_ct, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case25, shape_cl, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case25, shape_mx, slice0, slice1);
}

TEST_CASE("shape_slice(case26)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case26,   shape, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case26, shape_a, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case26, shape_v, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case26, shape_f, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case26, shape_h, slice0, slice1);

    SHAPE_SLICE_SUBCASE(case26, shape_ct, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case26, shape_cl, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case26, shape_mx, slice0, slice1);
}

TEST_CASE("shape_slice(case27)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case27,   shape, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case27, shape_a, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case27, shape_v, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case27, shape_f, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case27, shape_h, slice0, slice1, slice2);

    SHAPE_SLICE_SUBCASE(case27, shape_ct, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case27, shape_cl, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case27, shape_mx, slice0, slice1, slice2);
}

TEST_CASE("shape_slice(case28)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case28,   shape, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case28, shape_a, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case28, shape_v, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case28, shape_f, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case28, shape_h, slice0, slice1);

    SHAPE_SLICE_SUBCASE(case28, shape_ct, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case28, shape_cl, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case28, shape_mx, slice0, slice1);
}

TEST_CASE("shape_slice(case29)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case29,   shape, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case29, shape_a, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case29, shape_v, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case29, shape_f, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case29, shape_h, slice0, slice1, slice2);

    SHAPE_SLICE_SUBCASE(case29, shape_ct, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case29, shape_cl, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case29, shape_mx, slice0, slice1, slice2);
}

TEST_CASE("shape_slice(case30)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case30,   shape, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case30, shape_a, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case30, shape_v, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case30, shape_f, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case30, shape_h, slice0, slice1, slice2);

    SHAPE_SLICE_SUBCASE(case30, shape_ct, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case30, shape_cl, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case30, shape_mx, slice0, slice1, slice2);
}

TEST_CASE("shape_slice(case31)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case31,   shape, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case31, shape_a, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case31, shape_v, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case31, shape_f, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case31, shape_h, slice0, slice1, slice2);

    SHAPE_SLICE_SUBCASE(case31, shape_ct, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case31, shape_cl, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case31, shape_mx, slice0, slice1, slice2);
}

TEST_CASE("shape_slice(case32)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case32,   shape, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case32, shape_a, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case32, shape_v, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case32, shape_f, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case32, shape_h, slice0, slice1);

    SHAPE_SLICE_SUBCASE(case32, shape_ct, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case32, shape_cl, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case32, shape_mx, slice0, slice1);
}

TEST_CASE("shape_slice(case33)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case33,   shape, slice0_a);
    SHAPE_SLICE_SUBCASE(case33, shape_a, slice0_a);
    SHAPE_SLICE_SUBCASE(case33, shape_v, slice0_a);
    SHAPE_SLICE_SUBCASE(case33, shape_f, slice0_a);
    SHAPE_SLICE_SUBCASE(case33, shape_h, slice0_a);
}

TEST_CASE("shape_slice(case34)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case34,   shape, slice0_a);
    SHAPE_SLICE_SUBCASE(case34, shape_a, slice0_a);
    SHAPE_SLICE_SUBCASE(case34, shape_v, slice0_a);
    SHAPE_SLICE_SUBCASE(case34, shape_f, slice0_a);
    SHAPE_SLICE_SUBCASE(case34, shape_h, slice0_a);
}

#define SHAPE_DYNAMIC_SLICE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, shape_dynamic_slice, case_name); \
    using namespace args; \
    auto result = nmtools::index::shape_dynamic_slice(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("shape_dynamic_slice(case1)" * doctest::test_suite("index::shape_dynamic_slice"))
{
    SHAPE_DYNAMIC_SLICE_SUBCASE(case1, shape_a, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case1, shape_v, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case1, shape_h, slices);

    SHAPE_DYNAMIC_SLICE_SUBCASE(case1, shape_a, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case1, shape_v, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case1, shape_h, a_slices);
}

TEST_CASE("shape_dynamic_slice(case2)" * doctest::test_suite("index::shape_dynamic_slice"))
{
    SHAPE_DYNAMIC_SLICE_SUBCASE(case2, shape_a, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case2, shape_v, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case2, shape_h, slices);

    SHAPE_DYNAMIC_SLICE_SUBCASE(case2, shape_a, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case2, shape_v, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case2, shape_h, a_slices);
}

TEST_CASE("shape_dynamic_slice(case3)" * doctest::test_suite("index::shape_dynamic_slice"))
{
    SHAPE_DYNAMIC_SLICE_SUBCASE(case3, shape_a, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case3, shape_v, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case3, shape_h, slices);

    SHAPE_DYNAMIC_SLICE_SUBCASE(case3, shape_a, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case3, shape_v, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case3, shape_h, a_slices);
}

TEST_CASE("shape_dynamic_slice(case4)" * doctest::test_suite("index::shape_dynamic_slice"))
{
    SHAPE_DYNAMIC_SLICE_SUBCASE(case4, shape_a, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case4, shape_v, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case4, shape_h, slices);

    SHAPE_DYNAMIC_SLICE_SUBCASE(case4, shape_a, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case4, shape_v, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case4, shape_h, a_slices);
}

TEST_CASE("shape_dynamic_slice(case5)" * doctest::test_suite("index::shape_dynamic_slice"))
{
    SHAPE_DYNAMIC_SLICE_SUBCASE(case5, shape_a, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case5, shape_v, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case5, shape_h, slices);

    SHAPE_DYNAMIC_SLICE_SUBCASE(case5, shape_a, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case5, shape_v, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case5, shape_h, a_slices);
}

TEST_CASE("shape_dynamic_slice(case6)" * doctest::test_suite("index::shape_dynamic_slice"))
{
    SHAPE_DYNAMIC_SLICE_SUBCASE(case6, shape_a, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case6, shape_v, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case6, shape_h, slices);

    SHAPE_DYNAMIC_SLICE_SUBCASE(case6, shape_a, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case6, shape_v, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case6, shape_h, a_slices);
}

TEST_CASE("shape_dynamic_slice(case7)" * doctest::test_suite("index::shape_dynamic_slice"))
{
    SHAPE_DYNAMIC_SLICE_SUBCASE(case7, shape_a, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case7, shape_v, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case7, shape_h, slices);
    
    SHAPE_DYNAMIC_SLICE_SUBCASE(case7, shape_a, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case7, shape_v, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case7, shape_h, a_slices);
}

TEST_CASE("shape_dynamic_slice(case8)" * doctest::test_suite("index::shape_dynamic_slice"))
{
    SHAPE_DYNAMIC_SLICE_SUBCASE(case8, shape_a, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case8, shape_v, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case8, shape_h, slices);

    SHAPE_DYNAMIC_SLICE_SUBCASE(case8, shape_a, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case8, shape_v, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case8, shape_h, a_slices);
}

TEST_CASE("shape_dynamic_slice(case9)" * doctest::test_suite("index::shape_dynamic_slice"))
{
    SHAPE_DYNAMIC_SLICE_SUBCASE(case9, shape_a, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case9, shape_v, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case9, shape_h, slices);

    SHAPE_DYNAMIC_SLICE_SUBCASE(case9, shape_a, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case9, shape_v, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case9, shape_h, a_slices);
}

TEST_CASE("shape_dynamic_slice(case10)" * doctest::test_suite("index::shape_dynamic_slice"))
{
    SHAPE_DYNAMIC_SLICE_SUBCASE(case10, shape_a, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case10, shape_v, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case10, shape_h, slices);

    SHAPE_DYNAMIC_SLICE_SUBCASE(case10, shape_a, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case10, shape_v, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case10, shape_h, a_slices);
}

TEST_CASE("shape_dynamic_slice(case11)" * doctest::test_suite("index::shape_dynamic_slice"))
{
    SHAPE_DYNAMIC_SLICE_SUBCASE(case11, shape_a, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case11, shape_v, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case11, shape_h, slices);

    SHAPE_DYNAMIC_SLICE_SUBCASE(case11, shape_a, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case11, shape_v, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case11, shape_h, a_slices);
}

TEST_CASE("shape_dynamic_slice(case12)" * doctest::test_suite("index::shape_dynamic_slice"))
{
    SHAPE_DYNAMIC_SLICE_SUBCASE(case12, shape_a, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case12, shape_v, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case12, shape_h, slices);

    SHAPE_DYNAMIC_SLICE_SUBCASE(case12, shape_a, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case12, shape_v, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case12, shape_h, a_slices);
}

TEST_CASE("shape_dynamic_slice(case13)" * doctest::test_suite("index::shape_dynamic_slice"))
{
    SHAPE_DYNAMIC_SLICE_SUBCASE(case13, shape_a, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case13, shape_v, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case13, shape_h, slices);

    SHAPE_DYNAMIC_SLICE_SUBCASE(case13, shape_a, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case13, shape_v, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case13, shape_h, a_slices);
}

TEST_CASE("shape_dynamic_slice(case14)" * doctest::test_suite("index::shape_dynamic_slice"))
{
    SHAPE_DYNAMIC_SLICE_SUBCASE(case14, shape_a, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case14, shape_v, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case14, shape_h, slices);

    SHAPE_DYNAMIC_SLICE_SUBCASE(case14, shape_a, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case14, shape_v, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case14, shape_h, a_slices);
}

TEST_CASE("shape_dynamic_slice(case15)" * doctest::test_suite("index::shape_dynamic_slice"))
{
    SHAPE_DYNAMIC_SLICE_SUBCASE(case15, shape_a, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case15, shape_v, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case15, shape_h, slices);

    SHAPE_DYNAMIC_SLICE_SUBCASE(case15, shape_a, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case15, shape_v, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case15, shape_h, a_slices);
}

TEST_CASE("shape_dynamic_slice(case16)" * doctest::test_suite("index::shape_dynamic_slice"))
{
    SHAPE_DYNAMIC_SLICE_SUBCASE(case16, shape_a, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case16, shape_v, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case16, shape_h, slices);

    SHAPE_DYNAMIC_SLICE_SUBCASE(case16, shape_a, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case16, shape_v, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case16, shape_h, a_slices);
}

TEST_CASE("shape_dynamic_slice(case17)" * doctest::test_suite("index::shape_dynamic_slice"))
{
    SHAPE_DYNAMIC_SLICE_SUBCASE(case17, shape_a, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case17, shape_v, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case17, shape_h, slices);

    SHAPE_DYNAMIC_SLICE_SUBCASE(case17, shape_a, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case17, shape_v, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case17, shape_h, a_slices);
}

TEST_CASE("shape_dynamic_slice(case18)" * doctest::test_suite("index::shape_dynamic_slice"))
{
    SHAPE_DYNAMIC_SLICE_SUBCASE(case18, shape_a, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case18, shape_v, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case18, shape_h, slices);

    SHAPE_DYNAMIC_SLICE_SUBCASE(case18, shape_a, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case18, shape_v, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case18, shape_h, a_slices);
}

TEST_CASE("shape_dynamic_slice(case19)" * doctest::test_suite("index::shape_dynamic_slice"))
{
    SHAPE_DYNAMIC_SLICE_SUBCASE(case19, shape_a, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case19, shape_v, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case19, shape_h, slices);

    SHAPE_DYNAMIC_SLICE_SUBCASE(case19, shape_a, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case19, shape_v, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case19, shape_h, a_slices);
}

TEST_CASE("shape_dynamic_slice(case20)" * doctest::test_suite("index::shape_dynamic_slice"))
{
    SHAPE_DYNAMIC_SLICE_SUBCASE(case20, shape_a, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case20, shape_v, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case20, shape_h, slices);

    SHAPE_DYNAMIC_SLICE_SUBCASE(case20, shape_a, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case20, shape_v, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case20, shape_h, a_slices);
}

TEST_CASE("shape_dynamic_slice(case21)" * doctest::test_suite("index::shape_dynamic_slice"))
{
    SHAPE_DYNAMIC_SLICE_SUBCASE(case21, shape_a, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case21, shape_v, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case21, shape_h, slices);

    SHAPE_DYNAMIC_SLICE_SUBCASE(case21, shape_a, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case21, shape_v, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case21, shape_h, a_slices);
}

TEST_CASE("shape_dynamic_slice(case22)" * doctest::test_suite("index::shape_dynamic_slice"))
{
    SHAPE_DYNAMIC_SLICE_SUBCASE(case22, shape_a, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case22, shape_v, slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case22, shape_h, slices);

    SHAPE_DYNAMIC_SLICE_SUBCASE(case22, shape_a, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case22, shape_v, a_slices);
    SHAPE_DYNAMIC_SLICE_SUBCASE(case22, shape_h, a_slices);
}

#define DYNAMIC_SLICE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, dynamic_slice, case_name); \
    using namespace args; \
    auto result = nmtools::index::dynamic_slice(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

// TODO: use apply instead of dynamic_slice
#define APPLY_SLICE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, slice, case_name); \
    using namespace args; \
    auto result = nmtools::index::dynamic_slice(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

#define SLICE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, slice, case_name); \
    using namespace args; \
    auto result = nmtools::index::slice(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("slice(case1)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case1,   indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case2)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case2, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case3)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case3, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case4)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case4, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case5)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case5, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case6)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case6, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case6, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case6, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case6, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case6, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case7)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case7, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case7, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case7, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case7, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case7, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case8)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case8, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case8, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case8, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case8, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case8, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case9)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case9, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case9, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case9, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case9, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case9, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case10)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case10, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case10, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case10, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case10, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case10, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case11)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case11, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case11, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case11, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case11, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case11, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case12)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case12, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case12, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case12, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case12, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case12, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case13)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case13, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case13, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case13, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case13, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case13, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case14)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case14, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case14, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case14, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case14, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case14, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case15)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case15, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case15, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case15, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case15, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case15, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case16)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case16, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case16, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case16, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case16, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case16, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case17)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case17, indices,   shape, slice0, slice1);
    SLICE_SUBCASE(case17, indices_a, shape_a, slice0, slice1);
    SLICE_SUBCASE(case17, indices_v, shape_v, slice0, slice1);
    SLICE_SUBCASE(case17, indices_f, shape_f, slice0, slice1);
    SLICE_SUBCASE(case17, indices_h, shape_h, slice0, slice1);
}

TEST_CASE("slice(case18)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case18, indices,   shape, slice0, slice1);
    SLICE_SUBCASE(case18, indices_a, shape_a, slice0, slice1);
    SLICE_SUBCASE(case18, indices_v, shape_v, slice0, slice1);
    SLICE_SUBCASE(case18, indices_f, shape_f, slice0, slice1);
    SLICE_SUBCASE(case18, indices_h, shape_h, slice0, slice1);
}

TEST_CASE("slice(case19)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case19, indices,   shape, slice0, slice1);
    SLICE_SUBCASE(case19, indices_a, shape_a, slice0, slice1);
    SLICE_SUBCASE(case19, indices_v, shape_v, slice0, slice1);
    SLICE_SUBCASE(case19, indices_f, shape_f, slice0, slice1);
    SLICE_SUBCASE(case19, indices_h, shape_h, slice0, slice1);
}

TEST_CASE("slice(case20)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case20, indices,   shape, slice0, slice1);
    SLICE_SUBCASE(case20, indices_a, shape_a, slice0, slice1);
    SLICE_SUBCASE(case20, indices_v, shape_v, slice0, slice1);
    SLICE_SUBCASE(case20, indices_f, shape_f, slice0, slice1);
    SLICE_SUBCASE(case20, indices_h, shape_h, slice0, slice1);
}

TEST_CASE("slice(case21)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case21, indices,   shape, slice0, slice1);
    SLICE_SUBCASE(case21, indices_a, shape_a, slice0, slice1);
    SLICE_SUBCASE(case21, indices_v, shape_v, slice0, slice1);
    SLICE_SUBCASE(case21, indices_f, shape_f, slice0, slice1);
    SLICE_SUBCASE(case21, indices_h, shape_h, slice0, slice1);
}

TEST_CASE("slice(case22)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case22, indices,   shape, slice0, slice1);
    SLICE_SUBCASE(case22, indices_a, shape_a, slice0, slice1);
    SLICE_SUBCASE(case22, indices_v, shape_v, slice0, slice1);
    SLICE_SUBCASE(case22, indices_f, shape_f, slice0, slice1);
    SLICE_SUBCASE(case22, indices_h, shape_h, slice0, slice1);
}

TEST_CASE("slice(case23)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case23, indices,   shape, slice0, slice1);
    SLICE_SUBCASE(case23, indices_a, shape_a, slice0, slice1);
    SLICE_SUBCASE(case23, indices_v, shape_v, slice0, slice1);
    SLICE_SUBCASE(case23, indices_f, shape_f, slice0, slice1);
    SLICE_SUBCASE(case23, indices_h, shape_h, slice0, slice1);
}

TEST_CASE("slice(case24)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case24, indices,   shape, slice0, slice1);
    SLICE_SUBCASE(case24, indices_a, shape_a, slice0, slice1);
    SLICE_SUBCASE(case24, indices_v, shape_v, slice0, slice1);
    SLICE_SUBCASE(case24, indices_f, shape_f, slice0, slice1);
    SLICE_SUBCASE(case24, indices_h, shape_h, slice0, slice1);
}

TEST_CASE("slice(case25)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case25, indices,   shape, slice0, slice1);
    SLICE_SUBCASE(case25, indices_a, shape_a, slice0, slice1);
    SLICE_SUBCASE(case25, indices_v, shape_v, slice0, slice1);
    SLICE_SUBCASE(case25, indices_f, shape_f, slice0, slice1);
    SLICE_SUBCASE(case25, indices_h, shape_h, slice0, slice1);
}

TEST_CASE("slice(case26)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case26, indices,   shape, slice0, slice1);
    SLICE_SUBCASE(case26, indices_a, shape_a, slice0, slice1);
    SLICE_SUBCASE(case26, indices_v, shape_v, slice0, slice1);
    SLICE_SUBCASE(case26, indices_f, shape_f, slice0, slice1);
    SLICE_SUBCASE(case26, indices_h, shape_h, slice0, slice1);
}

TEST_CASE("slice(case27)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case27, indices,   shape, slice0, slice1);
    SLICE_SUBCASE(case27, indices_a, shape_a, slice0, slice1);
    SLICE_SUBCASE(case27, indices_v, shape_v, slice0, slice1);
    SLICE_SUBCASE(case27, indices_f, shape_f, slice0, slice1);
    SLICE_SUBCASE(case27, indices_h, shape_h, slice0, slice1);
}

TEST_CASE("slice(case28)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case28, indices,   shape, slice0, slice1);
    SLICE_SUBCASE(case28, indices_a, shape_a, slice0, slice1);
    SLICE_SUBCASE(case28, indices_v, shape_v, slice0, slice1);
    SLICE_SUBCASE(case28, indices_f, shape_f, slice0, slice1);
    SLICE_SUBCASE(case28, indices_h, shape_h, slice0, slice1);
}

TEST_CASE("slice(case29)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case29, indices,   shape, slice0, slice1);
    SLICE_SUBCASE(case29, indices_a, shape_a, slice0, slice1);
    SLICE_SUBCASE(case29, indices_v, shape_v, slice0, slice1);
    SLICE_SUBCASE(case29, indices_f, shape_f, slice0, slice1);
    SLICE_SUBCASE(case29, indices_h, shape_h, slice0, slice1);
}

TEST_CASE("slice(case30)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case30, indices,   shape, slice0, slice1);
    SLICE_SUBCASE(case30, indices_a, shape_a, slice0, slice1);
    SLICE_SUBCASE(case30, indices_v, shape_v, slice0, slice1);
    SLICE_SUBCASE(case30, indices_f, shape_f, slice0, slice1);
    SLICE_SUBCASE(case30, indices_h, shape_h, slice0, slice1);
}

TEST_CASE("slice(case31)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case31, indices,   shape, slice0, slice1);
    SLICE_SUBCASE(case31, indices_a, shape_a, slice0, slice1);
    SLICE_SUBCASE(case31, indices_v, shape_v, slice0, slice1);
    SLICE_SUBCASE(case31, indices_f, shape_f, slice0, slice1);
    SLICE_SUBCASE(case31, indices_h, shape_h, slice0, slice1);
}

TEST_CASE("slice(case32)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case32, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case32, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case32, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case32, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case32, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case33)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case33, indices,   shape, slice0, slice1);
    SLICE_SUBCASE(case33, indices_a, shape_a, slice0, slice1);
    SLICE_SUBCASE(case33, indices_v, shape_v, slice0, slice1);
    SLICE_SUBCASE(case33, indices_f, shape_f, slice0, slice1);
    SLICE_SUBCASE(case33, indices_h, shape_h, slice0, slice1);
}

TEST_CASE("slice(case34)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case34, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case34, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case34, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case34, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case34, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case35)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case35, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case35, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case35, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case35, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case35, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case36)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case36, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case36, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case36, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case36, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case36, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case37)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case37, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case37, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case37, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case37, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case37, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case38)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case38, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case38, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case38, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case38, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case38, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case39)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case39, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case39, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case39, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case39, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case39, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case40)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case40, indices,   shape, slice0, slice1);
    SLICE_SUBCASE(case40, indices_a, shape_a, slice0, slice1);
    SLICE_SUBCASE(case40, indices_v, shape_v, slice0, slice1);
    SLICE_SUBCASE(case40, indices_f, shape_f, slice0, slice1);
    SLICE_SUBCASE(case40, indices_h, shape_h, slice0, slice1);
}

TEST_CASE("slice(case41)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case41, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case41, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case41, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case41, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case41, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case42)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case42, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case42, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case42, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case42, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case42, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case43)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case43, indices,   shape, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case43, indices_a, shape_a, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case43, indices_v, shape_v, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case43, indices_f, shape_f, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case43, indices_h, shape_h, slice0, slice1, slice2, slice3);
}

TEST_CASE("slice(case44)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case44, indices,   shape, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case44, indices_a, shape_a, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case44, indices_v, shape_v, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case44, indices_f, shape_f, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case44, indices_h, shape_h, slice0, slice1, slice2, slice3);

    // TODO: support raw array indices/shape
    // APPLY_SLICE_SUBCASE( case44, indices, shape, d_slices );
    APPLY_SLICE_SUBCASE( case44, indices_a, shape_a, d_slices );
    APPLY_SLICE_SUBCASE( case44, indices_v, shape_v, d_slices );
}

TEST_CASE("slice(case45)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case45, indices,   shape, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case45, indices_a, shape_a, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case45, indices_v, shape_v, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case45, indices_f, shape_f, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case45, indices_h, shape_h, slice0, slice1, slice2, slice3);

    // TODO: support raw array indices/shape
    // APPLY_SLICE_SUBCASE( case45, indices, shape, d_slices );
    APPLY_SLICE_SUBCASE( case45, indices_a, shape_a, d_slices );
    APPLY_SLICE_SUBCASE( case45, indices_v, shape_v, d_slices );
}

TEST_CASE("dynamic_slice(case1)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case1, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case2)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case2, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case3)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case3, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case4)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case4, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case5)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case5, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case6)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case6, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case7)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case7, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case8)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case8, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case9)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case9, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case10)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case10, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case11)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case11, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case12)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case12, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case13)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case13, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case14)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case14, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case15)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case15, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case16)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case16, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case17)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case17, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case18)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case18, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case19)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case19, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case20)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case20, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case21)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case21, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case22)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case22, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case23)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case23, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case24)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case24, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case25)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case25, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case26)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case26, indices, shape, slices );
}