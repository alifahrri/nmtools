#include "nmtools/core/transform/linearize.hpp"
#include "nmtools/array/pooling.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/testing/doctest.hpp"

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

TEST_CASE("apply_graph(max_pool2d)" * doctest::test_suite("transform"))
{
    auto gen   = na::random_engine();
    auto dtype = nm::float32;

    auto input = na::random(array{1,1,7,7},dtype,gen);
    auto kernel_size = array{3,3};
    auto stride = array{2,2};
    auto ceil_mode = nm::True;

    auto res = view::max_pool2d(input,kernel_size,stride,nm::None,ceil_mode);

    auto graph = fn::linearize(fn::get_compute_graph(unwrap(res)));
    auto operands = fn::get_operands(graph);
    auto function = fn::get_function(graph);
    auto functor  = function.functor;

    auto result = fn::apply(functor,operands);
    auto expected = res;
    NMTOOLS_ASSERT_CLOSE( result, expected );
}

TEST_CASE("apply_graph(max_pool2d)" * doctest::test_suite("transform"))
{
    auto gen   = na::random_engine();
    auto dtype = nm::float32;

    auto input = na::random(array{1,1,7,7},dtype,gen);
    auto kernel_size = array{3,3};
    auto stride = array{2,2};
    auto ceil_mode = nm::False;

    auto res = view::max_pool2d(input,kernel_size,stride,nm::None,ceil_mode);

    auto graph = fn::linearize(fn::get_compute_graph(unwrap(res)));
    auto operands = fn::get_operands(graph);
    auto function = fn::get_function(graph);
    auto functor  = function.functor;

    auto result = fn::apply(functor,operands);
    auto expected = res;
    NMTOOLS_ASSERT_CLOSE( result, expected );
}

TEST_CASE("apply_graph(max_pool2d)" * doctest::test_suite("transform"))
{
    auto gen   = na::random_engine();
    auto dtype = nm::float32;

    auto input = na::random(array{1,1,7,7},dtype,gen);
    auto kernel_size = array{3,3};
    auto stride = array{2,2};
    auto dilation = array{2,2};
    auto ceil_mode = nm::True;

    auto res = view::max_pool2d(input,kernel_size,stride,dilation,ceil_mode);

    auto graph = fn::linearize(fn::get_compute_graph(unwrap(res)));
    auto operands = fn::get_operands(graph);
    auto function = fn::get_function(graph);
    auto functor  = function.functor;

    auto result = fn::apply(functor,operands);
    auto expected = res;
    NMTOOLS_ASSERT_CLOSE( result, expected );
}