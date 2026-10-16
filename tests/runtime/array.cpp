#include "nmtools/runtime/ndarray.hpp"
#include "nmtools/testing/doctest.hpp"

namespace view = nmtools::view;
namespace nrt = nmtools::runtime;

using index_type = nrt::ndarray::index_type;

TEST_CASE("ndarray" * doctest::test_suite("runtime"))
{
    auto shape = index_type{3,4};
    auto array = nrt::ndarray(shape,nrt::DType::Float32);

    NMTOOLS_ASSERT_EQUAL( array.shape(), shape );
    NMTOOLS_ASSERT_EQUAL( array.strides(), (index_type{4,1}) );

    array.resize({6,3});
    NMTOOLS_ASSERT_EQUAL( array.shape(), (index_type{6,3}) );
    NMTOOLS_ASSERT_EQUAL( array.strides(), (index_type{3,1}) );

    {
        auto reshaped = array.reshape(index_type{2,9});
        NMTOOLS_ASSERT_EQUAL( reshaped.shape(), (index_type{2,9}) );
        NMTOOLS_ASSERT_EQUAL( reshaped.strides(), (index_type{9,1}) );
    }

    CHECK( array.dtype() == nrt::DType::Float32 );
    CHECK( array.data<float>() );
    CHECK( !array.data<double>() );
    CHECK( !array.data<uint8_t>() );
    CHECK( !array.data<uint16_t>() );
    CHECK( !array.data<uint32_t>() );
    CHECK( !array.data<uint64_t>() );
    CHECK( !array.data<int8_t>() );
    CHECK( !array.data<int16_t>() );
    CHECK( !array.data<int32_t>() );
    CHECK( !array.data<int64_t>() );

    int rhs[2][3][2] = {
        {
            {1,2},
            {3,4},
            {5,6},
        },
        {
            { 7, 8},
            { 9,10},
            {11,12},
        },
    };

    array = rhs;

    CHECK( array.dtype() == nrt::DType::Int32 );
    CHECK( !array.data<float>() );
    CHECK( !array.data<double>() );
    CHECK( !array.data<uint8_t>() );
    CHECK( !array.data<uint16_t>() );
    CHECK( !array.data<uint32_t>() );
    CHECK( !array.data<uint64_t>() );
    CHECK( !array.data<int8_t>() );
    CHECK( !array.data<int16_t>() );
    CHECK( array.data<int32_t>() );
    CHECK( !array.data<int64_t>() );
    NMTOOLS_ASSERT_EQUAL( array.shape(), (nmtools_array{2,3,2}) );
    CHECK( array.size() == 12 );
    CHECK( array.dim() == 3 );
    NMTOOLS_ASSERT_EQUAL( array.view<int32_t>(), rhs );

    // static_assert( nmtools::has_data_v<decltype(array)> );
}

TEST_CASE("array" * doctest::test_suite("runtime"))
{
    int rhs[2][3][2] = {
        {
            {1,2},
            {3,4},
            {5,6},
        },
        {
            { 7, 8},
            { 9,10},
            {11,12},
        },
    };
    auto a = nrt::array(rhs);
    NMTOOLS_ASSERT_EQUAL( a.view<int32_t>(), rhs );

    // static_assert( nmtools::has_data_v<decltype(a)> );
}

TEST_CASE("scalar" * doctest::test_suite("runtime"))
{
    auto a = nrt::ndarray(3.14f, nmtools::dtype_t<float>{});
    CHECK( a.is_scalar() );
    CHECK( a.dim() == 0 );
    CHECK( a.size() == 1 );
    CHECK( a.dtype() == nrt::DType::Float32 );
    CHECK( a.is_evaluated() );
    NMTOOLS_ASSERT_EQUAL( a.shape(), index_type{} );
    NMTOOLS_ASSERT_EQUAL( a.strides(), index_type{} );
    CHECK( a.item<float>() == 3.14f );
    CHECK( a.data<float>() );

    auto b = nrt::ndarray(42, nmtools::dtype_t<int>{});
    CHECK( b.is_scalar() );
    CHECK( b.dim() == 0 );
    CHECK( b.size() == 1 );
    CHECK( b.dtype() == nrt::DType::Int32 );
    CHECK( b.item<int>() == 42 );

    auto c = nrt::ndarray(7, nmtools::dtype_t<float>{});
    CHECK( c.is_scalar() );
    CHECK( c.dtype() == nrt::DType::Float32 );
    CHECK( c.item<float>() == 7.0f );

    auto d = a;
    CHECK( d.is_scalar() );
    CHECK( d.item<float>() == 3.14f );

    auto e = nrt::ndarray(index_type{2,2}, nrt::DType::Float32);
    e = a;
    CHECK( e.is_scalar() );
    CHECK( e.size() == 1 );
    CHECK( e.item<float>() == 3.14f );

    int rhs[2][2] = {
        {1,2},
        {3,4},
    };
    auto f = nrt::ndarray(9, nmtools::dtype_t<int>{});
    auto g = nrt::ndarray(index_type{2,2}, nrt::DType::Int32);
    g = rhs;
    f = g;
    CHECK( !f.is_scalar() );
    CHECK( f.size() == 4 );
    CHECK( f.dim() == 2 );

    auto h = nrt::ndarray(index_type{2}, nrt::DType::Float32);
    h.resize(index_type{});
    CHECK( h.is_scalar() );
    CHECK( h.size() == 1 );
    h.resize(index_type{2,2});
    CHECK( !h.is_scalar() );
    CHECK( h.size() == 4 );

    auto i = nrt::ndarray(index_type{}, nmtools::dtype_t<float>{});
    CHECK( i.is_scalar() );
    CHECK( i.size() == 1 );
    CHECK( i.data<float>() );

    auto k = nrt::ndarray(a.graph());
    CHECK( k.is_scalar() );
    CHECK( k.dim() == 0 );
    CHECK( k.dtype() == nrt::DType::Float32 );
    CHECK( nmtools::is_scalar(a.graph()) );

    REQUIRE_THROWS( a.view<float>() );
    REQUIRE_THROWS( a.mutable_view<float>() );
    REQUIRE_THROWS( a.item<double>() );
}
TEST_CASE("ndarray strided" * doctest::test_suite("runtime"))
{
    auto a = nrt::ndarray(index_type{2,3},nrt::DType::Int32);
    {
        auto v = a.mutable_view<int32_t>();
        int x = 0;
        for (int i=0;i<2;i++) for (int j=0;j<3;j++) {
            nmtools::apply_at(v,nmtools_tuple{nm_size_t(i),nm_size_t(j)}) = x++;
        }
    }
    int32_t expect_a[2][3] = {
        {0,1,2},
        {3,4,5},
    };

    // transpose() reverses axes and shares the buffer
    auto t = a.transpose();
    NMTOOLS_ASSERT_EQUAL( t.shape(), (index_type{3,2}) );
    NMTOOLS_ASSERT_EQUAL( t.strides(), (index_type{1,3}) );
    int32_t expect_t[3][2] = {
        {0,3},
        {1,4},
        {2,5},
    };
    NMTOOLS_ASSERT_EQUAL( t.view<int32_t>(), expect_t );

    // explicit axes match reverse, negative axes normalize
    auto t2 = a.transpose(index_type{1,0});
    NMTOOLS_ASSERT_EQUAL( t2.view<int32_t>(), expect_t );
    auto t3 = a.transpose(index_type{-1,-2});
    NMTOOLS_ASSERT_EQUAL( t3.view<int32_t>(), expect_t );
    auto idem = a.transpose(index_type{-2,-1}); // normalizes to (0,1)
    NMTOOLS_ASSERT_EQUAL( idem.view<int32_t>(), expect_a );

    // invalid axes panic
    REQUIRE_THROWS( a.transpose(index_type{0,0}) );
    REQUIRE_THROWS( a.transpose(index_type{0,2}) );
    REQUIRE_THROWS( a.transpose(index_type{0}) );

    // as_strided window shares the buffer with the given strides
    auto w = a.as_strided(index_type{2,2},index_type{3,1});
    int32_t expect_w[2][2] = {
        {0,1},
        {3,4},
    };
    NMTOOLS_ASSERT_EQUAL( w.view<int32_t>(), expect_w );
    REQUIRE_THROWS( a.as_strided(index_type{2,2},index_type{3}) );

    // copy() materializes canonically and detaches
    auto c = t.copy();
    NMTOOLS_ASSERT_EQUAL( c.strides(), (index_type{2,1}) );
    NMTOOLS_ASSERT_EQUAL( c.view<int32_t>(), expect_t );
    {
        auto mv = a.mutable_view<int32_t>();
        nmtools::apply_at(mv,nmtools_tuple{nm_size_t(0),nm_size_t(0)}) = 42;
    }
    int32_t expect_t_aliased[3][2] = {
        {42,3},
        {1,4},
        {2,5},
    };
    NMTOOLS_ASSERT_EQUAL( t.view<int32_t>(), expect_t_aliased ); // aliasing
    NMTOOLS_ASSERT_EQUAL( c.view<int32_t>(), expect_t );         // detached

    // graph lowering rejects strided operands until the IR carries strides
    CHECK_THROWS( nmtools::add(t,t) );
    CHECK_THROWS( nmtools::negative(t) );

    // after materializing, graph builders work again
    auto ok = nmtools::add(c,c);
    CHECK( !ok.is_evaluated() );
    NMTOOLS_ASSERT_EQUAL( ok.shape(), (index_type{3,2}) );

    // lazy arrays reject transpose/as_strided/copy
    REQUIRE_THROWS( ok.transpose() );
    REQUIRE_THROWS( ok.as_strided(index_type{6},index_type{1}) );
    REQUIRE_THROWS( ok.copy() );
}

TEST_CASE("ndarray strided reshape/resize" * doctest::test_suite("runtime"))
{
    auto a = nrt::ndarray(index_type{2,3},nrt::DType::Int32);
    {
        auto v = a.mutable_view<int32_t>();
        int x = 0;
        for (int i=0;i<2;i++) for (int j=0;j<3;j++) {
            nmtools::apply_at(v,nmtools_tuple{nm_size_t(i),nm_size_t(j)}) = x++;
        }
    }

    // reshape of a canonical array stays zero-copy
    auto s = a.reshape(index_type{3,2});
    {
        auto sv = s.mutable_view<int32_t>();
        nmtools::apply_at(sv,nmtools_tuple{nm_size_t(0),nm_size_t(0)}) = 77;
    }
    int32_t expect_a[2][3] = {
        {77,1,2},
        {3,4,5},
    };
    NMTOOLS_ASSERT_EQUAL( a.view<int32_t>(), expect_a );

    // reshape of a strided array materializes the logical order
    auto tt = a.transpose();
    auto r = tt.reshape(index_type{6});
    NMTOOLS_ASSERT_EQUAL( r.strides(), (index_type{1}) );
    int32_t expect_r[6] = {77,3,1,4,2,5};
    NMTOOLS_ASSERT_EQUAL( r.view<int32_t>(), expect_r );
    {
        auto av = a.mutable_view<int32_t>();
        nmtools::apply_at(av,nmtools_tuple{nm_size_t(0),nm_size_t(0)}) = -1;
    }
    NMTOOLS_ASSERT_EQUAL( r.view<int32_t>(), expect_r ); // detached

    // resize preserves overlapping elements in logical order
    auto d = nrt::ndarray(index_type{2,3},nrt::DType::Int32);
    {
        auto dv = d.mutable_view<int32_t>();
        int x = 0;
        for (int i=0;i<2;i++) for (int j=0;j<3;j++) {
            nmtools::apply_at(dv,nmtools_tuple{nm_size_t(i),nm_size_t(j)}) = x++;
        }
    }
    d.resize(index_type{2,2});
    NMTOOLS_ASSERT_EQUAL( d.strides(), (index_type{2,1}) );
    int32_t expect_d[2][2] = {
        {0,1},
        {2,3},
    };
    NMTOOLS_ASSERT_EQUAL( d.view<int32_t>(), expect_d );

    // growing resize zero-fills the tail
    d.resize(index_type{2,3});
    int32_t expect_d2[2][3] = {
        {0,1,2},
        {3,0,0},
    };
    NMTOOLS_ASSERT_EQUAL( d.view<int32_t>(), expect_d2 );

    // resize of a strided array copies in logical order and detaches
    auto ta = a.transpose();
    ta.resize(index_type{3});
    NMTOOLS_ASSERT_EQUAL( ta.strides(), (index_type{1}) );
    int32_t expect_ta[3] = {-1,3,1};
    NMTOOLS_ASSERT_EQUAL( ta.view<int32_t>(), expect_ta );
    {
        auto av = a.mutable_view<int32_t>();
        nmtools::apply_at(av,nmtools_tuple{nm_size_t(0),nm_size_t(0)}) = 9;
    }
    NMTOOLS_ASSERT_EQUAL( ta.view<int32_t>(), expect_ta ); // detached
}
