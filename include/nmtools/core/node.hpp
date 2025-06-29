#ifndef NMTOOLS_CORE_NODE_HPP
#define NMTOOLS_CORE_NODE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/core/functor.hpp"
#include "nmtools/core/combinator.hpp"

#ifndef NMTOOLS_NODE_MAX_LEN
#define NMTOOLS_NODE_MAX_LEN 11
#endif // NMTOOLS_NODE_MAX_LEN

#ifndef NMTOOLS_NODE_MAX_COMPOSITION
#define NMTOOLS_NODE_MAX_COMPOSITION 32
#endif // NMTOOLS_NODE_MAX_LEN

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct LAYOUT_KIND_UNSUPPORTED : detail::fail_t {};
    }

    template <typename T>
    struct layout_kind
    {
        static constexpr auto value = error::LAYOUT_KIND_UNSUPPORTED<T>{};
    };

    template <typename T>
    struct layout_kind<const T> : layout_kind<T> {};

    template <typename T>
    struct layout_kind<T&> : layout_kind<T> {};

    template <typename T>
    constexpr inline auto layout_kind_v = layout_kind<T>::value;

    // TODO: move to meta/bits or functor
    template <typename T>
    struct is_binary_ufunc_functor : false_type {};

    template <typename T>
    struct is_binary_ufunc_functor<const T> : is_binary_ufunc_functor<T> {};

    template <typename T>
    struct is_binary_ufunc_functor<T&> : is_binary_ufunc_functor<T> {};

    template <typename T>
    constexpr inline auto is_binary_ufunc_functor_v = is_binary_ufunc_functor<T>::value;

    template <typename Op, typename operands_t, typename attributes_t>
    struct is_binary_ufunc_functor<
        functional::functor_t<functional::binary_fmap_t<functional::fun::binary_ufunc<Op>>,operands_t,attributes_t>
    > : true_type {};

    template <typename Op, typename operands_t, typename attributes_t>
    struct is_binary_ufunc_functor<
        functional::functor_t<functional::binary_fmap_t<functional::fun::broadcast_binary_ufunc<Op>>,operands_t,attributes_t>
    > : true_type {};

    template <typename T>
    struct is_functor_composition : false_type {};

    template <typename T>
    struct is_functor_composition<const T> : is_functor_composition<T> {};

    template <typename T>
    struct is_functor_composition<T&> : is_functor_composition<T> {};

    template <typename T>
    constexpr inline auto is_functor_composition_v = is_functor_composition<T>::value;

    template <template<typename...>typename tuple, typename...functors_t, typename operands_t>
    struct is_functor_composition<
        functional::functor_composition_t<tuple<functors_t...>,operands_t>
    > : true_type {};
}

namespace nmtools::functional
{
    enum class Kind : int
    {
        UNKNOWN      = -1,
        INDEXING     = 0,
        UNARY_UFUNC  = 1,
        BINARY_UFUNC = 2,
        REDUCE       = 3,
        BUFFERED     = 4,
        COMPOSITION  = 5,
    };

    enum class Type : int
    {
        UNKNOWN = -1,
        UInt8   = 0,
        UInt16  = 1,
        UInt32  = 2,
        UInt64  = 3,
        Int8    = 4,
        Int16   = 5,
        Int32   = 6,
        Int64   = 7,
        Float32 = 8,
        Float64 = 9,
    };

    // only valid for buffer, obviously
    enum class Layout : int
    {
        UNKNOWN   = -1,
        RowMajor = 0,
        ColMajor = 1,
    };

    enum class Combinator : int
    {
        INVALID = -1,
        SWAP = 0,
        DUP  = 1,
        DIG  = 2,
        BURY = 3,
    };

    // value node
    // attributes is useful for fully runtime Node
    // e.g. can easily handle variants
    template <
        auto MAX_DIM=NMTOOLS_NODE_MAX_LEN
        , auto MAX_COMPOSITION=NMTOOLS_NODE_MAX_COMPOSITION
        , typename attributes_t=none_t>
    struct Node
    {
        using vector_type  = meta::conditional_t<(MAX_DIM > 0)
            , nmtools_static_vector<nm_index_t,MAX_DIM>
            , nmtools_list<nm_index_t>>;
        using shape_type   = vector_type;
        using dim_type     = nm_index_t;
        // max dim is useful to check if this node results in bounded dim
        // in such case, dim will be -1 but max_dim > 0
        using max_dim_type = nm_index_t;
        // using shape, dim alone make it confusing to deduce if this node is num
        // is_num should be set by is_none_v<shape_t>
        // is_num is not Kind because both buffered and compute can be num
        using is_num_type  = nm_bool_t;
        // if dim -1 then num
        // if dim 0 then dynamic dim
        // if dim > 0 then fixed dim
        using composition_type = meta::conditional_t<
            (MAX_COMPOSITION > 0)
            , nmtools_static_vector<Node<MAX_DIM,0>,MAX_COMPOSITION>
            , meta::conditional_t<
                (MAX_COMPOSITION < 0) // for runtime, no need to limit composition
                , nmtools_list<Node>
                , none_t
            >>;

        // TODO: support attributes

        shape_type   shape;
        dim_type     dim;
        max_dim_type max_dim;
        is_num_type  is_num;
        Kind kind  = Kind::UNKNOWN;
        Type dtype = Type::UNKNOWN;

        // no is_composition but can check if this node is composition by checking the size
        composition_type composition = {};
        Layout layout = Layout::UNKNOWN;
        // when INVALID, assume this node is not combinator
        // combinator args is simply an int
        Combinator combinator_type = Combinator::INVALID;
        nm_index_t combinator_args = -1;

        static constexpr auto buffer(const shape_type& shape
            , dim_type dim
            , max_dim_type max_dim
            , Type dtype
            , Layout layout)
        {
            composition_type composition = {};
            Kind kind = Kind::BUFFERED;
            auto is_num = false;
            return Node{shape,dim,max_dim,is_num,kind,dtype,composition,layout};
        }

        static constexpr auto buffer(const shape_type& shape
            , Type dtype
            , Layout layout)
        {
            composition_type composition = {};
            Kind kind = Kind::BUFFERED;
            auto is_num = false;
            dim_type dim = shape.size();
            max_dim_type max_dim = shape.size();
            return Node{shape,dim,max_dim,is_num,kind,dtype,composition,layout};
        }

        template <typename shape_t>
        static constexpr auto buffer(const shape_t& shape
            , Type dtype
            , Layout layout)
        {
            static_assert( meta::is_index_array_v<shape_t>
                , "expected index array but got unsupported type for buffer" );

            auto m_shape = shape_type{};
            auto n = len(shape);
            if constexpr (meta::is_resizable_v<shape_type>) {
                m_shape.resize(n);
            }
            for (nm_size_t i=0; i<(nm_size_t)n; i++) {
                at(m_shape,i) = at(shape,i);
            }
            return buffer(m_shape,dtype,layout);
        }

        static constexpr auto buffer(none_t
            , Type dtype)
        {
            composition_type composition = {};
            Kind kind    = Kind::BUFFERED;
            auto shape   = shape_type{};
            auto is_num  = true;
            auto dim     = -1;
            auto max_dim = -1;
            auto layout  = Layout::UNKNOWN;
            return Node{shape,dim,max_dim,is_num,kind,dtype,composition,layout};
        }

        static constexpr auto compute(Kind kind
            , const shape_type& shape
            , dim_type dim
            , max_dim_type max_dim
            , is_num_type is_num
            , Type dtype
            , Layout layout=Layout::UNKNOWN)
        {
            composition_type composition = {};
            return Node{shape,dim,max_dim,is_num,kind,dtype,composition,layout};
        }

        static constexpr auto compute(Kind kind
            , const shape_type& shape
            , Type dtype
            , Layout layout=Layout::UNKNOWN)
        {
            composition_type composition = {};
            dim_type dim     = shape.size();
            max_dim_type max_dim = shape.size();
            auto is_num  = false;
            return Node{shape,dim,max_dim,is_num,kind,dtype,composition,layout};
        }

        template <typename shape_t>
        static constexpr auto compute(Kind kind
            , const shape_t& shape
            , Type dtype
            , Layout layout=Layout::UNKNOWN)
        {
            static_assert( meta::is_index_array_v<shape_t>
                , "expected index array but got unsupported type for buffer" );

            auto m_shape = shape_type{};
            auto n = len(shape);
            if constexpr (meta::is_resizable_v<shape_type>) {
                m_shape.resize(n);
            }
            for (nm_size_t i=0; i<(nm_size_t)n; i++) {
                at(m_shape,i) = at(shape,i);
            }
            return compute(kind,m_shape,dtype,layout);
        }

        static constexpr auto functor(Kind kind)
        {
            // functor is similar to compute but no real info
            auto shape   = shape_type {};
            auto layout  = Layout::UNKNOWN;
            auto dtype   = Type::UNKNOWN;
            auto is_num  = false;
            auto dim     = -1;
            auto max_dim = -1;
            composition_type composition = {};
            return Node{shape,dim,max_dim,is_num,kind,dtype,composition,layout};
        }

        static constexpr auto combinator(Combinator combinator, nm_index_t args=-1)
        {
            auto shape   = shape_type {};
            auto layout  = Layout::UNKNOWN;
            auto dtype   = Type::UNKNOWN;
            auto kind    = Kind::UNKNOWN;
            auto is_num  = false;
            auto dim     = -1;
            auto max_dim = -1;
            auto composition = composition_type {};
            return Node{shape,dim,max_dim,is_num,kind,dtype,composition,layout,combinator,args};
        }

        constexpr auto is_combinator() const noexcept
        {
            return (combinator_type != Combinator::INVALID);
        }

        constexpr auto is_composition() const noexcept
        {
            if constexpr (is_none_v<composition_type>) {
                return false;
            } else {
                return static_cast<bool>(composition.size());
            }
        }

        constexpr auto is_buffer() const noexcept
        {
            return ((kind == Kind::BUFFERED) && !is_combinator() && !is_composition());
        }

        constexpr auto is_compute() const noexcept
        {
            return (!is_buffer() && !is_combinator() && !is_composition());
        }

        constexpr auto operator*(const Node& other) const
        {
            // compose
            Node result;

            // assume not buffer, only comput/combinator/composition
            
        }

        #if NMTOOLS_HAS_STRING
        inline auto to_string() const
        {
            auto strs = nmtools_list<nmtools_string>{};

            if (is_buffer() || is_compute()) {
                auto kind_str = nmtools_string();
                switch (kind) {
                    case Kind::UNKNOWN:
                    kind_str += "UNKNOWN";
                    break;
                    case Kind::INDEXING:
                    kind_str += "INDEXING";
                    break;
                    case Kind::UNARY_UFUNC:
                    kind_str += "UNARY_UFUNC";
                    break;
                    case Kind::BINARY_UFUNC:
                    kind_str += "BINARY_UFUNC";
                    break;
                    case Kind::REDUCE:
                    kind_str += "REDUCE";
                    break;
                    case Kind::BUFFERED:
                    kind_str += "BUFFERED";
                    break;
                    case Kind::COMPOSITION:
                    kind_str += "COMPOSITION";
                    default:
                    break;
                };
                strs.push_back(kind_str);

                if (kind == Kind::BUFFERED && !is_num) {
                    auto layout_str = nmtools_string();
                    layout_str += "layout: ";

                    switch (layout) {
                        case Layout::UNKNOWN:
                        layout_str += "UNKNOWN";
                        break;
                        case Layout::RowMajor:
                        layout_str += "RowMajor";
                        break;
                        case Layout::ColMajor:
                        layout_str += "ColMajor";
                        break;
                        default:
                        break;
                    };

                    strs.push_back(layout_str);
                }

                if constexpr (!is_none_v<attributes_t>) {
                    
                }

                auto dtype_str = nmtools_string();
                dtype_str += "dtype: ";
                switch (dtype) {
                    case Type::UNKNOWN:
                    dtype_str += "UNKNOWN";
                    break;
                    case Type::UInt8:
                    dtype_str += "uint8";
                    break;
                    case Type::UInt16:
                    dtype_str += "uint16";
                    break;
                    case Type::UInt32:
                    dtype_str += "uint32";
                    break;
                    case Type::UInt64:
                    dtype_str += "uint64";
                    break;
                    case Type::Int8:
                    dtype_str += "int8";
                    break;
                    case Type::Int16:
                    dtype_str += "int16";
                    break;
                    case Type::Int32:
                    dtype_str += "int32";
                    break;
                    case Type::Int64:
                    dtype_str += "int64";
                    break;
                    case Type::Float32:
                    dtype_str += "float32";
                    break;
                    case Type::Float64:
                    dtype_str += "float64";
                    break;
                    default:
                    break;
                };

                if (!is_num) {
                    dtype_str += " | ";
                    dtype_str += "dim: ";
                    if (max_dim > 0) {
                        dtype_str += utils::to_string(max_dim);
                    } else {
                        dtype_str += "?";
                    }
                }

                dtype_str += " | ";
                dtype_str += "shape: ";
                if (is_num) {
                    dtype_str += "None";
                } else {
                    auto n = len(shape);
                    if (n > 0) {
                        dtype_str += "{";
                        for (nm_size_t i=0; i<(nm_size_t)n; i++) {
                            auto shape_i = at(shape,i);
                            if (shape_i <= 0) {
                                dtype_str += "?";
                            } else {
                                dtype_str += utils::to_string(shape_i);
                            }
                            if (i < (nm_size_t)n-1) {
                                dtype_str += ",";
                            }
                        }
                        dtype_str += "}";
                    } else {
                        dtype_str += "?";
                    }
                }
                strs.push_back(dtype_str);
            } else if (is_combinator()) {
                auto str = nmtools_string();
                switch (combinator_type) {
                    case Combinator::SWAP:
                    str += "SWAP";
                    break;
                    case Combinator::DUP:
                    str += "DUP";
                    break;
                    case Combinator::DIG:
                    str += "DIG";
                    break;
                    case Combinator::BURY:
                    str += "BURY";
                    break;
                    default:
                    break;
                };
                if (combinator_args > 0) {
                    str += "(";
                    str += utils::to_string(combinator_args);
                    str += ")";
                }
                strs.push_back(str);
            } else if (is_composition()) {
                // composition_type maybe none, to avoid blowing up the recursion
                if constexpr (!is_none_v<composition_type>) {
                    strs.push_back(composition.at(0).to_string().front());
                    for (nm_size_t i=1; i<(nm_size_t)composition.size(); i++) {
                        strs.push_back(composition.at(i).to_string().front());
                    }
                }
            }

            return strs;
        }
        #endif
    };

    template <typename input_t, typename shape_t, typename element_t=none_t>
    struct buffer_node_t
    {
        // TODO: input must be buffered array or num
        using input_type = meta::conditional_t<meta::is_num_v<input_t>,input_t,const input_t*>;
        using shape_type = const shape_t;
        using element_type = element_t;
        using dtype_type   = dtype_t<element_type>;

        input_type input;
        shape_type shape;
        dtype_type dtype = {};

        #if NMTOOLS_HAS_STRING
        auto to_string() const noexcept
        {
            auto strs = nmtools_list<nmtools_string>{};

            strs.push_back(utils::to_string(input,utils::Compact));

            auto str = nmtools_string();
            str += utils::to_string(dtype);
            if constexpr (!is_none_v<shape_t>) {
                str += ": ";
                str += utils::to_string(shape,utils::Compact);
            }
            strs.push_back(str);
            return strs;
        }
        #endif
    };

    template <typename input_t>
    constexpr auto buffer_node(const input_t& input)
    {
        if constexpr (meta::is_maybe_v<input_t>) {
            using result_t = decltype(buffer_node(unwrap(input)));
            using return_t = nmtools_maybe<result_t>;
            // TODO: make sure unwrap return reference
            return (has_value(input)
                ? return_t{buffer_node(unwrap(input))}
                : return_t{meta::Nothing}
            );
        } else {
            auto shape = nmtools::shape<true>(input);
            using element_t = meta::get_element_type_t<input_t>;
            using shape_t   = meta::remove_cvref_t<decltype(shape)>;
            using node_t    = buffer_node_t<input_t,shape_t,element_t>;
            if constexpr (meta::is_num_v<input_t>) {
                return node_t{input,shape};
            } else {
                return node_t{&input,shape};
            }
        }
    }

    template <typename functor_t, typename operands_t, typename output_shape_t=nmtools_tuple<>, typename output_element_t=none_t>
    struct compute_node_t
    {
        // TODO: assert functor_t is functor or functor composition
        // TODO: assert operands_t is tuple of integral constant

        using functor_type  = functor_t;
        using operands_type = operands_t;
        using output_shape_type   = output_shape_t;
        using output_element_type = meta::conditional_t<
            is_dtype_v<output_element_t> || is_none_v<output_element_t>
            , output_element_t
            , dtype_t<output_element_t>>;

        functor_type        functor;
        operands_type       operands;
        output_shape_type   output_shape   = {};
        output_element_type output_element = {};

        #if NMTOOLS_HAS_STRING
        auto to_string() const noexcept
        {
            if constexpr (meta::is_functor_composition_v<functor_type>) {
                auto strs = nmtools_list<nmtools_string>{};

                {
                    auto operands_str = nmtools_string("operands: ");
                    constexpr auto N = meta::len_v<operands_type>;
                    meta::template_for<N>([&](auto I){
                        operands_str += utils::to_string(at(operands,I),utils::Compact);
                        if (I < (N-1)) {
                            operands_str += ", ";
                        }
                    });
                    strs.push_back(operands_str);
                }

                constexpr auto N = meta::len_v<typename functor_type::functors_type>;
                meta::template_for<N>([&](auto I){
                    auto str = nmtools_string("");

                    const auto& m_functor = at(functor.functors,I);

                    using attributes_t = meta::remove_cvref_t<decltype(m_functor.attributes)>;
                    auto fmap_str = utils::to_string(m_functor.fmap,utils::Compact);

                    auto attr_str = nmtools_string("");
                    constexpr auto N = meta::len_v<attributes_t>;
                    meta::template_for<N>([&](auto index){
                        attr_str += utils::to_string(nmtools::at(m_functor.attributes,index),utils::Compact);
                        if (index < (N-1)) {
                            attr_str += ",";
                        }
                    });

                    str += fmap_str;
                    str += " ";
                    str += attr_str;

                    strs.push_back(str);
                });

                {
                    auto dtype_str = nmtools_string("");
                    dtype_str += utils::to_string(output_element);
                    if constexpr (!is_none_v<output_shape_type> && !meta::is_same_v<output_shape_type,nmtools_tuple<>>) {
                        dtype_str += " x ";
                        dtype_str += utils::to_string(output_shape,utils::Compact);
                    }
                    strs.push_back(dtype_str);
                }

                return strs;
            } else {
                #if 1
                auto strs = nmtools_list<nmtools_string>{};

                {
                    auto operands_str = nmtools_string("operands: ");
                    constexpr auto N = meta::len_v<operands_type>;
                    meta::template_for<N>([&](auto I){
                        operands_str += utils::to_string(at(operands,I),utils::Compact);
                        if (I < (N-1)) {
                            operands_str += ", ";
                        }
                    });
                    strs.push_back(operands_str);
                }
                {
                    auto str = nmtools_string("");
                    using attributes_t = meta::remove_cvref_t<decltype(functor.attributes)>;
                    auto fmap_str = utils::to_string(functor.fmap,utils::Compact);

                    auto attr_str = nmtools_string("");
                    constexpr auto N = meta::len_v<attributes_t>;
                    meta::template_for<N>([&](auto index){
                        attr_str += utils::to_string(nmtools::at(functor.attributes,index),utils::Compact);
                        if (index < (N-1)) {
                            attr_str += ",";
                        }
                    });

                    str += fmap_str;
                    str += " ";
                    str += attr_str;

                    strs.push_back(str);
                }
                {
                    auto dtype_str = nmtools_string("");
                    dtype_str += utils::to_string(output_element);
                    if constexpr (!is_none_v<output_shape_type> && !meta::is_same_v<output_shape_type,nmtools_tuple<>>) {
                        dtype_str += ": ";
                        dtype_str += utils::to_string(output_shape,utils::Compact);
                    }
                    strs.push_back(dtype_str);
                }

                return strs;
                #else
                auto str = nmtools_string("");
                {
                    using attributes_t = meta::remove_cvref_t<decltype(functor.attributes)>;
                    auto fmap_str = utils::to_string(functor.fmap,utils::Compact);

                    auto attr_str = nmtools_string("");
                    constexpr auto N = meta::len_v<attributes_t>;
                    meta::template_for<N>([&](auto index){
                        attr_str += utils::to_string(nmtools::at(functor.attributes,index),utils::Compact);
                        if (index < (N-1)) {
                            attr_str += ",";
                        }
                    });

                    str += fmap_str;
                    str += " ";
                    str += attr_str;
                }
                {
                    auto operands_str = nmtools_string("operands: ");
                    constexpr auto N = meta::len_v<operands_type>;
                    meta::template_for<N>([&](auto I){
                        operands_str += utils::to_string(at(operands,I),utils::Compact);
                        if (I < (N-1)) {
                            operands_str += ", ";
                        }
                    });
                    str += " | ";
                    str += operands_str;
                }

                str += " | ";
                str += utils::to_string(output_element);
                if constexpr (!is_none_v<output_shape_type> && !meta::is_same_v<output_shape_type,nmtools_tuple<>>) {
                    str += " | ";
                    str += utils::to_string(output_shape,utils::Compact);
                }

                return str;
                #endif
            }
        }
        #endif
    };

    template <typename functor_t, typename operands_t, typename output_shape_t, typename output_element_t>
    compute_node_t(const functor_t&,const operands_t&,const output_shape_t&,const output_element_t&)
        -> compute_node_t<functor_t,operands_t,output_shape_t,output_element_t>;

    template <typename functor_t, typename operands_t, typename output_shape_t=nmtools_tuple<>, typename output_element_t=none_t>
    constexpr auto compute_node(const functor_t& functor
        , const operands_t& operands
        , const output_shape_t& output_shape=output_shape_t{}
        , const output_element_t& output_element=output_element_t{})
    {
        using node_t = compute_node_t<functor_t,operands_t,output_shape_t,output_element_t>;
        return node_t{functor,operands,output_shape,output_element};
    }

    template <typename view_t>
    constexpr auto compute_node(const view_t& view)
    {
        if constexpr (meta::is_maybe_v<view_t>) {
            using result_t = decltype(compute_node(unwrap(view)));
            using return_t = nmtools_maybe<result_t>;
            return (has_value(view)
                ? return_t{compute_node(unwrap(view))}
                : return_t{meta::Nothing}
            );
        } else {
            auto functor   = get_function(view);
            auto operands  = view.operands_ids;
            auto shape     = nmtools::shape<true>(view);
            using output_t = meta::get_element_type_t<view_t>;
            auto dtype = dtype_t<output_t>{};
            auto node  = compute_node(functor,operands,shape,dtype);
            return node;
        }
    }

    template <typename input_t>
    constexpr auto node(const input_t& input)
    {
        if constexpr (meta::is_maybe_v<input_t>) {
            using result_t = decltype(node(unwrap(input)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(input)
                ? return_t{node(unwrap(input))}
                : return_t{meta::Nothing}
            );
        } else if constexpr (meta::is_same_view_v<view::alias_t,input_t>) {
            if constexpr (meta::is_pointer_v<decltype(input.array)>) {
                return buffer_node(*(input.array));
            } else {
                return buffer_node(input.array);
            }
        } else if constexpr (meta::is_view_v<input_t>) {
            return compute_node(input);
        } else {
            return buffer_node(input);
        }
    }
} // nmtools::functional

namespace nmtools::meta
{
    template <
          typename buffer_t
        , typename shape_buffer_t
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t>
    struct layout_kind<
        ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>
    > {
        using array_type  = ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>;
        using offset_type = typename array_type::offset_type;
        static constexpr auto value = [](){
            if constexpr (is_row_major_offset_v<offset_type>) {
                return functional::Layout::RowMajor;
            } else if constexpr (is_column_major_offset_v<offset_type>) {
                return functional::Layout::ColMajor;
            } else {
                return error::LAYOUT_KIND_UNSUPPORTED<array_type>{};
            }
        }();
    };

    template <typename input_t, typename shape_t, typename element_t>
    struct to_value<
        functional::buffer_node_t<input_t,shape_t,element_t>
    > {
        static constexpr auto value = [](){
            using Node = functional::Node<>;
            using Type = functional::Type;
            using Layout = functional::Layout;

            Type dtype    = Type::UNKNOWN;
            Layout layout = Layout::UNKNOWN;

            if (is_same_v<element_t,float32_t>) {
                dtype = Type::Float32;
            } else if (is_same_v<element_t,float64_t>) {
                dtype = Type::Float64;
            } else if (is_same_v<element_t,uint8_t>) {
                dtype = Type::UInt8;
            } else if (is_same_v<element_t,uint16_t>) {
                dtype = Type::UInt16;
            } else if (is_same_v<element_t,uint32_t>) {
                dtype = Type::UInt32;
            } else if (is_same_v<element_t,uint64_t>) {
                dtype = Type::UInt64;
            } else if (is_same_v<element_t,int8_t>) {
                dtype = Type::Int8;
            } else if (is_same_v<element_t,int16_t>) {
                dtype = Type::Int16;
            } else if (is_same_v<element_t,int32_t>) {
                dtype = Type::Int32;
            } else if (is_same_v<element_t,int64_t>) {
                dtype = Type::Int64;
            }

            auto layout_kind = layout_kind_v<input_t>;
            if constexpr (!is_fail_v<decltype(layout_kind)>) {
                layout = layout_kind;
            }

            using shape_type = Node::shape_type;
            auto shape = shape_type{};

            constexpr auto dim     = len_v<shape_t>;
            constexpr auto max_dim = max_len_v<shape_t>;

            if constexpr (dim > 0) {
                shape.resize(dim);
            }
            constexpr auto src_shape = to_value_v<shape_t>;
            using src_shape_t = decltype(src_shape);

            auto is_num = false;
            using nmtools::at, nmtools::len;
            if constexpr (is_none_v<src_shape_t>) {
                is_num = true;
            } else if constexpr (!is_fail_v<src_shape_t>) {
                for (nm_size_t i=0; i<(nm_size_t)len(src_shape); i++) {
                    at(shape,i) = at(src_shape,i);
                }
            }

            if (is_num) {
                return Node::buffer(None,dtype);
            } else {
                return Node::buffer(shape,dim,max_dim,dtype,layout);
            }
        }();
    };

    template <typename functor_t, typename operands_t, typename output_shape_t, typename output_element_t>
    struct to_value<
        functional::compute_node_t<functor_t,operands_t,output_shape_t,output_element_t>
    > {
        static constexpr auto value = [](){
            using Node = functional::Node<>;

            using shape_t   = output_shape_t;
            using element_t = get_dtype_t<output_element_t>;

            using Kind = functional::Kind;
            using Type = functional::Type;
            using Combinator = functional::Combinator;

            Kind kind  = Kind::UNKNOWN;
            Type dtype = Type::UNKNOWN;

            if (is_same_v<element_t,float32_t>) {
                dtype = Type::Float32;
            } else if (is_same_v<element_t,float64_t>) {
                dtype = Type::Float64;
            } else if (is_same_v<element_t,uint8_t>) {
                dtype = Type::UInt8;
            } else if (is_same_v<element_t,uint16_t>) {
                dtype = Type::UInt16;
            } else if (is_same_v<element_t,uint32_t>) {
                dtype = Type::UInt32;
            } else if (is_same_v<element_t,uint64_t>) {
                dtype = Type::UInt64;
            } else if (is_same_v<element_t,int8_t>) {
                dtype = Type::Int8;
            } else if (is_same_v<element_t,int16_t>) {
                dtype = Type::Int16;
            } else if (is_same_v<element_t,int32_t>) {
                dtype = Type::Int32;
            } else if (is_same_v<element_t,int64_t>) {
                dtype = Type::Int64;
            }

            using shape_type = Node::shape_type;
            auto shape = shape_type{};

            constexpr auto dim     = len_v<shape_t>;
            constexpr auto max_dim = max_len_v<shape_t>;

            if constexpr (dim > 0) {
                shape.resize(dim);
            }
            constexpr auto src_shape = to_value_v<shape_t>;
            using src_shape_t = decltype(src_shape);

            auto is_num = false;
            using nmtools::at, nmtools::len;
            if constexpr (is_none_v<src_shape_t>) {
                is_num = true;
            } else if constexpr (!is_fail_v<src_shape_t>) {
                for (nm_size_t i=0; i<(nm_size_t)len(src_shape); i++) {
                    at(shape,i) = at(src_shape,i);
                }
            }

            using composition_type = Node::composition_type;
            auto composition = composition_type{};

            if constexpr (is_functor_composition_v<remove_cvref_t<functor_t>>) {
                using functors_t = remove_cvref_t<typename remove_cvref_t<functor_t>::functors_type>;
                kind = Kind::COMPOSITION;
                constexpr auto num_functors = len_v<functors_t>;
                composition.resize(num_functors);
                using ComposeNode = remove_cvref_t<decltype(at(composition,0))>;
                meta::template_for<num_functors>([&](auto init){
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
            } else {
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
            }

            return Node{shape,dim,max_dim,is_num,kind,dtype,composition};
        }();
    };
}

#endif // NMTOOLS_CORE_NODE_HPP