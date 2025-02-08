#include "nmtools/core/transform/linearize.hpp"
#include "nmtools/utility/ct_digraph.hpp"
#include "nmtools/array/matmul.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/array/random.hpp"

namespace nm = nmtools;
namespace fn = nmtools::functional;
namespace meta = nmtools::meta;
namespace view = nmtools::view;
namespace na = nmtools::array;
namespace ix = nmtools::index;
namespace utl = nmtools::utl;
namespace utils = nmtools::utils;
namespace utility = nmtools::utility;

using namespace nmtools::literals;

using nmtools_array, nmtools_tuple, nmtools::unwrap;

#if 1
TEST_CASE("apply_graph(matmul)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();
    auto dtype = nm::float32;

    auto lhs_shape = array{3,4};
    auto rhs_shape = array{4,3};

    auto lhs = na::random(lhs_shape,dtype,gen);
    auto rhs = na::random(rhs_shape,dtype,gen);

    auto res = view::matmulv2(lhs,rhs);

    auto graph = fn::linearize(fn::get_compute_graph(unwrap(res)));

    auto function = fn::get_function(graph);
    auto operands = fn::get_operands(graph);

    auto f = function.functor;
    static_assert( meta::len_v<decltype(operands)> == 2 );

    auto result = fn::apply(f,operands);

    auto expected = res;

    NMTOOLS_ASSERT_EQUAL( decltype(f)::arity, 2 );
    NMTOOLS_ASSERT_CLOSE( result, expected );
}
#endif