#include "nmtools/array/broadcast_to.hpp"
#include "nmtools/runtime/ndarray.hpp"
#include "nmtools/testing/doctest.hpp"

#include "nmtools/array/random.hpp"
#include "nmtools/context/default.hpp"

namespace nm = nmtools;
namespace nrt = nmtools::runtime;

using namespace nm::literals;

TEST_CASE("broadcast_to" * doctest::test_suite("runtime"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto inp_shape = nrt::IndexType{4};
    auto dst_shape = nrt::IndexType{3,4};

    nrt::ndarray input = nm::random(inp_shape,dtype,gen);
    CHECK( input.is_evaluated() );

    auto result = nm::broadcast_to(input,dst_shape);

    CHECK( result.dtype() == nrt::DType::Float32 );
    CHECK( !result.is_evaluated() );
    NMTOOLS_ASSERT_EQUAL( result.shape(), dst_shape );
}

TEST_CASE("broadcast_to" * doctest::test_suite("runtime"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::uint16;

    auto inp_shape = nrt::IndexType{4};
    auto dst_shape = nrt::IndexType{3,4};

    nrt::ndarray input = nm::random(inp_shape,dtype,gen);
    CHECK( input.is_evaluated() );

    auto result = nm::broadcast_to(input,dst_shape);

    CHECK( result.dtype() == nrt::DType::UInt16 );
    CHECK( !result.is_evaluated() );
    NMTOOLS_ASSERT_EQUAL( result.shape(), dst_shape );
}