#if __has_include(<boost/array.hpp>)
#define NMTOOLS_ENABLE_BOOST
#endif
#include "nmtools/array/view/flatten.hpp"
#include "nmtools/array/ndarray/ndarray.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

using nmtools::shape, nmtools::size;

using namespace nm::literals;
using nm::none_t;

TEST_CASE("is_fixed_shape" * doctest::test_suite("view"))
{
    SUBCASE("flatten")
    {
        {
            using array_t = int[2][3][2];
            using src_shape_t = decltype(shape<true>(meta::declval<array_t>()));
            using src_size_t  = decltype(size<true>(meta::declval<array_t>()));
            using indexer_t   = view::flatten_t<src_shape_t,src_size_t>;
            using view_t = view::decorator_t< view::indexing_t, array_t, indexer_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_t );
        }
        {
            using array_t = nmtools_array<int,3>;
            using src_shape_t = decltype(shape<true>(meta::declval<array_t>()));
            using src_size_t  = decltype(size<true>(meta::declval<array_t>()));
            using indexer_t   = view::flatten_t<src_shape_t,src_size_t>;
            using view_t = view::decorator_t< view::indexing_t, array_t, indexer_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_t );
        }
        {
            using array_t = na::fixed_ndarray<int,2,3,2>;
            using src_shape_t = decltype(shape<true>(meta::declval<array_t>()));
            using src_size_t  = decltype(size<true>(meta::declval<array_t>()));
            using indexer_t   = view::flatten_t<src_shape_t,src_size_t>;
            using view_t = view::decorator_t< view::indexing_t, array_t, indexer_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_t );
        }
        {
            using array_t = na::dynamic_ndarray<int>;
            using src_shape_t = decltype(shape<true>(meta::declval<array_t>()));
            using src_size_t  = decltype(size<true>(meta::declval<array_t>()));
            using indexer_t   = view::flatten_t<src_shape_t,src_size_t>;
            using view_t = view::decorator_t< view::indexing_t, array_t, indexer_t >;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_t );
        }
        {
            using array_t = na::hybrid_ndarray<int,12,3>;
            using src_shape_t = decltype(shape<true>(meta::declval<array_t>()));
            using src_size_t  = decltype(size<true>(meta::declval<array_t>()));
            using indexer_t   = view::flatten_t<src_shape_t,src_size_t>;
            using view_t = view::decorator_t< view::indexing_t, array_t, indexer_t >;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_t );
        }
    }
}

TEST_CASE("is_fixed_dim_ndarray" * doctest::test_suite("view"))
{
    SUBCASE("flatten")
    {
        {
            using array_t = int[2][3][2];
            using src_shape_t = decltype(shape<true>(meta::declval<array_t>()));
            using src_size_t  = decltype(size<true>(meta::declval<array_t>()));
            using indexer_t   = view::flatten_t<src_shape_t,src_size_t>;
            using view_t = view::decorator_t< view::indexing_t, array_t, indexer_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }
        {
            using array_t = nmtools_array<int,3>;
            using src_shape_t = decltype(shape<true>(meta::declval<array_t>()));
            using src_size_t  = decltype(size<true>(meta::declval<array_t>()));
            using indexer_t   = view::flatten_t<src_shape_t,src_size_t>;
            using view_t = view::decorator_t< view::indexing_t, array_t, indexer_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }
        {
            using array_t = na::fixed_ndarray<int,2,3,2>;
            using src_shape_t = decltype(shape<true>(meta::declval<array_t>()));
            using src_size_t  = decltype(size<true>(meta::declval<array_t>()));
            using indexer_t   = view::flatten_t<src_shape_t,src_size_t>;
            using view_t = view::decorator_t< view::indexing_t, array_t, indexer_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }
        {
            using array_t = na::hybrid_ndarray<int,12,3>;
            using src_shape_t = decltype(shape<true>(meta::declval<array_t>()));
            using src_size_t  = decltype(size<true>(meta::declval<array_t>()));
            using indexer_t   = view::flatten_t<src_shape_t,src_size_t>;
            using view_t = view::decorator_t< view::indexing_t, array_t, indexer_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }
        {
            using array_t = na::dynamic_ndarray<int>;
            using src_shape_t = decltype(shape<true>(meta::declval<array_t>()));
            using src_size_t  = decltype(size<true>(meta::declval<array_t>()));
            using indexer_t   = view::flatten_t<src_shape_t,src_size_t>;
            using view_t = view::decorator_t< view::indexing_t, array_t, indexer_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }
    }
}

TEST_CASE("flatten(case1)" * doctest::test_suite("meta::flatten"))
{
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = nmtools_array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using array_t     = array_type;
        using src_shape_t = decltype(shape<true>(meta::declval<array_t>()));
        using src_size_t  = decltype(size<true>(meta::declval<array_t>()));
        using indexer_t   = view::flatten_t<src_shape_t,src_size_t>;
        using view_type   = view::decorator_t< view::indexing_t, array_t, indexer_t >;
        // fixed shape because buffer is fixed and dim exactly 1
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, nmtools_array{12});
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using array_t     = array_type;
        using src_shape_t = decltype(shape<true>(meta::declval<array_t>()));
        using src_size_t  = decltype(size<true>(meta::declval<array_t>()));
        using indexer_t   = view::flatten_t<src_shape_t,src_size_t>;
        using view_type   = view::decorator_t< view::indexing_t, array_t, indexer_t >;
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, nmtools_array{12});
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using array_t     = array_type;
        using src_shape_t = decltype(shape<true>(meta::declval<array_t>()));
        using src_size_t  = decltype(size<true>(meta::declval<array_t>()));
        using indexer_t   = view::flatten_t<src_shape_t,src_size_t>;
        using view_type   = view::decorator_t< view::indexing_t, array_t, indexer_t >;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        // Should be fixed size because shape is constant
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );
        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, nmtools_array{12});
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using array_t     = array_type;
        using src_shape_t = decltype(shape<true>(meta::declval<array_t>()));
        using src_size_t  = decltype(size<true>(meta::declval<array_t>()));
        using indexer_t   = view::flatten_t<src_shape_t,src_size_t>;
        using view_type   = view::decorator_t< view::indexing_t, array_t, indexer_t >;
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, nmtools_array{12});
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = na::static_vector<size_t,6>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using array_t     = array_type;
        using src_shape_t = decltype(shape<true>(meta::declval<array_t>()));
        using src_size_t  = decltype(size<true>(meta::declval<array_t>()));
        using indexer_t   = view::flatten_t<src_shape_t,src_size_t>;
        using view_type   = view::decorator_t< view::indexing_t, array_t, indexer_t >;
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, nmtools_array{12});
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = na::static_vector<float,12>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using array_t     = array_type;
        using src_shape_t = decltype(shape<true>(meta::declval<array_t>()));
        using src_size_t  = decltype(size<true>(meta::declval<array_t>()));
        using indexer_t   = view::flatten_t<src_shape_t,src_size_t>;
        using view_type   = view::decorator_t< view::indexing_t, array_t, indexer_t >;
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, nmtools_array{12});
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using array_t     = array_type;
        using src_shape_t = decltype(shape<true>(meta::declval<array_t>()));
        using src_size_t  = decltype(size<true>(meta::declval<array_t>()));
        using indexer_t   = view::flatten_t<src_shape_t,src_size_t>;
        using view_type   = view::decorator_t< view::indexing_t, array_t, indexer_t >;
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, nmtools_array{12});
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = na::static_vector<float,12>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using array_t     = array_type;
        using src_shape_t = decltype(shape<true>(meta::declval<array_t>()));
        using src_size_t  = decltype(size<true>(meta::declval<array_t>()));
        using indexer_t   = view::flatten_t<src_shape_t,src_size_t>;
        using view_type   = view::decorator_t< view::indexing_t, array_t, indexer_t >;
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, nmtools_array{12});
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using array_t     = array_type;
        using src_shape_t = decltype(shape<true>(meta::declval<array_t>()));
        using src_size_t  = decltype(size<true>(meta::declval<array_t>()));
        using indexer_t   = view::flatten_t<src_shape_t,src_size_t>;
        using view_type   = view::decorator_t< view::indexing_t, array_t, indexer_t >;
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, nmtools_array{12});
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
#ifdef NMTOOLS_ENABLE_BOOST
    {
        using buffer_type = boost::array<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using array_t     = array_type;
        using src_shape_t = decltype(shape<true>(meta::declval<array_t>()));
        using src_size_t  = decltype(size<true>(meta::declval<array_t>()));
        using indexer_t   = view::flatten_t<src_shape_t,src_size_t>;
        using view_type   = view::decorator_t< view::indexing_t, array_t, indexer_t >;
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, nmtools_array{12});
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = boost::container::static_vector<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using array_t     = array_type;
        using src_shape_t = decltype(shape<true>(meta::declval<array_t>()));
        using src_size_t  = decltype(size<true>(meta::declval<array_t>()));
        using indexer_t   = view::flatten_t<src_shape_t,src_size_t>;
        using view_type   = view::decorator_t< view::indexing_t, array_t, indexer_t >;
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, nmtools_array{12});
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        // NOTE: boost small vector is unbounded
        using buffer_type = boost::container::small_vector<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using array_t     = array_type;
        using src_shape_t = decltype(shape<true>(meta::declval<array_t>()));
        using src_size_t  = decltype(size<true>(meta::declval<array_t>()));
        using indexer_t   = view::flatten_t<src_shape_t,src_size_t>;
        using view_type   = view::decorator_t< view::indexing_t, array_t, indexer_t >;
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, nmtools_array{12});
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = boost::container::vector<float>;
        using shape_type  = boost::container::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using array_t     = array_type;
        using src_shape_t = decltype(shape<true>(meta::declval<array_t>()));
        using src_size_t  = decltype(size<true>(meta::declval<array_t>()));
        using indexer_t   = view::flatten_t<src_shape_t,src_size_t>;
        using view_type   = view::decorator_t< view::indexing_t, array_t, indexer_t >;
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, nmtools_array{12});
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = boost::array<float,12>;
        using shape_type  = boost::container::small_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using array_t     = array_type;
        using src_shape_t = decltype(shape<true>(meta::declval<array_t>()));
        using src_size_t  = decltype(size<true>(meta::declval<array_t>()));
        using indexer_t   = view::flatten_t<src_shape_t,src_size_t>;
        using view_type   = view::decorator_t< view::indexing_t, array_t, indexer_t >;
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, nmtools_array{12});
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
#endif
}