#include "nmtools/meta.hpp"
#include "nmtools/meta/utl/array.hpp"
#include "nmtools/array/index/gather.hpp"
#include "nmtools/array/view/broadcast_to.hpp"
#include "nmtools/array/array/activations/relu.hpp"
#include "nmtools/array/array/ufuncs/add.hpp"
#include "nmtools/array/array/matmul.hpp"
#include "nmtools/utils/isequal.hpp"

#include <Arduino.h>
#include <unity.h>

namespace nm = nmtools;
namespace na = nm::array;
namespace ix = nm::index;
namespace utl = nm::utl;
namespace meta = nm::meta;
namespace view = nm::view;

using nm::utils::isequal;

#define NM_TEST_SUBCASE(case_name, subcase_name) \
void test_##case_name##_##subcase_name()

#define NM_RUN_SUBCASE(case_name, subcase_name) \
RUN_TEST(test_##case_name##_##subcase_name);

/* ================================================================= */

NM_TEST_SUBCASE(is_integer, case0)
{
    using arg_t = nm::uint32_t;
    TEST_ASSERT_TRUE( meta::is_integer_v<arg_t> );
}

NM_TEST_SUBCASE(is_num, case0)
{
    using arg_t = size_t;
    TEST_ASSERT_TRUE( meta::is_num_v<arg_t> );
}

NM_TEST_SUBCASE(fixed_ndarray_shape, case0)
{
    using arg_t = int[2][3][2];
    using result_t = decltype(meta::fixed_ndarray_shape_v<arg_t>);
    using expect_t = const utl::array<size_t,3>;
    TEST_ASSERT_TRUE( (meta::is_same_v<result_t,expect_t>) );
}

NM_TEST_SUBCASE(fixed_ndarray_shape, case1)
{
    using arg_t = utl::array<int,2>;
    using result_t = decltype(meta::fixed_ndarray_shape_v<arg_t>);
    using expect_t = const utl::array<size_t,1>;
    TEST_ASSERT_TRUE( (meta::is_same_v<result_t,expect_t>) );
}

NM_TEST_SUBCASE(fixed_size_ndarray, case0)
{
    using arg_t = int[2][3][2];
    TEST_ASSERT_TRUE( meta::is_fixed_size_ndarray_v<arg_t> );
}

NM_TEST_SUBCASE(fixed_size_ndarray, case1)
{
    using arg_t = utl::array<int,2>;
    TEST_ASSERT_TRUE( meta::is_fixed_size_ndarray_v<arg_t> );
}

NM_TEST_SUBCASE(fixed_size_ndarray, case2)
{
    using arg_t = utl::array<utl::array<int,3>,2>;
    TEST_ASSERT_TRUE( meta::is_fixed_size_ndarray_v<arg_t> );
}

NM_TEST_SUBCASE(fixed_dim_ndarray, case0)
{
    using arg_t = int[2][3][2];
    TEST_ASSERT_TRUE( meta::is_fixed_dim_ndarray_v<arg_t> );
}

NM_TEST_SUBCASE(fixed_index_array, case0)
{
    using arg_t = utl::array<int,3>;
    TEST_ASSERT_TRUE( meta::is_fixed_index_array_v<arg_t> );
}

NM_TEST_SUBCASE(fixed_index_array, case1)
{
    using arg_t = utl::tuple<int,int>;
    TEST_ASSERT_TRUE( meta::is_fixed_index_array_v<arg_t> );
}

NM_TEST_SUBCASE(fixed_index_array, case2)
{
    using arg_t = utl::tuple<meta::ct<1>,meta::ct<2>>;
    static_assert( meta::is_fixed_index_array_v<arg_t> );
    TEST_ASSERT_TRUE( meta::is_fixed_index_array_v<arg_t> );
}

NM_TEST_SUBCASE(fixed_dim, case1)
{
    using arg_t = int[2][3][2];
    TEST_ASSERT_TRUE( meta::fixed_dim_v<arg_t> == 3 );
}

NM_TEST_SUBCASE(constant_index_array, case1)
{
    using arg_t = utl::tuple<meta::ct<1>,meta::ct<2>>;
    static_assert( meta::is_constant_index_array_v<arg_t> );
    TEST_ASSERT_TRUE( meta::is_constant_index_array_v<arg_t> );
}

NM_TEST_SUBCASE(constant_index_array, case2)
{
    using arg_t = utl::tuple<meta::integral_constant<size_t,1>,meta::integral_constant<size_t,2>>;
    static_assert( meta::is_constant_index_array_v<arg_t> );
    TEST_ASSERT_TRUE( meta::is_constant_index_array_v<arg_t> );
}

NM_TEST_SUBCASE(resolve_gather, case1)
{
    using vector_t  = utl::array<size_t,2>;
    using indices_t = utl::array<int,2>;
    using result_t  = meta::resolve_optype_t<ix::gather_t,vector_t,indices_t>;
    using expect_t  = utl::array<size_t,2>;
    static_assert(( meta::is_fixed_index_array_v<vector_t> ));
    static_assert(( meta::is_fixed_index_array_v<indices_t> ));
    static_assert(( meta::is_fixed_size_ndarray_v<vector_t> ));
    static_assert(( meta::is_same_v<result_t,expect_t> ));
    TEST_ASSERT_TRUE(( meta::is_same_v<result_t,expect_t> ));
}

NM_TEST_SUBCASE(to_value, case1)
{
    using arg_t = utl::tuple<meta::ct<1>>;
    constexpr auto result = meta::to_value_v<arg_t>;
    constexpr auto expect = utl::array{1ul};
    TEST_ASSERT_TRUE( (isequal(result,expect)) );
}

NM_TEST_SUBCASE(append_type, case1)
{
    using tuple  = utl::tuple<size_t>;
    using result = meta::append_type_t<tuple,int>;
    using expected = utl::tuple<size_t,int>;
    static_assert( meta::is_same_v<result,expected> );
    TEST_ASSERT_TRUE( (meta::is_same_v<result,expected>) );
}

NM_TEST_SUBCASE(transform_bounded_array, case1)
{
    {
        using array_t = int[2][3][2];
        using result_t = meta::transform_bounded_array_t<array_t>;
        using expect_t = utl::array<utl::array<utl::array<int,2>,3>,2>;
        TEST_ASSERT_TRUE(( meta::is_same_v<result_t,expect_t> ));
    }
}

NM_TEST_SUBCASE(resize_fixed_ndarray, case1)
{
    {
        using array_t = utl::array<int,3>;
        using ref_type = int[2][3][2];
        using result_t = meta::resize_fixed_ndarray_t<array_t,ref_type>;
        using expect_t = utl::array<utl::array<utl::array<int,2>,3>,2>;
        TEST_ASSERT_TRUE(( meta::is_same_v<result_t,expect_t> ));
    }
}

NM_TEST_SUBCASE(replace_element_type, case1)
{
    {
        using array_t = utl::array<utl::array<utl::array<int,2>,3>,2>;
        using result_t = meta::replace_element_type_t<array_t,float>;
        using expect_t = utl::array<utl::array<utl::array<float,2>,3>,2>;
        TEST_ASSERT_TRUE(( meta::is_same_v<result_t,expect_t> ));
    }
}

#define declval(T) meta::declval<T>()

NM_TEST_SUBCASE(broadcast_to, case1)
{
    {
        using array_t = int[10];
        using shape_t = utl::tuple<meta::ct<10>>;
        using broadcasted_t = decltype(view::broadcast_to(declval(array_t),declval(shape_t)));
        static_assert( meta::is_ndarray_v<broadcasted_t> );
        static_assert( meta::is_view_v<broadcasted_t> );
        TEST_ASSERT_TRUE( meta::is_ndarray_v<broadcasted_t> );
        TEST_ASSERT_TRUE( meta::is_view_v<broadcasted_t> );
    }
    {
        using array_t = int[10];
        using shape_t = utl::tuple<meta::ct<1ul>,meta::ct<10ul>>;
        using broadcasted_t = decltype(view::broadcast_to(declval(array_t),declval(shape_t)));
        static_assert( meta::is_ndarray_v<broadcasted_t> );
        static_assert( meta::is_view_v<broadcasted_t> );
        TEST_ASSERT_TRUE( meta::is_ndarray_v<broadcasted_t> );
        TEST_ASSERT_TRUE( meta::is_view_v<broadcasted_t> );
    }
}

NM_TEST_SUBCASE(ufuncs, case1)
{
    // unary ufunc
    {
        using arg_t = utl::array<int8_t,3>;
        using ufunc_t = decltype(view::relu(declval(arg_t)));
        using operands_t = typename ufunc_t::operands_type;
        static_assert( meta::is_same_v<operands_t,utl::tuple<const arg_t*>> );
        TEST_ASSERT_TRUE(( meta::is_same_v<operands_t,utl::tuple<const arg_t*>> ));
    }
}

NM_TEST_SUBCASE(ufuncs, case2)
{
    // binary ufunc
    {
        using lhs_t = int[2][3][2];
        using rhs_t = int;
        using view_t = decltype(view::add(declval(lhs_t),declval(rhs_t)));
        using result_t = meta::get_element_type_t<view_t>;
        using expect_t = int;
        constexpr auto shape  = meta::fixed_shape_v<view_t>;
        constexpr auto expect = utl::array{2,3,2};
        TEST_ASSERT_TRUE(( isequal(shape,expect) ));
        // to allow debugging type
        constexpr auto is_same = meta::is_same<result_t,expect_t>{};
        TEST_ASSERT_TRUE(( is_same.value ));
    }
}

NM_TEST_SUBCASE(ufuncs, case3)
{
    {
        using array_t = int[2][3][2];
        using axis_t  = int;
        using view_t  = decltype(view::reduce_add(declval(array_t),declval(axis_t)));
        TEST_ASSERT_TRUE((  meta::is_hybrid_ndarray_v<view_t> ));
        TEST_ASSERT_TRUE(( !meta::is_dynamic_ndarray_v<view_t> ));
        TEST_ASSERT_TRUE(( !meta::is_fixed_size_ndarray_v<view_t> ));
        TEST_ASSERT_TRUE((  meta::is_fixed_size_ndarray_v<array_t> ));
    }
}

NM_TEST_SUBCASE(shape_matmul, case1)
{
    {
        using lhs_t = int[2];
        using rhs_t = int[2];
        using result_t = meta::resolve_optype_t<nmtools::index::shape_matmul_t,lhs_t,rhs_t>;
        using expect_t = utl::array<int,2>;
        // to allow debugging type
        constexpr auto is_same = meta::is_same<result_t,expect_t>{};
        TEST_ASSERT_TRUE(( is_same.value ));
        static_assert( meta::is_fixed_index_array_v<lhs_t> );
        static_assert( meta::is_fixed_index_array_v<rhs_t> );
    }
}

NM_TEST_SUBCASE(eval, case6)
{
    {
        using lhs_t = int[2][3][2];
        using rhs_t = int;
        using view_t = decltype(view::add(declval(lhs_t),declval(rhs_t)));
        using result_t = meta::resolve_optype_t<na::eval_result_t,view_t,nm::none_t>;
        using expect_t = utl::array<utl::array<utl::array<int,2>,3>,2>;
        // to allow debugging type
        constexpr auto is_same = meta::is_same<result_t,expect_t>{};
        TEST_ASSERT_TRUE(( is_same.value ));
    }
}

NM_TEST_SUBCASE(eval, case7)
{
    {
        using array_t = int[2][3][2];
        using axis_t  = int;
        using view_t  = decltype(view::reduce_add(declval(array_t),declval(axis_t)));
        using result_t = meta::resolve_optype_t<na::eval_result_t,view_t,nm::none_t>;
        // using expect_t = na::hybrid_ndarray<int,2*3*2,2>;
        using expect_t = meta::make_hybrid_ndarray_t<int,2*3*2,2>;
        // to allow debugging type
        constexpr auto is_same = meta::is_same<result_t,expect_t>{};
        TEST_ASSERT_TRUE(( is_same.value ));
    }
}

/* ================================================================= */

#ifndef LED_BUILTIN
#define LED_BUILTIN PC13
#endif

void setup()
{
    // initialize LED digital pin as an output.
    pinMode(LED_BUILTIN, OUTPUT);

    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(1000);

    UNITY_BEGIN();    // IMPORTANT LINE!

    NM_RUN_SUBCASE(is_integer, case0);
    NM_RUN_SUBCASE(is_num, case0);

    NM_RUN_SUBCASE(fixed_ndarray_shape, case0);
    NM_RUN_SUBCASE(fixed_ndarray_shape, case1);

    NM_RUN_SUBCASE(fixed_size_ndarray, case0);
    NM_RUN_SUBCASE(fixed_size_ndarray, case1);
    NM_RUN_SUBCASE(fixed_size_ndarray, case2);

    NM_RUN_SUBCASE(fixed_dim_ndarray, case0);

    NM_RUN_SUBCASE(fixed_index_array, case0);
    NM_RUN_SUBCASE(fixed_index_array, case1);
    NM_RUN_SUBCASE(fixed_index_array, case2);

    NM_RUN_SUBCASE(fixed_dim, case1);

    NM_RUN_SUBCASE(transform_bounded_array, case1);

    NM_RUN_SUBCASE(resize_fixed_ndarray, case1);
    NM_RUN_SUBCASE(replace_element_type, case1);

    NM_RUN_SUBCASE(broadcast_to, case1);

    NM_RUN_SUBCASE(ufuncs, case1);
    NM_RUN_SUBCASE(ufuncs, case2);
    NM_RUN_SUBCASE(ufuncs, case3);

    NM_RUN_SUBCASE(shape_matmul, case1);

    NM_RUN_SUBCASE(eval, case6);
    NM_RUN_SUBCASE(eval, case7);

    UNITY_END();
}

void loop()
{
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
}