#if __has_include(<boost/array.hpp>)
#include "nmtools/utility/impl/boost.hpp"
#endif

#include "nmtools/meta.hpp"
#include "nmtools/ndarray/ndarray.hpp"
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/index/cast.hpp"
#include "nmtools/index/compute_strides.hpp"
#include "nmtools/index/ndindex.hpp"
#include "nmtools/utl.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/utility/cast.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace ix = nm::index;
namespace meta = nm::meta;

TEST_CASE("ndarray(case1)" * doctest::test_suite("array::ndarray"))
{
    using buffer_t = nmtools_array<float,12>;
    using shape_buffer_t = nmtools_array<nm_size_t,3>;
    using ndarray = nm::ndarray_t<buffer_t,shape_buffer_t>;

    auto a = ndarray{};

    NMTOOLS_ASSERT_EQUAL( nm::has_shape_v<decltype(a)>, true );
    NMTOOLS_REQUIRE_EQUAL( a.dim(), 3 );
    NMTOOLS_REQUIRE_EQUAL( a.shape(), (nmtools_array{1,1,12}) );
    NMTOOLS_REQUIRE_EQUAL( a.size(), 12 );
    NMTOOLS_REQUIRE_EQUAL( a.strides(), (nmtools_array{12,12,1}));
    NMTOOLS_REQUIRE_EQUAL( nm::dim(a), 3 );
    NMTOOLS_REQUIRE_EQUAL( nm::shape(a), (nmtools_array{1,1,12}) );

    auto success = a.resize(2,3,2);
    NMTOOLS_REQUIRE_EQUAL( success, true );
    NMTOOLS_REQUIRE_EQUAL( a.shape(), (nmtools_array{2,3,2}) );
    NMTOOLS_REQUIRE_EQUAL( a.size(), 12 );
    NMTOOLS_REQUIRE_EQUAL( a.strides(), (nmtools_array{6,2,1}));

    {
        auto ndindex = ix::ndindex(a.shape());
        for (size_t i=0; i<ndindex.size(); i++) {
            nm::apply_at(a,ndindex[i]) = i;
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
        NMTOOLS_ASSERT_CLOSE( a,  expect );
    }
}

TEST_CASE("ndarray(case2)" * doctest::test_suite("array::ndarray"))
{
    using buffer_t = nmtools_array<float,12>;
    using shape_buffer_t = nmtools_tuple<nm::ct<2>,nm::ct<3>,nm::ct<2>>;
    using ndarray = nm::ndarray_t<buffer_t,shape_buffer_t>;

    auto a = ndarray{};

    NMTOOLS_ASSERT_EQUAL( nm::has_shape_v<decltype(a)>, true );
    NMTOOLS_REQUIRE_EQUAL( a.shape(), (nmtools_array{2,3,2}) );
    NMTOOLS_REQUIRE_EQUAL( a.size(), 12 );
    NMTOOLS_REQUIRE_EQUAL( a.strides(), (nmtools_array{6,2,1}));

    {
        auto ndindex = ix::ndindex(a.shape());
        for (size_t i=0; i<ndindex.size(); i++) {
            nm::apply_at(a,ndindex[i]) = i;
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
        NMTOOLS_ASSERT_CLOSE( a,  expect );
    }
}

TEST_CASE("ndarray(case3)" * doctest::test_suite("array::ndarray"))
{
    using buffer_t = nmtools_list<float>;
    using shape_buffer_t = nmtools_tuple<nm::ct<2>,nm::ct<3>,nm::ct<2>>;
    using ndarray = nm::ndarray_t<buffer_t,shape_buffer_t>;

    auto a = ndarray{};

    NMTOOLS_ASSERT_EQUAL( nm::has_shape_v<decltype(a)>, true );
    NMTOOLS_REQUIRE_EQUAL( a.shape(), (nmtools_array{2,3,2}) );
    NMTOOLS_REQUIRE_EQUAL( a.size(), 12 );
    NMTOOLS_REQUIRE_EQUAL( a.strides(), (nmtools_array{6,2,1}));

    {
        auto ndindex = ix::ndindex(a.shape());
        for (size_t i=0; i<ndindex.size(); i++) {
            nm::apply_at(a,ndindex[i]) = i;
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
        NMTOOLS_ASSERT_CLOSE( a,  expect );
    }
}

TEST_CASE("ndarray(case4)" * doctest::test_suite("array::ndarray"))
{
    using buffer_t = nmtools_array<float,12>;
    using shape_buffer_t = nmtools_list<nm_size_t>;
    using ndarray = nm::ndarray_t<buffer_t,shape_buffer_t>;

    auto a = ndarray{};

    NMTOOLS_ASSERT_EQUAL( nm::has_shape_v<decltype(a)>, true );
    NMTOOLS_REQUIRE_EQUAL( a.dim(), 1 );
    NMTOOLS_REQUIRE_EQUAL( a.shape(), (nmtools_array{12}) );
    NMTOOLS_REQUIRE_EQUAL( a.size(), 12 );
    NMTOOLS_REQUIRE_EQUAL( a.strides(), (nmtools_array{1}));
    NMTOOLS_REQUIRE_EQUAL( nm::dim(a), 1 );
    NMTOOLS_REQUIRE_EQUAL( nm::shape(a), (nmtools_array{12}) );

    auto success = a.resize(2,3,2);
    NMTOOLS_REQUIRE_EQUAL( success, true );
    NMTOOLS_REQUIRE_EQUAL( a.shape(), (nmtools_array{2,3,2}) );
    NMTOOLS_REQUIRE_EQUAL( a.size(), 12 );
    NMTOOLS_REQUIRE_EQUAL( a.strides(), (nmtools_array{6,2,1}));

    {
        auto ndindex = ix::ndindex(a.shape());
        for (size_t i=0; i<ndindex.size(); i++) {
            nm::apply_at(a,ndindex[i]) = i;
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
        NMTOOLS_ASSERT_CLOSE( a,  expect );
    }
}

TEST_CASE("ndarray(case5)" * doctest::test_suite("array::ndarray"))
{
    using buffer_t = nmtools_array<float,12>;
    using shape_buffer_t = nmtools_static_vector<nm_size_t,6>;
    using ndarray = nm::ndarray_t<buffer_t,shape_buffer_t>;

    auto a = ndarray{};

    NMTOOLS_ASSERT_EQUAL( nm::has_shape_v<decltype(a)>, true );
    NMTOOLS_REQUIRE_EQUAL( a.dim(), 1 );
    NMTOOLS_REQUIRE_EQUAL( a.shape(), (nmtools_array{12}) );
    NMTOOLS_REQUIRE_EQUAL( a.size(), 12 );
    NMTOOLS_REQUIRE_EQUAL( a.strides(), (nmtools_array{1}));
    NMTOOLS_REQUIRE_EQUAL( nm::dim(a), 1 );
    NMTOOLS_REQUIRE_EQUAL( nm::shape(a), (nmtools_array{12}) );

    auto success = a.resize(2,3,2);
    NMTOOLS_REQUIRE_EQUAL( success, true );
    NMTOOLS_REQUIRE_EQUAL( a.shape(), (nmtools_array{2,3,2}) );
    NMTOOLS_REQUIRE_EQUAL( a.size(), 12 );
    NMTOOLS_REQUIRE_EQUAL( a.strides(), (nmtools_array{6,2,1}));

    {
        auto ndindex = ix::ndindex(a.shape());
        for (size_t i=0; i<ndindex.size(); i++) {
            nm::apply_at(a,ndindex[i]) = i;
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
        NMTOOLS_ASSERT_CLOSE( a,  expect );
    }
}

TEST_CASE("ndarray(case6)" * doctest::test_suite("array::ndarray"))
{
    using buffer_t = nmtools_static_vector<float,12>;
    using shape_buffer_t = nmtools_tuple<nm::ct<2>,nm::ct<3>,nm::ct<2>>;
    using ndarray = nm::ndarray_t<buffer_t,shape_buffer_t>;

    auto a = ndarray{};

    NMTOOLS_ASSERT_EQUAL( nm::has_shape_v<decltype(a)>, true );
    NMTOOLS_REQUIRE_EQUAL( a.shape(), (nmtools_array{2,3,2}) );
    NMTOOLS_REQUIRE_EQUAL( a.size(), 12 );
    NMTOOLS_REQUIRE_EQUAL( a.strides(), (nmtools_array{6,2,1}));

    {
        auto ndindex = ix::ndindex(a.shape());
        for (size_t i=0; i<ndindex.size(); i++) {
            nm::apply_at(a,ndindex[i]) = i;
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
        NMTOOLS_ASSERT_CLOSE( a,  expect );
    }
}

TEST_CASE("ndarray(case7)" * doctest::test_suite("array::ndarray"))
{
    using buffer_t = nmtools_list<float>;
    using shape_buffer_t = nmtools_static_vector<nm_size_t,3>;
    using ndarray = nm::ndarray_t<buffer_t,shape_buffer_t>;

    auto a = ndarray{};

    NMTOOLS_ASSERT_EQUAL( nm::has_shape_v<decltype(a)>, true );
    NMTOOLS_REQUIRE_EQUAL( a.dim(), 1 );
    NMTOOLS_REQUIRE_EQUAL( a.shape(), (nmtools_array{1}) );
    NMTOOLS_REQUIRE_EQUAL( a.size(), 1 );
    NMTOOLS_REQUIRE_EQUAL( a.strides(), (nmtools_array{1}));
    NMTOOLS_REQUIRE_EQUAL( nm::dim(a), 1 );
    NMTOOLS_REQUIRE_EQUAL( nm::shape(a), (nmtools_array{1}) );

    auto success = a.resize(2,3,2);
    NMTOOLS_REQUIRE_EQUAL( success, true );
    NMTOOLS_REQUIRE_EQUAL( a.shape(), (nmtools_array{2,3,2}) );
    NMTOOLS_REQUIRE_EQUAL( a.size(), 12 );
    NMTOOLS_REQUIRE_EQUAL( a.strides(), (nmtools_array{6,2,1}));

    {
        auto ndindex = ix::ndindex(a.shape());
        for (size_t i=0; i<ndindex.size(); i++) {
            nm::apply_at(a,ndindex[i]) = i;
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
        NMTOOLS_ASSERT_CLOSE( a,  expect );
    }
}

TEST_CASE("ndarray(case8)" * doctest::test_suite("array::ndarray"))
{
    using buffer_t = nmtools_static_vector<float,12>;
    using shape_buffer_t = nmtools_static_vector<nm_size_t,6>;
    using ndarray = nm::ndarray_t<buffer_t,shape_buffer_t>;

    auto a = ndarray{};

    NMTOOLS_ASSERT_EQUAL( nm::has_shape_v<decltype(a)>, true );
    NMTOOLS_REQUIRE_EQUAL( a.dim(), 1 );
    NMTOOLS_REQUIRE_EQUAL( a.shape(), (nmtools_array{1}) );
    NMTOOLS_REQUIRE_EQUAL( a.size(), 1 );
    NMTOOLS_REQUIRE_EQUAL( a.strides(), (nmtools_array{1}));
    NMTOOLS_REQUIRE_EQUAL( nm::dim(a), 1 );
    NMTOOLS_REQUIRE_EQUAL( nm::shape(a), (nmtools_array{1}) );

    auto success = a.resize(2,3,2);
    NMTOOLS_REQUIRE_EQUAL( success, true );
    NMTOOLS_REQUIRE_EQUAL( a.shape(), (nmtools_array{2,3,2}) );
    NMTOOLS_REQUIRE_EQUAL( a.size(), 12 );
    NMTOOLS_REQUIRE_EQUAL( a.strides(), (nmtools_array{6,2,1}));

    {
        auto ndindex = ix::ndindex(a.shape());
        for (size_t i=0; i<ndindex.size(); i++) {
            nm::apply_at(a,ndindex[i]) = i;
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
        NMTOOLS_ASSERT_CLOSE( a,  expect );
    }
}

TEST_CASE("ndarray(case8)" * doctest::test_suite("array::ndarray"))
{
    using buffer_t = nmtools_list<float>;
    using shape_buffer_t = nmtools_list<nm_size_t>;
    using ndarray = nm::ndarray_t<buffer_t,shape_buffer_t>;

    auto a = ndarray{};

    NMTOOLS_ASSERT_EQUAL( nm::has_shape_v<decltype(a)>, true );
    NMTOOLS_REQUIRE_EQUAL( a.dim(), 1 );
    NMTOOLS_REQUIRE_EQUAL( a.shape(), (nmtools_array{1}) );
    NMTOOLS_REQUIRE_EQUAL( a.size(), 1 );
    NMTOOLS_REQUIRE_EQUAL( a.strides(), (nmtools_array{1}));
    NMTOOLS_REQUIRE_EQUAL( nm::dim(a), 1 );
    NMTOOLS_REQUIRE_EQUAL( nm::shape(a), (nmtools_array{1}) );

    auto success = a.resize(2,3,2);
    NMTOOLS_REQUIRE_EQUAL( success, true );
    NMTOOLS_REQUIRE_EQUAL( a.shape(), (nmtools_array{2,3,2}) );
    NMTOOLS_REQUIRE_EQUAL( a.size(), 12 );
    NMTOOLS_REQUIRE_EQUAL( a.strides(), (nmtools_array{6,2,1}));

    {
        auto ndindex = ix::ndindex(a.shape());
        for (size_t i=0; i<ndindex.size(); i++) {
            nm::apply_at(a,ndindex[i]) = i;
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
        NMTOOLS_ASSERT_CLOSE( a,  expect );
    }
}

namespace ix = nmtools::index;

// TODO: column major using explicit stride
#if 1
TEST_CASE("ndarray(case10)" * doctest::test_suite("array::ndarray"))
{
    using buffer_t = nmtools_list<int>;
    using shape_buffer_t  = nmtools_list<nm_size_t>;
    using stride_buffer_t = nmtools_list<nm_size_t>;
    using ndarray = na::ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t>;

    int buffer[12] = {0,6,2,8,4,10,1,7,3,9,5,11};
    int shape[3]   = {2,3,2};
    int strides[3] = {1,2,6};
    auto array     = ndarray(ix::cast<buffer_t>(buffer),ix::cast<shape_buffer_t>(shape),ix::cast<stride_buffer_t>(strides));

    NMTOOLS_ASSERT_EQUAL( nm::has_shape_v<decltype(array)>, true );

    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{2,3,2}) );
    NMTOOLS_REQUIRE_EQUAL( array.size(), 12 );
    NMTOOLS_REQUIRE_EQUAL( array.strides(), (nmtools_array{1,2,6}));

    {
        // no need to re-assign
        // auto ndindex = ix::ndindex(array.shape());
        // for (size_t i=0; i<ndindex.size(); i++) {
        //     nm::apply_at(array,ndindex[i]) = i;
        // }
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
}
#endif

// broadcast: stride 0 on the first axis
// see testing/data/array/stride.hpp case1
#if 1
TEST_CASE("ndarray(case21)" * doctest::test_suite("array::ndarray"))
{
    using buffer_t = nmtools_list<int>;
    using shape_buffer_t  = nmtools_list<nm_size_t>;
    using stride_buffer_t = nmtools_list<nm_size_t>;
    using ndarray = na::ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t>;

    int buffer[3] = {1,2,3};
    int shape[2]   = {3,3};
    int strides[2] = {0,1};
    auto array     = ndarray(ix::cast<buffer_t>(buffer),ix::cast<shape_buffer_t>(shape),ix::cast<stride_buffer_t>(strides));

    NMTOOLS_REQUIRE_EQUAL( array.dim(), 2 );
    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{3,3}) );
    NMTOOLS_REQUIRE_EQUAL( array.strides(), (nmtools_array{0,1}) );

    int expect[3][3] = {
        {1,2,3},
        {1,2,3},
        {1,2,3},
    };
    NMTOOLS_ASSERT_CLOSE( array, expect );
}
#endif

// column major
// see testing/data/array/stride.hpp case12
#if 1
TEST_CASE("ndarray(case22)" * doctest::test_suite("array::ndarray"))
{
    using buffer_t = nmtools_list<int>;
    using shape_buffer_t  = nmtools_list<nm_size_t>;
    using stride_buffer_t = nmtools_list<nm_size_t>;
    using ndarray = na::ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t>;

    int buffer[32] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
    int shape[2]   = {4,8};
    int strides[2] = {1,4};
    auto array     = ndarray(ix::cast<buffer_t>(buffer),ix::cast<shape_buffer_t>(shape),ix::cast<stride_buffer_t>(strides));

    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{4,8}) );
    NMTOOLS_REQUIRE_EQUAL( array.size(), 32 );
    NMTOOLS_REQUIRE_EQUAL( array.strides(), (nmtools_array{1,4}) );

    int expect[4][8] = {
        {0,4, 8,12,16,20,24,28},
        {1,5, 9,13,17,21,25,29},
        {2,6,10,14,18,22,26,30},
        {3,7,11,15,19,23,27,31},
    };
    NMTOOLS_ASSERT_CLOSE( array, expect );
}
#endif

// column major padded (leading dimension larger than shape)
// see testing/data/array/stride.hpp case13
#if 1
TEST_CASE("ndarray(case23)" * doctest::test_suite("array::ndarray"))
{
    using buffer_t = nmtools_list<int>;
    using shape_buffer_t  = nmtools_list<nm_size_t>;
    using stride_buffer_t = nmtools_list<nm_size_t>;
    using ndarray = na::ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t>;

    int buffer[40] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39};
    int shape[2]   = {4,8};
    int strides[2] = {1,5};
    auto array     = ndarray(ix::cast<buffer_t>(buffer),ix::cast<shape_buffer_t>(shape),ix::cast<stride_buffer_t>(strides));

    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{4,8}) );
    NMTOOLS_REQUIRE_EQUAL( array.strides(), (nmtools_array{1,5}) );

    int expect[4][8] = {
        {0,5,10,15,20,25,30,35},
        {1,6,11,16,21,26,31,36},
        {2,7,12,17,22,27,32,37},
        {3,8,13,18,23,28,33,38},
    };
    NMTOOLS_ASSERT_CLOSE( array, expect );
}
#endif

// transpose view of a contiguous buffer
// see testing/data/array/stride.hpp case15
#if 1
TEST_CASE("ndarray(case24)" * doctest::test_suite("array::ndarray"))
{
    using buffer_t = nmtools_list<int>;
    using shape_buffer_t  = nmtools_list<nm_size_t>;
    using stride_buffer_t = nmtools_list<nm_size_t>;
    using ndarray = na::ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t>;

    int buffer[24] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};
    int shape[2]   = {8,3};
    int strides[2] = {1,8};
    auto array     = ndarray(ix::cast<buffer_t>(buffer),ix::cast<shape_buffer_t>(shape),ix::cast<stride_buffer_t>(strides));

    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{8,3}) );
    NMTOOLS_REQUIRE_EQUAL( array.strides(), (nmtools_array{1,8}) );

    int expect[8][3] = {
        { 0,  8, 16},
        { 1,  9, 17},
        { 2, 10, 18},
        { 3, 11, 19},
        { 4, 12, 20},
        { 5, 13, 21},
        { 6, 14, 22},
        { 7, 15, 23}
    };
    NMTOOLS_ASSERT_CLOSE( array, expect );
}
#endif

// strided slice, x[::2]
// see testing/data/array/stride.hpp case6
#if 1
TEST_CASE("ndarray(case25)" * doctest::test_suite("array::ndarray"))
{
    using buffer_t = nmtools_list<int>;
    using shape_buffer_t  = nmtools_list<nm_size_t>;
    using stride_buffer_t = nmtools_list<nm_size_t>;
    using ndarray = na::ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t>;

    int buffer[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
    int shape[1]   = {6};
    int strides[1] = {2};
    auto array     = ndarray(ix::cast<buffer_t>(buffer),ix::cast<shape_buffer_t>(shape),ix::cast<stride_buffer_t>(strides));

    NMTOOLS_REQUIRE_EQUAL( array.dim(), 1 );
    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{6}) );
    NMTOOLS_REQUIRE_EQUAL( array.strides(), (nmtools_array{2}) );

    int expect[6] = {1,3,5,7,9,11};
    NMTOOLS_ASSERT_CLOSE( array, expect );
}
#endif

// reshape then slice, x.reshape(3,4)[::2,::2]
// see testing/data/array/stride.hpp case8
#if 1
TEST_CASE("ndarray(case26)" * doctest::test_suite("array::ndarray"))
{
    using buffer_t = nmtools_list<int>;
    using shape_buffer_t  = nmtools_list<nm_size_t>;
    using stride_buffer_t = nmtools_list<nm_size_t>;
    using ndarray = na::ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t>;

    int buffer[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
    int shape[2]   = {2,2};
    int strides[2] = {8,2};
    auto array     = ndarray(ix::cast<buffer_t>(buffer),ix::cast<shape_buffer_t>(shape),ix::cast<stride_buffer_t>(strides));

    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{2,2}) );
    NMTOOLS_REQUIRE_EQUAL( array.strides(), (nmtools_array{8,2}) );

    int expect[2][2] = {
        {1,3},
        {9,11},
    };
    NMTOOLS_ASSERT_CLOSE( array, expect );
}
#endif

// row-major striding generated by compute_row_major_strides
#if 1
TEST_CASE("ndarray(case27)" * doctest::test_suite("array::ndarray"))
{
    using buffer_t = nmtools_list<int>;
    using shape_buffer_t  = nmtools_list<nm_size_t>;
    using stride_buffer_t = nmtools_list<nm_size_t>;
    using ndarray = na::ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t>;

    int buffer[12] = {0,1,2,3,4,5,6,7,8,9,10,11};
    int shape[2]   = {3,4};
    auto strides   = ix::compute_row_major_strides(shape);
    auto array     = ndarray(ix::cast<buffer_t>(buffer),ix::cast<shape_buffer_t>(shape),ix::cast<stride_buffer_t>(strides));

    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{3,4}) );
    NMTOOLS_REQUIRE_EQUAL( array.size(), 12 );
    NMTOOLS_REQUIRE_EQUAL( array.strides(), (nmtools_array{4,1}) );
    NMTOOLS_ASSERT_EQUAL( ix::is_row_major(array.shape(), array.strides()), true );
    NMTOOLS_ASSERT_EQUAL( ix::is_col_major(array.shape(), array.strides()), false );

    int expect[3][4] = {
        {0,1,2,3},
        {4,5,6,7},
        {8,9,10,11},
    };
    NMTOOLS_ASSERT_CLOSE( array, expect );
}
#endif

// column-major striding generated by compute_col_major_strides
// same striding as case22, but computed from the shape instead of
// written out; see testing/data/array/stride.hpp case12
#if 1
TEST_CASE("ndarray(case28)" * doctest::test_suite("array::ndarray"))
{
    using buffer_t = nmtools_list<int>;
    using shape_buffer_t  = nmtools_list<nm_size_t>;
    using stride_buffer_t = nmtools_list<nm_size_t>;
    using ndarray = na::ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t>;

    int buffer[32] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
    int shape[2]   = {4,8};
    auto strides   = ix::compute_col_major_strides(shape);
    auto array     = ndarray(ix::cast<buffer_t>(buffer),ix::cast<shape_buffer_t>(shape),ix::cast<stride_buffer_t>(strides));

    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{4,8}) );
    NMTOOLS_REQUIRE_EQUAL( array.size(), 32 );
    NMTOOLS_REQUIRE_EQUAL( array.strides(), (nmtools_array{1,4}) );
    NMTOOLS_ASSERT_EQUAL( ix::is_col_major(array.shape(), array.strides()), true );
    NMTOOLS_ASSERT_EQUAL( ix::is_row_major(array.shape(), array.strides()), false );

    int expect[4][8] = {
        {0,4, 8,12,16,20,24,28},
        {1,5, 9,13,17,21,25,29},
        {2,6,10,14,18,22,26,30},
        {3,7,11,15,19,23,27,31},
    };
    NMTOOLS_ASSERT_CLOSE( array, expect );
}
#endif

// blocked striding generated by compute_blocked_strides.
// ndarray cannot hold nested strides yet (its offset path is a flat
// dot product), so pin down the generated strides against the
// reference blocked column major layout of stride.hpp case18: each
// flat subscript decomposes row-major into the nested mode subscripts
// and the offset is the dot product with the nested strides.
#if 1
TEST_CASE("ndarray(case29)" * doctest::test_suite("array::ndarray"))
{
    using namespace nmtools::literals;

    constexpr auto shape_ct    = nmtools_tuple{8_ct,8_ct};
    constexpr auto block_ct    = nmtools_tuple{4_ct,2_ct};
    constexpr auto grid_order  = nmtools_tuple{1_ct,0_ct};
    constexpr auto inner_order = nmtools_tuple{0_ct,1_ct};
    constexpr auto strides = ix::compute_blocked_strides(shape_ct, block_ct, grid_order, inner_order);

    // ((32,1),(8,4)), matches index::compute_blocked_strides case1
    static_assert(std::get<0>(std::get<0>(strides)) == 32);
    static_assert(std::get<1>(std::get<0>(strides)) == 1);
    static_assert(std::get<0>(std::get<1>(strides)) == 8);
    static_assert(std::get<1>(std::get<1>(strides)) == 4);

    int buffer[64];
    for (int i=0; i<64; i++) buffer[i] = i;

    int expect[8][8] = {
        {0,4,8,12,16,20,24,28},
        {1,5,9,13,17,21,25,29},
        {2,6,10,14,18,22,26,30},
        {3,7,11,15,19,23,27,31},
        {32,36,40,44,48,52,56,60},
        {33,37,41,45,49,53,57,61},
        {34,38,42,46,50,54,58,62},
        {35,39,43,47,51,55,59,63},
    };

    // mode 0: m = g0*4 + t0, mode 1: n = g1*2 + t1
    for (int m=0; m<8; m++) {
        int g0 = m/4, t0 = m%4;
        for (int n=0; n<8; n++) {
            int g1 = n/2, t1 = n%2;
            auto offset = g0*std::get<0>(std::get<0>(strides))
                        + t0*std::get<1>(std::get<0>(strides))
                        + g1*std::get<0>(std::get<1>(strides))
                        + t1*std::get<1>(std::get<1>(strides));
            NMTOOLS_ASSERT_EQUAL( buffer[offset], expect[m][n] );
        }
    }
}
#endif

// resizing a column-major strided array keeps it column-major
#if 1
TEST_CASE("ndarray(case30)" * doctest::test_suite("array::ndarray"))
{
    using buffer_t = nmtools_list<int>;
    using shape_buffer_t  = nmtools_list<nm_size_t>;
    using stride_buffer_t = nmtools_list<nm_size_t>;
    using ndarray = na::ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t>;

    int buffer[32] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
    int shape[2]   = {4,8};
    auto strides   = ix::compute_col_major_strides(shape);
    auto array     = ndarray(ix::cast<buffer_t>(buffer),ix::cast<shape_buffer_t>(shape),ix::cast<stride_buffer_t>(strides));

    auto success = array.resize(8,4);
    NMTOOLS_REQUIRE_EQUAL( success, true );
    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{8,4}) );
    NMTOOLS_REQUIRE_EQUAL( array.strides(), (nmtools_array{1,8}) );
    NMTOOLS_ASSERT_EQUAL( ix::is_col_major(array.shape(), array.strides()), true );

    // element (r,c) reads buffer[r + 8*c]
    int expect[8][4] = {
        {0, 8,16,24},
        {1, 9,17,25},
        {2,10,18,26},
        {3,11,19,27},
        {4,12,20,28},
        {5,13,21,29},
        {6,14,22,30},
        {7,15,23,31},
    };
    NMTOOLS_ASSERT_CLOSE( array, expect );
}
#endif

// resizing a row-major strided array with fixed-size strides keeps it
// row-major; a rank change is rejected because the strides cannot grow
#if 1
TEST_CASE("ndarray(case31)" * doctest::test_suite("array::ndarray"))
{
    using buffer_t = nmtools_list<int>;
    using shape_buffer_t  = nmtools_list<nm_size_t>;
    using stride_buffer_t = nmtools_array<int32_t,2>;
    using ndarray = na::ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t>;

    int buffer[12] = {0,1,2,3,4,5,6,7,8,9,10,11};
    int shape[2]   = {3,4};
    auto strides   = ix::compute_row_major_strides(shape);
    auto array     = ndarray(ix::cast<buffer_t>(buffer),ix::cast<shape_buffer_t>(shape),ix::cast<stride_buffer_t>(strides));

    // same numel but new rank: rejected, array untouched
    NMTOOLS_REQUIRE_EQUAL( array.resize(2,2,3), false );
    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{3,4}) );
    NMTOOLS_REQUIRE_EQUAL( array.strides(), (nmtools_array{4,1}) );

    auto success = array.resize(4,3);
    NMTOOLS_REQUIRE_EQUAL( success, true );
    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{4,3}) );
    NMTOOLS_REQUIRE_EQUAL( array.strides(), (nmtools_array{3,1}) );
    NMTOOLS_ASSERT_EQUAL( ix::is_row_major(array.shape(), array.strides()), true );

    int expect[4][3] = {
        {0,1,2},
        {3,4,5},
        {6,7,8},
        {9,10,11},
    };
    NMTOOLS_ASSERT_CLOSE( array, expect );
}
#endif

// strided arrays with non-canonical strides (broadcast, padded) cannot
// be mapped onto a canonical layout; resize rejects and leaves them
// untouched
#if 1
TEST_CASE("ndarray(case32)" * doctest::test_suite("array::ndarray"))
{
    using buffer_t = nmtools_list<int>;
    using shape_buffer_t  = nmtools_list<nm_size_t>;
    using stride_buffer_t = nmtools_list<nm_size_t>;
    using ndarray = na::ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t>;

    int buffer[12] = {1,2,3,4,5,6,7,8,9,10,11,12};

    // broadcast strides {0,1}: neither row nor col major
    {
        int shape[2]   = {3,4};
        int strides[2] = {0,1};
        auto array     = ndarray(ix::cast<buffer_t>(buffer),ix::cast<shape_buffer_t>(shape),ix::cast<stride_buffer_t>(strides));

        NMTOOLS_REQUIRE_EQUAL( array.resize(4,3), false );
        NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{3,4}) );
        NMTOOLS_REQUIRE_EQUAL( array.strides(), (nmtools_array{0,1}) );

        // still usable as before
        int expect[3][4] = {
            {1,2,3,4},
            {1,2,3,4},
            {1,2,3,4},
        };
        NMTOOLS_ASSERT_CLOSE( array, expect );
    }

    // padded column-major strides {1,5}: not dense column-major either
    {
        int shape[2]   = {4,3};
        int strides[2] = {1,5};
        auto array     = ndarray(ix::cast<buffer_t>(buffer),ix::cast<shape_buffer_t>(shape),ix::cast<stride_buffer_t>(strides));

        NMTOOLS_REQUIRE_EQUAL( array.resize(3,4), false );
        NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{4,3}) );
        NMTOOLS_REQUIRE_EQUAL( array.strides(), (nmtools_array{1,5}) );
    }
}
#endif

// resizing across ranks re-strides resizable strides
#if 1
TEST_CASE("ndarray(case33)" * doctest::test_suite("array::ndarray"))
{
    using buffer_t = nmtools_list<int>;
    using shape_buffer_t  = nmtools_list<nm_size_t>;
    using stride_buffer_t = nmtools_list<nm_size_t>;
    using ndarray = na::ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t>;

    int buffer[12] = {0,1,2,3,4,5,6,7,8,9,10,11};
    int shape[2]   = {3,4};
    auto strides   = ix::compute_row_major_strides(shape);
    auto array     = ndarray(ix::cast<buffer_t>(buffer),ix::cast<shape_buffer_t>(shape),ix::cast<stride_buffer_t>(strides));

    auto success = array.resize(2,2,3);
    NMTOOLS_REQUIRE_EQUAL( success, true );
    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{2,2,3}) );
    NMTOOLS_REQUIRE_EQUAL( array.strides(), (nmtools_array{6,3,1}) );
    NMTOOLS_ASSERT_EQUAL( ix::is_row_major(array.shape(), array.strides()), true );

    int expect[2][2][3] = {
        {
            {0,1,2},
            {3,4,5},
        },
        {
            {6,7,8},
            {9,10,11},
        },
    };
    NMTOOLS_ASSERT_CLOSE( array, expect );
}
#endif

// actual resize: shrinking a row-major strided array truncates the
// buffer and recomputes row-major strides for the smaller shape
#if 1
TEST_CASE("ndarray(case34)" * doctest::test_suite("array::ndarray"))
{
    using buffer_t = nmtools_list<int>;
    using shape_buffer_t  = nmtools_list<nm_size_t>;
    using stride_buffer_t = nmtools_list<nm_size_t>;
    using ndarray = na::ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t>;

    int buffer[12] = {0,1,2,3,4,5,6,7,8,9,10,11};
    int shape[2]   = {3,4};
    auto strides   = ix::compute_row_major_strides(shape);
    auto array     = ndarray(ix::cast<buffer_t>(buffer),ix::cast<shape_buffer_t>(shape),ix::cast<stride_buffer_t>(strides));

    auto success = array.resize(2,3);
    NMTOOLS_REQUIRE_EQUAL( success, true );
    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{2,3}) );
    NMTOOLS_REQUIRE_EQUAL( array.size(), 6 );
    NMTOOLS_REQUIRE_EQUAL( array.strides(), (nmtools_array{3,1}) );
    NMTOOLS_ASSERT_EQUAL( ix::is_row_major(array.shape(), array.strides()), true );

    int expect[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    NMTOOLS_ASSERT_CLOSE( array, expect );
}
#endif

// actual resize: growing a column-major strided array appends zeros
// and keeps it column-major
#if 1
TEST_CASE("ndarray(case35)" * doctest::test_suite("array::ndarray"))
{
    using buffer_t = nmtools_list<int>;
    using shape_buffer_t  = nmtools_list<nm_size_t>;
    using stride_buffer_t = nmtools_list<nm_size_t>;
    using ndarray = na::ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t>;

    int buffer[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int shape[2]   = {4,4};
    auto strides   = ix::compute_col_major_strides(shape);
    auto array     = ndarray(ix::cast<buffer_t>(buffer),ix::cast<shape_buffer_t>(shape),ix::cast<stride_buffer_t>(strides));

    auto success = array.resize(8,4);
    NMTOOLS_REQUIRE_EQUAL( success, true );
    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{8,4}) );
    NMTOOLS_REQUIRE_EQUAL( array.size(), 32 );
    NMTOOLS_REQUIRE_EQUAL( array.strides(), (nmtools_array{1,8}) );
    NMTOOLS_ASSERT_EQUAL( ix::is_col_major(array.shape(), array.strides()), true );

    // new elements are zero-filled, old ones keep their column-major striding
    int expect[8][4] = {
        {0, 8,0,0},
        {1, 9,0,0},
        {2,10,0,0},
        {3,11,0,0},
        {4,12,0,0},
        {5,13,0,0},
        {6,14,0,0},
        {7,15,0,0},
    };
    NMTOOLS_ASSERT_CLOSE( array, expect );
}
#endif

// actual resize with fixed-size strides: same rank, different numel is
// allowed even when the stride container cannot be resized
#if 1
TEST_CASE("ndarray(case36)" * doctest::test_suite("array::ndarray"))
{
    using buffer_t = nmtools_list<int>;
    using shape_buffer_t  = nmtools_list<nm_size_t>;
    using stride_buffer_t = nmtools_array<int32_t,2>;
    using ndarray = na::ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t>;

    int buffer[12] = {0,1,2,3,4,5,6,7,8,9,10,11};
    int shape[2]   = {4,3};
    auto strides   = ix::compute_col_major_strides(shape);
    auto array     = ndarray(ix::cast<buffer_t>(buffer),ix::cast<shape_buffer_t>(shape),ix::cast<stride_buffer_t>(strides));

    auto success = array.resize(2,3);
    NMTOOLS_REQUIRE_EQUAL( success, true );
    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{2,3}) );
    NMTOOLS_REQUIRE_EQUAL( array.size(), 6 );
    NMTOOLS_REQUIRE_EQUAL( array.strides(), (nmtools_array{1,2}) );
    NMTOOLS_ASSERT_EQUAL( ix::is_col_major(array.shape(), array.strides()), true );

    int expect[2][3] = {
        {0,2,4},
        {1,3,5},
    };
    NMTOOLS_ASSERT_CLOSE( array, expect );
}
#endif

// actual resize across ranks: shrinking and re-striding at once
#if 1
TEST_CASE("ndarray(case37)" * doctest::test_suite("array::ndarray"))
{
    using buffer_t = nmtools_list<int>;
    using shape_buffer_t  = nmtools_list<nm_size_t>;
    using stride_buffer_t = nmtools_list<nm_size_t>;
    using ndarray = na::ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t>;

    int buffer[12] = {0,1,2,3,4,5,6,7,8,9,10,11};
    int shape[2]   = {3,4};
    auto strides   = ix::compute_row_major_strides(shape);
    auto array     = ndarray(ix::cast<buffer_t>(buffer),ix::cast<shape_buffer_t>(shape),ix::cast<stride_buffer_t>(strides));

    auto success = array.resize(2,2,2);
    NMTOOLS_REQUIRE_EQUAL( success, true );
    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{2,2,2}) );
    NMTOOLS_REQUIRE_EQUAL( array.size(), 8 );
    NMTOOLS_REQUIRE_EQUAL( array.strides(), (nmtools_array{4,2,1}) );
    NMTOOLS_ASSERT_EQUAL( ix::is_row_major(array.shape(), array.strides()), true );

    int expect[2][2][2] = {
        {
            {0,1},
            {2,3},
        },
        {
            {4,5},
            {6,7},
        },
    };
    NMTOOLS_ASSERT_CLOSE( array, expect );
}
#endif

#if 1
TEST_CASE("ndarray(case15)" * doctest::test_suite("array::ndarray"))
{
    int a[2][3][2] = {
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

    {
        auto res = nmtools::cast(a,nmtools::kind::ndarray_ls_fb);
        NMTOOLS_ASSERT_EQUAL( nm::shape(res), nm::shape(a) );
        #ifndef __EMSCRIPTEN__
        NMTOOLS_ASSERT_EQUAL( res.strides(), (nmtools_array{6,3,1}) );
        #endif // __EMSCRIPTEN__
        NMTOOLS_ASSERT_CLOSE( res, a );
    }
    {
        auto res = nmtools::cast(a,nmtools::kind::ndarray_ls_hb);
        NMTOOLS_ASSERT_EQUAL( nm::shape(res), nm::shape(a) );
        NMTOOLS_ASSERT_CLOSE( res, a );
    }
    {
        auto res = nmtools::cast(a,nmtools::kind::ndarray_ls_db);
        NMTOOLS_ASSERT_EQUAL( nm::shape(res), nm::shape(a) );
        NMTOOLS_ASSERT_CLOSE( res, a );
    }
}
#endif

#if 1

namespace na = nmtools;
namespace kind = na::kind;
using namespace nmtools::literals;

TEST_CASE("ndarray(case16)" * doctest::test_suite("array::ndarray"))
{
    using buffer_t = nmtools_array<float,12>;
    using shape_buffer_t = decltype(nmtools_tuple{"1:[3]"_ct,"1:[4]"_ct,"1:[4]"_ct});
    using ndarray = na::ndarray_t<buffer_t,shape_buffer_t>;

    auto array = ndarray {};

    NMTOOLS_REQUIRE_EQUAL( array.dim(), 3 );
    #ifndef __EMSCRIPTEN__
    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{1,1,12}) );
    #endif // __EMSCRIPTEN__
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

    success = array.resize(3,4,4);
    NMTOOLS_REQUIRE_EQUAL( success, false );

    success = array.resize(12,1,1);
    NMTOOLS_REQUIRE_EQUAL( success, false );
}

TEST_CASE("ndarray(case17)" * doctest::test_suite("array::ndarray"))
{
    using buffer_t = na::static_vector<float,12>;
    using shape_buffer_t = decltype(nmtools_tuple{"1:[3]"_ct,"1:[4]"_ct,"1:[4]"_ct});
    using ndarray = na::ndarray_t<buffer_t,shape_buffer_t>;

    auto array = ndarray {};

    NMTOOLS_REQUIRE_EQUAL( array.dim(), 3 );
    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{1,1,1}) );
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
    NMTOOLS_REQUIRE_EQUAL( success, false );

    success = array.resize(3,4,4);
    NMTOOLS_REQUIRE_EQUAL( success, false );

    success = array.resize(12,1,1);
    NMTOOLS_REQUIRE_EQUAL( success, false );
}

TEST_CASE("ndarray(case18)" * doctest::test_suite("array::ndarray"))
{
    using buffer_t = nmtools_list<float>;
    using shape_buffer_t = decltype(nmtools_tuple{"1:[3]"_ct,"1:[4]"_ct,"1:[4]"_ct});
    using ndarray = na::ndarray_t<buffer_t,shape_buffer_t>;

    auto array = ndarray {};

    NMTOOLS_REQUIRE_EQUAL( array.dim(), 3 );
    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{1,1,1}) );
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
    NMTOOLS_REQUIRE_EQUAL( success, false );

    success = array.resize(3,4,4);
    NMTOOLS_REQUIRE_EQUAL( success, true );

    success = array.resize(12,1,1);
    NMTOOLS_REQUIRE_EQUAL( success, false );
}

TEST_CASE("ndarray(case19)" * doctest::test_suite("array::ndarray"))
{
    using buffer_t = nmtools_list<float>;
    using shape_buffer_t = nmtools_array<nm::clipped_size_t<3>,3>;
    using ndarray = na::ndarray_t<buffer_t,shape_buffer_t>;

    static_assert( meta::is_clipped_index_array_v<typename ndarray::shape_type> );
    static_assert( meta::is_clipped_index_array_v<typename ndarray::stride_type> );
    static_assert( !meta::is_resizable_v<typename ndarray::shape_type> );
    static_assert( !meta::is_resizable_v<typename ndarray::stride_type> );

    auto array = ndarray {};

    NMTOOLS_REQUIRE_EQUAL( array.dim(), 3 );
    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{1,1,1}) );
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
    NMTOOLS_REQUIRE_EQUAL( success, false );

    success = array.resize(3,4,4);
    NMTOOLS_REQUIRE_EQUAL( success, false );

    success = array.resize(12,1,1);
    NMTOOLS_REQUIRE_EQUAL( success, false );
}

namespace utl = nm::utl;

TEST_CASE("ndarray(case20)" * doctest::test_suite("array::ndarray"))
{
    using buffer_t = utl::array<float,12>;
    using shape_buffer_t = decltype(utl::tuple{"1:[3]"_ct,"1:[4]"_ct,"1:[4]"_ct});
    using ndarray = na::ndarray_t<buffer_t,shape_buffer_t>;

    auto array = ndarray {};

    NMTOOLS_REQUIRE_EQUAL( array.dim(), 3 );
    #ifndef __EMSCRIPTEN__
    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{1,1,12}) );
    #endif // __EMSCRIPTEN__
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

    success = array.resize(3,4,4);
    NMTOOLS_REQUIRE_EQUAL( success, false );

    success = array.resize(12,1,1);
    NMTOOLS_REQUIRE_EQUAL( success, false );
}
#endif