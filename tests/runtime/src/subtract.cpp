#include "nmtools/runtime/ndarray.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/runtime/cpu/subtract.hpp"
#include "nmtools/runtime/cpu.hpp"
#include "nmtools/core/transform/gvn.hpp"

#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nmtools::functional;
namespace nrt = nmtools::runtime;
namespace utils = nm::utils;

TEST_CASE("subtract(f32,f32)" * doctest::test_suite("runtime"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto lhs_shape = nrt::IndexType{3,4};
    auto rhs_shape = nrt::IndexType{3,4};

    nrt::ndarray lhs = nm::random(lhs_shape,dtype,gen);
    nrt::ndarray rhs = nm::random(rhs_shape,dtype,gen);

    /*********************************************************************** */

    auto result = nrt::subtract(lhs,rhs);

    CHECK( lhs.is_evaluated() );
    CHECK( rhs.is_evaluated() );

    CHECK( result.dtype() == nrt::DType::Float32 );
    CHECK( !result.is_evaluated() );
    NMTOOLS_ASSERT_EQUAL( result.shape(), (nrt::IndexType{3,4}) );

    CHECK_MESSAGE( true, utils::to_string(result.graph(),utils::Graphviz) );

    /*********************************************************************** */
    {
        auto fn = nrt::cpu_subtract(nrt::DType::Float32,nrt::DType::Float32);
        auto result = fn({lhs,rhs});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::subtract(lhs.view(dtype),rhs.view(dtype))) );
        CHECK_MESSAGE( true, utils::to_string(fn.graph(),utils::Graphviz) );
    }
    {
        auto ctx = nrt::cpu();
        auto fn  = ctx.get_functor(result.graph());
        auto result = (*fn)({lhs,rhs});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::subtract(lhs.view(dtype),rhs.view(dtype))) );
    }
}

TEST_CASE("subtract(f32,i32)" * doctest::test_suite("runtime"))
{
    auto gen = nm::random_engine();
    auto lhs_dtype = nm::float32;
    auto rhs_dtype = nm::int32;

    auto lhs_shape = nrt::IndexType{3,4};
    auto rhs_shape = nrt::IndexType{3,4};

    nrt::ndarray lhs = nm::random(lhs_shape,lhs_dtype,gen);
    nrt::ndarray rhs = nm::random(rhs_shape,rhs_dtype,gen);

    /*********************************************************************** */

    auto result = nrt::subtract(lhs,rhs);

    CHECK( lhs.is_evaluated() );
    CHECK( rhs.is_evaluated() );

    CHECK( result.dtype() == nrt::DType::Float32 );
    CHECK( !result.is_evaluated() );
    NMTOOLS_ASSERT_EQUAL( result.shape(), (nrt::IndexType{3,4}) );

    CHECK_MESSAGE( true, utils::to_string(result.graph(),utils::Graphviz) );

    /*********************************************************************** */
    auto dtype = nm::float32;
    {
        auto fn = nrt::cpu_subtract(nrt::DType::Float32,nrt::DType::Int32);
        auto result = fn({lhs,rhs});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::subtract(lhs.view(lhs_dtype),rhs.view(rhs_dtype))) );
        CHECK_MESSAGE( true, utils::to_string(fn.graph(),utils::Graphviz) );
    }
    {
        auto ctx = nrt::cpu();
        auto res_hashed = fn::gvn(result.graph(),false,false);
        CHECK( res_hashed.size() != 0 );
        for (const auto& [k,v] : res_hashed) {
            auto key = k;
            auto value = v;
            CHECK_MESSAGE( true, key );
            CHECK_MESSAGE( true, value );
        }
        for (const auto& fn : ctx.functors()) {
            auto fn_hashes = fn::gvn(fn->graph(),false,false);
            CHECK( fn_hashes.size() != 0 );
            for (const auto& [k,v] : fn_hashes) {
                auto key = k;
                auto value = v;
                CHECK_MESSAGE( true, key );
                CHECK_MESSAGE( true, value );
            }
        }
        for (const auto h : ctx.hashes()) {
            CHECK_MESSAGE( true, h );
        }
        auto fn = ctx.get_functor(result.graph());
        auto result = (*fn)({lhs,rhs});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::subtract(lhs.view(lhs_dtype),rhs.view(rhs_dtype))) );
    }
}

TEST_CASE("subtract(i32,i32)" * doctest::test_suite("runtime"))
{
    auto gen = nm::random_engine();
    auto lhs_dtype = nm::int32;
    auto rhs_dtype = nm::int32;

    auto lhs_shape = nrt::IndexType{3,4};
    auto rhs_shape = nrt::IndexType{3,4};

    nrt::ndarray lhs = nm::random(lhs_shape,lhs_dtype,gen);
    nrt::ndarray rhs = nm::random(rhs_shape,rhs_dtype,gen);

    /*********************************************************************** */

    auto result = nrt::subtract(lhs,rhs);

    CHECK( lhs.is_evaluated() );
    CHECK( rhs.is_evaluated() );

    CHECK( result.dtype() == nrt::DType::Int32 );
    CHECK( !result.is_evaluated() );
    NMTOOLS_ASSERT_EQUAL( result.shape(), (nrt::IndexType{3,4}) );

    CHECK_MESSAGE( true, utils::to_string(result.graph(),utils::Graphviz) );

    /*********************************************************************** */
    auto dtype = nm::int32;
    {
        auto fn = nrt::cpu_subtract(nrt::DType::Int32,nrt::DType::Int32);
        auto result = fn({lhs,rhs});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::subtract(lhs.view(lhs_dtype),rhs.view(rhs_dtype))) );
        CHECK_MESSAGE( true, utils::to_string(fn.graph(),utils::Graphviz) );
    }
    {
        auto ctx = nrt::cpu();
        auto fn  = ctx.get_functor(result.graph());
        auto result = (*fn)({lhs,rhs});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::subtract(lhs.view(lhs_dtype),rhs.view(rhs_dtype))) );
    }
}

// operator-
TEST_CASE("subtract(f32,f32)" * doctest::test_suite("runtime"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto lhs_shape = nrt::IndexType{3,4};
    auto rhs_shape = nrt::IndexType{3,4};

    nrt::ndarray lhs = nm::random(lhs_shape,dtype,gen);
    nrt::ndarray rhs = nm::random(rhs_shape,dtype,gen);

    /*********************************************************************** */

    auto result = lhs - rhs;

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
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::subtract(lhs.view(dtype),rhs.view(dtype))) );
    }
}

// operator-
TEST_CASE("subtract(i32,i32)" * doctest::test_suite("runtime"))
{
    auto gen = nm::random_engine();
    auto lhs_dtype = nm::int32;
    auto rhs_dtype = nm::int32;

    auto lhs_shape = nrt::IndexType{3,4};
    auto rhs_shape = nrt::IndexType{3,4};

    nrt::ndarray lhs = nm::random(lhs_shape,lhs_dtype,gen);
    nrt::ndarray rhs = nm::random(rhs_shape,rhs_dtype,gen);

    /*********************************************************************** */

    auto result = lhs - rhs;

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
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::subtract(lhs.view(lhs_dtype),rhs.view(rhs_dtype))) );
    }
}
