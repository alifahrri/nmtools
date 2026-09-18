#ifndef NMTOOLS_RUNTIME_DEF_HPP
#define NMTOOLS_RUNTIME_DEF_HPP

#include "nmtools/meta.hpp"
#include "nmtools/dtypes.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/network/digraph.hpp"
#include "nmtools/core/node.hpp"

// TODO: parametrize shared_ptr
#include <memory>

namespace nmtools::runtime
{
    using DType = functional::Type;
    using IndexType = nmtools_list<nm_index_t>;

    using functional::Kind;
    using functional::Type;
    using functional::Layout;
    using functional::Combinator;

    // TODO: use small vector
    template <
        typename integer_t=nm_index_t
        , typename float_t=float32_t
        , typename index_array_t=nmtools_list<integer_t>
        , typename string_t=nmtools_string>
    using Attribute = functional::Attribute<integer_t,float_t,index_array_t,string_t>;

    template <
        typename integer_t=nm_index_t
        , typename float_t=float32_t>
    using Attributes = nmtools_default_map<nmtools_string,Attribute<integer_t,float_t>>;

    using BufferType = nmtools_variant<
        none_t, // not evaluated
        ::std::shared_ptr<nmtools_list<uint8_t>>,
        ::std::shared_ptr<nmtools_list<uint16_t>>,
        ::std::shared_ptr<nmtools_list<uint32_t>>,
        ::std::shared_ptr<nmtools_list<uint64_t>>,
        ::std::shared_ptr<nmtools_list<int8_t>>,
        ::std::shared_ptr<nmtools_list<int16_t>>,
        ::std::shared_ptr<nmtools_list<int32_t>>,
        ::std::shared_ptr<nmtools_list<int64_t>>,
        ::std::shared_ptr<nmtools_list<float>>,
        ::std::shared_ptr<nmtools_list<double>>
    >;

    template <
        typename integer_t=nm_index_t
        , typename float_t=float32_t
        , typename input_buffer_t=BufferType>
    using Node = functional::Node<-1,-1,integer_t,float_t,nmtools_list<integer_t>,Attributes<>,nmtools_string,input_buffer_t>;

    // TODO: use small vector
    using AdjacencyList  = nmtools_list<nmtools_list<nm_index_t>>;
    using NodeAttributes = nmtools_list<runtime::Node<>>;
    using NodeIDs = nmtools_list<nm_index_t>;

    using Graph = network::digraph_t<AdjacencyList,NodeIDs,NodeAttributes>;
}

#endif // NMTOOLS_RUNTIME_DEF_HPP