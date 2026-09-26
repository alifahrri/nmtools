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

    array.resize({6,3});
    NMTOOLS_ASSERT_EQUAL( array.shape(), (index_type{6,3}) );

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