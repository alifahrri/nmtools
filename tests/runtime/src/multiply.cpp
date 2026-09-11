#include "nmtools/runtime/ndarray.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/runtime/cpu/multiply.hpp"
#include "nmtools/runtime/cpu.hpp"
#include "nmtools/core/transform/gvn.hpp"

#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nmtools::functional;
namespace nrt = nmtools::runtime;
namespace utils = nm::utils;

TEST_CASE("multiply(f32,f32)" * doctest::test_suite("runtime"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto lhs_shape = nrt::IndexType{3,4};
    auto rhs_shape = nrt::IndexType{3,4};

    nrt::ndarray lhs = nm::random(lhs_shape,dtype,gen);
    nrt::ndarray rhs = nm::random(rhs_shape,dtype,gen);

    /*********************************************************************** */

    auto result = nrt::multiply(lhs,rhs);

    CHECK( lhs.is_evaluated() );
    CHECK( rhs.is_evaluated() );

    CHECK( result.dtype() == nrt::DType::Float32 );
    CHECK( !result.is_evaluated() );
    NMTOOLS_ASSERT_EQUAL( result.shape(), (nrt::IndexType{3,4}) );

    CHECK_MESSAGE( true, utils::to_string(result.graph(),utils::Graphviz) );

    /*********************************************************************** */
    {
        auto ctx = nrt::cpu();
        auto fn  = ctx.get_functor(result.graph());
        auto result = (*fn)({lhs,rhs});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::multiply(lhs.view(dtype),rhs.view(dtype))) );
    }
}

TEST_CASE("multiply(f32,i32)" * doctest::test_suite("runtime"))
{
    auto gen = nm::random_engine();
    auto lhs_dtype = nm::float32;
    auto rhs_dtype = nm::int32;

    auto lhs_shape = nrt::IndexType{3,4};
    auto rhs_shape = nrt::IndexType{3,4};

    nrt::ndarray lhs = nm::random(lhs_shape,lhs_dtype,gen);
    nrt::ndarray rhs = nm::random(rhs_shape,rhs_dtype,gen);

    /*********************************************************************** */

    auto result = nrt::multiply(lhs,rhs);

    CHECK( lhs.is_evaluated() );
    CHECK( rhs.is_evaluated() );

    CHECK( result.dtype() == nrt::DType::Float32 );
    CHECK( !result.is_evaluated() );
    NMTOOLS_ASSERT_EQUAL( result.shape(), (nrt::IndexType{3,4}) );

    CHECK_MESSAGE( true, utils::to_string(result.graph(),utils::Graphviz) );

    /*********************************************************************** */
    auto dtype = nm::float32;
    {
        auto ctx = nrt::cpu();
        auto fn  = ctx.get_functor(result.graph());
        auto result = (*fn)({lhs,rhs});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::multiply(lhs.view(lhs_dtype),rhs.view(rhs_dtype))) );
    }
}

TEST_CASE("multiply(i32,i32)" * doctest::test_suite("runtime"))
{
    auto gen = nm::random_engine();
    auto lhs_dtype = nm::int32;
    auto rhs_dtype = nm::int32;

    auto lhs_shape = nrt::IndexType{3,4};
    auto rhs_shape = nrt::IndexType{3,4};

    nrt::ndarray lhs = nm::random(lhs_shape,lhs_dtype,gen);
    nrt::ndarray rhs = nm::random(rhs_shape,rhs_dtype,gen);

    /*********************************************************************** */

    auto result = nrt::multiply(lhs,rhs);

    CHECK( lhs.is_evaluated() );
    CHECK( rhs.is_evaluated() );

    CHECK( result.dtype() == nrt::DType::Int32 );
    CHECK( !result.is_evaluated() );
    NMTOOLS_ASSERT_EQUAL( result.shape(), (nrt::IndexType{3,4}) );

    CHECK_MESSAGE( true, utils::to_string(result.graph(),utils::Graphviz) );

    /*********************************************************************** */
    auto dtype = nm::int32;
    {
        auto fn = nrt::cpu_multiply(nrt::DType::Int32,nrt::DType::Int32);
        auto result = fn({lhs,rhs});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::multiply(lhs.view(lhs_dtype),rhs.view(rhs_dtype))) );
        CHECK_MESSAGE( true, utils::to_string(fn.graph(),utils::Graphviz) );
    }
    {
        auto ctx = nrt::cpu();
        auto fn  = ctx.get_functor(result.graph());
        auto result = (*fn)({lhs,rhs});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::multiply(lhs.view(lhs_dtype),rhs.view(rhs_dtype))) );
    }
}

// operator*
TEST_CASE("multiply(f32,f32)" * doctest::test_suite("runtime"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto lhs_shape = nrt::IndexType{3,4};
    auto rhs_shape = nrt::IndexType{3,4};

    nrt::ndarray lhs = nm::random(lhs_shape,dtype,gen);
    nrt::ndarray rhs = nm::random(rhs_shape,dtype,gen);

    /*********************************************************************** */

    auto result = lhs * rhs;

    CHECK( lhs.is_evaluated() );
    CHECK( rhs.is_evaluated() );

    CHECK( result.dtype() == nrt::DType::Float32 );
    CHECK( !result.is_evaluated() );
    NMTOOLS_ASSERT_EQUAL( result.shape(), (nrt::IndexType{3,4}) );

    CHECK_MESSAGE( true, utils::to_string(result.graph(),utils::Graphviz) );

    /*********************************************************************** */
    {
        auto ctx = nrt::cpu();
        auto fn  = ctx.get_functor(result.graph());
        auto result = (*fn)({lhs,rhs});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::multiply(lhs.view(dtype),rhs.view(dtype))) );
    }
}

// operator*
TEST_CASE("multiply(i32,i32)" * doctest::test_suite("runtime"))
{
    auto gen = nm::random_engine();
    auto lhs_dtype = nm::int32;
    auto rhs_dtype = nm::int32;

    auto lhs_shape = nrt::IndexType{3,4};
    auto rhs_shape = nrt::IndexType{3,4};

    nrt::ndarray lhs = nm::random(lhs_shape,lhs_dtype,gen);
    nrt::ndarray rhs = nm::random(rhs_shape,rhs_dtype,gen);

    /*********************************************************************** */

    auto result = lhs * rhs;

    CHECK( lhs.is_evaluated() );
    CHECK( rhs.is_evaluated() );

    CHECK( result.dtype() == nrt::DType::Int32 );
    CHECK( !result.is_evaluated() );
    NMTOOLS_ASSERT_EQUAL( result.shape(), (nrt::IndexType{3,4}) );

    CHECK_MESSAGE( true, utils::to_string(result.graph(),utils::Graphviz) );

    /*********************************************************************** */
    auto dtype = nm::int32;
    {
        auto ctx = nrt::cpu();
        auto fn  = ctx.get_functor(result.graph());
        auto result = (*fn)({lhs,rhs});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::multiply(lhs.view(lhs_dtype),rhs.view(rhs_dtype))) );
    }
}