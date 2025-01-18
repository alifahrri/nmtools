#include "nmtools/core/transform/binary_fusion.hpp"
#include "nmtools/utility/ct_digraph.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/ufuncs/tanh.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/array/arange.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/ufuncs/subtract.hpp"
#include "nmtools/array/ufuncs/multiply.hpp"
#include "nmtools/array/ufuncs/divide.hpp"
#include "nmtools/array/ufuncs/fabs.hpp"
#include "nmtools/array/ufuncs/square.hpp"
#include "nmtools/array/ufuncs/tanh.hpp"
#include "nmtools/array/ufuncs/exp.hpp"
#include "nmtools/array/ufuncs/maximum.hpp"
#include "nmtools/array/activations/relu.hpp"
#include "nmtools/array/tile.hpp"
#include "nmtools/array/transpose.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/array/sum.hpp"
#include "nmtools/array/matmul.hpp"
#include "nmtools/array/softmax.hpp"
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

using nmtools_array, nmtools_tuple;

// matmul
TEST_CASE("find_binary_fusion(case1a)" * doctest::test_suite("functional"))
{
    using vector = utl::static_vector<int,5>;

    auto make_vector = [](auto...v){
        auto vec = vector();
        (vec.push_back(v),...);
        return vec;
    };

    auto list = array<vector,5>{
        make_vector(2),
        make_vector(3),
        make_vector(4),
        make_vector(4),
        make_vector()
    };

    auto result = fn::find_binary_fusion(list);

    // NOTE: the operand is unordered
    auto expected = nmtools_tuple{2,3,4};

    NMTOOLS_ASSERT_EQUAL( result, expected );
}

// softmax
TEST_CASE("find_binary_fusion(case2a)" * doctest::test_suite("functional"))
{
    using vector = utl::static_vector<int,5>;

    auto make_vector = [](auto...v){
        auto vec = vector();
        (vec.push_back(v),...);
        return vec;
    };

    auto list = array<vector,5>{
        make_vector(1,2),
        make_vector(2),
        make_vector(3,4),
        make_vector(4),
        make_vector()
    };

    auto result = fn::find_binary_fusion(list);

    // NOTE: the operand is unordered
    auto expected = nmtools_tuple{0,1,2};

    NMTOOLS_ASSERT_EQUAL( result, expected );
}

// var
TEST_CASE("find_binary_fusion(case3a)" * doctest::test_suite("functional"))
{
    using vector = utl::static_vector<int,7>;

    auto make_vector = [](auto...v){
        auto vec = vector();
        (vec.push_back(v),...);
        return vec;
    };

    auto list = array<vector,7>{
        make_vector(2,4),
        make_vector(3),
        make_vector(3),
        make_vector(4),
        make_vector(6),
        make_vector(6),
        make_vector()
    };

    auto result = fn::find_binary_fusion(list);

    // NOTE: the operand is unordered
    auto expected = nmtools_tuple{1,2,3};

    NMTOOLS_ASSERT_EQUAL( result, expected );
}

// matmul
TEST_CASE("transform_binary_fusion(case1a)" * doctest::test_suite("functional"))
{
    auto lhs_shape = array{3,4};
    auto rhs_shape = array{4,3};

    auto lhs = nm::unwrap(na::reshape(na::arange(ix::product(lhs_shape)),lhs_shape));
    auto rhs = nm::unwrap(na::reshape(na::arange(ix::product(rhs_shape)),rhs_shape));

    auto graph = utility::ct_digraph()
        .add_node(0_ct,&lhs)
        .add_node(1_ct,&rhs)
        .add_node(765_ct,fn::reshape[/*dst_shape=*/array{3,3,4}] * fn::tile[/*reps=*/array{1,3}])
        .add_node(447_ct,fn::reshape[/*dst_shape=*/array{1,3,4}] * fn::transpose[/*axes=*/array{1,0}])
        .add_node(635_ct,fn::sum[/*axis=*/-1] * fn::multiply)
        .add_edge(0_ct,765_ct)
        .add_edge(1_ct,447_ct)
        .add_edge(447_ct,635_ct)
        .add_edge(765_ct,635_ct)
    ;

    auto result = fn::transform_binary_fusion(graph);

    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}