#include "nmtools/index/hash.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/runtime/computational_graph.hpp"
#include "nmtools/core/node.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/array/ufuncs/cos.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/sum.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/array/vector_norm.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace nrt = nmtools::runtime;
namespace view = nmtools::view;
namespace nk = nmtools::network;
namespace fn = nmtools::functional;

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

/********************************************************************* */
/* The test cases below check every node of some computational trees:
 *
 * (1) the tree holds buffer/compute node of expected kind
 * (2) meta::to_value_v (compile-time value) and runtime::to_value
 *     produce consistent structural attributes
 * (3) fn::hash on the meta value, the node (which may dispatch to
 *     either path), and the runtime value must be equal
 *
 * NOTE: some runtime::to_value / hash paths may currently raise panic
 * (e.g. indexer attribute whose type-name doesn't fit into the attribute
 * string capacity), in which case the panic is caught so that checks
 * become a failed assert instead of aborting the whole test binary.
 ********************************************************************* */

TEST_CASE("hash(unary_ufunc)" * doctest::test_suite("transform"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto a_shape = tuple{3_ct,4_ct};

    auto a = nm::random(a_shape,dtype,gen);

    auto res = view::cos(a);

    auto graph = unwrap(fn::get_computational_tree(res));

    constexpr auto NUM_NODES = nm::meta::len_v<decltype(unwrap(graph).adjacency_list)>;

    CHECK( (nm_size_t)NUM_NODES == 2 );

    {
        // node 0: output node, unary ufunc
        auto output = graph.nodes(0_ct);
        static_assert( nm::is_compute_node_v<decltype(output)> );
        CHECK_MESSAGE( true, join(output.to_string()) );

        constexpr auto v = nm::to_value_v<nm::remove_cvref_t<decltype(output)>>;
        static_assert( !nm::is_fail_v<decltype(v)> );
        CHECK_MESSAGE( true, v.to_string() );

        try {
            auto r = nrt::to_value(output);
            CHECK_MESSAGE( true, r.to_string() );

            CHECK( r.kind() == fn::Kind::UNARY_UFUNC );
            CHECK( v.kind()  == r.kind() );
            CHECK( v.dtype() == r.dtype() );
            CHECK( (bool)v.is_num() == (bool)r.is_num() );
            CHECK( (nm_index_t)v.dim() == (nm_index_t)r.dim() );

            // hash w/o address: meta path
            auto h = fn::hash(output,nm::True,nm::False);
            CHECK( h != 0 );
            CHECK( h == fn::hash(r,true,false) );
            CHECK( nm::is_constant_index_v<decltype(h)> );

            // hash both shape and address: runtime path
            auto h2 = fn::hash(output);
            CHECK( h2 != 0 );
            CHECK( h2 == fn::hash(r) );
        } catch (std::exception& e) {
            CHECK_MESSAGE( false, "panic runtime::to_value(output): ", e.what() );
        }
    }
    {
        // node 1: input node, buffer with compile-time shape
        auto input = graph.nodes(1_ct);
        static_assert( nm::is_buffer_node_v<decltype(input)> );
        CHECK_MESSAGE( true, join(input.to_string()) );

        constexpr auto v = nm::to_value_v<nm::remove_cvref_t<decltype(input)>>;
        static_assert( !nm::is_fail_v<decltype(v)> );
        CHECK_MESSAGE( true, v.to_string() );

        auto r = nrt::to_value(input);
        CHECK_MESSAGE( true, r.to_string() );

        CHECK( r.kind() == fn::Kind::BUFFERED );
        CHECK( v.kind()  == r.kind() );
        CHECK( v.dtype() == r.dtype() );
        CHECK( (bool)v.is_num() == (bool)r.is_num() );
        CHECK( (nm_index_t)v.dim() == (nm_index_t)r.dim() );

        // hash w/o address and w/o shape
        auto h0 = fn::hash(input,nm::False,nm::False);
        CHECK( h0 != 0 );
        CHECK( h0 == fn::hash(r,false,false) );
        CHECK( nm::is_constant_index_v<decltype(h0)> );

        // hash w/o address, w/ shape
        auto h1 = fn::hash(input,nm::True,nm::False);
        CHECK( h1 != 0 );
        CHECK( h1 == fn::hash(r,true,false) );
        CHECK( nm::is_constant_index_v<decltype(h1)> );

        // hash both shape and address
        auto h2 = fn::hash(input);
        CHECK( h2 != 0 );
        CHECK( h2 == fn::hash(r) );
    }
}

TEST_CASE("hash(unary_ufunc, runtime shape)" * doctest::test_suite("transform"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto a_shape = array{3,4};

    auto a = nm::random(a_shape,dtype,gen);

    auto res = view::cos(a);

    auto graph = unwrap(fn::get_computational_tree(res));

    constexpr auto NUM_NODES = nm::meta::len_v<decltype(unwrap(graph).adjacency_list)>;

    CHECK( (nm_size_t)NUM_NODES == 2 );

    {
        // node 0: output node, unary ufunc with runtime shape
        auto output = graph.nodes(0_ct);
        static_assert( nm::is_compute_node_v<decltype(output)> );
        CHECK_MESSAGE( true, join(output.to_string()) );

        constexpr auto v = nm::to_value_v<nm::remove_cvref_t<decltype(output)>>;
        static_assert( !nm::is_fail_v<decltype(v)> );
        CHECK_MESSAGE( true, v.to_string() );

        try {
            auto r = nrt::to_value(output);
            CHECK_MESSAGE( true, r.to_string() );

            CHECK( r.kind() == fn::Kind::UNARY_UFUNC );
            CHECK( v.kind()  == r.kind() );
            CHECK( v.dtype() == r.dtype() );
            CHECK( (bool)v.is_num() == (bool)r.is_num() );
            CHECK( (nm_index_t)v.dim() == (nm_index_t)r.dim() );

            // hash w/o address: meta path
            auto h = fn::hash(output,nm::True,nm::False);
            CHECK( h != 0 );
            CHECK( h == fn::hash(r,true,false) );

            // hash both shape and address: runtime path
            auto h2 = fn::hash(output);
            CHECK( h2 != 0 );
            CHECK( h2 == fn::hash(r) );
        } catch (std::exception& e) {
            CHECK_MESSAGE( false, "panic runtime::to_value(output): ", e.what() );
        }
    }
    {
        // node 1: input node, buffer with runtime shape
        // NOTE: meta::to_value_v of runtime-shape buffer is available but its
        // shape attribute doesn't carry the runtime shape, so hash parity is
        // expected to fail until shape handling is unified in to_value
        auto input = graph.nodes(1_ct);
        static_assert( nm::is_buffer_node_v<decltype(input)> );
        CHECK_MESSAGE( true, join(input.to_string()) );

        auto r = nrt::to_value(input);
        CHECK_MESSAGE( true, r.to_string() );

        CHECK( r.kind() == fn::Kind::BUFFERED );
        CHECK( (nm_index_t)r.dim() == (nm_index_t)2 );

        // hash w/o address and w/o shape
        auto h0 = fn::hash(input,nm::False,nm::False);
        CHECK( h0 != 0 );
        CHECK( h0 == fn::hash(r,false,false) );

        // hash w/o address, w/ shape
        auto h1 = fn::hash(input,nm::True,nm::False);
        CHECK( h1 != 0 );
        CHECK( h1 == fn::hash(r,true,false) );

        // hash both shape and address
        auto h2 = fn::hash(input);
        CHECK( h2 != 0 );
        CHECK( h2 == fn::hash(r) );
    }
}

// binary ufunc with two same-shape buffers
// NOTE: even for same-shape operands, the tree holds indexing (broadcast_to)
// nodes wrapping each operand buffer
TEST_CASE("hash(binary_ufunc)" * doctest::test_suite("transform"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto a_shape = tuple{3_ct,4_ct};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(a_shape,dtype,gen);

    auto res = view::add(a,b);

    auto graph = unwrap(fn::get_computational_tree(res));

    constexpr auto NUM_NODES = nm::meta::len_v<decltype(unwrap(graph).adjacency_list)>;

    CHECK( (nm_size_t)NUM_NODES == 5 );

    {
        // node 0: output node, binary ufunc
        auto output = graph.nodes(0_ct);
        static_assert( nm::is_compute_node_v<decltype(output)> );
        CHECK_MESSAGE( true, join(output.to_string()) );

        constexpr auto v = nm::to_value_v<nm::remove_cvref_t<decltype(output)>>;
        static_assert( !nm::is_fail_v<decltype(v)> );
        CHECK_MESSAGE( true, v.to_string() );

        auto r = nrt::to_value(output);
        CHECK_MESSAGE( true, r.to_string() );

        CHECK( r.kind() == fn::Kind::BINARY_UFUNC );
        CHECK( v.kind()  == r.kind() );
        CHECK( v.dtype() == r.dtype() );
        CHECK( (bool)v.is_num() == (bool)r.is_num() );
        CHECK( (nm_index_t)v.dim() == (nm_index_t)r.dim() );

        // hash w/o address: meta path
        auto h = fn::hash(output,nm::True,nm::False);
        CHECK( h != 0 );
        CHECK( h == fn::hash(r,true,false) );

        // hash both shape and address: runtime path
        auto h2 = fn::hash(output);
        CHECK( h2 != 0 );
        CHECK( h2 == fn::hash(r) );
    }
    {
        // node 1: broadcast_to node wrapping the first operand buffer
        auto node = graph.nodes(1_ct);
        static_assert( nm::is_compute_node_v<decltype(node)> );
        CHECK_MESSAGE( true, join(node.to_string()) );

        constexpr auto v = nm::to_value_v<nm::remove_cvref_t<decltype(node)>>;
        static_assert( !nm::is_fail_v<decltype(v)> );
        CHECK_MESSAGE( true, v.to_string() );

        try {
            auto r = nrt::to_value(node);
            CHECK_MESSAGE( true, r.to_string() );

            CHECK( r.kind() == fn::Kind::INDEXING );
            CHECK( v.kind()  == r.kind() );
            CHECK( v.dtype() == r.dtype() );
            CHECK( (nm_index_t)v.dim() == (nm_index_t)r.dim() );

            auto h = fn::hash(node,nm::True,nm::False);
            CHECK( h != 0 );
            CHECK( h == fn::hash(r,true,false) );

            auto h2 = fn::hash(node);
            CHECK( h2 != 0 );
            CHECK( h2 == fn::hash(r) );
        } catch (std::exception& e) {
            CHECK_MESSAGE( false, "panic runtime::to_value(node): ", e.what() );
        }
    }
    {
        // node 2: first operand, buffer node
        auto input = graph.nodes(2_ct);
        static_assert( nm::is_buffer_node_v<decltype(input)> );
        CHECK_MESSAGE( true, join(input.to_string()) );

        constexpr auto v = nm::to_value_v<nm::remove_cvref_t<decltype(input)>>;
        static_assert( !nm::is_fail_v<decltype(v)> );
        CHECK_MESSAGE( true, v.to_string() );

        auto r = nrt::to_value(input);
        CHECK_MESSAGE( true, r.to_string() );

        CHECK( r.kind() == fn::Kind::BUFFERED );
        CHECK( v.kind()  == r.kind() );
        CHECK( v.dtype() == r.dtype() );
        CHECK( (bool)v.is_num() == (bool)r.is_num() );
        CHECK( (nm_index_t)v.dim() == (nm_index_t)r.dim() );

        auto h0 = fn::hash(input,nm::False,nm::False);
        CHECK( h0 != 0 );
        CHECK( h0 == fn::hash(r,false,false) );

        auto h1 = fn::hash(input,nm::True,nm::False);
        CHECK( h1 != 0 );
        CHECK( h1 == fn::hash(r,true,false) );

        auto h2 = fn::hash(input);
        CHECK( h2 != 0 );
        CHECK( h2 == fn::hash(r) );
    }
    {
        // node 3: broadcast_to node wrapping the second operand buffer
        auto node = graph.nodes(3_ct);
        static_assert( nm::is_compute_node_v<decltype(node)> );
        CHECK_MESSAGE( true, join(node.to_string()) );

        constexpr auto v = nm::to_value_v<nm::remove_cvref_t<decltype(node)>>;
        static_assert( !nm::is_fail_v<decltype(v)> );
        CHECK_MESSAGE( true, v.to_string() );

        try {
            auto r = nrt::to_value(node);
            CHECK_MESSAGE( true, r.to_string() );

            CHECK( r.kind() == fn::Kind::INDEXING );
            CHECK( v.kind()  == r.kind() );
            CHECK( v.dtype() == r.dtype() );
            CHECK( (nm_index_t)v.dim() == (nm_index_t)r.dim() );

            auto h = fn::hash(node,nm::True,nm::False);
            CHECK( h != 0 );
            CHECK( h == fn::hash(r,true,false) );

            auto h2 = fn::hash(node);
            CHECK( h2 != 0 );
            CHECK( h2 == fn::hash(r) );
        } catch (std::exception& e) {
            CHECK_MESSAGE( false, "panic runtime::to_value(node): ", e.what() );
        }
    }
    {
        // node 4: second operand, buffer node
        auto input = graph.nodes(4_ct);
        static_assert( nm::is_buffer_node_v<decltype(input)> );
        CHECK_MESSAGE( true, join(input.to_string()) );

        constexpr auto v = nm::to_value_v<nm::remove_cvref_t<decltype(input)>>;
        static_assert( !nm::is_fail_v<decltype(v)> );
        CHECK_MESSAGE( true, v.to_string() );

        auto r = nrt::to_value(input);
        CHECK_MESSAGE( true, r.to_string() );

        CHECK( r.kind() == fn::Kind::BUFFERED );
        CHECK( v.kind()  == r.kind() );
        CHECK( v.dtype() == r.dtype() );
        CHECK( (bool)v.is_num() == (bool)r.is_num() );
        CHECK( (nm_index_t)v.dim() == (nm_index_t)r.dim() );

        auto h0 = fn::hash(input,nm::False,nm::False);
        CHECK( h0 != 0 );
        CHECK( h0 == fn::hash(r,false,false) );

        auto h1 = fn::hash(input,nm::True,nm::False);
        CHECK( h1 != 0 );
        CHECK( h1 == fn::hash(r,true,false) );

        auto h2 = fn::hash(input);
        CHECK( h2 != 0 );
        CHECK( h2 == fn::hash(r) );
    }
}

// binary ufunc with a scalar (num) operand: broadcasting + num buffer node
TEST_CASE("hash(binary_ufunc, broadcast)" * doctest::test_suite("transform"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto a_shape = tuple{3_ct,4_ct};

    auto a = nm::random(a_shape,dtype,gen);

    auto res = view::add(a,2);

    auto graph = unwrap(fn::get_computational_tree(res));

    constexpr auto NUM_NODES = nm::meta::len_v<decltype(unwrap(graph).adjacency_list)>;

    CHECK( (nm_size_t)NUM_NODES == 5 );

    {
        // node 0: output node, binary ufunc
        auto output = graph.nodes(0_ct);
        static_assert( nm::is_compute_node_v<decltype(output)> );
        CHECK_MESSAGE( true, join(output.to_string()) );

        constexpr auto v = nm::to_value_v<nm::remove_cvref_t<decltype(output)>>;
        static_assert( !nm::is_fail_v<decltype(v)> );
        CHECK_MESSAGE( true, v.to_string() );

        auto r = nrt::to_value(output);
        CHECK_MESSAGE( true, r.to_string() );

        CHECK( r.kind() == fn::Kind::BINARY_UFUNC );
        CHECK( v.kind()  == r.kind() );
        CHECK( v.dtype() == r.dtype() );
        CHECK( (bool)v.is_num() == (bool)r.is_num() );
        CHECK( (nm_index_t)v.dim() == (nm_index_t)r.dim() );

        auto h = fn::hash(output,nm::True,nm::False);
        CHECK( h != 0 );
        CHECK( h == fn::hash(r,true,false) );

        auto h2 = fn::hash(output);
        CHECK( h2 != 0 );
        CHECK( h2 == fn::hash(r) );
    }
    {
        // node 1: broadcast_to node wrapping the ndarray operand
        auto node = graph.nodes(1_ct);
        static_assert( nm::is_compute_node_v<decltype(node)> );
        CHECK_MESSAGE( true, join(node.to_string()) );

        constexpr auto v = nm::to_value_v<nm::remove_cvref_t<decltype(node)>>;
        static_assert( !nm::is_fail_v<decltype(v)> );
        CHECK_MESSAGE( true, v.to_string() );

        try {
            auto r = nrt::to_value(node);
            CHECK_MESSAGE( true, r.to_string() );

            CHECK( r.kind() == fn::Kind::INDEXING );
            CHECK( v.kind()  == r.kind() );
            CHECK( v.dtype() == r.dtype() );
            CHECK( (nm_index_t)v.dim() == (nm_index_t)r.dim() );

            auto h = fn::hash(node,nm::True,nm::False);
            CHECK( h != 0 );
            CHECK( h == fn::hash(r,true,false) );

            auto h2 = fn::hash(node);
            CHECK( h2 != 0 );
            CHECK( h2 == fn::hash(r) );
        } catch (std::exception& e) {
            CHECK_MESSAGE( false, "panic runtime::to_value(node): ", e.what() );
        }
    }
    {
        // node 2: ndarray operand, buffer node
        auto input = graph.nodes(2_ct);
        static_assert( nm::is_buffer_node_v<decltype(input)> );
        CHECK_MESSAGE( true, join(input.to_string()) );

        constexpr auto v = nm::to_value_v<nm::remove_cvref_t<decltype(input)>>;
        static_assert( !nm::is_fail_v<decltype(v)> );
        CHECK_MESSAGE( true, v.to_string() );

        auto r = nrt::to_value(input);
        CHECK_MESSAGE( true, r.to_string() );

        CHECK( r.kind() == fn::Kind::BUFFERED );
        CHECK( v.kind()  == r.kind() );
        CHECK( v.dtype() == r.dtype() );
        CHECK( (bool)v.is_num() == (bool)r.is_num() );
        CHECK( (nm_index_t)v.dim() == (nm_index_t)r.dim() );

        auto h0 = fn::hash(input,nm::False,nm::False);
        CHECK( h0 != 0 );
        CHECK( h0 == fn::hash(r,false,false) );

        auto h1 = fn::hash(input,nm::True,nm::False);
        CHECK( h1 != 0 );
        CHECK( h1 == fn::hash(r,true,false) );

        auto h2 = fn::hash(input);
        CHECK( h2 != 0 );
        CHECK( h2 == fn::hash(r) );
    }
    {
        // node 3: broadcast_to node wrapping the scalar operand, int32
        auto node = graph.nodes(3_ct);
        static_assert( nm::is_compute_node_v<decltype(node)> );
        CHECK_MESSAGE( true, join(node.to_string()) );

        constexpr auto v = nm::to_value_v<nm::remove_cvref_t<decltype(node)>>;
        static_assert( !nm::is_fail_v<decltype(v)> );
        CHECK_MESSAGE( true, v.to_string() );
        CHECK( v.kind() == fn::Kind::INDEXING );
        CHECK( v.dtype() == fn::Type::Int32 );

        try {
            auto r = nrt::to_value(node);
            CHECK_MESSAGE( true, r.to_string() );

            CHECK( r.kind() == fn::Kind::INDEXING );
            CHECK( v.kind()  == r.kind() );
            CHECK( v.dtype() == r.dtype() );
            CHECK( (nm_index_t)v.dim() == (nm_index_t)r.dim() );

            auto h = fn::hash(node,nm::True,nm::False);
            CHECK( h != 0 );
            CHECK( h == fn::hash(r,true,false) );

            auto h2 = fn::hash(node);
            CHECK( h2 != 0 );
            CHECK( h2 == fn::hash(r) );
        } catch (std::exception& e) {
            CHECK_MESSAGE( false, "panic runtime::to_value(node): ", e.what() );
        }
    }
    {
        // node 4: scalar operand, num buffer node (no shape)
        auto input = graph.nodes(4_ct);
        static_assert( nm::is_buffer_node_v<decltype(input)> );
        CHECK_MESSAGE( true, join(input.to_string()) );

        constexpr auto v = nm::to_value_v<nm::remove_cvref_t<decltype(input)>>;
        static_assert( !nm::is_fail_v<decltype(v)> );
        CHECK_MESSAGE( true, v.to_string() );
        CHECK( v.is_num() );
        CHECK( v.dtype() == fn::Type::Int32 );

        auto r = nrt::to_value(input);
        CHECK_MESSAGE( true, r.to_string() );

        CHECK( r.is_num() );
        CHECK( r.kind() == fn::Kind::BUFFERED );
        CHECK( v.kind()  == r.kind() );
        CHECK( v.dtype() == r.dtype() );
        CHECK( (bool)v.is_num() == (bool)r.is_num() );
        CHECK( (nm_index_t)v.dim() == (nm_index_t)r.dim() );

        auto h0 = fn::hash(input,nm::False,nm::False);
        CHECK( h0 != 0 );
        CHECK( h0 == fn::hash(r,false,false) );

        auto h1 = fn::hash(input,nm::True,nm::False);
        CHECK( h1 != 0 );
        CHECK( h1 == fn::hash(r,true,false) );

        auto h2 = fn::hash(input);
        CHECK( h2 != 0 );
        CHECK( h2 == fn::hash(r) );
    }
}

// reduce with compile-time axis
TEST_CASE("hash(reduce)" * doctest::test_suite("transform"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto a_shape = tuple{3_ct,4_ct};

    auto a = nm::random(a_shape,dtype,gen);

    auto res = view::sum(a,0_ct);

    auto graph = unwrap(fn::get_computational_tree(res));

    constexpr auto NUM_NODES = nm::meta::len_v<decltype(unwrap(graph).adjacency_list)>;

    CHECK( (nm_size_t)NUM_NODES == 2 );

    {
        // node 0: output node, reduce with compile-time axis
        auto output = graph.nodes(0_ct);
        static_assert( nm::is_compute_node_v<decltype(output)> );
        CHECK_MESSAGE( true, join(output.to_string()) );

        constexpr auto v = nm::to_value_v<nm::remove_cvref_t<decltype(output)>>;
        static_assert( !nm::is_fail_v<decltype(v)> );
        CHECK_MESSAGE( true, v.to_string() );

        auto r = nrt::to_value(output);
        CHECK_MESSAGE( true, r.to_string() );

        CHECK( r.kind() == fn::Kind::REDUCE );
        CHECK( v.kind()  == r.kind() );
        CHECK( v.dtype() == r.dtype() );
        CHECK( (bool)v.is_num() == (bool)r.is_num() );
        CHECK( (nm_index_t)v.dim() == (nm_index_t)r.dim() );

        auto h = fn::hash(output,nm::True,nm::False);
        CHECK( h != 0 );
        CHECK( h == fn::hash(r,true,false) );

        auto h2 = fn::hash(output);
        CHECK( h2 != 0 );
        CHECK( h2 == fn::hash(r) );
    }
    {
        // node 1: input node, buffer with compile-time shape
        auto input = graph.nodes(1_ct);
        static_assert( nm::is_buffer_node_v<decltype(input)> );
        CHECK_MESSAGE( true, join(input.to_string()) );

        constexpr auto v = nm::to_value_v<nm::remove_cvref_t<decltype(input)>>;
        static_assert( !nm::is_fail_v<decltype(v)> );
        CHECK_MESSAGE( true, v.to_string() );

        auto r = nrt::to_value(input);
        CHECK_MESSAGE( true, r.to_string() );

        CHECK( r.kind() == fn::Kind::BUFFERED );
        CHECK( v.kind()  == r.kind() );
        CHECK( v.dtype() == r.dtype() );
        CHECK( (bool)v.is_num() == (bool)r.is_num() );
        CHECK( (nm_index_t)v.dim() == (nm_index_t)r.dim() );

        auto h0 = fn::hash(input,nm::False,nm::False);
        CHECK( h0 != 0 );
        CHECK( h0 == fn::hash(r,false,false) );

        auto h1 = fn::hash(input,nm::True,nm::False);
        CHECK( h1 != 0 );
        CHECK( h1 == fn::hash(r,true,false) );

        auto h2 = fn::hash(input);
        CHECK( h2 != 0 );
        CHECK( h2 == fn::hash(r) );
    }
}

// reduce with runtime axis value
// NOTE: with runtime axis, the meta value falls back to the axis type name
// instead of the runtime value, hence hash parity is expected to fail until
// runtime-value attributes are unified in to_value
TEST_CASE("hash(reduce, runtime axis)" * doctest::test_suite("transform"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto a_shape = tuple{3_ct,4_ct};

    auto a = nm::random(a_shape,dtype,gen);

    auto axis = 0;
    auto res = view::sum(a,axis);

    auto graph = unwrap(fn::get_computational_tree(res));

    constexpr auto NUM_NODES = nm::meta::len_v<decltype(unwrap(graph).adjacency_list)>;

    CHECK( (nm_size_t)NUM_NODES == 2 );

    {
        // node 0: output node, reduce with runtime axis
        auto output = graph.nodes(0_ct);
        static_assert( nm::is_compute_node_v<decltype(output)> );
        CHECK_MESSAGE( true, join(output.to_string()) );

        constexpr auto v = nm::to_value_v<nm::remove_cvref_t<decltype(output)>>;
        static_assert( !nm::is_fail_v<decltype(v)> );
        CHECK_MESSAGE( true, v.to_string() );

        auto r = nrt::to_value(output);
        CHECK_MESSAGE( true, r.to_string() );

        CHECK( r.kind() == fn::Kind::REDUCE );
        CHECK( v.kind()  == r.kind() );
        CHECK( v.dtype() == r.dtype() );
        CHECK( (bool)v.is_num() == (bool)r.is_num() );
        CHECK( (nm_index_t)v.dim() == (nm_index_t)r.dim() );

        auto h = fn::hash(output,nm::True,nm::False);
        CHECK( h != 0 );
        CHECK( h == fn::hash(r,true,false) );

        auto h2 = fn::hash(output);
        CHECK( h2 != 0 );
        CHECK( h2 == fn::hash(r) );
    }
    {
        // node 1: input node, buffer with compile-time shape
        auto input = graph.nodes(1_ct);
        static_assert( nm::is_buffer_node_v<decltype(input)> );
        CHECK_MESSAGE( true, join(input.to_string()) );

        constexpr auto v = nm::to_value_v<nm::remove_cvref_t<decltype(input)>>;
        static_assert( !nm::is_fail_v<decltype(v)> );
        CHECK_MESSAGE( true, v.to_string() );

        auto r = nrt::to_value(input);
        CHECK_MESSAGE( true, r.to_string() );

        CHECK( r.kind() == fn::Kind::BUFFERED );
        CHECK( v.kind()  == r.kind() );
        CHECK( v.dtype() == r.dtype() );
        CHECK( (bool)v.is_num() == (bool)r.is_num() );
        CHECK( (nm_index_t)v.dim() == (nm_index_t)r.dim() );

        auto h0 = fn::hash(input,nm::False,nm::False);
        CHECK( h0 != 0 );
        CHECK( h0 == fn::hash(r,false,false) );

        auto h1 = fn::hash(input,nm::True,nm::False);
        CHECK( h1 != 0 );
        CHECK( h1 == fn::hash(r,true,false) );

        auto h2 = fn::hash(input);
        CHECK( h2 != 0 );
        CHECK( h2 == fn::hash(r) );
    }
}

// indexing node (reshape) with compile-time source/target shape
TEST_CASE("hash(indexing)" * doctest::test_suite("transform"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto src_shape = tuple{12_ct};
    auto dst_shape = tuple{3_ct,4_ct};

    auto input = nm::random(src_shape,dtype,gen);

    auto res = view::reshape(input,dst_shape);

    auto graph = unwrap(fn::get_computational_tree(res));

    constexpr auto NUM_NODES = nm::meta::len_v<decltype(unwrap(graph).adjacency_list)>;

    CHECK( (nm_size_t)NUM_NODES == 2 );

    {
        // node 0: output node, indexing (reshape)
        auto output = graph.nodes(0_ct);
        static_assert( nm::is_compute_node_v<decltype(output)> );
        CHECK_MESSAGE( true, join(output.to_string()) );

        constexpr auto v = nm::to_value_v<nm::remove_cvref_t<decltype(output)>>;
        static_assert( !nm::is_fail_v<decltype(v)> );
        CHECK_MESSAGE( true, v.to_string() );
        CHECK( v.kind() == fn::Kind::INDEXING );

        try {
            auto r = nrt::to_value(output);
            CHECK_MESSAGE( true, r.to_string() );

            CHECK( r.kind() == fn::Kind::INDEXING );
            CHECK( v.kind()  == r.kind() );
            CHECK( v.dtype() == r.dtype() );
            CHECK( (bool)v.is_num() == (bool)r.is_num() );
            CHECK( (nm_index_t)v.dim() == (nm_index_t)r.dim() );

            auto h = fn::hash(output,nm::True,nm::False);
            CHECK( h != 0 );
            CHECK( h == fn::hash(r,true,false) );

            auto h2 = fn::hash(output);
            CHECK( h2 != 0 );
            CHECK( h2 == fn::hash(r) );
        } catch (std::exception& e) {
            CHECK_MESSAGE( false, "panic runtime::to_value(output): ", e.what() );
        }
    }
    {
        // node 1: input node, buffer with compile-time shape
        auto input = graph.nodes(1_ct);
        static_assert( nm::is_buffer_node_v<decltype(input)> );
        CHECK_MESSAGE( true, join(input.to_string()) );

        constexpr auto v = nm::to_value_v<nm::remove_cvref_t<decltype(input)>>;
        static_assert( !nm::is_fail_v<decltype(v)> );
        CHECK_MESSAGE( true, v.to_string() );

        auto r = nrt::to_value(input);
        CHECK_MESSAGE( true, r.to_string() );

        CHECK( r.kind() == fn::Kind::BUFFERED );
        CHECK( v.kind()  == r.kind() );
        CHECK( v.dtype() == r.dtype() );
        CHECK( (bool)v.is_num() == (bool)r.is_num() );
        CHECK( (nm_index_t)v.dim() == (nm_index_t)r.dim() );

        auto h0 = fn::hash(input,nm::False,nm::False);
        CHECK( h0 != 0 );
        CHECK( h0 == fn::hash(r,false,false) );

        auto h1 = fn::hash(input,nm::True,nm::False);
        CHECK( h1 != 0 );
        CHECK( h1 == fn::hash(r,true,false) );

        auto h2 = fn::hash(input);
        CHECK( h2 != 0 );
        CHECK( h2 == fn::hash(r) );
    }
}

// indexing node (reshape) with runtime target shape
TEST_CASE("hash(indexing, runtime shape)" * doctest::test_suite("transform"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto src_shape = array{12};
    auto dst_shape = array{3,4};

    auto input = nm::random(src_shape,dtype,gen);

    auto res = view::reshape(input,dst_shape);

    auto graph = unwrap(fn::get_computational_tree(res));

    constexpr auto NUM_NODES = nm::meta::len_v<decltype(unwrap(graph).adjacency_list)>;

    CHECK( (nm_size_t)NUM_NODES == 2 );

    {
        // node 0: output node, indexing (reshape) with runtime target shape
        auto output = graph.nodes(0_ct);
        static_assert( nm::is_compute_node_v<decltype(output)> );
        CHECK_MESSAGE( true, join(output.to_string()) );

        constexpr auto v = nm::to_value_v<nm::remove_cvref_t<decltype(output)>>;
        static_assert( !nm::is_fail_v<decltype(v)> );
        CHECK_MESSAGE( true, v.to_string() );
        CHECK( v.kind() == fn::Kind::INDEXING );

        try {
            auto r = nrt::to_value(output);
            CHECK_MESSAGE( true, r.to_string() );

            CHECK( r.kind() == fn::Kind::INDEXING );
            CHECK( v.kind()  == r.kind() );
            CHECK( v.dtype() == r.dtype() );
            CHECK( (bool)v.is_num() == (bool)r.is_num() );
            CHECK( (nm_index_t)v.dim() == (nm_index_t)r.dim() );

            auto h = fn::hash(output,nm::True,nm::False);
            CHECK( h != 0 );
            CHECK( h == fn::hash(r,true,false) );

            auto h2 = fn::hash(output);
            CHECK( h2 != 0 );
            CHECK( h2 == fn::hash(r) );
        } catch (std::exception& e) {
            CHECK_MESSAGE( false, "panic runtime::to_value(output): ", e.what() );
        }
    }
    {
        // node 1: input node, buffer with runtime shape
        auto input = graph.nodes(1_ct);
        static_assert( nm::is_buffer_node_v<decltype(input)> );
        CHECK_MESSAGE( true, join(input.to_string()) );

        auto r = nrt::to_value(input);
        CHECK_MESSAGE( true, r.to_string() );
        CHECK( r.kind() == fn::Kind::BUFFERED );

        auto h0 = fn::hash(input,nm::False,nm::False);
        CHECK( h0 != 0 );
        CHECK( h0 == fn::hash(r,false,false) );

        auto h1 = fn::hash(input,nm::True,nm::False);
        CHECK( h1 != 0 );
        CHECK( h1 == fn::hash(r,true,false) );

        auto h2 = fn::hash(input);
        CHECK( h2 != 0 );
        CHECK( h2 == fn::hash(r) );
    }
}

// composition: vector_norm is composed of
//   power(broadcast_to(reduce(power(broadcast_to(fabs(x), ord), axis), ...)))
// which involves multiple node kinds; every node is checked below
//
// node kinds in tree order:
//   0  BINARY_UFUNC (power, float64)
//   1  INDEXING (broadcast_to, float64)
//   2  REDUCE (add, axis={-2,-1}, keepdims)
//   3  BINARY_UFUNC (power, float64)
//   4  INDEXING (broadcast_to, float32)
//   5  UNARY_UFUNC (fabs, float32)
//   6  buffer (float32, (2,3,2))
//   7  INDEXING (broadcast_to, int32)
//   8  buffer (int32, num)
//   9  INDEXING (broadcast_to, float32)
//  10  buffer (float32, num)
TEST_CASE("hash(composition)" * doctest::test_suite("transform"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto x = nm::random(tuple{2_ct,3_ct,2_ct},dtype,gen);
    auto axis = array{-2,-1};
    auto keepdims = nm::True;
    auto ord = 1;

    auto res = view::vector_norm(x,axis,keepdims,ord);

    auto graph = unwrap(fn::get_computational_tree(res));

    constexpr auto NUM_NODES = nm::meta::len_v<decltype(unwrap(graph).adjacency_list)>;

    CHECK( (nm_size_t)NUM_NODES == 11 );

    {
        // node 0: root output node, power(-1/2)
        auto output = graph.nodes(0_ct);
        static_assert( nm::is_compute_node_v<decltype(output)> );
        CHECK_MESSAGE( true, join(output.to_string()) );

        constexpr auto v = nm::to_value_v<nm::remove_cvref_t<decltype(output)>>;
        static_assert( !nm::is_fail_v<decltype(v)> );
        CHECK_MESSAGE( true, v.to_string() );
        CHECK( v.kind() == fn::Kind::BINARY_UFUNC );

        auto r = nrt::to_value(output);
        CHECK_MESSAGE( true, r.to_string() );

        CHECK( r.kind() == fn::Kind::BINARY_UFUNC );
        CHECK( v.kind()  == r.kind() );
        CHECK( v.dtype() == r.dtype() );
        CHECK( (nm_index_t)v.dim() == (nm_index_t)r.dim() );

        auto h = fn::hash(output,nm::True,nm::False);
        CHECK( h != 0 );
        CHECK( h == fn::hash(r,true,false) );

        auto h2 = fn::hash(output);
        CHECK( h2 != 0 );
        CHECK( h2 == fn::hash(r) );
    }
    {
        // node 1: broadcast_to node between root power and reduce, float64
        auto node = graph.nodes(1_ct);
        static_assert( nm::is_compute_node_v<decltype(node)> );
        CHECK_MESSAGE( true, join(node.to_string()) );

        constexpr auto v = nm::to_value_v<nm::remove_cvref_t<decltype(node)>>;
        static_assert( !nm::is_fail_v<decltype(v)> );
        CHECK_MESSAGE( true, v.to_string() );
        CHECK( v.kind() == fn::Kind::INDEXING );

        try {
            auto r = nrt::to_value(node);
            CHECK_MESSAGE( true, r.to_string() );

            CHECK( r.kind() == fn::Kind::INDEXING );
            CHECK( v.kind()  == r.kind() );
            CHECK( v.dtype() == r.dtype() );
            CHECK( (nm_index_t)v.dim() == (nm_index_t)r.dim() );

            auto h = fn::hash(node,nm::True,nm::False);
            CHECK( h != 0 );
            CHECK( h == fn::hash(r,true,false) );

            auto h2 = fn::hash(node);
            CHECK( h2 != 0 );
            CHECK( h2 == fn::hash(r) );
        } catch (std::exception& e) {
            CHECK_MESSAGE( false, "panic runtime::to_value(node): ", e.what() );
        }
    }
    {
        // node 2: reduce (add) node over axis {-2,-1}, keepdims
        auto node = graph.nodes(2_ct);
        static_assert( nm::is_compute_node_v<decltype(node)> );
        CHECK_MESSAGE( true, join(node.to_string()) );

        constexpr auto v = nm::to_value_v<nm::remove_cvref_t<decltype(node)>>;
        static_assert( !nm::is_fail_v<decltype(v)> );
        CHECK_MESSAGE( true, v.to_string() );
        CHECK( v.kind() == fn::Kind::REDUCE );

        auto r = nrt::to_value(node);
        CHECK_MESSAGE( true, r.to_string() );

        CHECK( r.kind() == fn::Kind::REDUCE );
        CHECK( v.kind()  == r.kind() );
        CHECK( v.dtype() == r.dtype() );
        CHECK( (nm_index_t)v.dim() == (nm_index_t)r.dim() );

        auto h = fn::hash(node,nm::True,nm::False);
        CHECK( h != 0 );
        CHECK( h == fn::hash(r,true,false) );

        auto h2 = fn::hash(node);
        CHECK( h2 != 0 );
        CHECK( h2 == fn::hash(r) );
    }
    {
        // node 3: power node raising fabs(x) by ord, float64
        auto node = graph.nodes(3_ct);
        static_assert( nm::is_compute_node_v<decltype(node)> );
        CHECK_MESSAGE( true, join(node.to_string()) );

        constexpr auto v = nm::to_value_v<nm::remove_cvref_t<decltype(node)>>;
        static_assert( !nm::is_fail_v<decltype(v)> );
        CHECK_MESSAGE( true, v.to_string() );
        CHECK( v.kind() == fn::Kind::BINARY_UFUNC );

        auto r = nrt::to_value(node);
        CHECK_MESSAGE( true, r.to_string() );

        CHECK( r.kind() == fn::Kind::BINARY_UFUNC );
        CHECK( v.kind()  == r.kind() );
        CHECK( v.dtype() == r.dtype() );
        CHECK( (nm_index_t)v.dim() == (nm_index_t)r.dim() );

        auto h = fn::hash(node,nm::True,nm::False);
        CHECK( h != 0 );
        CHECK( h == fn::hash(r,true,false) );

        auto h2 = fn::hash(node);
        CHECK( h2 != 0 );
        CHECK( h2 == fn::hash(r) );
    }
    {
        // node 4: broadcast_to node between power and fabs, float32
        auto node = graph.nodes(4_ct);
        static_assert( nm::is_compute_node_v<decltype(node)> );
        CHECK_MESSAGE( true, join(node.to_string()) );

        constexpr auto v = nm::to_value_v<nm::remove_cvref_t<decltype(node)>>;
        static_assert( !nm::is_fail_v<decltype(v)> );
        CHECK_MESSAGE( true, v.to_string() );
        CHECK( v.kind() == fn::Kind::INDEXING );

        try {
            auto r = nrt::to_value(node);
            CHECK_MESSAGE( true, r.to_string() );

            CHECK( r.kind() == fn::Kind::INDEXING );
            CHECK( v.kind()  == r.kind() );
            CHECK( v.dtype() == r.dtype() );
            CHECK( (nm_index_t)v.dim() == (nm_index_t)r.dim() );

            auto h = fn::hash(node,nm::True,nm::False);
            CHECK( h != 0 );
            CHECK( h == fn::hash(r,true,false) );

            auto h2 = fn::hash(node);
            CHECK( h2 != 0 );
            CHECK( h2 == fn::hash(r) );
        } catch (std::exception& e) {
            CHECK_MESSAGE( false, "panic runtime::to_value(node): ", e.what() );
        }
    }
    {
        // node 5: fabs node, unary ufunc
        auto node = graph.nodes(5_ct);
        static_assert( nm::is_compute_node_v<decltype(node)> );
        CHECK_MESSAGE( true, join(node.to_string()) );

        constexpr auto v = nm::to_value_v<nm::remove_cvref_t<decltype(node)>>;
        static_assert( !nm::is_fail_v<decltype(v)> );
        CHECK_MESSAGE( true, v.to_string() );
        CHECK( v.kind() == fn::Kind::UNARY_UFUNC );

        auto r = nrt::to_value(node);
        CHECK_MESSAGE( true, r.to_string() );

        CHECK( r.kind() == fn::Kind::UNARY_UFUNC );
        CHECK( v.kind()  == r.kind() );
        CHECK( v.dtype() == r.dtype() );
        CHECK( (nm_index_t)v.dim() == (nm_index_t)r.dim() );

        auto h = fn::hash(node,nm::True,nm::False);
        CHECK( h != 0 );
        CHECK( h == fn::hash(r,true,false) );

        auto h2 = fn::hash(node);
        CHECK( h2 != 0 );
        CHECK( h2 == fn::hash(r) );
    }
    {
        // node 6: input buffer of fabs
        auto input = graph.nodes(6_ct);
        static_assert( nm::is_buffer_node_v<decltype(input)> );
        CHECK_MESSAGE( true, join(input.to_string()) );

        constexpr auto v = nm::to_value_v<nm::remove_cvref_t<decltype(input)>>;
        static_assert( !nm::is_fail_v<decltype(v)> );
        CHECK_MESSAGE( true, v.to_string() );

        auto r = nrt::to_value(input);
        CHECK_MESSAGE( true, r.to_string() );

        CHECK( r.kind() == fn::Kind::BUFFERED );
        CHECK( v.kind()  == r.kind() );
        CHECK( v.dtype() == r.dtype() );
        CHECK( (bool)v.is_num() == (bool)r.is_num() );
        CHECK( (nm_index_t)v.dim() == (nm_index_t)r.dim() );

        auto h0 = fn::hash(input,nm::False,nm::False);
        CHECK( h0 != 0 );
        CHECK( h0 == fn::hash(r,false,false) );

        auto h1 = fn::hash(input,nm::True,nm::False);
        CHECK( h1 != 0 );
        CHECK( h1 == fn::hash(r,true,false) );

        auto h2 = fn::hash(input);
        CHECK( h2 != 0 );
        CHECK( h2 == fn::hash(r) );
    }
    {
        // node 7: broadcast_to node of the scalar ord operand, int32
        auto node = graph.nodes(7_ct);
        static_assert( nm::is_compute_node_v<decltype(node)> );
        CHECK_MESSAGE( true, join(node.to_string()) );

        constexpr auto v = nm::to_value_v<nm::remove_cvref_t<decltype(node)>>;
        static_assert( !nm::is_fail_v<decltype(v)> );
        CHECK_MESSAGE( true, v.to_string() );
        CHECK( v.kind() == fn::Kind::INDEXING );

        try {
            auto r = nrt::to_value(node);
            CHECK_MESSAGE( true, r.to_string() );

            CHECK( r.kind() == fn::Kind::INDEXING );
            CHECK( v.kind()  == r.kind() );
            CHECK( v.dtype() == r.dtype() );
            CHECK( (nm_index_t)v.dim() == (nm_index_t)r.dim() );

            auto h = fn::hash(node,nm::True,nm::False);
            CHECK( h != 0 );
            CHECK( h == fn::hash(r,true,false) );

            auto h2 = fn::hash(node);
            CHECK( h2 != 0 );
            CHECK( h2 == fn::hash(r) );
        } catch (std::exception& e) {
            CHECK_MESSAGE( false, "panic runtime::to_value(node): ", e.what() );
        }
    }
    {
        // node 8: scalar ord operand, num buffer node
        auto input = graph.nodes(8_ct);
        static_assert( nm::is_buffer_node_v<decltype(input)> );
        CHECK_MESSAGE( true, join(input.to_string()) );

        constexpr auto v = nm::to_value_v<nm::remove_cvref_t<decltype(input)>>;
        static_assert( !nm::is_fail_v<decltype(v)> );
        CHECK_MESSAGE( true, v.to_string() );

        auto r = nrt::to_value(input);
        CHECK_MESSAGE( true, r.to_string() );

        CHECK( r.kind() == fn::Kind::BUFFERED );
        CHECK( v.kind()  == r.kind() );
        CHECK( v.dtype() == r.dtype() );
        CHECK( (bool)v.is_num() == (bool)r.is_num() );
        CHECK( (nm_index_t)v.dim() == (nm_index_t)r.dim() );

        auto h0 = fn::hash(input,nm::False,nm::False);
        CHECK( h0 != 0 );
        CHECK( h0 == fn::hash(r,false,false) );

        auto h1 = fn::hash(input,nm::True,nm::False);
        CHECK( h1 != 0 );
        CHECK( h1 == fn::hash(r,true,false) );

        auto h2 = fn::hash(input);
        CHECK( h2 != 0 );
        CHECK( h2 == fn::hash(r) );
    }
    {
        // node 9: broadcast_to node between reduce and scalar 1 operand, float32
        auto node = graph.nodes(9_ct);
        static_assert( nm::is_compute_node_v<decltype(node)> );
        CHECK_MESSAGE( true, join(node.to_string()) );

        constexpr auto v = nm::to_value_v<nm::remove_cvref_t<decltype(node)>>;
        static_assert( !nm::is_fail_v<decltype(v)> );
        CHECK_MESSAGE( true, v.to_string() );
        CHECK( v.kind() == fn::Kind::INDEXING );

        try {
            auto r = nrt::to_value(node);
            CHECK_MESSAGE( true, r.to_string() );

            CHECK( r.kind() == fn::Kind::INDEXING );
            CHECK( v.kind()  == r.kind() );
            CHECK( v.dtype() == r.dtype() );
            CHECK( (nm_index_t)v.dim() == (nm_index_t)r.dim() );

            auto h = fn::hash(node,nm::True,nm::False);
            CHECK( h != 0 );
            CHECK( h == fn::hash(r,true,false) );

            auto h2 = fn::hash(node);
            CHECK( h2 != 0 );
            CHECK( h2 == fn::hash(r) );
        } catch (std::exception& e) {
            CHECK_MESSAGE( false, "panic runtime::to_value(node): ", e.what() );
        }
    }
    {
        // node 10: scalar 1 operand, num buffer node
        auto input = graph.nodes(10_ct);
        static_assert( nm::is_buffer_node_v<decltype(input)> );
        CHECK_MESSAGE( true, join(input.to_string()) );

        constexpr auto v = nm::to_value_v<nm::remove_cvref_t<decltype(input)>>;
        static_assert( !nm::is_fail_v<decltype(v)> );
        CHECK_MESSAGE( true, v.to_string() );

        auto r = nrt::to_value(input);
        CHECK_MESSAGE( true, r.to_string() );

        CHECK( r.kind() == fn::Kind::BUFFERED );
        CHECK( v.kind()  == r.kind() );
        CHECK( v.dtype() == r.dtype() );
        CHECK( (bool)v.is_num() == (bool)r.is_num() );
        CHECK( (nm_index_t)v.dim() == (nm_index_t)r.dim() );

        auto h0 = fn::hash(input,nm::False,nm::False);
        CHECK( h0 != 0 );
        CHECK( h0 == fn::hash(r,false,false) );

        auto h1 = fn::hash(input,nm::True,nm::False);
        CHECK( h1 != 0 );
        CHECK( h1 == fn::hash(r,true,false) );

        auto h2 = fn::hash(input);
        CHECK( h2 != 0 );
        CHECK( h2 == fn::hash(r) );
    }
    // TODO(hash): aliased buffer node hashing is not yet exercised here,
    // the tree operands refer to aliased (generated) node ids
}
