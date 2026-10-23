#ifndef NMTOOLS_RUNTIME_NODE_HPP
#define NMTOOLS_RUNTIME_NODE_HPP

#include "nmtools/core/computational_graph.hpp"
#include "nmtools/core/node.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/runtime/def.hpp"

namespace nmtools::runtime
{
    template <typename input_t, typename shape_t, typename element_t>
    auto to_value(const functional::buffer_node_t<input_t,shape_t,element_t>& node)
    {
        using Node = runtime::Node<>;
        return functional::to_value<Node>(node);
    } // to_value

    template <typename functor_t, typename operands_t, typename output_shape_t, typename output_element_t>
    auto to_value(const functional::compute_node_t<functor_t,operands_t,output_shape_t,output_element_t>& node)
    {
        using Node = runtime::Node<>;
        return functional::to_value<Node>(node);
    } // to_value
}

#endif // NMTOOLS_RUNTIME_NODE_HPP