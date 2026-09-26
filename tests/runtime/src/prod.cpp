#include "nmtools/runtime/ndarray.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/runtime/cpu/prod.hpp"
#include "nmtools/runtime/cpu.hpp"
#include "nmtools/core/transform/gvn.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

#include "nmtools/testing/doctest.hpp"

namespace nm    = nmtools;
namespace view  = nmtools::view;
namespace fn    = nmtools::functional;
namespace nrt   = nmtools::runtime;
namespace utils = nmtools::utils;

TEST_CASE("prod(f32)" * doctest::test_suite("runtime"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto shape = nrt::Shape(3,4);

    nrt::ndarray x = nm::random(shape,dtype,gen);

    {
        auto result = view::prod(x.view(dtype),-1);
        auto ctree  = fn::get_computational_tree(result);

        auto graph = nrt::to_value(nm::unwrap(ctree));
        auto graphviz = utils::to_string(graph,utils::Graphviz);
        CHECK_MESSAGE( true, graphviz );

        {
            auto rtree = nrt::to_value(ctree);
            auto graph = fn::cse(rtree);
            auto graphviz = utils::to_string(graph,utils::Graphviz);
            CHECK_MESSAGE( true, graphviz );
        }
    }

    CHECK( x.is_evaluated() );

    auto prod = nm::prod(x,-1);

    CHECK( !prod.is_evaluated() );
    CHECK( prod.dtype() == nrt::DType::Float32 );

    {
        auto op = nrt::cpu_prod(nm::float32,false);

        auto result = op({x});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (view::prod(x.view(dtype),-1)) );
    }
    {
        auto ctx = nrt::cpu();
        auto fn  = ctx.get_functor(prod.graph());
        auto result = (*fn)({x});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (view::prod(x.view(dtype),-1)) );
    }
}

TEST_CASE("prod(f32, keepdims)" * doctest::test_suite("runtime"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto shape = nrt::Shape(3,4);

    nrt::ndarray x = nm::random(shape,dtype,gen);

    {
        auto result = view::prod(x.view(dtype),-1,nm::None,nm::None,nm::True);
        auto ctree  = fn::get_computational_tree(result);

        auto graph = nrt::to_value(nm::unwrap(ctree));
        auto graphviz = utils::to_string(graph,utils::Graphviz);
        CHECK_MESSAGE( true, graphviz );

        {
            auto rtree = nrt::to_value(ctree);
            auto graph = fn::cse(rtree);
            auto graphviz = utils::to_string(graph,utils::Graphviz);
            CHECK_MESSAGE( true, graphviz );
        }
    }

    CHECK( x.is_evaluated() );

    auto prod = nm::prod(x,-1,nm::None,nm::None,true);

    CHECK( !prod.is_evaluated() );
    CHECK( prod.dtype() == nrt::DType::Float32 );

    {
        auto op = nrt::cpu_prod(nm::float32,true);

        auto result = op({x});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (view::prod(x.view(dtype),-1,nm::None,nm::None,nm::True)) );
    }
    {
        auto ctx = nrt::cpu();
        auto fn  = ctx.get_functor(prod.graph());
        auto result = (*fn)({x});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (view::prod(x.view(dtype),-1,nm::None,nm::None,nm::True)) );
    }
}

TEST_CASE("prod(f32, 3D)" * doctest::test_suite("runtime"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto shape = nrt::Shape(2,3,4);

    nrt::ndarray x = nm::random(shape,dtype,gen);

    CHECK( x.is_evaluated() );

    auto prod = nm::prod(x,-1);

    CHECK( !prod.is_evaluated() );
    CHECK( prod.dtype() == nrt::DType::Float32 );

    {
        auto op = nrt::cpu_prod(nm::float32,false);

        auto result = op({x});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (view::prod(x.view(dtype),-1)) );
    }
    {
        auto ctx = nrt::cpu();
        auto fn  = ctx.get_functor(prod.graph());
        auto result = (*fn)({x});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (view::prod(x.view(dtype),-1)) );
    }
}

TEST_CASE("prod(f32, 3D, keepdims)" * doctest::test_suite("runtime"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto shape = nrt::Shape(2,3,4);

    nrt::ndarray x = nm::random(shape,dtype,gen);

    CHECK( x.is_evaluated() );

    auto prod = nm::prod(x,-1,nm::None,nm::None,true);

    CHECK( !prod.is_evaluated() );
    CHECK( prod.dtype() == nrt::DType::Float32 );

    {
        auto op = nrt::cpu_prod(nm::float32,true);

        auto result = op({x});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (view::prod(x.view(dtype),-1,nm::None,nm::None,nm::True)) );
    }
    {
        auto ctx = nrt::cpu();
        auto fn  = ctx.get_functor(prod.graph());
        auto result = (*fn)({x});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (view::prod(x.view(dtype),-1,nm::None,nm::None,nm::True)) );
    }
}

TEST_CASE("prod(i32)" * doctest::test_suite("runtime"))
{
    auto dtype = nm::int32;

    auto shape = nrt::IndexType{3,4};

    nrt::ndarray x = nm::full(shape,nm::int32_t{2});

    CHECK( x.is_evaluated() );

    auto prod = nm::prod(x,-1);

    CHECK( !prod.is_evaluated() );
    CHECK( prod.dtype() == nrt::DType::Int32 );

    {
        auto op = nrt::cpu_prod(nm::int32,false);

        auto result = op({x});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (view::prod(x.view(dtype),-1)) );
    }
    {
        auto ctx = nrt::cpu();
        auto fn  = ctx.get_functor(prod.graph());
        auto result = (*fn)({x});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (view::prod(x.view(dtype),-1)) );
    }
}

TEST_CASE("prod(i32, keepdims)" * doctest::test_suite("runtime"))
{
    auto dtype = nm::int32;

    auto shape = nrt::IndexType{3,4};

    nrt::ndarray x = nm::full(shape,nm::int32_t{2});

    CHECK( x.is_evaluated() );

    auto prod = nm::prod(x,-1,nm::None,nm::None,true);

    CHECK( !prod.is_evaluated() );
    CHECK( prod.dtype() == nrt::DType::Int32 );

    {
        auto op = nrt::cpu_prod(nm::int32,true);

        auto result = op({x});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (view::prod(x.view(dtype),-1,nm::None,nm::None,nm::True)) );
    }
    {
        auto ctx = nrt::cpu();
        auto fn  = ctx.get_functor(prod.graph());
        auto result = (*fn)({x});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (view::prod(x.view(dtype),-1,nm::None,nm::None,nm::True)) );
    }
}