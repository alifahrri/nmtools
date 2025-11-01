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

/* ======================================================================================================== */

using Kind = fn::Kind;
using Type = fn::Type;
using Layout = fn::Layout;
using Combinator = fn::Combinator;

/* ======================================================================================================== */

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

/* ======================================================================================================== */

using Attribute = fn::Attribute<>;

TEST_CASE("attribute" * doctest::test_suite("graph"))
{
    {
        auto attribute = Attribute();
        CHECK_MESSAGE( attribute.is_none(), attribute.to_string() );
        NMTOOLS_ASSERT_EQUAL( attribute.none, nm::None );
    }
    {
        auto attribute = Attribute(99);
        CHECK_MESSAGE( attribute.is_integer(), attribute.to_string() );
        NMTOOLS_ASSERT_EQUAL( attribute.integer, 99 );
    }
    {
        auto attribute = Attribute(9.9f);
        CHECK_MESSAGE( attribute.is_floating(), attribute.to_string() );
        NMTOOLS_ASSERT_CLOSE( attribute.floating, 9.9 );
    }
    {
        auto attribute = Attribute("example");
        CHECK_MESSAGE( attribute.is_string(), attribute.to_string() );
        CHECK( attribute.string == "example" );
    }
    {
        auto value = nmtools_array{1,2,3};
        auto attribute = Attribute(value);
        CHECK_MESSAGE( attribute.is_index_array(), attribute.to_string() );
        NMTOOLS_ASSERT_EQUAL( attribute.index_array, value );
    }

    {
        constexpr auto attribute = Attribute();
        CHECK_MESSAGE( attribute.is_none(), attribute.to_string() );
        NMTOOLS_ASSERT_EQUAL( attribute.none, nm::None );
    }
    {
        constexpr auto attribute = Attribute(99);
        CHECK_MESSAGE( attribute.is_integer(), attribute.to_string() );
        NMTOOLS_ASSERT_EQUAL( attribute.integer, 99 );
    }
    {
        constexpr auto attribute = Attribute(9.9f);
        CHECK_MESSAGE( attribute.is_floating(), attribute.to_string() );
        NMTOOLS_ASSERT_CLOSE( attribute.floating, 9.9 );
    }
    {
        constexpr auto attribute = Attribute("example");
        CHECK_MESSAGE( attribute.is_string(), attribute.to_string() );
        CHECK( attribute.string == "example" );
    }
    {
        constexpr auto value = nmtools_array{1,2,3};
        constexpr auto attribute = Attribute(value);
        CHECK_MESSAGE( attribute.is_index_array(), attribute.to_string() );
        NMTOOLS_ASSERT_EQUAL( attribute.index_array, value );
    }
}

using Attributes = fn::Attributes<>;

TEST_CASE("attributes" * doctest::test_suite("graph"))
{
    {
        auto attributes = Attributes();
        CHECK( attributes.size() == 0);

        attributes["number"] = 99;
        CHECK( attributes.size() == 1);
        CHECK_MESSAGE( attributes.at("number").is_integer(), attributes.at("number").to_string() );
        NMTOOLS_ASSERT_EQUAL( attributes.at("number").integer, 99 );

        attributes["string"] = "hello world";
        CHECK( attributes.size() == 2 );
        CHECK_MESSAGE( attributes.at("string").is_string(), attributes.at("string").to_string() );
        CHECK( attributes.at("string").string == "hello world" );

        auto value = nmtools_array{1,2,3};
        attributes["indices"] = value;
        CHECK( attributes.size() == 3 );
        CHECK_MESSAGE( attributes.at("indices").is_index_array(), attributes.at("indices").to_string() );
        NMTOOLS_ASSERT_EQUAL( attributes.at("indices").index_array, value );
    }
    {
        constexpr auto value = nmtools_array{1,2,3};
        auto attributes = Attributes();
        attributes.emplace("number",99);
        attributes.emplace("string","hello world");
        attributes.emplace("indices",value);

        CHECK_MESSAGE( attributes.at("number").is_integer(), attributes.at("number").to_string() );
        NMTOOLS_ASSERT_EQUAL( attributes.at("number").integer, 99 );
        CHECK_MESSAGE( attributes.at("string").is_string(), attributes.at("string").to_string() );
        CHECK( attributes.at("string").string == "hello world" );

        CHECK( attributes.size() == 3 );
        CHECK_MESSAGE( attributes.at("indices").is_index_array(), attributes.at("indices").to_string() );
        NMTOOLS_ASSERT_EQUAL( attributes.at("indices").index_array, value );
    }
    #if 1
    {
        constexpr auto value = nmtools_array{1,2,3};
        constexpr auto attributes = [&](){
            auto attributes = Attributes();
            attributes["number"]  = 99;
            attributes["string"]  = "hello world";
            attributes["indices"] = value;
            return attributes;
        }();

        CHECK_MESSAGE( attributes.at("number").is_integer(), attributes.at("number").to_string() );
        NMTOOLS_ASSERT_EQUAL( attributes.at("number").integer, 99 );
        CHECK_MESSAGE( attributes.at("string").is_string(), attributes.at("string").to_string() );
        CHECK( attributes.at("string").string == "hello world" );

        CHECK( attributes.size() == 3 );
        CHECK_MESSAGE( attributes.at("indices").is_index_array(), attributes.at("indices").to_string() );
        NMTOOLS_ASSERT_EQUAL( attributes.at("indices").index_array, value );
    }
    #endif
    // require c++20, constexpr placement new
    #if 0
    {
        constexpr auto value = nmtools_array{1,2,3};
        constexpr auto attributes = [&](){
            auto attributes = Attributes();
            attributes.emplace("number",99);
            attributes.emplace("string","hello world");
            attributes.emplace("indices",value);
            return attributes;
        }();

        CHECK_MESSAGE( attributes.at("number").is_integer(), attributes.at("number").to_string() );
        NMTOOLS_ASSERT_EQUAL( attributes.at("number").integer, 99 );
        CHECK_MESSAGE( attributes.at("string").is_string(), attributes.at("string").to_string() );
        CHECK( attributes.at("string").string == "hello world" );

        CHECK( attributes.size() == 3 );
        CHECK_MESSAGE( attributes.at("indices").is_index_array(), attributes.at("indices").to_string() );
        NMTOOLS_ASSERT_EQUAL( attributes.at("indices").index_array, value );
    }
    #endif
}

/* ======================================================================================================== */

using Node = fn::Node<>;
using nmtools_array;
namespace utl = nmtools::utl;

TEST_CASE("node" * doctest::test_suite("graph"))
{
    // buffer
    {
        auto node = Node::buffer(array{3,4},Type::Float32,Layout::RowMajor);
        CHECK_MESSAGE( node.attributes().size() == 9, node.to_string().front() ); // 9
    }
    // indexing
    {
        auto node = Node::indexing(array{3,4},Type::Float32);
        node.attributes()["indexer"] = "broadcast_to";
        node.attributes()["indexer.n_args"] = 4;
        node.attributes()["indexer.args.0"] = array{4};
        node.attributes()["indexer.args.1"] = array{3,4};
        node.attributes()["indexer.args.2"] = array{1};
        node.attributes()["indexer.args.3"] = 12;
        CHECK( node.attributes().size() == 15 ); // 9+6
        CHECK( node.attributes().count("indexer") );
        CHECK( node.attributes().count("indexer.n_args") );
        CHECK( node.attributes().count("indexer.args.0") );
        CHECK( node.attributes().count("indexer.args.1") );
        CHECK( node.attributes().count("indexer.args.2") );
        CHECK( node.attributes().count("indexer.args.3") );
        {
            auto key = utl::static_string("indexer.args.") + utl::to_string(0);
            CHECK( node.attributes().count(key) );
        }
        CHECK_MESSAGE( true, node.to_string().front() );
    }
    {
        constexpr auto node = [](){
            auto node = Node::indexing(array{3,4},Type::Float32);
            node.attributes()["indexer"] = "broadcast_to";
            node.attributes()["indexer.n_args"] = 4;
            node.attributes()["indexer.args.0"] = array{4};
            node.attributes()["indexer.args.1"] = array{3,4};
            node.attributes()["indexer.args.2"] = array{1};
            node.attributes()["indexer.args.3"] = 12;
            node.attributes()["indexer.args.0.name"] = "src_shape";
            node.attributes()["indexer.args.1.name"] = "dst_shape";
            node.attributes()["indexer.args.2.name"] = "origin";
            node.attributes()["indexer.args.3.name"] = "bsize";
            return node;
        }();
        CHECK_MESSAGE( node.attributes().size() == 19, node.to_string().front() ); // 9+10
    }
    // binary ufunc
    {
        auto node = Node::binary_ufunc(array{3,4},Type::Float32);
        node.attributes()["op"] = "add";
        CHECK_MESSAGE( node.attributes().size() == 10, node.to_string().front() );
    }
    {
        constexpr auto node = [](){
            auto node = Node::binary_ufunc(array{3,4},Type::Float32);
            node.attributes()["op"] = "add";
            return node;
        }();
        CHECK_MESSAGE( node.attributes().size() == 10, node.to_string().front() );
    }
    // reduce
    {
        auto node = Node::reduce(array{3,1},Type::Float32);
        node.attributes()["op"]       = "maximum";
        node.attributes()["axis"]     = -1;
        node.attributes()["dtype"]    = nm::None;
        node.attributes()["initial"]  = nm::None;
        node.attributes()["keepdims"] = 1;
        CHECK_MESSAGE( node.attributes().size() == 13, node.to_string().front() );
    }
    {
        constexpr auto node = [](){
            auto node = Node::reduce(array{3,1},Type::Float32);
            node.attributes()["op"]       = "maximum";
            node.attributes()["axis"]     = -1;
            node.attributes()["dtype"]    = nm::None;
            node.attributes()["initial"]  = nm::None;
            node.attributes()["keepdims"] = 1;
            return node;
        }();
        CHECK_MESSAGE( node.attributes().size() == 13, node.to_string().front() );
    }
}

// composition
TEST_CASE("node(composition)" * doctest::test_suite("graph"))
{
    {
        auto node0 = Node::reduce("maximum",-1,array{3,1},Type::Float32);
        auto node1 = Node::binary_ufunc("add",array{3,4},Type::Float32);
        auto node  = node0 | node1;
        CHECK( node.is_composition() );
        CHECK_MESSAGE( true, node.to_string().front() );
        CHECK_MESSAGE( true, node.to_string().back() );
    }
    {
        constexpr auto node = [](){
            auto node0 = Node::reduce("maximum",-1,array{3,1},Type::Float32);
            auto node1 = Node::binary_ufunc("add",array{3,4},Type::Float32);
            auto node  = node0 | node1;
            return node;
        }();
        CHECK( node.is_composition() );
        CHECK_MESSAGE( true, node.to_string().front() );
        CHECK_MESSAGE( true, node.to_string().back() );
    }
}

// graph
TEST_CASE("to_value(Node)" * doctest::test_suite("graph"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto shape = array{3,4};
    auto input = nm::random(shape,dtype,gen);
    auto node  = fn::node(input);

    using Node = fn::Node<>;

    constexpr auto NODE = nm::meta::to_value_v<decltype(node),Node>;
    NMTOOLS_ASSERT_EQUAL( (nm::meta::is_same_v<meta::remove_cvref_t<decltype(NODE)>,Node>), true );
    NMTOOLS_ASSERT_EQUAL( NODE.is_buffer(), true );
    NMTOOLS_ASSERT_EQUAL( NODE.dim(), nm::len(shape) );
    NMTOOLS_ASSERT_EQUAL( NODE.max_dim(), nm::len(shape) );
    NMTOOLS_ASSERT_EQUAL( NODE.is_num(), 0 );
    CHECK( NODE.kind() == fn::Kind::BUFFERED );
    CHECK( NODE.dtype() == fn::Type::Float32 );
    CHECK_MESSAGE( true, join(NODE.to_string()) );
}

TEST_CASE("to_value(Node)" * doctest::test_suite("graph"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::int8;

    auto shape = nmtools_list{3,4};
    auto input = nm::random(shape,dtype,gen);
    auto node  = fn::node(input);

    using Node = fn::Node<>;

    constexpr auto NODE = nm::meta::to_value_v<decltype(node),Node>;
    // NMTOOLS_ASSERT_EQUAL( (nm::meta::is_same_v<meta::remove_cvref_t<decltype(NODE)>,Node>), true );
    NMTOOLS_STATIC_CHECK_IS_SAME( meta::remove_cvref_t<decltype(NODE)>, Node );
    NMTOOLS_ASSERT_EQUAL( NODE.is_buffer(), true );
    NMTOOLS_ASSERT_EQUAL( NODE.dim(), -1 );
    NMTOOLS_ASSERT_EQUAL( NODE.max_dim(), -1 );
    NMTOOLS_ASSERT_EQUAL( NODE.is_num(), 0 );
    CHECK( NODE.kind() == fn::Kind::BUFFERED );
    CHECK( NODE.dtype() == fn::Type::Int8 );
    CHECK_MESSAGE( true, join(NODE.to_string()) );
}

TEST_CASE("to_value(Node)" * doctest::test_suite("graph"))
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

    constexpr auto NODE = nm::meta::to_value_v<decltype(node),Node>;
    NMTOOLS_ASSERT_EQUAL( (nm::meta::is_same_v<meta::remove_cvref_t<decltype(NODE)>,Node>), true );
    NMTOOLS_ASSERT_EQUAL( NODE.is_compute(), true );
    NMTOOLS_ASSERT_EQUAL( NODE.dim(), 2 );
    NMTOOLS_ASSERT_EQUAL( NODE.max_dim(), 2 );
    NMTOOLS_ASSERT_EQUAL( NODE.is_num(), 0 );
    CHECK( NODE.kind() == fn::Kind::BINARY_UFUNC );
    CHECK( NODE.dtype() == fn::Type::Float32 );
    CHECK_MESSAGE( true, node.to_string() );
    CHECK_MESSAGE( true, join(NODE.to_string()) );
}

TEST_CASE("to_value(Node)" * doctest::test_suite("graph"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto src_shape = array{12};
    auto dst_shape = array{3,4};

    auto input = nm::random(src_shape,dtype,gen);

    auto res = view::reshape(input,dst_shape);

    auto node = unwrap(fn::node(res));

    using Node = fn::Node<>;

    constexpr auto NODE = nm::meta::to_value_v<decltype(node),Node>;
    NMTOOLS_ASSERT_EQUAL( (nm::meta::is_same_v<meta::remove_cvref_t<decltype(NODE)>,Node>), true );
    NMTOOLS_ASSERT_EQUAL( NODE.is_compute(), true );
    NMTOOLS_ASSERT_EQUAL( NODE.dim(), 2 );
    NMTOOLS_ASSERT_EQUAL( NODE.max_dim(), 2 );
    NMTOOLS_ASSERT_EQUAL( NODE.is_num(), 0 );
    CHECK( NODE.kind() == fn::Kind::INDEXING );
    CHECK( NODE.dtype() == fn::Type::Float32 );
    CHECK_MESSAGE( true, node.to_string() );
    CHECK_MESSAGE( true, join(NODE.to_string()) );
}

TEST_CASE("to_value(Node)" * doctest::test_suite("graph"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto src_shape = array{3,4};

    auto input = nm::random(src_shape,dtype,gen);
    auto axis  = -1;

    auto res = view::sum(input,axis);

    auto node = unwrap(fn::node(res));

    using Node = fn::Node<>;

    constexpr auto NODE = nm::meta::to_value_v<decltype(node),Node>;
    NMTOOLS_ASSERT_EQUAL( (nm::meta::is_same_v<meta::remove_cvref_t<decltype(NODE)>,Node>), true );
    NMTOOLS_ASSERT_EQUAL( NODE.is_compute(), true );
    NMTOOLS_ASSERT_EQUAL( NODE.dim(), 1 );
    NMTOOLS_ASSERT_EQUAL( NODE.max_dim(), 1 );
    NMTOOLS_ASSERT_EQUAL( NODE.is_num(), 0 );
    CHECK( NODE.kind() == fn::Kind::REDUCE );
    CHECK( NODE.dtype() == fn::Type::Float32 );
    CHECK_MESSAGE( true, node.to_string() );
    CHECK_MESSAGE( true, join(NODE.to_string()) );
}

TEST_CASE("to_value(Node)" * doctest::test_suite("graph"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto src_shape = array{3,4};

    auto input = nm::random(src_shape,dtype,gen);

    auto res = view::cos(input);

    auto node = unwrap(fn::node(res));

    using Node = fn::Node<>;

    constexpr auto NODE = nm::meta::to_value_v<decltype(node),Node>;
    NMTOOLS_ASSERT_EQUAL( (nm::meta::is_same_v<meta::remove_cvref_t<decltype(NODE)>,Node>), true );
    NMTOOLS_ASSERT_EQUAL( NODE.is_compute(), true );
    NMTOOLS_ASSERT_EQUAL( NODE.dim(), 2 );
    NMTOOLS_ASSERT_EQUAL( NODE.max_dim(), 2 );
    NMTOOLS_ASSERT_EQUAL( NODE.is_num(), 0 );
    CHECK( NODE.kind() == fn::Kind::UNARY_UFUNC );
    CHECK( NODE.dtype() == fn::Type::Float32 );
    CHECK_MESSAGE( true, node.to_string() );
    CHECK_MESSAGE( true, join(NODE.to_string()) );
}

TEST_CASE("to_value(Node)" * doctest::test_suite("graph"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto src_shape = array{3,4};

    auto input = nm::random(src_shape,dtype,gen);
    auto axis  = nm::None;

    auto res = view::sum(input,axis);

    auto node = unwrap(fn::node(res));

    using Node = fn::Node<>;

    constexpr auto NODE = nm::meta::to_value_v<decltype(node),Node>;
    NMTOOLS_ASSERT_EQUAL( (nm::meta::is_same_v<meta::remove_cvref_t<decltype(NODE)>,Node>), true );
    NMTOOLS_ASSERT_EQUAL( NODE.is_compute(), true );
    NMTOOLS_ASSERT_EQUAL( NODE.dim(), -1 );
    NMTOOLS_ASSERT_EQUAL( NODE.max_dim(), -1 );
    NMTOOLS_ASSERT_EQUAL( NODE.is_num(), 1 );
    CHECK( NODE.kind() == fn::Kind::REDUCE );
    CHECK( NODE.dtype() == fn::Type::Float32 );
    CHECK_MESSAGE( true, node.to_string() );
    CHECK_MESSAGE( true, join(NODE.to_string()) );
}

TEST_CASE("to_value(Node)" * doctest::test_suite("graph"))
{
    auto input = 3;

    auto node = unwrap(fn::node(input));

    using Node = fn::Node<>;

    constexpr auto NODE = nm::meta::to_value_v<decltype(node),Node>;
    NMTOOLS_ASSERT_EQUAL( (nm::meta::is_same_v<meta::remove_cvref_t<decltype(NODE)>,Node>), true );
    NMTOOLS_ASSERT_EQUAL( NODE.is_buffer(), true );
    NMTOOLS_ASSERT_EQUAL( NODE.dim(), -1 );
    NMTOOLS_ASSERT_EQUAL( NODE.max_dim(), -1 );
    NMTOOLS_ASSERT_EQUAL( NODE.is_num(), 1 );
    CHECK( NODE.kind() == fn::Kind::BUFFERED );
    CHECK( NODE.dtype() == fn::Type::Int32 );
    CHECK_MESSAGE( true, node.to_string() );
    CHECK_MESSAGE( true, join(NODE.to_string()) );
}

TEST_CASE("to_value(Node)" * doctest::test_suite("graph"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto src_shape = nmtools_static_vector<int,4>{2,3,4};

    auto input = nm::random(src_shape,dtype,gen);

    auto res = view::cos(input);

    auto node = unwrap(fn::node(res));

    using Node = fn::Node<>;

    constexpr auto NODE = nm::meta::to_value_v<decltype(node),Node>;
    NMTOOLS_ASSERT_EQUAL( (nm::meta::is_same_v<meta::remove_cvref_t<decltype(NODE)>,Node>), true );
    NMTOOLS_ASSERT_EQUAL( NODE.is_compute(), true );
    NMTOOLS_ASSERT_EQUAL( NODE.dim(), -1 );
    NMTOOLS_ASSERT_EQUAL( NODE.max_dim(), 4 );
    NMTOOLS_ASSERT_EQUAL( NODE.is_num(), 0 );
    CHECK( NODE.kind() == fn::Kind::UNARY_UFUNC );
    CHECK( NODE.dtype() == fn::Type::Float32 );
    CHECK_MESSAGE( true, node.to_string() );
    CHECK_MESSAGE( true, join(NODE.to_string()) );
}

TEST_CASE("to_value(Node)" * doctest::test_suite("graph"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto src_shape = nmtools_tuple{3_ct,4_ct};

    auto input = nm::random(src_shape,dtype,gen);

    auto res = view::cos(input);

    auto node = unwrap(fn::node(res));

    using Node = fn::Node<>;

    constexpr auto NODE = nm::meta::to_value_v<decltype(node),Node>;
    NMTOOLS_ASSERT_EQUAL( (nm::meta::is_same_v<meta::remove_cvref_t<decltype(NODE)>,Node>), true );
    NMTOOLS_ASSERT_EQUAL( NODE.is_compute(), true );
    NMTOOLS_ASSERT_EQUAL( NODE.dim(), 2 );
    NMTOOLS_ASSERT_EQUAL( NODE.max_dim(), 2 );
    NMTOOLS_ASSERT_EQUAL( NODE.is_num(), 0 );
    NMTOOLS_ASSERT_EQUAL( NODE.shape(), src_shape );
    CHECK( NODE.kind() == fn::Kind::UNARY_UFUNC );
    CHECK( NODE.dtype() == fn::Type::Float32 );
    CHECK_MESSAGE( true, node.to_string() );
    CHECK_MESSAGE( true, join(NODE.to_string()) );
}

TEST_CASE("to_value(Node)" * doctest::test_suite("graph"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto src_shape = nmtools_tuple{3_ct,4_ct};

    auto input = nm::random(src_shape,dtype,gen);

    auto node = unwrap(fn::node(input));

    using Node = fn::Node<>;

    constexpr auto NODE = nm::meta::to_value_v<decltype(node),Node>;
    NMTOOLS_ASSERT_EQUAL( (nm::meta::is_same_v<meta::remove_cvref_t<decltype(NODE)>,Node>), true );
    NMTOOLS_ASSERT_EQUAL( NODE.is_buffer(), true );
    NMTOOLS_ASSERT_EQUAL( NODE.dim(), 2 );
    NMTOOLS_ASSERT_EQUAL( NODE.max_dim(), 2 );
    NMTOOLS_ASSERT_EQUAL( NODE.is_num(), 0 );
    NMTOOLS_ASSERT_EQUAL( NODE.shape(), src_shape );
    CHECK( NODE.kind() == fn::Kind::BUFFERED );
    CHECK( NODE.dtype() == fn::Type::Float32 );
    CHECK_MESSAGE( true, node.to_string() );
    CHECK_MESSAGE( true, join(NODE.to_string()) );
}

TEST_CASE("to_value(Node)" * doctest::test_suite("graph"))
{
    auto functors = fn::reshape[array{3,4}] * fn::flatten;

    using Node = fn::Node<>;

    auto node = fn::compute_node_t{functors,nmtools_tuple{},array{3,4},nm::float32};
    static_assert( meta::is_functor_composition_v<decltype(node.functor)> );
    static_assert( meta::len_v<meta::remove_cvref_t<decltype(node.functor.functors)>> == 2 );
    constexpr auto NODE = nm::meta::to_value_v<decltype(node),Node>;
    NMTOOLS_ASSERT_EQUAL( (nm::meta::is_same_v<meta::remove_cvref_t<decltype(NODE)>,Node>), true );
    NMTOOLS_ASSERT_EQUAL( NODE.is_composition(), true );
    NMTOOLS_ASSERT_EQUAL( NODE.is_buffer(), false );
    CHECK( NODE.composition().size() == 2);

    // TODO: fix
    // CHECK_MESSAGE( true, node.to_string() );
    CHECK_MESSAGE( true, join(NODE.to_string()) );
}

TEST_CASE("to_value(case13)" * doctest::test_suite("graph"))
{
    auto combinator = cb::swap;

    using Node = fn::Node<>;

    auto node = fn::compute_node_t{combinator,nmtools_tuple{},nm::None,nm::None};
    constexpr auto NODE = nm::meta::to_value_v<decltype(node),Node>;
    NMTOOLS_ASSERT_EQUAL( (nm::meta::is_same_v<meta::remove_cvref_t<decltype(NODE)>,Node>), true );
    NMTOOLS_ASSERT_EQUAL( NODE.is_combinator(), true );
    CHECK( NODE.combinator_type() == fn::Combinator::SWAP );

    CHECK_MESSAGE( true, join(NODE.to_string()) );
}

TEST_CASE("to_value(Node)" * doctest::test_suite("graph"))
{
    auto combinator = cb::dup;

    using Node = fn::Node<>;

    auto node = fn::compute_node_t{combinator,nmtools_tuple{},nm::None,nm::None};
    constexpr auto NODE = nm::meta::to_value_v<decltype(node),Node>;
    NMTOOLS_ASSERT_EQUAL( (nm::meta::is_same_v<meta::remove_cvref_t<decltype(NODE)>,Node>), true );
    NMTOOLS_ASSERT_EQUAL( NODE.is_combinator(), true );
    CHECK( NODE.combinator_type() == fn::Combinator::DUP );
    CHECK( NODE.combinator_args() == 2 );

    CHECK_MESSAGE( true, join(NODE.to_string()) );
}

TEST_CASE("to_value(Node)" * doctest::test_suite("graph"))
{
    auto functors = fn::reshape[array{3,4}] * fn::flatten * cb::swap;

    using Node = fn::Node<>;

    auto node = fn::compute_node_t{functors,nmtools_tuple{},array{3,4},nm::float32};
    // static_assert( meta::is_functor_composition_v<decltype(node.functor)> );
    // static_assert( meta::len_v<meta::remove_cvref_t<decltype(node.functor.functors)>> == 2 );
    constexpr auto NODE = nm::meta::to_value_v<decltype(node),Node>;
    NMTOOLS_ASSERT_EQUAL( (nm::meta::is_same_v<meta::remove_cvref_t<decltype(NODE)>,Node>), true );
    NMTOOLS_ASSERT_EQUAL( NODE.is_composition(), true );
    NMTOOLS_ASSERT_EQUAL( NODE.is_buffer(), false );
    CHECK( NODE.composition().size() == 3 );

    // TODO: fix
    // CHECK_MESSAGE( true, node.to_string() );
    CHECK_MESSAGE( true, join(NODE.to_string()) );
}