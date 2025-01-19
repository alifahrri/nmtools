#if __has_include(<boost/array.hpp>)
#define NMTOOLS_ENABLE_BOOST
#endif
#include "nmtools/ndarray.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

using nm::none_t;
using namespace nm::literals;

#define declval(type) meta::declval<type>()

#ifdef NMTOOLS_DISABLE_STL
using meta::true_type, meta::false_type;
#else
using std::true_type, std::false_type;
#endif

// TODO: fix
TEST_CASE("is_fixed_shape" * doctest::test_suite("view::reduce") * doctest::may_fail())
{
    // reduce add, as needed by mean view
    // TODO: fix
    // {
    //     using op_t    = view::add_t<none_t, none_t, float>;
    //     using array_t = int[3][2];
    //     using axis_t  = decltype(0_ct);
    //     using view_t  = view::decorator_t<view::reduce_t, op_t, array_t, axis_t, none_t, false_type, none_t >;
    //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_t );
    // }
    // {
    //     using op_t    = view::add_t<none_t, none_t, float>;
    //     using array_t = na::fixed_ndarray<int,3,2>;
    //     using axis_t  = decltype(0_ct);
    //     using view_t  = view::decorator_t<view::reduce_t, op_t, array_t, axis_t, none_t, false_type, none_t >;
    //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_t );
    // }
    // TODO: fix
    // {
    //     using op_t    = view::add_t<none_t, none_t, float>;
    //     using array_t = nmtools_array<nmtools_array<int,2>,3>;
    //     using axis_t  = decltype(0_ct);
    //     using view_t  = view::decorator_t<view::reduce_t, op_t, array_t, axis_t, none_t, false_type, none_t >;
    //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_t );
    // }
    // {
    //     using op_t    = view::add_t<none_t, none_t, float>;
    //     using array_t = na::hybrid_ndarray<int,6,2>;
    //     using axis_t  = decltype(0_ct);
    //     using view_t  = view::decorator_t<view::reduce_t, op_t, array_t, axis_t, none_t, false_type, none_t >;
    //     NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_t );
    // }
    // {
    //     using op_t    = view::add_t<none_t, none_t, float>;
    //     using array_t = na::dynamic_ndarray<int>;
    //     using axis_t  = decltype(0_ct);
    //     using view_t  = view::decorator_t<view::reduce_t, op_t, array_t, axis_t, none_t, false_type, none_t >;
    //     NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_t );
    // }

    // keepdims
    {
        using op_t       = view::add_t<none_t, none_t, float>;
        using array_t    = int[3][2];
        using axis_t     = none_t;
        using dtype_t    = none_t;
        using keepdims_t = true_type;
        using view_t     = view::decorator_t<view::reduce_t, op_t, array_t, axis_t, dtype_t, keepdims_t, none_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_t );
    }
}

TEST_CASE("fixed_ndarray_shape" * doctest::test_suite("view::reduce"))
{
    // reduce add, as needed by mean view
    // TODO: fix
    // {
    //     using op_t    = view::add_t<none_t, none_t, float>;
    //     using array_t = int[3][2];
    //     using axis_t  = decltype(0_ct);
    //     using view_t  = view::decorator_t<view::reduce_t, op_t, array_t, axis_t, none_t, false_type, none_t >;
    //     constexpr auto shape = meta::fixed_shape_v<view_t>;
    //     constexpr auto expected = nmtools_array{2ul};
    //     NMTOOLS_STATIC_ASSERT_EQUAL( shape, expected );
    // }
    // {
    //     using op_t    = view::add_t<none_t, none_t, float>;
    //     using array_t = na::fixed_ndarray<int,3,2>;
    //     using axis_t  = decltype(0_ct);
    //     using view_t  = view::decorator_t<view::reduce_t, op_t, array_t, axis_t, none_t, false_type, none_t >;
    //     constexpr auto shape = meta::fixed_shape_v<view_t>;
    //     constexpr auto expected = nmtools_array{2ul};
    //     NMTOOLS_STATIC_ASSERT_EQUAL( shape, expected );
    // }
    // TODO: fix
    // {
    //     using op_t    = view::add_t<none_t, none_t, float>;
    //     using array_t = nmtools_array<nmtools_array<int,2>,3>;
    //     using axis_t  = decltype(0_ct);
    //     using view_t  = view::decorator_t<view::reduce_t, op_t, array_t, axis_t, none_t, false_type, none_t >;
    //     constexpr auto shape = meta::fixed_shape_v<view_t>;
    //     constexpr auto expected = nmtools_array{2ul};
    //     NMTOOLS_STATIC_ASSERT_EQUAL( shape, expected );
    // }
}

TEST_CASE("is_fixed_dim_ndarray" * doctest::test_suite("view::reduce"))
{
    // {
    //     using op_t    = view::add_t<none_t, none_t, float>;
    //     using array_t = int[3][2];
    //     using axis_t  = decltype(0_ct);
    //     using view_t  = view::decorator_t<view::reduce_t, op_t, array_t, axis_t, none_t, false_type, none_t >;
    //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
    // }
    // TODO: fix
    // {
    //     using op_t    = view::add_t<none_t, none_t, float>;
    //     using array_t = na::fixed_ndarray<int,3,2>;
    //     using axis_t  = decltype(0_ct);
    //     using view_t  = view::decorator_t<view::reduce_t, op_t, array_t, axis_t, none_t, false_type, none_t >;
    //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
    // }
    // {
    //     using op_t    = view::add_t<none_t, none_t, float>;
    //     using array_t = nmtools_array<nmtools_array<int,2>,3>;
    //     using axis_t  = decltype(0_ct);
    //     using view_t  = view::decorator_t<view::reduce_t, op_t, array_t, axis_t, none_t, false_type, none_t >;
    //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
    // }
    // {
    //     using op_t    = view::add_t<none_t, none_t, float>;
    //     using array_t = na::hybrid_ndarray<int,6,2>;
    //     using axis_t  = decltype(0_ct);
    //     using view_t  = view::decorator_t<view::reduce_t, op_t, array_t, axis_t, none_t, false_type, none_t >;
    //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
    // }
    // {
    //     using op_t    = view::add_t<none_t, none_t, float>;
    //     using array_t = na::dynamic_ndarray<int>;
    //     using axis_t  = decltype(0_ct);
    //     using view_t  = view::decorator_t<view::reduce_t, op_t, array_t, axis_t, none_t, false_type, none_t >;
    //     NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim_ndarray, view_t );
    // }
}

#if 1
// TODO: fix
TEST_CASE("reduce(case1)" * doctest::test_suite("meta::reduce") * doctest::may_fail())
{
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = nmtools_array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type = decltype(0_ct);
        using init_type = nm::none_t;
        using keepdims_type = decltype(nm::False);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(init_type),declval(keepdims_type)));
        
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{3,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 2);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 6);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 2);
            // reduction may change size but not maximum size
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type = decltype(0_ct);
        using init_type = nm::none_t;
        using keepdims_type = decltype(nm::False);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(init_type),declval(keepdims_type)));
        
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{3,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 2);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 6);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 2);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 6);
        }
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type = decltype(0_ct);
        using init_type = nm::none_t;
        using keepdims_type = decltype(nm::False);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(init_type),declval(keepdims_type)));
        
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{3,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 2);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 6);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 2);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 6);
        }
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type = decltype(0_ct);
        using init_type = nm::none_t;
        using keepdims_type = decltype(nm::False);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(init_type),declval(keepdims_type)));

        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{3,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 2);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 6);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 2);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type = decltype(0_ct);
        using init_type = nm::none_t;
        using keepdims_type = decltype(nm::False);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(init_type),declval(keepdims_type)));

        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{3,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 2);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 6);
            // TODO: fix bounded dim
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = na::static_vector<float,12>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type = decltype(0_ct);
        using init_type = nm::none_t;
        using keepdims_type = decltype(nm::False);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(init_type),declval(keepdims_type)));

        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{3,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 2);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 6);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 2);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 6);
        }
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type = decltype(0_ct);
        using init_type = nm::none_t;
        using keepdims_type = decltype(nm::False);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(init_type),declval(keepdims_type)));

        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{3,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 2);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 6);
            // TODO: fix bounded dim
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = na::static_vector<float,12>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type = decltype(0_ct);
        using init_type = nm::none_t;
        using keepdims_type = decltype(nm::False);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(init_type),declval(keepdims_type)));

        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{3,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 2);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 6);
            // TODO: fix bounded dim
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type = decltype(0_ct);
        using init_type = nm::none_t;
        using keepdims_type = decltype(nm::False);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(init_type),declval(keepdims_type)));

        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{3,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 2);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 6);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 2);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
#ifdef NMTOOLS_ENABLE_BOOST
    {
        using buffer_type = boost::array<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type = decltype(0_ct);
        using init_type = nm::none_t;
        using keepdims_type = decltype(nm::False);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(init_type),declval(keepdims_type)));

        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{3,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 2);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 6);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 2);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = boost::container::static_vector<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type = decltype(0_ct);
        using init_type = nm::none_t;
        using keepdims_type = decltype(nm::False);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(init_type),declval(keepdims_type)));

        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{3,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 2);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 6);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 2);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = boost::container::small_vector<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type = decltype(0_ct);
        using init_type = nm::none_t;
        using keepdims_type = decltype(nm::False);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(init_type),declval(keepdims_type)));

        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{3,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 2);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 6);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 2);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = boost::container::vector<float>;
        using shape_type  = boost::container::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type = decltype(0_ct);
        using init_type = nm::none_t;
        using keepdims_type = decltype(nm::False);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(init_type),declval(keepdims_type)));

        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{3,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 2);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 6);
            // TODO: fix bounded dim
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = boost::array<float,12>;
        using shape_type  = boost::container::small_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type = decltype(0_ct);
        using init_type = nm::none_t;
        using keepdims_type = decltype(nm::False);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(init_type),declval(keepdims_type)));

        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{3,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 2);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 6);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 2);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
#endif // NMTOOLS_ENABLE_BOOST
}
#endif

TEST_CASE("reduce(case2)" * doctest::test_suite("meta::reduce"))
{
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = nmtools_array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type = nm::none_t;
        using init_type = nm::none_t;
        using keepdims_type = decltype(nm::False);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(init_type),declval(keepdims_type)));
        
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, view_type );
        static_assert( !meta::is_ndarray_v<view_type> );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type = nm::none_t;
        using init_type = nm::none_t;
        using keepdims_type = decltype(nm::False);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(init_type),declval(keepdims_type)));
        
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, view_type );
        static_assert( !meta::is_ndarray_v<view_type> );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type = nm::none_t;
        using init_type = nm::none_t;
        using keepdims_type = decltype(nm::False);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(init_type),declval(keepdims_type)));
        
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type = nm::none_t;
        using init_type = nm::none_t;
        using keepdims_type = decltype(nm::False);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(init_type),declval(keepdims_type)));
        
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type = nm::none_t;
        using init_type = nm::none_t;
        using keepdims_type = decltype(nm::False);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(init_type),declval(keepdims_type)));
        
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );
    }
    {
        using buffer_type = na::static_vector<float,12>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type = nm::none_t;
        using init_type = nm::none_t;
        using keepdims_type = decltype(nm::False);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(init_type),declval(keepdims_type)));
        
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type = nm::none_t;
        using init_type = nm::none_t;
        using keepdims_type = decltype(nm::False);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(init_type),declval(keepdims_type)));
        
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );
    }
    {
        using buffer_type = na::static_vector<float,12>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type = nm::none_t;
        using init_type = nm::none_t;
        using keepdims_type = decltype(nm::False);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(init_type),declval(keepdims_type)));
        
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type = nm::none_t;
        using init_type = nm::none_t;
        using keepdims_type = decltype(nm::False);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(init_type),declval(keepdims_type)));
        
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );
    }
#ifdef NMTOOLS_ENABLE_BOOST
    {
        using buffer_type = boost::array<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type = nm::none_t;
        using init_type = nm::none_t;
        using keepdims_type = decltype(nm::False);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(init_type),declval(keepdims_type)));
        
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );
    }
    {
        using buffer_type = boost::container::static_vector<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type = nm::none_t;
        using init_type = nm::none_t;
        using keepdims_type = decltype(nm::False);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(init_type),declval(keepdims_type)));
        
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );
    }
    {
        using buffer_type = boost::container::small_vector<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type = nm::none_t;
        using init_type = nm::none_t;
        using keepdims_type = decltype(nm::False);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(init_type),declval(keepdims_type)));
        
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );
    }
    {
        using buffer_type = boost::container::vector<float>;
        using shape_type  = boost::container::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type = nm::none_t;
        using init_type = nm::none_t;
        using keepdims_type = decltype(nm::False);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(init_type),declval(keepdims_type)));
        
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );
    }
    {
        using buffer_type = boost::array<float,12>;
        using shape_type  = boost::container::small_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type = nm::none_t;
        using init_type = nm::none_t;
        using keepdims_type = decltype(nm::False);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(init_type),declval(keepdims_type)));
        
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );
    }
#endif // NMTOOLS_ENABLE_BOOST
}

// TODO: fix
TEST_CASE("reduce(case3)" * doctest::test_suite("meta::reduce") * doctest::may_fail())
{
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = nmtools_array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type  = nm::none_t;
        using init_type  = nm::none_t;
        using dtype_type = nm::none_t;
        using keepdims_type = decltype(nm::True);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(dtype_type),declval(init_type),declval(keepdims_type)));
        
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,1}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 1);
        }
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type  = nm::none_t;
        using init_type  = nm::none_t;
        using dtype_type = nm::none_t;
        using keepdims_type = decltype(nm::True);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(dtype_type),declval(init_type),declval(keepdims_type)));
        
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,1}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 1);
        }
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type  = nm::none_t;
        using init_type  = nm::none_t;
        using dtype_type = nm::none_t;
        using keepdims_type = decltype(nm::True);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(dtype_type),declval(init_type),declval(keepdims_type)));
        
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,1}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 1);
        }
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type  = nm::none_t;
        using init_type  = nm::none_t;
        using dtype_type = nm::none_t;
        using keepdims_type = decltype(nm::True);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(dtype_type),declval(init_type),declval(keepdims_type)));
        
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,1}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 1);
        }
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type  = nm::none_t;
        using init_type  = nm::none_t;
        using dtype_type = nm::none_t;
        using keepdims_type = decltype(nm::True);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(dtype_type),declval(init_type),declval(keepdims_type)));
        
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,1}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 1);
        }
    }
    {
        using buffer_type = na::static_vector<float,12>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type  = nm::none_t;
        using init_type  = nm::none_t;
        using dtype_type = nm::none_t;
        using keepdims_type = decltype(nm::True);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(dtype_type),declval(init_type),declval(keepdims_type)));
        
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,1}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 1);
        }
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type  = nm::none_t;
        using init_type  = nm::none_t;
        using dtype_type = nm::none_t;
        using keepdims_type = decltype(nm::True);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(dtype_type),declval(init_type),declval(keepdims_type)));
        
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,1}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 1);
        }
    }
    {
        using buffer_type = na::static_vector<float,12>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type  = nm::none_t;
        using init_type  = nm::none_t;
        using dtype_type = nm::none_t;
        using keepdims_type = decltype(nm::True);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(dtype_type),declval(init_type),declval(keepdims_type)));
        
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,1}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 1);
        }
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type  = nm::none_t;
        using init_type  = nm::none_t;
        using dtype_type = nm::none_t;
        using keepdims_type = decltype(nm::True);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(dtype_type),declval(init_type),declval(keepdims_type)));
        
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 1);
        }
    }
#ifdef NMTOOLS_ENABLE_BOOST
    {
        using buffer_type = boost::array<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type  = nm::none_t;
        using init_type  = nm::none_t;
        using dtype_type = nm::none_t;
        using keepdims_type = decltype(nm::True);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(dtype_type),declval(init_type),declval(keepdims_type)));

        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,1}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 1);
        }
    }
    {
        using buffer_type = boost::container::static_vector<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type  = nm::none_t;
        using init_type  = nm::none_t;
        using dtype_type = nm::none_t;
        using keepdims_type = decltype(nm::True);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(dtype_type),declval(init_type),declval(keepdims_type)));

        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,1}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 1);
        }
    }
    {
        using buffer_type = boost::container::small_vector<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type  = nm::none_t;
        using init_type  = nm::none_t;
        using dtype_type = nm::none_t;
        using keepdims_type = decltype(nm::True);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(dtype_type),declval(init_type),declval(keepdims_type)));

        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,1}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 1);
        }
    }
    {
        using buffer_type = boost::container::vector<float>;
        using shape_type  = boost::container::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type  = nm::none_t;
        using init_type  = nm::none_t;
        using dtype_type = nm::none_t;
        using keepdims_type = decltype(nm::True);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(dtype_type),declval(init_type),declval(keepdims_type)));

        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,1}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 1);
        }
    }
    {
        using buffer_type = boost::array<float,12>;
        using shape_type  = boost::container::small_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using axis_type  = nm::none_t;
        using init_type  = nm::none_t;
        using dtype_type = nm::none_t;
        using keepdims_type = decltype(nm::True);
        using view_type = decltype(view::reduce_add(declval(array_type),declval(axis_type),declval(dtype_type),declval(init_type),declval(keepdims_type)));

        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,1}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 1);
        }
    }
#endif // NMTOOLS_ENABLE_BOOST
}