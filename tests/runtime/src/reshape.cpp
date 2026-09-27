#include "nmtools/runtime/ndarray.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nmtools::functional;
namespace nrt = nmtools::runtime;

TEST_CASE("reshape" * doctest::test_suite("runtime"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto src_shape = nrt::IndexType{2,3,2};

    nrt::ndarray inp = nm::random(src_shape,dtype,gen);

    auto result = inp.reshape({6,2});

    NMTOOLS_ASSERT_EQUAL( result.shape(), (nmtools_array{6,2}) );
    NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nm::reshape(inp.view(dtype),nmtools_array{6,2})));
}