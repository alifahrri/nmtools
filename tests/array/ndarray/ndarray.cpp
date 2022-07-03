#if __has_include(<boost/array.hpp>)
#include "nmtools/array/impl/boost.hpp"
#endif

#include "nmtools/array/ndarray/ndarray.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/index/ndindex.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace ix = nm::index;
namespace meta = nm::meta;

// fixed-dim, fixed-buffer
namespace case1
{
    using T = float;
    using index_t = size_t;

    constexpr auto numel = 12;
    using buffer_t = nmtools_array<T,numel>;

    constexpr auto dim = 3;
    using shape_buffer_t = nmtools_array<index_t,dim>;
} // namespace case1

using namespace nm::literals;

// fixed-shape fixed-buffer
namespace case2
{
    using T = float;
    using index_t = size_t;

    constexpr auto numel = 12;
    using buffer_t = nmtools_array<T,numel>;

    using shape_buffer_t = decltype(nmtools_tuple{2_ct,3_ct,2_ct});

    template <typename...>
    using stride_buffer_t = meta::resolve_optype_t<ix::compute_strides_t,shape_buffer_t>;
} // namespace case2

// fixed-shape dynamic-buffer
namespace case3
{
    using T = float;
    using index_t = size_t;

    using buffer_t = nmtools_list<T>;

    using shape_buffer_t = decltype(nmtools_tuple{2_ct,3_ct,2_ct});

    template <typename...>
    using stride_buffer_t = meta::resolve_optype_t<ix::compute_strides_t,shape_buffer_t>;
} // namespace case3

// dynamic-shape fixed-buffer
namespace case4
{
    using T = float;
    using index_t = size_t;

    constexpr auto numel = 12;
    using buffer_t = nmtools_array<T,numel>;

    using shape_buffer_t = nmtools_list<index_t>;
} // namespace case4

// hybrid-shape fixed-buffer
namespace case5
{
    using T = float;
    using index_t = size_t;

    constexpr auto numel = 12;
    using buffer_t = nmtools_array<T,numel>;

    constexpr auto bounded_dim = 6;
    using shape_buffer_t = na::hybrid_ndarray<index_t,bounded_dim,1>;
} // namespace case5

// fixed-shape hybrid-buffer
namespace case6
{
    using T = float;
    using index_t = size_t;

    constexpr auto max_numel = 12;
    using buffer_t = na::hybrid_ndarray<T,max_numel,1>;

    using shape_buffer_t = decltype(nmtools_tuple{2_ct,3_ct,2_ct});

    template <typename...>
    using stride_buffer_t = meta::resolve_optype_t<ix::compute_strides_t,shape_buffer_t>;
} // namespace case6

// hybrid-shape dynamic-buffer
namespace case7
{
    using T = float;
    using index_t = size_t;

    using buffer_t = nmtools_list<T>;

    constexpr auto bounded_dim = 3;
    using shape_buffer_t = na::hybrid_ndarray<index_t,bounded_dim,1>;
} // namespace case7

// hybrid-shape hybrid-buffer
namespace case8
{
    using T = float;
    using index_t = size_t;

    constexpr auto max_numel = 12;
    using buffer_t = na::hybrid_ndarray<T,max_numel,1>;

    constexpr auto bounded_dim = 3;
    using shape_buffer_t = na::hybrid_ndarray<index_t,bounded_dim,1>;
} // namespace case8

// dynamic-shape dynamic-buffer
namespace case9
{
    using T = float;
    using index_t = size_t;

    using buffer_t = nmtools_list<T>;

    using shape_buffer_t = nmtools_list<index_t>;
} // namespace case9

// TODO: add partial shape


TEST_CASE("ndarray(case1)" * doctest::test_suite("array::ndarray"))
{
    using namespace case1;
    using ndarray = na::ndarray_t<buffer_t,shape_buffer_t>;

    auto array = ndarray{};

    NMTOOLS_ASSERT_EQUAL( meta::has_shape_v<decltype(array)>, true );
    NMTOOLS_REQUIRE_EQUAL( array.dim(), 3 );
    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{1,1,12}) );
    NMTOOLS_REQUIRE_EQUAL( array.size(), 12 );
    NMTOOLS_REQUIRE_EQUAL( array.strides(), (nmtools_array{12,12,1}));
    NMTOOLS_REQUIRE_EQUAL( nm::dim(array), 3 );
    NMTOOLS_REQUIRE_EQUAL( nm::shape(array), (nmtools_array{1,1,12}) );

    auto success = array.resize(2,3,2);
    NMTOOLS_REQUIRE_EQUAL( success, true );
    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{2,3,2}) );
    NMTOOLS_REQUIRE_EQUAL( array.size(), 12 );
    NMTOOLS_REQUIRE_EQUAL( array.strides(), (nmtools_array{6,2,1}));

    {
        auto ndindex = ix::ndindex(array.shape());
        for (size_t i=0; i<ndindex.size(); i++) {
            nm::apply_at(array,ndindex[i]) = i;
        }
        int expect[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_ASSERT_CLOSE( array,  expect );
    }

    {
        constexpr auto array = ndarray{};
        NMTOOLS_REQUIRE_EQUAL( array.dim(), 3 );
        NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{1,1,12}) );
        NMTOOLS_REQUIRE_EQUAL( array.size(), 12 );
        NMTOOLS_REQUIRE_EQUAL( array.strides(), (nmtools_array{12,12,1}));
    }
}

TEST_CASE("ndarray(case2)" * doctest::test_suite("array::ndarray"))
{
    using namespace case2;
    using ndarray = na::ndarray_t<buffer_t,shape_buffer_t>;

    {
        auto array = ndarray{};
        NMTOOLS_REQUIRE_EQUAL( array.dim(), 3 );
        NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{2,3,2}) );
        NMTOOLS_REQUIRE_EQUAL( array.size(), 12 );
        NMTOOLS_REQUIRE_EQUAL( array.strides(), (nmtools_array{6,2,1}));
    }
    {
        auto array = ndarray{};
        auto ndindex = ix::ndindex(array.shape());
        for (size_t i=0; i<ndindex.size(); i++) {
            nm::apply_at(array,ndindex[i]) = i;
        }
        int expect[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_ASSERT_CLOSE( array,  expect );
    }
    {
        constexpr auto array = ndarray{};
        NMTOOLS_REQUIRE_EQUAL( array.dim(), 3 );
        NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{2,3,2}) );
        NMTOOLS_REQUIRE_EQUAL( array.size(), 12 );
    }
}

TEST_CASE("ndarray(case3)" * doctest::test_suite("array::ndarray"))
{
    using namespace case3;
    using ndarray = na::ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t>;

    auto array = ndarray{};
    NMTOOLS_REQUIRE_EQUAL( array.dim(), 3 );
    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{2,3,2}) );
    NMTOOLS_REQUIRE_EQUAL( array.size(), 12 );
    NMTOOLS_REQUIRE_EQUAL( array.strides(), (nmtools_array{6,2,1}));
    {
        auto ndindex = ix::ndindex(array.shape());
        for (size_t i=0; i<ndindex.size(); i++) {
            nm::apply_at(array,ndindex[i]) = i;
        }
        int expect[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_ASSERT_CLOSE( array,  expect );
    }
}

TEST_CASE("ndarray(case4)" * doctest::test_suite("array::ndarray"))
{
    using namespace case4;
    using ndarray = na::ndarray_t<buffer_t,shape_buffer_t>;

    {
        auto array = ndarray{};
        NMTOOLS_REQUIRE_EQUAL( array.dim(), 1 );
        NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{12}) );
        NMTOOLS_REQUIRE_EQUAL( array.size(), 12 );

        auto success = array.resize(2,3,2);
        NMTOOLS_REQUIRE_EQUAL( success, true );
        NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{2,3,2}) );
        NMTOOLS_REQUIRE_EQUAL( array.size(), 12 );

        {
            auto ndindex = ix::ndindex(array.shape());
            for (size_t i=0; i<ndindex.size(); i++) {
                nm::apply_at(array,ndindex[i]) = i;
            }
            int expect[2][3][2] = {
                {
                    {0,1},
                    {2,3},
                    {4,5},
                },
                {
                    { 6, 7},
                    { 8, 9},
                    {10,11},
                }
            };
            NMTOOLS_ASSERT_CLOSE( array,  expect );
        }
    }

    {
        auto array = ndarray{};
        auto success = array.resize(2,3,1);
        NMTOOLS_REQUIRE_EQUAL( success, false );
    }
}

TEST_CASE("ndarray(case5)" * doctest::test_suite("array::ndarray"))
{
    using namespace case5;
    using ndarray = na::ndarray_t<buffer_t,shape_buffer_t>;

    {
        auto array = ndarray {};

        NMTOOLS_REQUIRE_EQUAL( array.dim(), 1 );
        NMTOOLS_REQUIRE_EQUAL( array.shape(), nmtools_array{12} );
        NMTOOLS_REQUIRE_EQUAL( array.size(), 12 );

        auto success = array.resize(6,2);
        NMTOOLS_REQUIRE_EQUAL( success, true );
        NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{6,2}) );
        NMTOOLS_REQUIRE_EQUAL( array.size(), 12 );

        success = array.resize(2,3,2,1);
        NMTOOLS_REQUIRE_EQUAL( success, true );
        NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{2,3,2,1}) );
        NMTOOLS_REQUIRE_EQUAL( array.size(), 12 );
        
        auto ndindex = ix::ndindex(array.shape());
        for (size_t i=0; i<ndindex.size(); i++) {
            nm::apply_at(array,ndindex[i]) = i;
        }
        int expect[2][3][2][1] = {
            {
                {{0},{1}},
                {{2},{3}},
                {{4},{5}},
            },
            {
                {{ 6},{ 7}},
                {{ 8},{ 9}},
                {{10},{11}},
            }
        };
        NMTOOLS_ASSERT_CLOSE( array,  expect );

        success = array.resize(1,2,1,3,1,2,1);
        NMTOOLS_REQUIRE_EQUAL( success, false );

        success = array.resize(6,3);
        NMTOOLS_REQUIRE_EQUAL( success, false );
    }
}

TEST_CASE("ndarray(case6)" * doctest::test_suite("array::ndarray"))
{
    using namespace case6;
    using ndarray = na::ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t>;

    auto array = ndarray {};

    NMTOOLS_REQUIRE_EQUAL( array.dim(), 3 );
    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{2,3,2}) );
    NMTOOLS_REQUIRE_EQUAL( array.size(), 12 );
    NMTOOLS_REQUIRE_EQUAL( nm::dim(array), 3 );
    NMTOOLS_REQUIRE_EQUAL( nm::shape(array), (nmtools_array{2,3,2}) );

    {
        auto ndindex = ix::ndindex(array.shape());
        for (size_t i=0; i<ndindex.size(); i++) {
            nm::apply_at(array,ndindex[i]) = i;
        }
        int expect[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_ASSERT_CLOSE( array,  expect );
    }
}

TEST_CASE("ndarray(case7)" * doctest::test_suite("array::ndarray"))
{
    using namespace case7;
    using ndarray = na::ndarray_t<buffer_t,shape_buffer_t>;

    auto array = ndarray {};

    NMTOOLS_REQUIRE_EQUAL( array.dim(), 1 );
    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{1}) );
    NMTOOLS_REQUIRE_EQUAL( array.size(), 1 );

    auto success = array.resize(2,3,2);
    NMTOOLS_REQUIRE_EQUAL( success, true );
    NMTOOLS_REQUIRE_EQUAL( array.dim(), 3 );
    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{2,3,2}) );
    NMTOOLS_REQUIRE_EQUAL( array.size(), 12 );

    {
        auto ndindex = ix::ndindex(array.shape());
        for (size_t i=0; i<ndindex.size(); i++) {
            nm::apply_at(array,ndindex[i]) = i;
        }
        int expect[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_ASSERT_CLOSE( array,  expect );
    }

    success = array.resize(2,3,2,1);
    NMTOOLS_REQUIRE_EQUAL( success, false );
}

TEST_CASE("ndarray(case8)" * doctest::test_suite("array::ndarray"))
{
    using namespace case8;
    using ndarray = na::ndarray_t<buffer_t,shape_buffer_t>;

    auto array = ndarray {};

    NMTOOLS_REQUIRE_EQUAL( array.dim(), 1 );
    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{1}) );
    NMTOOLS_REQUIRE_EQUAL( array.size(), 1 );

    auto success = array.resize(2,3,2);
    NMTOOLS_REQUIRE_EQUAL( success, true );
    NMTOOLS_REQUIRE_EQUAL( array.dim(), 3 );
    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{2,3,2}) );
    NMTOOLS_REQUIRE_EQUAL( array.size(), 12 );
    NMTOOLS_REQUIRE_EQUAL( nm::dim(array), 3 );
    NMTOOLS_REQUIRE_EQUAL( nm::shape(array), (nmtools_array{2,3,2}) );

    {
        auto ndindex = ix::ndindex(array.shape());
        for (size_t i=0; i<ndindex.size(); i++) {
            nm::apply_at(array,ndindex[i]) = i;
        }
        int expect[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_ASSERT_CLOSE( array,  expect );
    }

    success = array.resize(2,3,2,1);
    NMTOOLS_REQUIRE_EQUAL( success, false );
}

TEST_CASE("ndarray(case9)" * doctest::test_suite("array::ndarray"))
{
    using namespace case9;
    using ndarray = na::ndarray_t<buffer_t,shape_buffer_t>;

    auto array = ndarray {};

    NMTOOLS_REQUIRE_EQUAL( array.dim(), 1 );
    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{1}) );
    NMTOOLS_REQUIRE_EQUAL( array.size(), 1 );

    auto success = array.resize(2,3,2);
    NMTOOLS_REQUIRE_EQUAL( success, true );
    NMTOOLS_REQUIRE_EQUAL( array.dim(), 3 );
    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{2,3,2}) );
    NMTOOLS_REQUIRE_EQUAL( array.size(), 12 );

    {
        auto ndindex = ix::ndindex(array.shape());
        for (size_t i=0; i<ndindex.size(); i++) {
            nm::apply_at(array,ndindex[i]) = i;
        }
        int expect[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_ASSERT_CLOSE( array,  expect );
    }

    success = array.resize(2,1,3,1,1,1);
    NMTOOLS_REQUIRE_EQUAL( success, true );
    NMTOOLS_REQUIRE_EQUAL( array.dim(), 6 );
    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{2,1,3,1,1,1}) );
    NMTOOLS_REQUIRE_EQUAL( array.size(), 6 );
}

using nmtools::array::column_major_offset_t;

// custom strides
namespace case10
{
    using T = float;
    using index_t = size_t;

    constexpr auto numel = 12;
    using buffer_t = nmtools_array<T,numel>;

    constexpr auto dim = 3;
    using shape_buffer_t = nmtools_array<index_t,dim>;

    template <typename...>
    using stride_buffer_t = shape_buffer_t;
} // namespace case1



TEST_CASE("ndarray(case10)" * doctest::test_suite("array::ndarray"))
{
    using namespace case10;
    using ndarray = na::ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,column_major_offset_t>;

    auto array = ndarray{};

    NMTOOLS_ASSERT_EQUAL( meta::has_shape_v<decltype(array)>, true );
    NMTOOLS_REQUIRE_EQUAL( array.dim(), 3 );
    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{1,1,12}) );
    NMTOOLS_REQUIRE_EQUAL( array.size(), 12 );
    NMTOOLS_REQUIRE_EQUAL( array.strides(), (nmtools_array{12,12,1}));
    NMTOOLS_REQUIRE_EQUAL( nm::dim(array), 3 );
    NMTOOLS_REQUIRE_EQUAL( nm::shape(array), (nmtools_array{1,1,12}) );

    auto success = array.resize(2,3,2);
    NMTOOLS_REQUIRE_EQUAL( success, true );
    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{2,3,2}) );
    NMTOOLS_REQUIRE_EQUAL( array.size(), 12 );
    NMTOOLS_REQUIRE_EQUAL( array.strides(), (nmtools_array{6,2,1}));

    {
        auto ndindex = ix::ndindex(array.shape());
        for (size_t i=0; i<ndindex.size(); i++) {
            nm::apply_at(array,ndindex[i]) = i;
        }
        int expect[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_ASSERT_CLOSE( array,  expect );
        {
            // NOTE: expect column major, the left most index is contiguous
            int expect[12] = {0,6,2,8,4,10,1,7,3,9,5,11};
            NMTOOLS_ASSERT_CLOSE( array.data_, expect );
        }
    }

    {
        constexpr auto array = ndarray{};
        NMTOOLS_REQUIRE_EQUAL( array.dim(), 3 );
        NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{1,1,12}) );
        NMTOOLS_REQUIRE_EQUAL( array.size(), 12 );
        NMTOOLS_REQUIRE_EQUAL( array.strides(), (nmtools_array{12,12,1}));
    }
}

#if __has_include(<boost/array.hpp>)
#include "nmtools/array/impl/boost.hpp"

// custom array type (boost)
namespace case11
{
    using T = float;
    using index_t = size_t;

    constexpr auto numel = 12;
    using buffer_t = ::boost::array<T,numel>;

    constexpr auto dim = 3;
    using shape_buffer_t = ::boost::array<index_t,dim>;

    static_assert( meta::is_index_array_v<shape_buffer_t> );

    template <typename...>
    using stride_buffer_t = shape_buffer_t;
} // namespace case1

TEST_CASE("ndarray(case11)" * doctest::test_suite("array::ndarray"))
{
    using namespace case11;
    using ndarray = na::ndarray_t<buffer_t,shape_buffer_t>;

    auto array = ndarray {};

    NMTOOLS_REQUIRE_EQUAL( array.dim(), 3 );
    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{1,1,12}) );
    NMTOOLS_REQUIRE_EQUAL( array.size(), 12 );

    auto success = array.resize(2,3,2);
    NMTOOLS_REQUIRE_EQUAL( success, true );
    NMTOOLS_REQUIRE_EQUAL( array.dim(), 3 );
    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{2,3,2}) );
    NMTOOLS_REQUIRE_EQUAL( array.size(), 12 );

    {
        auto ndindex = ix::ndindex(array.shape());
        for (size_t i=0; i<ndindex.size(); i++) {
            nm::apply_at(array,ndindex[i]) = i;
        }
        int expect[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_ASSERT_CLOSE( array,  expect );
    }

    success = array.resize(2,1,3,1,1,1);
    NMTOOLS_REQUIRE_EQUAL( success, false );
}

namespace case12
{
    using T = float;
    using index_t = size_t;

    constexpr auto max_numel = 12;
    using buffer_t = ::boost::container::static_vector<T,max_numel>;

    constexpr auto bounded_dim = 6;
    using shape_buffer_t = ::boost::container::static_vector<index_t,bounded_dim>;

    static_assert( meta::is_index_array_v<shape_buffer_t> );

    template <typename...>
    using stride_buffer_t = shape_buffer_t;
} // namespace case1

TEST_CASE("ndarray(case12)" * doctest::test_suite("array::ndarray"))
{
    using namespace case12;
    using ndarray = na::ndarray_t<buffer_t,shape_buffer_t>;

    auto array = ndarray {};

    NMTOOLS_REQUIRE_EQUAL( array.dim(), 1 );
    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{1}) );
    NMTOOLS_REQUIRE_EQUAL( array.size(), 1 );

    auto success = array.resize(2,3,2);
    NMTOOLS_REQUIRE_EQUAL( success, true );
    NMTOOLS_REQUIRE_EQUAL( array.dim(), 3 );
    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{2,3,2}) );
    NMTOOLS_REQUIRE_EQUAL( array.size(), 12 );

    {
        auto ndindex = ix::ndindex(array.shape());
        for (size_t i=0; i<ndindex.size(); i++) {
            nm::apply_at(array,ndindex[i]) = i;
        }
        int expect[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_ASSERT_CLOSE( array,  expect );
    }

    success = array.resize(2,1,3,1,1,1);
    NMTOOLS_REQUIRE_EQUAL( success, true );

    // throws
    // success = array.resize(2,1,3,1,1,1,1);
    // NMTOOLS_REQUIRE_EQUAL( success, false );

    // throws
    // success = array.resize(16);
    // NMTOOLS_REQUIRE_EQUAL( success, false );
}

namespace case13
{
    using T = float;
    using index_t = size_t;

    constexpr auto max_numel = 12;
    using buffer_t = ::boost::container::small_vector<T,max_numel>;

    constexpr auto bounded_dim = 6;
    using shape_buffer_t = ::boost::container::small_vector<index_t,bounded_dim>;

    static_assert( meta::is_index_array_v<shape_buffer_t> );

    template <typename...>
    using stride_buffer_t = shape_buffer_t;
}

TEST_CASE("ndarray(case13)" * doctest::test_suite("array::ndarray"))
{
    using namespace case13;
    using ndarray = na::ndarray_t<buffer_t,shape_buffer_t>;

    auto array = ndarray {};

    NMTOOLS_REQUIRE_EQUAL( array.dim(), 1 );
    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{1}) );
    NMTOOLS_REQUIRE_EQUAL( array.size(), 1 );

    auto success = array.resize(2,3,2);
    NMTOOLS_REQUIRE_EQUAL( success, true );
    NMTOOLS_REQUIRE_EQUAL( array.dim(), 3 );
    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{2,3,2}) );
    NMTOOLS_REQUIRE_EQUAL( array.size(), 12 );

    {
        auto ndindex = ix::ndindex(array.shape());
        for (size_t i=0; i<ndindex.size(); i++) {
            nm::apply_at(array,ndindex[i]) = i;
        }
        int expect[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_ASSERT_CLOSE( array,  expect );
    }

    success = array.resize(2,1,3,1,1,1);
    NMTOOLS_REQUIRE_EQUAL( success, true );

    // throws
    // success = array.resize(2,1,3,1,1,1,1);
    // NMTOOLS_REQUIRE_EQUAL( success, false );

    // throws
    // success = array.resize(16);
    // NMTOOLS_REQUIRE_EQUAL( success, false );
}

namespace case14
{
    using T = float;
    using index_t = size_t;

    using buffer_t = ::boost::container::vector<T>;

    using shape_buffer_t = ::boost::container::vector<index_t>;

    static_assert( meta::is_index_array_v<shape_buffer_t> );
}

TEST_CASE("ndarray(case14)" * doctest::test_suite("array::ndarray"))
{
    using namespace case14;
    using ndarray = na::ndarray_t<buffer_t,shape_buffer_t>;

    auto array = ndarray {};

    NMTOOLS_REQUIRE_EQUAL( array.dim(), 1 );
    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{1}) );
    NMTOOLS_REQUIRE_EQUAL( array.size(), 1 );

    auto success = array.resize(2,3,2);
    NMTOOLS_REQUIRE_EQUAL( success, true );
    NMTOOLS_REQUIRE_EQUAL( array.dim(), 3 );
    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{2,3,2}) );
    NMTOOLS_REQUIRE_EQUAL( array.size(), 12 );

    {
        auto ndindex = ix::ndindex(array.shape());
        for (size_t i=0; i<ndindex.size(); i++) {
            nm::apply_at(array,ndindex[i]) = i;
        }
        int expect[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_ASSERT_CLOSE( array,  expect );
    }

    success = array.resize(2,1,3,1,1,1);
    NMTOOLS_REQUIRE_EQUAL( success, true );

    // throws
    // success = array.resize(2,1,3,1,1,1,1);
    // NMTOOLS_REQUIRE_EQUAL( success, false );

    // throws
    // success = array.resize(16);
    // NMTOOLS_REQUIRE_EQUAL( success, false );
}

#endif