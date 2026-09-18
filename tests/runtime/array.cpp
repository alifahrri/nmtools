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