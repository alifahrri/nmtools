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

        Type dtype = Type::UNKNOWN;
        Layout layout = Layout::UNKNOWN;

        if constexpr (!is_none_v<element_t>) {
            dtype = to_value_v<dtype_t<element_t>>;
        }

        auto layout_kind = layout_kind_v<input_t>;
        if constexpr (!is_fail_v<decltype(layout_kind)>) {
            layout = layout_kind;
        }

        constexpr auto MAX_DIM = max_len_v<shape_t>;

        using shape_type = typename Node::shape_type;
        auto shape = shape_type{};
        auto src_shape = node.shape;
        auto dim = len(src_shape);
        shape.resize(dim);

        auto is_num = false;
        using nmtools::at, nmtools::len;
        if constexpr (is_none_v<shape_t>) {
            is_num = true;
        } else if constexpr (!is_fail_v<shape_t>) {
            for (nm_size_t i=0; i<(nm_size_t)len(src_shape); i++) {
                at(shape,i) = at(src_shape,i);
            }
        }

        if (is_num) {
            auto node = Node::buffer(None,dtype);
            // TODO: better conversion operator
            node.attributes()["input_type"] = type_name_v<input_t>.data();
            return node;
        } else if constexpr (is_shared_ptr_v<input_t>) {
            // TODO: assuming runtime node input type is variant, make sure input_t is acceptable type
            auto buffer = node.input;
            auto node = Node::buffer(shape,dim,MAX_DIM,dtype,layout,buffer);
            node.attributes()["input_type"] = type_name_v<input_t>.data();
            return node;
        } else {
            auto node = Node::buffer(shape,dim,MAX_DIM,dtype,layout);
            node.attributes()["input_type"] = type_name_v<input_t>.data();
            return node;
        }
    } // to_value

    template <typename functor_t, typename operands_t, typename output_shape_t, typename output_element_t>
    auto to_value(const functional::compute_node_t<functor_t,operands_t,output_shape_t,output_element_t>& node)
    {
        using Node = runtime::Node<>;

        /*********************************************************** */
        using shape_t   = output_shape_t;
        using element_t = get_dtype_t<output_element_t>;

        Kind kind  = Kind::UNKNOWN;
        Type dtype = Type::UNKNOWN;

        if constexpr (!is_none_v<element_t>) {
            dtype = to_value_v<dtype_t<element_t>>;
        }
        /*********************************************************** */

        // the following differ from meta::to_value since we have the actual value at runtime
        /*********************************************************** */
        constexpr auto MAX_DIM = max_len_v<shape_t>;

        using shape_type = typename Node::shape_type;
        auto shape = shape_type{};
        auto src_shape = node.output_shape;
        auto dim = len(src_shape);
        shape.resize(dim);

        auto is_num = false;
        using nmtools::at, nmtools::len;
        if constexpr (is_none_v<shape_t>) {
            is_num = true;
        } else if constexpr (is_constant_index_array_v<shape_t>) {
            constexpr auto N = len_v<shape_t>;
            template_for<N>([&](auto i){
                at(shape,i) = at(src_shape,i);
            });
        } else if constexpr (!is_fail_v<shape_t>) {
            for (nm_size_t i=0; i<(nm_size_t)len(src_shape); i++) {
                at(shape,i) = at(src_shape,i);
            }
        }
        /*********************************************************** */

        using composition_type = typename Node::composition_type;
        auto composition = composition_type{};

        using attributes_type = Attributes<>;
        [[maybe_unused]]
        auto attributes = attributes_type{};

        if constexpr (is_functor_composition_v<remove_cvref_t<functor_t>>) {
            /*********************************************************** */
            using functors_t = remove_cvref_t<typename remove_cvref_t<functor_t>::functors_type>;
            kind = Kind::COMPOSITION;
            constexpr auto num_functors = len_v<functors_t>;
            composition.resize(num_functors);
            using ComposeNode = remove_cvref_t<decltype(at(composition,0))>;
            template_for<num_functors>([&](auto init){
                auto node = ComposeNode{};
                constexpr auto I = decltype(init)::value;
                using functor_type = at_t<functors_t,I>;
                using fmap_type = remove_cvref_t<typename functor_type::fmap_type>;
                if constexpr (is_combinator_v<fmap_type>) {
                    auto args = get_combinator_args_v<fmap_type>;
                    if (is_same_combinator_v<combinator::dig_t,fmap_type>) {
                        node = ComposeNode::combinator(Combinator::DIG,args);
                    } else if (is_same_combinator_v<combinator::dup_t,fmap_type>) {
                        node = ComposeNode::combinator(Combinator::DUP,args);
                    } else if (is_same_combinator_v<combinator::bury_t,fmap_type>) {
                        node = ComposeNode::combinator(Combinator::BURY,args);
                    } else {
                        node = ComposeNode::combinator(Combinator::SWAP,args);
                    }
                } else {
                    Kind kind = {};
                    if (is_same_functor_v<functional::unary_fmap_t<functional::fun::indexing>,functor_type>) {
                        kind = Kind::INDEXING;
                    } else if (is_same_functor_v<functional::unary_fmap_t<functional::fun::reduce<>>,functor_type>) {
                        // TODO: propagate op
                        kind = Kind::REDUCE;
                    } else if (is_binary_ufunc_functor_v<functor_type>) {
                        kind = Kind::BINARY_UFUNC;
                    } else if (is_same_functor_v<functional::unary_fmap_t<functional::fun::unary_ufunc<>>,functor_type>) {
                        kind = Kind::UNARY_UFUNC;
                    }
                    node = ComposeNode::functor(kind);
                }
                at(composition,I) = node;
            });
            /*********************************************************** */
        } else {
            // same with meta::to_value
            /*********************************************************** */
            using functor_type = functor_t;
            using fmap_type = remove_cvref_t<typename functor_type::fmap_type>;
            if constexpr (is_combinator_v<fmap_type>) {
                auto args = get_combinator_args_v<fmap_type>;
                if (is_same_combinator_v<combinator::dig_t,fmap_type>) {
                    return Node::combinator(Combinator::DIG,args);
                } else if (is_same_combinator_v<combinator::dup_t,fmap_type>) {
                    return Node::combinator(Combinator::DUP,args);
                } else if (is_same_combinator_v<combinator::bury_t,fmap_type>) {
                    return Node::combinator(Combinator::BURY,args);
                } else {
                    return Node::combinator(Combinator::SWAP,args);
                }
            } else if (is_same_functor_v<functional::unary_fmap_t<functional::fun::indexing>,functor_type>) {
                kind = Kind::INDEXING;
            } else if (is_same_functor_v<functional::unary_fmap_t<functional::fun::reduce<>>,functor_type>) {
                // TODO: propagate op
                kind = Kind::REDUCE;
            } else if (is_binary_ufunc_functor_v<functor_type>) {
                kind = Kind::BINARY_UFUNC;
            } else if (is_same_functor_v<functional::unary_fmap_t<functional::fun::unary_ufunc<>>,functor_type>) {
                kind = Kind::UNARY_UFUNC;
            }
            /*********************************************************** */

            if constexpr (is_same_functor_v<functional::unary_fmap_t<functional::fun::indexing>,functor_type>) {
                // same with meta::to_value
                /*********************************************************** */
                using attributes_t = remove_cvref_t<typename functor_type::attributes_type>;
                using attribute_t  = remove_cvref_t<at_t<attributes_t,0>>;
                using indexer_type = typename attribute_t::indexer_type;

                auto indexer_name = type_name_v<indexer_type>;

                #if 1
                using key_type = typename attributes_type::key_type;
                if constexpr (!is_same_v<key_type,decltype(indexer_name)>) {
                    attributes["indexer"] = key_type(indexer_name.data());
                } else {
                    attributes["indexer"] = indexer_name;
                }
                #else
                attributes["indexer"] = indexer_name;
                #endif
                /*********************************************************** */
            }

            if constexpr (
                (is_binary_ufunc_functor_v<functor_type>)
                || (is_same_functor_v<functional::unary_fmap_t<functional::fun::unary_ufunc<>>,functor_type>)
            ) {
                // same with meta::to_value
                /*********************************************************** */
                utl::static_string str = {};
                auto n = str.capacity; 
                using op_type = typename fmap_type::f_type::op_type;
                using attributes_t = remove_cvref_t<typename functor_type::attributes_type>;
                using attribute_t  = remove_cvref_t<at_t<attributes_t,0>>;
                // if op_type is none, check first attribute
                auto op_name = type_name_v<conditional_t<!is_none_v<op_type>,op_type,attribute_t>>;
                if (op_name.size() < n) {
                    n = op_name.size();
                }
                str.resize(n);
                for (nm_size_t i=0; i<(nm_size_t)n; i++) {
                    str[i] = op_name[i];
                }
                /*********************************************************** */
                // TODO: better conversion operator
                attributes["op"] = nmtools_string(str.c_str());
            }

            if constexpr (is_same_functor_v<functional::unary_fmap_t<functional::fun::reduce<>>,functor_type>)
            {
                // same with meta::to_value
                /*********************************************************** */
                utl::static_string str = {};
                auto n = str.capacity; 
                using attributes_t = remove_cvref_t<typename functor_type::attributes_type>;
                using attribute_t  = remove_cvref_t<at_t<attributes_t,0>>;

                // nmtools::args::reduce::op_type
                using op_type = typename attribute_t::op_type;
                auto op_name = type_name_v<op_type>;

                if (op_name.size() < n) {
                    n = op_name.size();
                }
                str.resize(n);
                for (nm_size_t i=0; i<(nm_size_t)n; i++) {
                    str[i] = op_name[i];
                }
                /*********************************************************** */
                // TODO: better conversion operator
                attributes["op"] = nmtools_string(str.c_str());

                // The following part differ from meta::to_value since we have actual value at runtime
                /*********************************************************** */
                auto make_value = [](const auto& value){
                    using type = remove_cvref_t<decltype(value)>;
                    if constexpr (is_index_array_v<type>) {
                        auto dim = len(value);
                        // TODO: deduce from Node index_array_t
                        using result_t = nmtools_list<nm_index_t>;
                        auto result = result_t {};
                        if constexpr (is_resizable_v<result_t>) {
                            result.resize(dim);
                        }
                        for (nm_size_t i=0; i<(nm_size_t)dim; i++) {
                            // only known at runtime
                            at(result,i) = at(value,i);
                        }
                        return result;
                    } else if constexpr (is_index_v<type>) {
                        return (nm_index_t)value;
                    } else if constexpr (is_none_v<type>) {
                        return None;
                    } else {
                        return type_name_v<type>;
                    }
                };
                const auto& attr = nmtools::get<0>(node.functor.attributes);
                attributes["axis"]     = make_value(attr.axis);
                attributes["initial"]  = make_value(attr.initial);
                attributes["keepdims"] = make_value(attr.keepdims);
                /*********************************************************** */
            }
        }

        auto result = Node{shape,(nm_index_t)dim,MAX_DIM,is_num,kind,dtype,composition};
        if (attributes.count("indexer")) {
            result.attributes()["indexer"] = attributes["indexer"];
        }
        if (attributes.count("op")) {
            result.attributes()["op"] = attributes["op"];
        }
        if (attributes.count("axis")) {
            result.attributes()["axis"] = attributes["axis"];
        }
        if (attributes.count("initial")) {
            result.attributes()["initial"] = attributes["initial"];
        }
        if (attributes.count("keepdims")) {
            result.attributes()["keepdims"] = attributes["keepdims"];
        }
        return result;
    } // to_value
}

#endif // NMTOOLS_RUNTIME_NODE_HPP