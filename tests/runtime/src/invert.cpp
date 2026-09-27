#include "nmtools/runtime/ndarray.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/runtime/cpu.hpp"
#include "nmtools/runtime/cpu/invert.hpp"

#include "nmtools/testing/doctest.hpp"

namespace nm  = nmtools;
namespace fn  = nmtools::functional;
namespace nrt = nmtools::runtime;

TEST_CASE("invert(i32)" * doctest::test_suite("runtime"))
{
    auto dtype = nm::int32;

    auto shape = nrt::IndexType{1,4};

    nrt::ndarray input = nm::full(shape,nm::int32_t{2});

    auto result = nm::invert(input);

    CHECK( input.is_evaluated() );
    CHECK( !result.is_evaluated() );
    CHECK( result.dtype() == nrt::DType::Int32 );

    {
        auto fn = nrt::cpu_invert(nrt::DType::Int32);
        auto result = fn({input});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::invert(input.view(dtype))) );
        CHECK_MESSAGE( true, utils::to_string(fn.graph(),utils::Graphviz) );
    }
    {
        auto ctx = nrt::cpu();
        auto fn  = ctx.get_functor(result.graph());
        auto result = (*fn)({input});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::invert(input.view(dtype))) );
    }
}
