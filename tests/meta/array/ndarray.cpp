#include "nmtools/array/ndarray/ndarray.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace ix = nm::index;
namespace meta = nm::meta;

namespace case1
{
    using T = float;
    using index_t = size_t;

    constexpr auto numel = 12;
    template <typename value_t>
    using buffer_t = nmtools_array<value_t,numel>;

    constexpr auto dim = 3;
    template <typename...>
    using shape_buffer_t = nmtools_array<index_t,dim>;
} // namespace case1

using namespace nm::literals;

namespace case2
{
    using T = float;
    using index_t = size_t;

    constexpr auto numel = 12;
    template <typename value_t>
    using buffer_t = nmtools_array<value_t,numel>;

    template <typename...>
    using shape_buffer_t = decltype(nmtools_tuple{2_ct,3_ct,2_ct});

    template <typename...>
    using stride_buffer_t = meta::resolve_optype_t<ix::compute_strides_t,shape_buffer_t<>>;
} // namespace case2

namespace case3
{
    using T = float;
    using index_t = size_t;

    template <typename value_t>
    using buffer_t = nmtools_list<value_t>;

    template <typename...>
    using shape_buffer_t = decltype(nmtools_tuple{2_ct,3_ct,2_ct});

    template <typename...>
    using stride_buffer_t = meta::resolve_optype_t<ix::compute_strides_t,shape_buffer_t<>>;
} // namespace case3

namespace case4
{
    using T = float;
    using index_t = size_t;

    constexpr auto numel = 12;
    template <typename value_t>
    using buffer_t = nmtools_array<value_t,numel>;

    template <typename...>
    using shape_buffer_t = nmtools_list<index_t>;
} // namespace case4

// hybrid-shape fixed-buffer
namespace case5
{
    using T = float;
    using index_t = size_t;

    constexpr auto numel = 12;
    template <typename value_t>
    using buffer_t = nmtools_array<value_t,numel>;

    constexpr auto bounded_dim = 6;
    template <typename...>
    using shape_buffer_t = na::hybrid_ndarray<index_t,bounded_dim,1>;
} // namespace case5

// fixed-shape hybrid-buffer
namespace case6
{
    using T = float;
    using index_t = size_t;

    constexpr auto max_numel = 12;
    template <typename value_t>
    using buffer_t = na::hybrid_ndarray<index_t,max_numel,1>;

    template <typename...>
    using shape_buffer_t = decltype(nmtools_tuple{2_ct,3_ct,2_ct});

    template <typename...>
    using stride_buffer_t = meta::resolve_optype_t<ix::compute_strides_t,shape_buffer_t<>>;
} // namespace case6

// hybrid-shape dynamic-buffer
namespace case7
{
    using T = float;
    using index_t = size_t;

    template <typename value_t>
    using buffer_t = nmtools_list<value_t>;

    constexpr auto bounded_dim = 3;
    template <typename...>
    using shape_buffer_t = na::hybrid_ndarray<index_t,bounded_dim,1>;
} // namespace case7

// hybrid-shape hybrid-buffer
namespace case8
{
    using T = float;
    using index_t = size_t;

    constexpr auto max_numel = 12;
    template <typename value_t>
    using buffer_t = na::hybrid_ndarray<value_t,max_numel,1>;

    constexpr auto bounded_dim = 3;
    template <typename...>
    using shape_buffer_t = na::hybrid_ndarray<index_t,bounded_dim,1>;
} // namespace case8

// dynamic-shape dynamic-buffer
namespace case9
{
    using T = float;
    using index_t = size_t;

    template <typename value_t>
    using buffer_t = nmtools_list<value_t>;

    template <typename...>
    using shape_buffer_t = nmtools_list<index_t>;
} // namespace case9

TEST_CASE("is_fixed_shape(case1)" * doctest::test_suite("meta::ndarray"))
{
    {
        using namespace case1;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, array_type );
    }
    {
        using namespace case2;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, array_type );
    }
    {
        using namespace case3;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, array_type );
    }
    {
        using namespace case4;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, array_type );
    }
    {
        using namespace case5;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, array_type );
    }
    {
        using namespace case6;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, array_type );
    }
    {
        using namespace case7;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, array_type );
    }
    {
        using namespace case8;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, array_type );
    }
    {
        using namespace case9;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, array_type );
    }
}

TEST_CASE("is_fixed_size(case1)" * doctest::test_suite("meta::ndarray"))
{
    {
        // this is fixed size because buffer is fixed size
        using namespace case1;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, array_type );
    }
    {
        // this is fixed size because buffer is fixed size
        using namespace case2;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, array_type );
    }
    {
        // this is fixed size because shape is constant index array
        using namespace case3;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, array_type );
    }
    {
        // this is fixed size because buffer is fixed size
        using namespace case4;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, array_type );
    }
    {
        // this is fixed size because buffer is fixed size
        using namespace case5;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, array_type );
    }
    {
        // this is fixed size because shape is constant index array
        using namespace case6;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, array_type );
    }
    {
        using namespace case7;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, array_type );
    }
    {
        using namespace case8;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, array_type );
    }
    {
        using namespace case9;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, array_type );
    }
}

TEST_CASE("is_fixed_dim(case1)" * doctest::test_suite("meta::ndarray"))
{
    {
        using namespace case1;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, array_type );
    }
    {
        using namespace case2;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, array_type );
    }
    {
        using namespace case3;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, array_type );
    }
    {
        using namespace case4;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, array_type );
    }
    {
        using namespace case5;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, array_type );
    }
    {
        using namespace case6;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, array_type );
    }
    {
        using namespace case7;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, array_type );
    }
    {
        using namespace case8;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, array_type );
    }
    {
        using namespace case9;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, array_type );
    }
}

TEST_CASE("is_bounded_dim(case1)" * doctest::test_suite("meta::ndarray"))
{
    {
        using namespace case1;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, array_type );
    }
    {
        using namespace case2;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, array_type );
    }
    {
        using namespace case3;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, array_type );
    }
    {
        using namespace case4;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, array_type );
    }
    {
        using namespace case5;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, array_type );
    }
    {
        using namespace case6;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, array_type );
    }
    {
        using namespace case7;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, array_type );
    }
    {
        using namespace case8;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, array_type );
    }
    {
        using namespace case9;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, array_type );
    }
}

TEST_CASE("is_bounded_size(case1)" * doctest::test_suite("meta::ndarray"))
{
    {
        using namespace case1;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, array_type );
    }
    {
        using namespace case2;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, array_type );
    }
    {
        using namespace case3;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, array_type );
    }
    {
        // has max size because buffer has fixed size
        using namespace case4;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, array_type );
    }
    {
        // has max size because buffer has fixed size
        using namespace case5;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, array_type );
    }
    {
        // has max size because shape has fixed size
        using namespace case6;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, array_type );
    }
    {
        // doesn't have max size because buffer is dynamic and shape is hybrid
        using namespace case7;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, array_type );
    }
    {
        // has max size because buffer has max size
        using namespace case8;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, array_type );
    }
    {
        using namespace case9;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, array_type );
    }
}

TEST_CASE("resize_shape(case1)" * doctest::test_suite("meta::ndarray"))
{
    {
        using namespace case1;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        using result_t   = meta::resize_shape_t<array_type,meta::as_type<2,3,2>>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, result_t );
    }
    {
        using namespace case2;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        using result_t   = meta::resize_shape_t<array_type,meta::as_type<12>>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, result_t );
    }
    {
        using namespace case3;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        using result_t   = meta::resize_shape_t<array_type,meta::as_type<12>>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, result_t );
    }
    {
        using namespace case4;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        using result_t   = meta::resize_shape_t<array_type,meta::as_type<2,3,2>>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, result_t );
    }
    {
        using namespace case5;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        using result_t   = meta::resize_shape_t<array_type,meta::as_type<2,3,2>>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, result_t );
    }
    {
        using namespace case6;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        using result_t   = meta::resize_shape_t<array_type,meta::as_type<12>>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, result_t );
    }
    {
        using namespace case7;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        using result_t   = meta::resize_shape_t<array_type,meta::as_type<12>>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, result_t );
    }
    {
        using namespace case8;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        using result_t   = meta::resize_shape_t<array_type,meta::as_type<12>>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, result_t );
    }
    {
        using namespace case9;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        using result_t   = meta::resize_shape_t<array_type,meta::as_type<12>>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, result_t );
    }
}

TEST_CASE("resize_dim(case1)" * doctest::test_suite("meta::ndarray"))
{
    {
        using namespace case1;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        using result_t   = meta::resize_dim_t<array_type,4>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, result_t );
    }
    {
        using namespace case2;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        using result_t   = meta::resize_dim_t<array_type,4>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, result_t );
    }
    {
        using namespace case3;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        using result_t   = meta::resize_dim_t<array_type,4>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, result_t );
    }
    {
        using namespace case4;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        using result_t   = meta::resize_dim_t<array_type,4>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, result_t );
    }
    {
        using namespace case5;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        using result_t   = meta::resize_dim_t<array_type,4>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, result_t );
    }
    {
        using namespace case6;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        using result_t   = meta::resize_dim_t<array_type,4>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, result_t );
    }
    {
        using namespace case7;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        using result_t   = meta::resize_dim_t<array_type,4>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, result_t );
    }
    {
        using namespace case8;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        using result_t   = meta::resize_dim_t<array_type,4>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, result_t );
    }
    {
        using namespace case9;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        using result_t   = meta::resize_dim_t<array_type,4>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, result_t );
    }
}

TEST_CASE("resize_size(case1)" * doctest::test_suite("meta::ndarray"))
{
    {
        using namespace case1;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        using result_t   = meta::resize_size_t<array_type,4>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, result_t );
    }
    {
        using namespace case2;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        using result_t   = meta::resize_size_t<array_type,4>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, result_t );
    }
    {
        using namespace case3;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        using result_t   = meta::resize_size_t<array_type,4>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, result_t );
    }
    {
        using namespace case4;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        using result_t   = meta::resize_size_t<array_type,4>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, result_t );
    }
    {
        using namespace case5;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        using result_t   = meta::resize_size_t<array_type,4>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, result_t );
    }
    {
        using namespace case6;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        using result_t   = meta::resize_size_t<array_type,4>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, result_t );
    }
    {
        using namespace case7;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        using result_t   = meta::resize_size_t<array_type,4>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, result_t );
    }
    {
        using namespace case8;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        using result_t   = meta::resize_size_t<array_type,4>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, result_t );
    }
    {
        using namespace case9;
        using array_type = na::ndarray_t<T,index_t,buffer_t,shape_buffer_t>;
        using result_t   = meta::resize_size_t<array_type,4>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, result_t );
    }
}