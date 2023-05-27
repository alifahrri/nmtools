#include "nmtools/array/eval/opencl/kernels/add.hpp"
#ifndef NMTOOLS_OPENCL_BUILD_KERNELS
#include "nmtools/array/eval/opencl/context.hpp"
#include "nmtools/array/eval/opencl/evaluator.hpp"
#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/array/ones.hpp"
#include "nmtools/array/array/ufuncs/add.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;
namespace opencl = na::opencl;

#define OPENCL_TEST(fn,...) \
{ \
    auto expect = na::fn(__VA_ARGS__); \
    auto result = na::fn(__VA_ARGS__,opencl::default_context()); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

TEST_CASE("add(case1)" * doctest::test_suite("opencl::add"))
{
    auto left  = na::arange(1,2,0.0125);
    auto right = na::arange(1,2,0.0125);
    {
        auto left_ptr  = nm::data(left);
        auto right_ptr = nm::data(right);

        auto left_view  = view::ref(left_ptr,nm::size(left));
        auto right_view = view::ref(right_ptr,nm::size(right));

        static_assert( meta::is_ndarray_v<decltype(left_view)> );
        static_assert( meta::is_ndarray_v<decltype(right_view)> );

        auto result = view::add(left_view,right_view);
        using element_t = meta::get_element_type_t<decltype(result)>;
        static_assert( meta::is_same_v<element_t,float> );
        static_assert( meta::is_ndarray_v<decltype(result)> );

        auto expect = na::add(left,right);
        NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) );
        NMTOOLS_ASSERT_CLOSE( result, expect );
    }
    OPENCL_TEST(add,left,right);
}

#endif