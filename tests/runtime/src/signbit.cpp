#include "nmtools/runtime/ndarray.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/runtime/cpu.hpp"
#include "nmtools/runtime/cpu/signbit.hpp"

#include "nmtools/testing/doctest.hpp"

namespace nm  = nmtools;
namespace fn  = nmtools::functional;
namespace nrt = nmtools::runtime;

TEST_CASE("signbit(f32)" * doctest::test_suite("runtime"))
{
    auto shape = nrt::IndexType{1,4};

    float input_data[1][4] = {
        {
            -1.0f
            , 0.0f
            , 1.0f
            , -2.0f
        }
    };

    int8_t expected[1][4] = {
        {
            1
            , 0
            , 0
            , 1
        }
    };

    nrt::ndarray input(shape,nrt::DType::Float32);
    input = input_data;

    auto result = nm::signbit(input);

    CHECK( input.is_evaluated() );
    CHECK( !result.is_evaluated() );
    NMTOOLS_ASSERT_EQUAL( input.shape(), shape );
    CHECK( result.dtype() == nrt::DType::UInt8 );

    {
        auto fn = nrt::cpu_signbit(nrt::DType::Float32);
        auto result = fn({input});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(nm::uint8), expected );
        CHECK_MESSAGE( true, utils::to_string(fn.graph(),utils::Graphviz) );
    }
    {
        auto ctx = nrt::cpu();
        auto fn  = ctx.get_functor(result.graph());
        auto result = (*fn)({input});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(nm::uint8), expected );
    }
}
