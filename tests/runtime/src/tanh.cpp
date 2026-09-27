#include "nmtools/runtime/ndarray.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/runtime/cpu.hpp"
#include "nmtools/runtime/cpu/tanh.hpp"

#include "nmtools/testing/doctest.hpp"

namespace nm  = nmtools;
namespace fn  = nmtools::functional;
namespace nrt = nmtools::runtime;

TEST_CASE("tanh(f32)" * doctest::test_suite("runtime"))
{
    auto dtype = nm::float32;
    auto shape = nrt::IndexType{1,4};

    float input_data[1][4] = {
        {
            -1.5f
            , -0.5f
            , 0.5f
            , 1.5f
        }
    };

    nrt::ndarray input(shape,nrt::DType::Float32);
    input = input_data;

    auto result = nm::tanh(input);

    CHECK( input.is_evaluated() );
    CHECK( !result.is_evaluated() );
    NMTOOLS_ASSERT_EQUAL( input.shape(), shape );
    CHECK( result.dtype() == nrt::DType::Float32 );

    {
        auto fn = nrt::cpu_tanh(nrt::DType::Float32);
        auto result = fn({input});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::tanh(input.view(dtype))) );
        CHECK_MESSAGE( true, utils::to_string(fn.graph(),utils::Graphviz) );
    }
    {
        auto ctx = nrt::cpu();
        auto fn  = ctx.get_functor(result.graph());
        auto result = (*fn)({input});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::tanh(input.view(dtype))) );
    }
}
