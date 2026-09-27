#include "nmtools/runtime/ndarray.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/runtime/cpu.hpp"
#include "nmtools/runtime/cpu/exp2.hpp"

#include "nmtools/testing/doctest.hpp"

namespace nm  = nmtools;
namespace fn  = nmtools::functional;
namespace nrt = nmtools::runtime;

TEST_CASE("exp2(f32)" * doctest::test_suite("runtime"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto shape = nrt::IndexType{1,4};

    nrt::ndarray input = nm::random(shape,dtype,gen);

    auto result = nm::exp2(input);

    CHECK( input.is_evaluated() );
    CHECK( !result.is_evaluated() );

    {
        auto fn = nrt::cpu_exp2(nrt::DType::Float32);
        auto result = fn({input});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::exp2(input.view(dtype))) );
        CHECK_MESSAGE( true, utils::to_string(fn.graph(),utils::Graphviz) );
    }
    {
        auto ctx = nrt::cpu();
        auto fn  = ctx.get_functor(result.graph());
        auto result = (*fn)({input});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::exp2(input.view(dtype))) );
    }
}
