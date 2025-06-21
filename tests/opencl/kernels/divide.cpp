#include "nmtools/evaluator/opencl/kernels/divide.hpp"
#ifndef NMTOOLS_OPENCL_BUILD_KERNELS
#include "nmtools/evaluator/opencl/context.hpp"
#include "nmtools/evaluator/opencl/evaluator.hpp"
#include "nmtools/array/arange.hpp"
#include "nmtools/array/ones.hpp"
#include "nmtools/array/ufuncs/divide.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace view = nm::view;
namespace meta = nm::meta;
namespace opencl = na::opencl;

#define OPENCL_TEST(fn,...) \
{ \
    auto expect = na::fn(__VA_ARGS__); \
    auto result = na::fn(__VA_ARGS__,opencl::default_context()); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

TEST_CASE("divide(case1)" * doctest::test_suite("opencl::divide"))
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

        auto result = view::divide(left_view,right_view);
        using element_t = meta::get_element_type_t<decltype(result)>;
        static_assert( meta::is_same_v<element_t,float> );
        static_assert( meta::is_ndarray_v<decltype(result)> );

        auto expect = na::divide(left,right);
        NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) );
        NMTOOLS_ASSERT_CLOSE( result, expect );
    }
    OPENCL_TEST(divide,left,right);
}

#endif