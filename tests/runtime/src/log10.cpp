#include "nmtools/runtime/ndarray.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/runtime/cpu.hpp"
#include "nmtools/runtime/cpu/log10.hpp"

#include "nmtools/testing/doctest.hpp"

namespace nm  = nmtools;
namespace fn  = nmtools::functional;
namespace nrt = nmtools::runtime;

TEST_CASE("log10(f32)" * doctest::test_suite("runtime"))
{
    auto dtype = nm::float32;
    auto shape = nrt::IndexType{1,4};

    float input_data[1][4] = {
        {
            1.0f
            , 10.0f
            , 100.0f
            , 1000.0f
        }
    };

    nrt::ndarray input(shape,nrt::DType::Float32);
    input = input_data;

    auto result = nm::log10(input);

    CHECK( input.is_evaluated() );
    CHECK( !result.is_evaluated() );
    NMTOOLS_ASSERT_EQUAL( input.shape(), shape );
    CHECK( result.dtype() == nrt::DType::Float32 );

    {
        auto fn = nrt::cpu_log10(nrt::DType::Float32);
        auto result = fn({input});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::log10(input.view(dtype))) );
        CHECK_MESSAGE( true, utils::to_string(fn.graph(),utils::Graphviz) );
    }
    {
        auto ctx = nrt::cpu();
        auto fn  = ctx.get_functor(result.graph());
        auto result = (*fn)({input});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::log10(input.view(dtype))) );
    }
}
