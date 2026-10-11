#if __has_include(<boost/array.hpp>)
#include "nmtools/utility/impl/boost.hpp"
#endif

#include "nmtools/meta.hpp"
#include "nmtools/ndarray/ndarray.hpp"
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/index/cast.hpp"
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