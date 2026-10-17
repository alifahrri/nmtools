#include "nmtools/runtime/ndarray.hpp"
#include "nmtools/runtime/context.hpp"
#include "nmtools/runtime/cpu.hpp"
#include "nmtools/runtime/cpu/add.hpp"
#include "nmtools/testing/doctest.hpp"

namespace view = nmtools::view;
namespace nrt = nmtools::runtime;
namespace utils = nmtools::utils;

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
    int32_t expect_tt[3][2] = {
        {77,3},
        { 1,4},
        { 2,5},
    };
    NMTOOLS_ASSERT_EQUAL( tt.view<int32_t>(), expect_tt );
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

TEST_CASE("ndarray layout predicates" * doctest::test_suite("runtime"))
{
    auto a = nrt::ndarray(index_type{2,3},nrt::DType::Int32);
    CHECK( a.is_row_major() );
    CHECK_FALSE( a.is_col_major() ); // {2,3}: canonical col-major differs

    auto t = a.transpose();          // strides {1,3}
    CHECK( t.is_col_major() );
    CHECK_FALSE( t.is_row_major() );

    // explicit col-major strides match the transpose layout
    auto w = a.as_strided(index_type{3,2},index_type{1,3});
    CHECK( w.is_col_major() );
    CHECK_FALSE( w.is_row_major() );

    // rank <= 1: canonical row-major and col-major coincide
    auto v = a.reshape(index_type{6});
    CHECK( v.is_row_major() );
    CHECK( v.is_col_major() );
    auto s = nrt::ndarray(1,nmtools::dtype_t<int32_t>{});
    CHECK( s.is_row_major() );
    CHECK( s.is_col_major() );

    // degenerate extent: stride of an extent-1 dim is don't care, so both
    // predicates hold even with a zero stride there
    auto d = a.as_strided(index_type{1,4},index_type{0,1});
    CHECK( d.is_row_major() );
    CHECK( d.is_col_major() );

    // general striding is neither layout
    auto window = a.as_strided(index_type{2,2},index_type{3,1});
    CHECK_FALSE( window.is_row_major() );
    CHECK_FALSE( window.is_col_major() );
    auto mixed = a.as_strided(index_type{2,2},index_type{3,2});
    CHECK_FALSE( mixed.is_row_major() );
    CHECK_FALSE( mixed.is_col_major() );
}

TEST_CASE("ndarray col major graph" * doctest::test_suite("runtime"))
{
    auto a = nrt::ndarray(index_type{2,3},nrt::DType::Int32);
    auto b = nrt::ndarray(index_type{2,3},nrt::DType::Int32);
    {
        auto v = a.mutable_view<int32_t>();
        int x = 0;
        for (int i=0;i<2;i++) for (int j=0;j<3;j++) {
            nmtools::apply_at(v,nmtools_tuple{nm_size_t(i),nm_size_t(j)}) = x++;
        }
    }
    // distinct buffer, equal values: two operands sharing one buffer would
    // be merged by cse into a single input and no longer match a registered
    // functor hash (pre-existing aliasing limitation, unrelated to strides)
    {
        auto src = a.view<int32_t>();
        auto dst = b.mutable_view<int32_t>();
        for (int i=0;i<2;i++) for (int j=0;j<3;j++) {
            nmtools::apply_at(dst,nmtools_tuple{nm_size_t(i),nm_size_t(j)})
                = nmtools::apply_at(src,nmtools_tuple{nm_size_t(i),nm_size_t(j)});
        }
    }

    // operands with column-major strides
    auto lhs = a.transpose();
    auto rhs = b.transpose();
    CHECK( lhs.is_col_major() );
    CHECK( rhs.is_col_major() );

    auto result = nmtools::add(lhs,rhs);
    CHECK( !result.is_evaluated() );
    NMTOOLS_ASSERT_EQUAL( result.shape(), (index_type{3,2}) );
    CHECK( result.dtype() == nrt::DType::Int32 );

    // print the runtime graph built over col-major operands
    CHECK_MESSAGE( true, utils::to_string(result.graph(),utils::Graphviz) );

    // direct cpu execution: re-evaluates through compile-time views, so the
    // strides are honored
    int32_t expect_sum[3][2] = {
        {0,6},
        {2,8},
        {4,10},
    };
    {
        auto fn = nrt::cpu_add(nrt::DType::Int32,nrt::DType::Int32);
        auto evaluated = fn({lhs,rhs});
        CHECK( evaluated.is_evaluated() );
        NMTOOLS_ASSERT_EQUAL( evaluated.view<int32_t>(), expect_sum );
    }

    // context dispatch from the graph works as well
    {
        auto ctx = nrt::cpu();
        auto fn  = ctx.get_functor(result.graph());
        auto evaluated = (*fn)({lhs,rhs});
        CHECK( evaluated.is_evaluated() );
        NMTOOLS_ASSERT_EQUAL( evaluated.view<int32_t>(), expect_sum );
    }
}
