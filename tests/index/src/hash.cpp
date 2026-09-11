#include "nmtools/index/hash.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace ix = nmtools::index;

using namespace nmtools::literals;

TEST_CASE("hash")
{
    auto lhs_shape = nmtools_array{4};
    auto rhs_shape = nmtools_array{1,4};

    auto lhs_hash = ix::hash(lhs_shape);
    auto rhs_hash = ix::hash(rhs_shape);

    CHECK( lhs_hash != 0 );
    CHECK( rhs_hash != 0 );
    CHECK( lhs_hash != rhs_hash );
}

TEST_CASE("hash")
{
    auto lhs_shape = nmtools_array{4,1};
    auto rhs_shape = nmtools_array{1,4};

    CHECK( ix::hash(lhs_shape) != ix::hash(rhs_shape) );
}

TEST_CASE("hash")
{
    constexpr auto lhs_shape = nmtools_array{4,1};
    constexpr auto rhs_shape = nmtools_array{1,4};

    constexpr auto lhs_hash = ix::hash(lhs_shape);
    constexpr auto rhs_hash = ix::hash(rhs_shape);

    CHECK( lhs_hash != rhs_hash );
}

TEST_CASE("hash")
{
    auto lhs_shape = nmtools_list{1,4};
    auto rhs_shape = nmtools_array{1,4};

    CHECK( ix::hash(lhs_shape) == ix::hash(rhs_shape) );
}

TEST_CASE("hash")
{
    auto lhs_shape = nmtools_list{1,1,4};
    auto rhs_shape = nmtools_array{1,4};

    CHECK( ix::hash(lhs_shape) != ix::hash(rhs_shape) );
}

TEST_CASE("hash")
{
    auto lhs_shape = nmtools_tuple{1_ct,4_ct};
    auto rhs_shape = nmtools_tuple{1_ct,4_ct,1_ct};

    CHECK( ix::hash(lhs_shape) != ix::hash(rhs_shape) );
}

TEST_CASE("hash")
{
    auto f32_hash = ix::hash(nm::float32);
    auto f64_hash = ix::hash(nm::float64);
    auto i16_hash = ix::hash(nm::int16);
    auto i32_hash = ix::hash(nm::int32);
    auto i64_hash = ix::hash(nm::int64);
    auto u16_hash = ix::hash(nm::uint16);
    auto u32_hash = ix::hash(nm::uint32);
    auto u64_hash = ix::hash(nm::uint64);

    auto F32_hash = ix::hash(nm::DType::Float32);
    auto F64_hash = ix::hash(nm::DType::Float64);
    auto I16_hash = ix::hash(nm::DType::Int16);
    auto I32_hash = ix::hash(nm::DType::Int32);
    auto I64_hash = ix::hash(nm::DType::Int64);
    auto U16_hash = ix::hash(nm::DType::UInt16);
    auto U32_hash = ix::hash(nm::DType::UInt32);
    auto U64_hash = ix::hash(nm::DType::UInt64);

    CHECK( f32_hash != 0 );
    CHECK( f64_hash != 0 );
    CHECK( i16_hash != 0 );
    CHECK( i32_hash != 0 );
    CHECK( i64_hash != 0 );
    CHECK( u16_hash != 0 );
    CHECK( u32_hash != 0 );
    CHECK( u64_hash != 0 );
    CHECK( f32_hash != f64_hash );
    CHECK( f32_hash != i16_hash );
    CHECK( f32_hash != i32_hash );
    CHECK( f32_hash != i64_hash );
    CHECK( f32_hash != u16_hash );
    CHECK( f32_hash != u32_hash );
    CHECK( f32_hash != u64_hash );

    CHECK( F32_hash != 0 );
    CHECK( F64_hash != 0 );
    CHECK( I16_hash != 0 );
    CHECK( I32_hash != 0 );
    CHECK( I64_hash != 0 );
    CHECK( U16_hash != 0 );
    CHECK( U32_hash != 0 );
    CHECK( U64_hash != 0 );
    CHECK( F32_hash != F64_hash );
    CHECK( F32_hash != I16_hash );
    CHECK( F32_hash != I32_hash );
    CHECK( F32_hash != I64_hash );
    CHECK( F32_hash != U16_hash );
    CHECK( F32_hash != U32_hash );
    CHECK( F32_hash != U64_hash );

    CHECK( f32_hash == F32_hash );
    CHECK( f64_hash == F64_hash );
    CHECK( i16_hash == I16_hash );
    CHECK( i32_hash == I32_hash );
    CHECK( i64_hash == I64_hash );
    CHECK( u16_hash == U16_hash );
    CHECK( u32_hash == U32_hash );
    CHECK( u64_hash == U64_hash );
}

TEST_CASE("hash")
{
    auto ufunc_str = nmtools_string("ufunc");
    auto index_str = nmtools_string("indexing");

    static_assert( nm::is_string_v<decltype(ufunc_str)> );

    auto ufunc_hash = ix::hash(ufunc_str);
    auto index_hash = ix::hash(index_str);

    CHECK( ufunc_hash != 0 );
    CHECK( index_hash != 0 );
    CHECK( ufunc_hash != index_hash );
}