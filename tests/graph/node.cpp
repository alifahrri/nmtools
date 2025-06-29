#include "nmtools/core/node.hpp"
#include "nmtools/core/combinator.hpp"
#include "nmtools/array/flatten.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/ufuncs/cos.hpp"
#include "nmtools/array/sum.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace cb = nmtools::combinator;
namespace fn = nmtools::functional;
namespace view = nmtools::view;
namespace utils = nmtools::utils;

using namespace nmtools::literals;

using nmtools_array, nmtools_tuple, nmtools::unwrap;

static auto join(const nmtools_list<nmtools_string>& strs)
{
    auto str = nmtools_string();

    str += "[";
    str += strs.at(0);
    str += "]";
    for (nm_size_t i=1; i<(nm_size_t)strs.size(); i++) {
        str += " * ";
        str += "[";
        str += strs.at(i);
        str += "]";
    }
    return str;
}

TEST_CASE("to_value(case1)" * doctest::test_suite("graph"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto shape = array{3,4};
    auto input = nm::random(shape,dtype,gen);
    auto node  = fn::node(input);

    using Node = fn::Node<>;

    constexpr auto NODE = nm::meta::to_value_v<decltype(node)>;
    NMTOOLS_ASSERT_EQUAL( (nm::meta::is_same_v<meta::remove_cvref_t<decltype(NODE)>,Node>), true );
    NMTOOLS_ASSERT_EQUAL( NODE.is_buffer(), true );
    NMTOOLS_ASSERT_EQUAL( NODE.dim, nm::len(shape) );
    NMTOOLS_ASSERT_EQUAL( NODE.max_dim, nm::len(shape) );
    NMTOOLS_ASSERT_EQUAL( NODE.is_num, 0 );
    CHECK( NODE.kind == fn::Kind::BUFFERED );
    CHECK( NODE.dtype == fn::Type::Float32 );
    CHECK_MESSAGE( true, join(NODE.to_string()) );
}

TEST_CASE("to_value(case2)" * doctest::test_suite("graph"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::int8;

    auto shape = nmtools_list{3,4};
    auto input = nm::random(shape,dtype,gen);
    auto node  = fn::node(input);

    using Node = fn::Node<>;

    constexpr auto NODE = nm::meta::to_value_v<decltype(node)>;
    NMTOOLS_ASSERT_EQUAL( (nm::meta::is_same_v<meta::remove_cvref_t<decltype(NODE)>,Node>), true );
    NMTOOLS_ASSERT_EQUAL( NODE.is_buffer(), true );
    NMTOOLS_ASSERT_EQUAL( NODE.dim, -1 );
    NMTOOLS_ASSERT_EQUAL( NODE.max_dim, -1 );
    NMTOOLS_ASSERT_EQUAL( NODE.is_num, 0 );
    CHECK( NODE.kind == fn::Kind::BUFFERED );
    CHECK( NODE.dtype == fn::Type::Int8 );
    CHECK_MESSAGE( true, join(NODE.to_string()) );
}

TEST_CASE("to_value(case3)" * doctest::test_suite("graph"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto lhs_shape = array{3,4};
    auto rhs_shape = array{4};

    auto lhs = nm::random(lhs_shape,dtype,gen);
    auto rhs = nm::random(rhs_shape,dtype,gen);

    auto res = view::add(lhs,rhs);

    auto node = unwrap(fn::node(res));

    using Node = fn::Node<>;

    constexpr auto NODE = nm::meta::to_value_v<decltype(node)>;
    NMTOOLS_ASSERT_EQUAL( (nm::meta::is_same_v<meta::remove_cvref_t<decltype(NODE)>,Node>), true );
    NMTOOLS_ASSERT_EQUAL( NODE.is_compute(), true );
    NMTOOLS_ASSERT_EQUAL( NODE.dim, 2 );
    NMTOOLS_ASSERT_EQUAL( NODE.max_dim, 2 );
    NMTOOLS_ASSERT_EQUAL( NODE.is_num, 0 );
    CHECK( NODE.kind == fn::Kind::BINARY_UFUNC );
    CHECK( NODE.dtype == fn::Type::Float32 );
    CHECK_MESSAGE( true, node.to_string() );
    CHECK_MESSAGE( true, join(NODE.to_string()) );
}

TEST_CASE("to_value(case4)" * doctest::test_suite("graph"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto src_shape = array{12};
    auto dst_shape = array{3,4};

    auto input = nm::random(src_shape,dtype,gen);

    auto res = view::reshape(input,dst_shape);

    auto node = unwrap(fn::node(res));

    using Node = fn::Node<>;

    constexpr auto NODE = nm::meta::to_value_v<decltype(node)>;
    NMTOOLS_ASSERT_EQUAL( (nm::meta::is_same_v<meta::remove_cvref_t<decltype(NODE)>,Node>), true );
    NMTOOLS_ASSERT_EQUAL( NODE.is_compute(), true );
    NMTOOLS_ASSERT_EQUAL( NODE.dim, 2 );
    NMTOOLS_ASSERT_EQUAL( NODE.max_dim, 2 );
    NMTOOLS_ASSERT_EQUAL( NODE.is_num, 0 );
    CHECK( NODE.kind == fn::Kind::INDEXING );
    CHECK( NODE.dtype == fn::Type::Float32 );
    CHECK_MESSAGE( true, node.to_string() );
    CHECK_MESSAGE( true, join(NODE.to_string()) );
}

TEST_CASE("to_value(case5)" * doctest::test_suite("graph"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto src_shape = array{3,4};

    auto input = nm::random(src_shape,dtype,gen);
    auto axis  = -1;

    auto res = view::sum(input,axis);

    auto node = unwrap(fn::node(res));

    using Node = fn::Node<>;

    constexpr auto NODE = nm::meta::to_value_v<decltype(node)>;
    NMTOOLS_ASSERT_EQUAL( (nm::meta::is_same_v<meta::remove_cvref_t<decltype(NODE)>,Node>), true );
    NMTOOLS_ASSERT_EQUAL( NODE.is_compute(), true );
    NMTOOLS_ASSERT_EQUAL( NODE.dim, 1 );
    NMTOOLS_ASSERT_EQUAL( NODE.max_dim, 1 );
    NMTOOLS_ASSERT_EQUAL( NODE.is_num, 0 );
    CHECK( NODE.kind == fn::Kind::REDUCE );
    CHECK( NODE.dtype == fn::Type::Float32 );
    CHECK_MESSAGE( true, node.to_string() );
    CHECK_MESSAGE( true, join(NODE.to_string()) );
}

TEST_CASE("to_value(case6)" * doctest::test_suite("graph"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto src_shape = array{3,4};

    auto input = nm::random(src_shape,dtype,gen);

    auto res = view::cos(input);

    auto node = unwrap(fn::node(res));

    using Node = fn::Node<>;

    constexpr auto NODE = nm::meta::to_value_v<decltype(node)>;
    NMTOOLS_ASSERT_EQUAL( (nm::meta::is_same_v<meta::remove_cvref_t<decltype(NODE)>,Node>), true );
    NMTOOLS_ASSERT_EQUAL( NODE.is_compute(), true );
    NMTOOLS_ASSERT_EQUAL( NODE.dim, 2 );
    NMTOOLS_ASSERT_EQUAL( NODE.max_dim, 2 );
    NMTOOLS_ASSERT_EQUAL( NODE.is_num, 0 );
    CHECK( NODE.kind == fn::Kind::UNARY_UFUNC );
    CHECK( NODE.dtype == fn::Type::Float32 );
    CHECK_MESSAGE( true, node.to_string() );
    CHECK_MESSAGE( true, join(NODE.to_string()) );
}

TEST_CASE("to_value(case7)" * doctest::test_suite("graph"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto src_shape = array{3,4};

    auto input = nm::random(src_shape,dtype,gen);
    auto axis  = nm::None;

    auto res = view::sum(input,axis);

    auto node = unwrap(fn::node(res));

    using Node = fn::Node<>;

    constexpr auto NODE = nm::meta::to_value_v<decltype(node)>;
    NMTOOLS_ASSERT_EQUAL( (nm::meta::is_same_v<meta::remove_cvref_t<decltype(NODE)>,Node>), true );
    NMTOOLS_ASSERT_EQUAL( NODE.is_compute(), true );
    NMTOOLS_ASSERT_EQUAL( NODE.dim, -1 );
    NMTOOLS_ASSERT_EQUAL( NODE.max_dim, -1 );
    NMTOOLS_ASSERT_EQUAL( NODE.is_num, 1 );
    CHECK( NODE.kind == fn::Kind::REDUCE );
    CHECK( NODE.dtype == fn::Type::Float32 );
    CHECK_MESSAGE( true, node.to_string() );
    CHECK_MESSAGE( true, join(NODE.to_string()) );
}

TEST_CASE("to_value(case8)" * doctest::test_suite("graph"))
{
    auto input = 3;

    auto node = unwrap(fn::node(input));

    using Node = fn::Node<>;

    constexpr auto NODE = nm::meta::to_value_v<decltype(node)>;
    NMTOOLS_ASSERT_EQUAL( (nm::meta::is_same_v<meta::remove_cvref_t<decltype(NODE)>,Node>), true );
    NMTOOLS_ASSERT_EQUAL( NODE.is_buffer(), true );
    NMTOOLS_ASSERT_EQUAL( NODE.dim, -1 );
    NMTOOLS_ASSERT_EQUAL( NODE.max_dim, -1 );
    NMTOOLS_ASSERT_EQUAL( NODE.is_num, 1 );
    CHECK( NODE.kind == fn::Kind::BUFFERED );
    CHECK( NODE.dtype == fn::Type::Int32 );
    CHECK_MESSAGE( true, node.to_string() );
    CHECK_MESSAGE( true, join(NODE.to_string()) );
}

TEST_CASE("to_value(case9)" * doctest::test_suite("graph"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto src_shape = nmtools_static_vector<int,4>{2,3,4};

    auto input = nm::random(src_shape,dtype,gen);

    auto res = view::cos(input);

    auto node = unwrap(fn::node(res));

    using Node = fn::Node<>;

    constexpr auto NODE = nm::meta::to_value_v<decltype(node)>;
    NMTOOLS_ASSERT_EQUAL( (nm::meta::is_same_v<meta::remove_cvref_t<decltype(NODE)>,Node>), true );
    NMTOOLS_ASSERT_EQUAL( NODE.is_compute(), true );
    NMTOOLS_ASSERT_EQUAL( NODE.dim, -1 );
    NMTOOLS_ASSERT_EQUAL( NODE.max_dim, 4 );
    NMTOOLS_ASSERT_EQUAL( NODE.is_num, 0 );
    CHECK( NODE.kind == fn::Kind::UNARY_UFUNC );
    CHECK( NODE.dtype == fn::Type::Float32 );
    CHECK_MESSAGE( true, node.to_string() );
    CHECK_MESSAGE( true, join(NODE.to_string()) );
}

TEST_CASE("to_value(case10)" * doctest::test_suite("graph"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto src_shape = nmtools_tuple{3_ct,4_ct};

    auto input = nm::random(src_shape,dtype,gen);

    auto res = view::cos(input);

    auto node = unwrap(fn::node(res));

    using Node = fn::Node<>;

    constexpr auto NODE = nm::meta::to_value_v<decltype(node)>;
    NMTOOLS_ASSERT_EQUAL( (nm::meta::is_same_v<meta::remove_cvref_t<decltype(NODE)>,Node>), true );
    NMTOOLS_ASSERT_EQUAL( NODE.is_compute(), true );
    NMTOOLS_ASSERT_EQUAL( NODE.dim, 2 );
    NMTOOLS_ASSERT_EQUAL( NODE.max_dim, 2 );
    NMTOOLS_ASSERT_EQUAL( NODE.is_num, 0 );
    NMTOOLS_ASSERT_EQUAL( NODE.shape, src_shape );
    CHECK( NODE.kind == fn::Kind::UNARY_UFUNC );
    CHECK( NODE.dtype == fn::Type::Float32 );
    CHECK_MESSAGE( true, node.to_string() );
    CHECK_MESSAGE( true, join(NODE.to_string()) );
}

TEST_CASE("to_value(case11)" * doctest::test_suite("graph"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto src_shape = nmtools_tuple{3_ct,4_ct};

    auto input = nm::random(src_shape,dtype,gen);

    auto node = unwrap(fn::node(input));

    using Node = fn::Node<>;

    constexpr auto NODE = nm::meta::to_value_v<decltype(node)>;
    NMTOOLS_ASSERT_EQUAL( (nm::meta::is_same_v<meta::remove_cvref_t<decltype(NODE)>,Node>), true );
    NMTOOLS_ASSERT_EQUAL( NODE.is_buffer(), true );
    NMTOOLS_ASSERT_EQUAL( NODE.dim, 2 );
    NMTOOLS_ASSERT_EQUAL( NODE.max_dim, 2 );
    NMTOOLS_ASSERT_EQUAL( NODE.is_num, 0 );
    NMTOOLS_ASSERT_EQUAL( NODE.shape, src_shape );
    CHECK( NODE.kind == fn::Kind::BUFFERED );
    CHECK( NODE.dtype == fn::Type::Float32 );
    CHECK_MESSAGE( true, node.to_string() );
    CHECK_MESSAGE( true, join(NODE.to_string()) );
}

TEST_CASE("to_value(case12)" * doctest::test_suite("graph"))
{
    auto functors = fn::reshape[array{3,4}] * fn::flatten;

    using Node = fn::Node<>;

    auto node = fn::compute_node_t{functors,nmtools_tuple{},array{3,4},nm::float32};
    static_assert( meta::is_functor_composition_v<decltype(node.functor)> );
    static_assert( meta::len_v<meta::remove_cvref_t<decltype(node.functor.functors)>> == 2 );
    constexpr auto NODE = nm::meta::to_value_v<decltype(node)>;
    NMTOOLS_ASSERT_EQUAL( (nm::meta::is_same_v<meta::remove_cvref_t<decltype(NODE)>,Node>), true );
    NMTOOLS_ASSERT_EQUAL( NODE.is_composition(), true );
    NMTOOLS_ASSERT_EQUAL( NODE.is_buffer(), false );
    CHECK( NODE.composition.size() == 2);

    // TODO: fix
    // CHECK_MESSAGE( true, node.to_string() );
    CHECK_MESSAGE( true, join(NODE.to_string()) );
}

TEST_CASE("to_value(case13)" * doctest::test_suite("graph"))
{
    auto combinator = cb::swap;

    using Node = fn::Node<>;

    auto node = fn::compute_node_t{combinator,nmtools_tuple{},nm::None,nm::None};
    constexpr auto NODE = nm::meta::to_value_v<decltype(node)>;
    NMTOOLS_ASSERT_EQUAL( (nm::meta::is_same_v<meta::remove_cvref_t<decltype(NODE)>,Node>), true );
    NMTOOLS_ASSERT_EQUAL( NODE.is_combinator(), true );
    CHECK( NODE.combinator_type == fn::Combinator::SWAP );

    CHECK_MESSAGE( true, join(NODE.to_string()) );
}

TEST_CASE("to_value(case14)" * doctest::test_suite("graph"))
{
    auto combinator = cb::dup;

    using Node = fn::Node<>;

    auto node = fn::compute_node_t{combinator,nmtools_tuple{},nm::None,nm::None};
    constexpr auto NODE = nm::meta::to_value_v<decltype(node)>;
    NMTOOLS_ASSERT_EQUAL( (nm::meta::is_same_v<meta::remove_cvref_t<decltype(NODE)>,Node>), true );
    NMTOOLS_ASSERT_EQUAL( NODE.is_combinator(), true );
    CHECK( NODE.combinator_type == fn::Combinator::DUP );
    CHECK( NODE.combinator_args == 2 );

    CHECK_MESSAGE( true, join(NODE.to_string()) );
}

TEST_CASE("to_value(case15)" * doctest::test_suite("graph"))
{
    auto functors = fn::reshape[array{3,4}] * fn::flatten * cb::swap;

    using Node = fn::Node<>;

    auto node = fn::compute_node_t{functors,nmtools_tuple{},array{3,4},nm::float32};
    // static_assert( meta::is_functor_composition_v<decltype(node.functor)> );
    // static_assert( meta::len_v<meta::remove_cvref_t<decltype(node.functor.functors)>> == 2 );
    constexpr auto NODE = nm::meta::to_value_v<decltype(node)>;
    NMTOOLS_ASSERT_EQUAL( (nm::meta::is_same_v<meta::remove_cvref_t<decltype(NODE)>,Node>), true );
    NMTOOLS_ASSERT_EQUAL( NODE.is_composition(), true );
    NMTOOLS_ASSERT_EQUAL( NODE.is_buffer(), false );
    CHECK( NODE.composition.size() == 3 );

    // TODO: fix
    // CHECK_MESSAGE( true, node.to_string() );
    CHECK_MESSAGE( true, join(NODE.to_string()) );
}

using Node = fn::Node<>;
using Kind = fn::Kind;
using Type = fn::Type;
using Combinator = fn::Combinator;

TEST_CASE("compose(case1)" * doctest::test_suite("graph"))
{
    auto node1 = Node::compute(Kind::INDEXING,array{2,2},Type::Float32);
    auto node2 = Node::compute(Kind::REDUCE,array{2},Type::Float32);

    auto cnode = node1 * node2;

    CHECK( cnode.is_composition() );
    CHECK( cnode.composition.size() == 2);
    CHECK_MESSAGE( true, join(cnode.to_string()) );
}

TEST_CASE("compose(case2)" * doctest::test_suite("graph"))
{
    auto node1 = Node::combinator(Combinator::DUP);
    auto node2 = Node::compute(Kind::INDEXING,array{2,2},Type::Float32);

    auto node3 = node1 * node2;

    auto node4 = Node::compute(Kind::REDUCE,array{2},Type::Float32);

    auto cnode = node4 * node3;

    CHECK( cnode.is_composition() );
    CHECK( cnode.composition.size() == 3);
    CHECK_MESSAGE( true, join(cnode.to_string()) );
}

enum class RuntimeOpset : int
{
    INVALID=0,
    BROADCAST_TO,
    MAXIMUM,
    SUBTRACT,
    EXP,
    ADD,
    DIVIDE,
};

struct RuntimeAttribute
{
    // TODO: use small vector
    // for index axis, just cast to array of size 1
    using axis_type = nmtools_either<nm::none_t,nmtools_list<nm_index_t>>;
    using keepdims_type = nm_bool_t;

    RuntimeOpset op;
    axis_type axis;
};