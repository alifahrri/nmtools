/**
 * @file to_string.hpp
 * @author Fahri Ali Rahman (ali.rahman.fahri@gmail.com)
 * @brief Contains definition of to_string
 * @version 0.1
 * @date 2020-11-17
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef NMTOOLS_UTILS_TO_STRING_HPP
#define NMTOOLS_UTILS_TO_STRING_HPP

#if __has_include(<string>)
    #define HAS_STRING true
    #include <string>
    #define nmtools_string std::string
    // NOTE: quick hack, arduino (esp. atmel avr) doesn't have std::to_string
    // TODO: find better alternative
    #define nmtools_to_string std::to_string
#elif defined(ARDUINO)
    // TODO: do not include arduino here (?)
    #include <Arduino.h>
    #define HAS_STRING true
    #define nmtools_string String
    // NOTE: quick hack
    // TODO: find better alternative
    #define nmtools_to_string String
#else
#define HAS_STRING false
#endif

#if __has_include(<sstream>)
#include <sstream>
#define NMTOOLS_HAS_SSTREAM true
#define nmtools_sstream ::std::stringstream
#else
#define NMTOOLS_HAS_SSTREAM false
#endif

#if defined(__clang__)
  #if __has_feature(cxx_rtti)
    #define NMTOOLS_HAS_RTTI
  #endif
#elif defined(__GNUG__)
  #if defined(__GXX_RTTI)
    #define NMTOOLS_HAS_RTTI
  #endif
#elif defined(_MSC_VER)
  #if defined(_CPPRTTI)
    #define NMTOOLS_HAS_RTTI
  #endif
#endif


#if __has_include(<boost/type_index.hpp>)
    #include <boost/type_index.hpp>
    #define NMTOOLS_TESTING_GET_TYPENAME(type) \
    boost::typeindex::type_id<type>().pretty_name()
#elif defined(NMTOOLS_HAS_RTTI)
    #define NMTOOLS_TESTING_GET_TYPENAME(type) \
    typeid(type).name()
#else
    #define NMTOOLS_TESTING_GET_TYPENAME(type) ""
#endif

#if HAS_STRING

#include "nmtools/meta.hpp"
#include "nmtools/array/utility.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/index/ndindex.hpp"
#include "nmtools/array/ndarray.hpp"
#include "nmtools/array/utility/apply_at.hpp"
#include "nmtools/array/functional/functor.hpp"

namespace nmtools::utils
{
    // NOTE: forward declare function here to allow function object to_string_t to
    // call the function,
    // this is because to_string_t can't deduce template args automatically (no constructor, and operator() cant be static)
    // TODO: revisit this and maybe refactor
    template <typename formatter_t=none_t, typename T>
    auto to_string(const T& array, formatter_t=formatter_t{});

    /**
     * @brief Quick workaround to remove substring from string
     * 
     * @tparam string 
     * @param str 
     * @param substr 
     * @return auto 
     */
    template <typename string>
    inline auto remove_string(string& str, const string& substr)
    {
        // NOTE: quick workaround for checkif if we have full std string features
        // maybe not available on arduino
        #if (NMTOOLS_HAS_SSTREAM)
        auto start_pos = string::npos;
        do {
          start_pos = str.find(substr);
          if (start_pos != string::npos) {
            str.erase(start_pos, substr.size());
          }
        } while (start_pos != string::npos);
        #endif // NMTOOLS_HAS_SSTREAM
    }

    struct graphviz_t {};

    constexpr inline auto Graphviz = graphviz_t {};
}

namespace nmtools::utils::impl
{
template <typename T, typename formatter_t, typename=void>
struct to_string_t;

}
namespace nmtools::utils
{
    /**
     * @brief to_string given array to given stream type.
     * 
     * @tparam stream_t stream type, e.g. std::stringstream,
     * @tparam T array-like, 2d, 1d, or scalar
     * @param array array to to_string
     * @return auto stream with type of stream_t
     */
    template <typename formatter_t, typename T>
    auto to_string(const T& array, formatter_t)
    {
        constexpr auto to_string = impl::to_string_t<T,formatter_t>{};
        return to_string(array);
    } // auto to_string
} // namespace nmtools::utils

namespace nmtools::utils::impl
{
template <typename T>
struct to_string_t<T,none_t,void>
{
    auto operator()(const T& array) const noexcept
    {
        nmtools_string str;
        using ::nmtools::index::ndindex;

        if constexpr (is_ellipsis_v<T>)
            str += "...";
        else if constexpr (is_none_v<T>)
            str += "None";
        else if constexpr (meta::is_either_v<T>) {
            using lhs_t = meta::get_either_left_t<T>;
            using rhs_t = meta::get_either_right_t<T>;
            // assume get_if<type>(&array) is available for either type
            if (auto l_ptr = nmtools::get_if<lhs_t>(&array)) {
                // NOTE: this call require forward declaration of to_string above
                str += to_string(*l_ptr);
            } else {
                auto r_ptr = nmtools::get_if<rhs_t>(&array);
                str += to_string(*r_ptr);
            }
        }
        else if constexpr (meta::is_nothing_v<T>) {
            str += "Nothing";
        }
        else if constexpr (meta::is_maybe_v<T>) {
            // for maybe type,
            // assume casting to bool checks if the objects contains a value
            // which is supported by std::optional
            if (static_cast<bool>(array))
                str += to_string(*array);
            else str += "Nothing";
        }
        else if constexpr (meta::is_num_v<T>) {
            // allow view type
            using type_t = meta::get_element_type_t<T>;
            str += nmtools_to_string(static_cast<type_t>(array));
        }
        else if constexpr (meta::is_integral_constant_v<T>) {
            str += nmtools_to_string(T::value);
        } // is_integral_constant
        else if constexpr (meta::is_ndarray_v<T>) {
            // TODO: do not use as array
            /**
             * @brief helper lambda to make sure to return array (instead of tuple)
             * this simplify indexing, since tuple must be unrolled (can't use runtime index)
             * 
             */
            auto as_array = [](auto shape_){
                using shape_t = decltype(shape_);
                using index_t = meta::get_element_or_common_type_t<shape_t>;
                if constexpr (meta::is_constant_index_array_v<shape_t>) {
                    return meta::to_value_v<shape_t>;
                } else if constexpr (meta::is_tuple_v<shape_t>) {
                    constexpr auto N = meta::len_v<shape_t>;
                    using array_t = meta::make_array_type_t<index_t,N>;
                    auto array = array_t{};
                    meta::template_for<N>([&](auto i){
                        at(array,i) = at(shape_,i);
                    });
                    return array;
                } else {
                    return shape_;
                }
            };

            auto shape_ = shape(array);
            auto s = as_array(shape_);
            auto indices = ndindex(s);

            // print empty ndarray
            if (!len(indices))
                str = "[]";
            
            for (size_t i=0; i<(size_t)len(indices); i++) {
                auto idx_ = indices[i];
                auto idx  = as_array(idx_);
                // TODO: support tuple for apply_at
                auto a = apply_at(array, idx);

                // check if we should print open bracket
                // only add open bracket up to axis n
                // that is equal to zero, starting from last axis
                for (int ii=len(idx)-1; ii>=0; ii--) {
                    if (at(idx,ii)==0)
                        str += "[";
                    else break;
                }

                str += "\t";
                str += to_string(a);

                int print_comma = 0;
                // check if we should print closing bracket
                // only add open bracket up to axis n
                // that is equal to shape[n]-1, starting from last axis
                for (int ii=(int)len(idx)-1; ii>=0; ii--) {
                    // for simplicity just use int
                    if ((int)at(idx,ii)==(int)(at(s,ii)-1)) {
                        str += "]";
                        // also count how much newline to be printed
                        print_comma++;
                    }
                    else break;
                }
                if (print_comma && i<len(indices)-1) {
                    str += ",";
                    for (int ii=0; ii<print_comma; ii++)
                        str += "\n";
                }
            }
        } // meta::is_ndarray_v<T>
        // TODO: remove tuple_size metafunctions
        // handle packed type (e.g. tuple), recursively call to_string for each elements
        else if constexpr (meta::has_tuple_size_v<T>) {
            constexpr auto N = meta::len_v<T>;
            str += "(";
            meta::template_for<N>([&](auto index){
                constexpr auto i = decltype(index)::value;
                const auto& a = nmtools::get<i>(array);
                str += to_string(a);
                if constexpr (i<(N-1))
                    str += ",\t";
            });
            str += ")";
        }
        else if constexpr (meta::is_list_v<T>) {
            auto dim = len(array);
            for (size_t i=0; i<(size_t)dim; i++) {
                if (i==0) {
                    str += "[";
                }
                str += "\t";
                str += to_string(at(array,i));
                if (i==(size_t)(dim-1)) {
                    str += "]";
                }
            }
        }
        #if NMTOOLS_HAS_SSTREAM
        else if constexpr (meta::is_pointer_v<T>) {
            nmtools_sstream ss;
            auto type_name = NMTOOLS_TESTING_GET_TYPENAME(T);
            ss << "<" << type_name << ">" << "(" << array << ")";

            str += ss.str();
        }
        #endif
        return str;
    } // operator()
}; // struct to_string_t

template <
    typename buffer_t
    , typename shape_buffer_t
    , template <typename...>typename stride_buffer_t
    , template <typename...>typename compute_offset_t
>
struct to_string_t<
    array::ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,compute_offset_t> *, none_t, void
> {
    using array_type = array::ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,compute_offset_t>;

    auto operator()(const array_type* ptr) const noexcept
    {
        auto ptr_str = nmtools_string("");

        #if NMTOOLS_HAS_SSTREAM

        nmtools_sstream ss;
        auto buffer_name = NMTOOLS_TESTING_GET_TYPENAME(buffer_t);
        auto shape_name  = NMTOOLS_TESTING_GET_TYPENAME(shape_buffer_t);
        ss << "(" << ptr << ")\n"
           << "<ndarray_t<" << buffer_name << "," << shape_name << "...> >";

        ptr_str += ss.str();

        #endif // NMTOOLS_HAS_SSTREAM

        return ptr_str;
    }
};

template <
    typename buffer_t
    , typename shape_buffer_t
    , template <typename...>typename stride_buffer_t
    , template <typename...>typename compute_offset_t
>
struct to_string_t<
    const array::ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,compute_offset_t> *, none_t, void
> : to_string_t<array::ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,compute_offset_t> *, none_t> {};

template <typename F, typename operands_t, typename attributes_t>
struct to_string_t<functional::functor_t<F,operands_t,attributes_t>,none_t,void>
{
    using functor_type = functional::functor_t<F,operands_t,attributes_t>;

    auto operator()(const functor_type& functor) const noexcept
    {
        auto fmap_str = NMTOOLS_TESTING_GET_TYPENAME(decltype(functor.fmap));

        auto attr_str = nmtools_string("");
        attr_str += "[{";
        constexpr auto N = meta::len_v<attributes_t>;
        meta::template_for<N>([&](auto index){
            attr_str += to_string(nmtools::at(functor.attributes,index));
            if (index < (N-1)) {
                attr_str += ",";
            }
        });
        attr_str += "}]";

        return fmap_str + attr_str;
    }
};

template <typename functor_t, typename operands_t>
struct to_string_t<
    functional::node_t<functor_t,operands_t>, none_t, void
> {
    using node_type = functional::node_t<functor_t,operands_t>;

    auto operator()(const node_type& node) const noexcept
    {
        auto node_str = nmtools_string("");
        node_str += to_string(node.functor);
        return node_str;
    }
};

template <typename nodes_t, typename edges_t, typename node_data_t>
struct to_string_t<
    // functional::compute_graph_t<nodes_t,edges_t,node_data_t>, none_t, void
    utility::ct_digraph<nodes_t,edges_t,node_data_t>, graphviz_t, void
> {
    // using graph_type = functional::compute_graph_t<nodes_t,edges_t,node_data_t>;
    using graph_type = utility::ct_digraph<nodes_t,edges_t,node_data_t>;

    auto operator()(const graph_type& graph) const noexcept
    {
        auto graphviz = nmtools_string("digraph G");
        graphviz += "{";

        {
            auto out_edges = graph.out_edges();
            constexpr auto N = meta::len_v<decltype(out_edges)>;
            meta::template_for<N>([&](auto index){
                auto out_edge = nmtools::at(out_edges,index);
                auto src_edge = nmtools::get<0>(out_edge);
                auto dst_edge = nmtools::get<1>(out_edge);

                graphviz += to_string(src_edge);
                graphviz += " -> ";
                graphviz += to_string(dst_edge);
                graphviz += "\n";
            });
        }

        {
            auto nodes = graph.nodes();
            constexpr auto N = meta::len_v<decltype(nodes)>;
            meta::template_for<N>([&](auto index){
                auto node_id  = nmtools::at(nodes,index);
                auto node = graph.nodes(node_id);

                auto node_id_str = to_string(node_id);
                graphviz += node_id_str;
                graphviz += "[";
                graphviz += "label=";
                graphviz += "\"";
                graphviz += "{id: ";
                graphviz += node_id_str;
                graphviz += "}\n";
                graphviz += to_string(node);
                graphviz += "\"";
                graphviz += "]\n";
            });
        }

        graphviz += "}";

        remove_string(graphviz, nmtools_string("nmtools::"));
        remove_string(graphviz, nmtools_string("array::"));
        remove_string(graphviz, nmtools_string("std::"));

        return graphviz;
    }
};

template <typename nodes_t, typename edges_t, typename node_data_t>
struct to_string_t<
    functional::compute_graph_t<nodes_t,edges_t,node_data_t>, graphviz_t, void
> : to_string_t<utility::ct_digraph<nodes_t,edges_t,node_data_t>, graphviz_t, void>
{};

}
#endif // HAS_STRING

#endif // NMTOOLS_UTILS_TO_STRING_HPP