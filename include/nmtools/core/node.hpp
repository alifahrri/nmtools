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

#ifndef NMTOOLS_NODE_ATTRIBUTE_MAX_KEY_LEN
#define NMTOOLS_NODE_ATTRIBUTE_MAX_KEY_LEN (NMTOOLS_DEFAULT_STATIC_STRING_MAX_SIZE)
#endif // NMTOOLS_NODE_ATTRIBUTE_MAX_KEY_LEN

#ifndef NMTOOLS_NODE_ATTRIBUTE_MAX_VALUE_STRING_LEN
#define NMTOOLS_NODE_ATTRIBUTE_MAX_VALUE_STRING_LEN (NMTOOLS_DEFAULT_STATIC_STRING_MAX_SIZE)
#endif // NMTOOLS_NODE_ATTRIBUTE_MAX_VALUE_STRING_LEN

#ifndef NMTOOLS_NODE_ATTRIBUTE_MAX_INDEX_ARRAY_LEN
#define NMTOOLS_NODE_ATTRIBUTE_MAX_INDEX_ARRAY_LEN (NMTOOLS_DEFAULT_STATIC_VECTOR_MAX_SIZE)
#endif // NMTOOLS_NODE_ATTRIBUTE_MAX_INDEX_ARRAY_LEN

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

    // temporary
    // TODO: remove
    template <typename T>
    struct is_nodev2 : false_type {};

    template <typename T>
    struct is_nodev2<const T> : is_nodev2<T> {};

    template <typename T>
    struct is_nodev2<T&> : is_nodev2<T> {};
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

    template <
        typename integer_t=nm_index_t
        , typename float_t=float32_t
        , auto max_len=NMTOOLS_NODE_ATTRIBUTE_MAX_INDEX_ARRAY_LEN
        , auto max_str_len=NMTOOLS_NODE_ATTRIBUTE_MAX_VALUE_STRING_LEN>
    struct Attribute
    {
        using index_array_type = utl::static_vector<integer_t,max_len>;
        using string_type  = utl::static_string_base<max_str_len>;
        using none_type    = none_t;
        using integer_type = integer_t;
        using float_type   = float_t;

        // very hard to make uninon work in constexpr (c++17)
        // maybe use union if c++20 for potential memory saving
        #if 0
        union {
            none_type        none;
            integer_type     integer;
            float_type       floating;
            index_array_type index_array;
            string_type      string;
        };
        #else
        none_type        none        = {};
        integer_type     integer     = {};
        float_type       floating    = {};
        index_array_type index_array = {};
        string_type      string      = {};
        #endif
        enum Tag
        {
            NONE,
            INTEGER,
            FLOATING,
            INDEX_ARRAY,
            STRING,
        };
        Tag tag;

        constexpr Attribute()
            : none{}
            , tag(Tag::NONE)
        {}

        explicit constexpr Attribute(integer_type value)
            : integer(value)
            , tag(Tag::INTEGER)
        {}

        explicit constexpr Attribute(float_type value)
            : floating(value)
            , tag(Tag::FLOATING)
        {}

        constexpr Attribute(string_type value)
            : string(value)
            , tag(Tag::STRING)
        {}

        template <typename T, meta::enable_if_t<meta::is_index_array_v<T>
            && !meta::is_same_v<meta::get_element_type_t<T>,char>
            , int> = 0>
        constexpr Attribute(const T& value)
            : index_array([&](){
                auto result = index_array_type{};
                auto n = len(value);
                result.resize(n);
                for (nm_size_t i=0; i<(nm_size_t)n; i++) {
                    at(result,i) = at(value,i);
                }
                return result;
            }())
            , tag(Tag::INDEX_ARRAY)
        {}

        constexpr auto is_none() const
        {
            return tag == Tag::NONE;
        }

        constexpr auto is_integer() const
        {
            return tag == Tag::INTEGER;
        }

        constexpr auto is_floating() const
        {
            return tag == Tag::FLOATING;
        }

        constexpr auto is_index_array() const
        {
            return tag == Tag::INDEX_ARRAY;
        }

        constexpr auto is_string() const
        {
            return tag == Tag::STRING;
        }

        constexpr decltype(auto) operator=(none_t)
        {
            tag = Tag::NONE;
            none = none_t{};
            return *this;
        }

        constexpr decltype(auto) operator=(integer_t value)
        {
            tag = Tag::INTEGER;
            integer = value;
            return *this;
        }

        constexpr decltype(auto) operator=(float_t value)
        {
            tag = Tag::FLOATING;
            floating = value;
            return *this;
        }

        constexpr decltype(auto) operator=(const string_type& value)
        {
            tag = Tag::STRING;
            string = value;
            return *this;
        }

        template <typename T, meta::enable_if_t<meta::is_index_array_v<T>
            && !meta::is_same_v<meta::get_element_type_t<T>,char>
            , int> = 0>
        constexpr decltype(auto) operator=(const T& value)
        {
            tag = Tag::INDEX_ARRAY;
            auto n = len(value);
            index_array.resize(n);
            for (nm_size_t i=0; i<(nm_size_t)n; i++) {
                at(index_array,i) = at(value,i);
            }
            return *this;
        }

        #if NMTOOLS_HAS_STRING
        inline auto to_string() const
        {
            nmtools_string str;
            if (is_none()) {
                str += "None";
            } else if (is_integer()) {
                str += utils::to_string(integer);
            } else if (is_floating()) {
                str += utils::to_string(floating);
            } else if (is_string()) {
                str += string.c_str();
            } else if (is_index_array()) {
                str += utils::to_string(index_array,utils::Compact);
            }
            return str;
        }
        #endif // NMTOOLS_HAS_STRING
    };

    template <
        typename integer_t=nm_index_t
        , typename float_t=float32_t
        , auto max_len=NMTOOLS_NODE_ATTRIBUTE_MAX_INDEX_ARRAY_LEN
        , auto max_str_len=NMTOOLS_NODE_ATTRIBUTE_MAX_VALUE_STRING_LEN>
    using Attributes = utl::static_map<utl::static_string,Attribute<integer_t,float_t,max_len,max_str_len>>;

    template <
        auto MAX_DIM=NMTOOLS_NODE_MAX_LEN
        , auto MAX_COMPOSITION=NMTOOLS_NODE_MAX_COMPOSITION
        , typename attributes_t=none_t
        , typename integer_t=nm_index_t
        , typename float_t=float32_t
        , auto max_len=NMTOOLS_NODE_ATTRIBUTE_MAX_INDEX_ARRAY_LEN
        , auto max_str_len=NMTOOLS_NODE_ATTRIBUTE_MAX_VALUE_STRING_LEN>
    struct NodeV2
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
            , nmtools_static_vector<NodeV2<MAX_DIM,0>,MAX_COMPOSITION>
            , meta::conditional_t<
                (MAX_COMPOSITION < 0) // for runtime, no need to limit composition
                , nmtools_list<NodeV2>
                , none_t
            >>;
        
        using attributes_type = Attributes<integer_t,float_t,max_len,max_str_len>;

        attributes_type  attributes_  = {};
        composition_type composition_ = {};

        static constexpr utl::static_string kind_to_string(Kind kind)
        {
            auto kind_str = utl::static_string();
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
            return kind_str;
        }

        static constexpr utl::static_string type_to_string(Type type)
        {
            auto dtype_str = utl::static_string();
            switch (type) {
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
            return dtype_str;
        }

        static constexpr utl::static_string layout_to_string(Layout layout)
        {
            auto layout_str = utl::static_string();

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
            return layout_str;
        }

        static constexpr utl::static_string combinator_to_string(Combinator combinator_type)
        {
            auto str = utl::static_string();
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
            return str;
        }

        static constexpr Kind string_to_kind(const utl::static_string& kind_str)
        {
            Kind kind = Kind::UNKNOWN;

            if (kind_str == "INDEXING") {
                kind = Kind::INDEXING;
            } else if (kind_str == "UNARY_UFUNC") {
                kind = Kind::UNARY_UFUNC;
            } else if (kind_str == "BINARY_UFUNC") {
                kind = Kind::BINARY_UFUNC;
            } else if (kind_str == "REDUCE") {
                kind = Kind::REDUCE;
            } else if (kind_str == "BUFFERED") {
                kind = Kind::BUFFERED;
            } else if (kind_str == "COMPOSITION") {
                kind = Kind::COMPOSITION;
            }

            return kind;
        }

        static constexpr Type string_to_type(const utl::static_string& dtype_str)
        {
            Type type = Type::UNKNOWN;

            if (dtype_str == "uint8") {
                type = Type::UInt8;
            } else if (dtype_str == "uint16") {
                type = Type::UInt16;
            } else if (dtype_str == "uint32") {
                type = Type::UInt32;
            } else if (dtype_str == "uint64") {
                type = Type::UInt64;
            } else if (dtype_str == "int8") {
                type = Type::Int8;
            } else if (dtype_str == "int16") {
                type = Type::Int16;
            } else if (dtype_str == "int32") {
                type = Type::Int32;
            } else if (dtype_str == "int64") {
                type = Type::Int64;
            } else if (dtype_str == "float32") {
                type = Type::Float32;
            } else if (dtype_str == "float64") {
                type = Type::Float64;
            }

            return type;
        }

        static constexpr Layout string_to_layout(const utl::static_string& layout_str)
        {
            Layout layout = Layout::UNKNOWN;

            if (layout_str == "RowMajor") {
                layout = Layout::RowMajor;
            } else if (layout_str == "ColMajor") {
                layout = Layout::ColMajor;
            }

            return layout;
        }

        static constexpr Combinator string_to_combinator(const utl::static_string& str)
        {
            Combinator combinator_type = Combinator::INVALID;

            if (str == "SWAP") {
                combinator_type = Combinator::SWAP;
            } else if (str == "DUP") {
                combinator_type = Combinator::DUP;
            } else if (str == "DIG") {
                combinator_type = Combinator::DIG;
            } else if (str == "BURY") {
                combinator_type = Combinator::BURY;
            }

            return combinator_type;
        }

        constexpr NodeV2(const shape_type& shape
            , dim_type dim
            , max_dim_type max_dim
            , is_num_type is_num
            , Kind kind
            , Type dtype
            , composition_type composition
            , Layout layout=Layout::UNKNOWN
            , Combinator combinator=Combinator::INVALID
            , nm_index_t combinator_args=-1)
            : attributes_([&](){
                auto attrs = attributes_type();
                attrs["shape"]   = shape;
                attrs["dim"]     = dim;
                attrs["max_dim"] = max_dim;
                attrs["is_num"]  = is_num;
                attrs["kind"]    = kind_to_string(kind);
                attrs["dtype"]   = type_to_string(dtype);
                attrs["layout"]  = layout_to_string(layout);
                attrs["combinator_type"] = combinator_to_string(combinator);
                attrs["combinator_args"] = combinator_args;
                return attrs;
            }())
            , composition_{composition}
        {}

        constexpr NodeV2() {}

        constexpr decltype(auto) attributes() const
        {
            return (attributes_);
        }

        constexpr decltype(auto) attributes()
        {
            return (attributes_);
        }

        /*************************************************/

        constexpr decltype(auto) shape() const
        {
            return attributes_.at("shape").index_array;
        }

        constexpr decltype(auto) dim() const
        {
            return attributes_.at("dim").integer;
        }

        constexpr decltype(auto) max_dim() const
        {
            return attributes_.at("max_dim").integer;
        }

        constexpr decltype(auto) is_num() const
        {
            return attributes_.at("is_num").integer;
        }

        constexpr decltype(auto) kind() const
        {
            auto kind = Kind::UNKNOWN;
            if (attributes_.count("kind")) {
                kind = string_to_kind(attributes_.at("kind").string);   
            }
            return kind;
        }

        constexpr decltype(auto) dtype() const
        {
            return string_to_type(attributes_.at("dtype").string);
        }

        constexpr decltype(auto) composition() const
        {
            return composition_;
        }

        constexpr decltype(auto) layout() const
        {
            return string_to_layout(attributes_.at("layout").string);
        }

        constexpr decltype(auto) combinator_type() const
        {
            auto type = Combinator::INVALID;
            if (attributes_.count("combinator_type")) {
                type = string_to_combinator(attributes_.at("combinator_type").string);
            }
            return type;
        }

        constexpr decltype(auto) combinator_args() const
        {
            return attributes_.at("combinator_args").integer;
        }

        /*************************************************/

        constexpr decltype(auto) composition()
        {
            return (composition_);
        }

        /*************************************************/

        static constexpr auto buffer(const shape_type& shape
            , dim_type dim
            , max_dim_type max_dim
            , Type dtype
            , Layout layout)
        {
            composition_type composition = {};
            Kind kind = Kind::BUFFERED;
            auto is_num = false;
            return NodeV2{shape,dim,max_dim,is_num,kind,dtype,composition,layout};
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
            return NodeV2{shape,dim,max_dim,is_num,kind,dtype,composition,layout};
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
            return NodeV2{shape,dim,max_dim,is_num,kind,dtype,composition,layout};
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
            return NodeV2{shape,dim,max_dim,is_num,kind,dtype,composition,layout};
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
            return NodeV2{shape,dim,max_dim,is_num,kind,dtype,composition,layout};
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
            return NodeV2{shape,dim,max_dim,is_num,kind,dtype,composition,layout};
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
            return NodeV2{shape,dim,max_dim,is_num,kind,dtype,composition,layout,combinator,args};
        }

        template <typename shape_t>
        static constexpr auto indexing(const shape_t& shape
            , Type dtype
            , Layout layout=Layout::UNKNOWN)
        {
            return compute(Kind::INDEXING,shape,dtype,layout);
        }

        template <typename shape_t>
        static constexpr auto binary_ufunc(const utl::static_string& op
            , const shape_t& shape
            , Type dtype
            , Layout layout=Layout::UNKNOWN)
        {
            auto node = compute(Kind::BINARY_UFUNC,shape,dtype,layout);
            node.attributes()["op"] = op;
            return node;
        }

        template <typename shape_t>
        static constexpr auto binary_ufunc(const shape_t& shape
            , Type dtype
            , Layout layout=Layout::UNKNOWN)
        {
            return compute(Kind::BINARY_UFUNC,shape,dtype,layout);
        }

        template <typename shape_t>
        static constexpr auto unary_ufunc(const utl::static_string& op
            , const shape_t& shape
            , Type dtype
            , Layout layout=Layout::UNKNOWN)
        {
            auto node = compute(Kind::UNARY_UFUNC,shape,dtype,layout);
            node.attributes()["op"] = op;
            return node;
        }

        template <typename shape_t>
        static constexpr auto unary_ufunc(const shape_t& shape
            , Type dtype
            , Layout layout=Layout::UNKNOWN)
        {
            return compute(Kind::UNARY_UFUNC,shape,dtype,layout);
        }

        template <typename shape_t, typename axis_t>
        static constexpr auto reduce(const utl::static_string& op
            , const axis_t& axis
            , const shape_t& shape
            , Type dtype
            , Layout layout=Layout::UNKNOWN)
        {
            auto node = compute(Kind::REDUCE,shape,dtype,layout);
            node.attributes()["op"]   = op;
            node.attributes()["axis"] = axis;
            return node;
        }

        template <typename shape_t>
        static constexpr auto reduce(const shape_t& shape
            , Type dtype
            , Layout layout=Layout::UNKNOWN)
        {
            return compute(Kind::REDUCE,shape,dtype,layout);
        }

        constexpr auto is_combinator() const noexcept
        {
            return (combinator_type() != Combinator::INVALID);
        }

        constexpr auto is_composition() const noexcept
        {
            if constexpr (is_none_v<composition_type>) {
                return false;
            } else {
                return static_cast<bool>(composition().size());
            }
        }

        constexpr auto is_buffer() const noexcept
        {
            return ((kind() == Kind::BUFFERED) && !is_combinator() && !is_composition());
        }

        constexpr auto is_compute() const noexcept
        {
            return (!is_buffer() && !is_combinator() && !is_composition());
        }

        template <
            auto RHS_MAX_DIM
            , auto RHS_MAX_COMPOSITION>
        constexpr auto operator=(const NodeV2<RHS_MAX_DIM,RHS_MAX_COMPOSITION,attributes_t>& other)
        {
            this->attributes_ = other.attributes_;

            if constexpr (meta::is_same_v<
                meta::remove_cvref_t<decltype(composition_)>
                , meta::remove_cvref_t<decltype(other.composition_)>
                >
            ) {
                this->composition() = other.composition();
            }
            return *this;
        }

        constexpr auto operator*(const NodeV2& other) const
        {
            // compose
            auto result = NodeV2{};

            // TODO: assert/throw
            // assume not buffer, only comput/combinator/composition
            
            auto dst_size = 2;
            dst_size += (is_composition() ? composition().size()-1 : 0);
            dst_size += (other.is_composition() ? other.composition().size()-1 : 0);
            result.composition().resize(dst_size);

            auto idx = 0ul;
            if (is_composition()) {
                for (nm_size_t i=0; i<composition().size(); i++) {
                    at(result.composition(),idx++) = at(composition(),i);
                }
            } else {
                at(result.composition(),idx++) = *this;
            }
            if (other.is_composition()) {
                for (nm_size_t i=0; i<other.composition().size(); i++) {
                    at(result.composition(),idx++) = at(other.composition(),i);
                }
            } else {
                at(result.composition(),idx++) = other;
            }
        
            return result;
        }

        constexpr auto operator|(const NodeV2& other) const
        {
            return other * *this;
        }

        #if NMTOOLS_HAS_STRING
        inline auto to_string() const
        {
            auto strs = nmtools_list<nmtools_string>{};

            auto indexer_args_to_string = [](const auto& attributes_){
                auto kind_str = nmtools_string();
                if (attributes_.count("indexer.n_args")) {
                    kind_str += "{";
                    auto n = attributes_.at("indexer.n_args").integer;
                    for (nm_size_t i=0; i<(nm_size_t)n; i++) {
                        auto arg_key = utl::static_string("indexer.args.");
                        auto key = arg_key + utl::to_string(i);
                        const auto& attr = attributes_.at(key);
                        if (attributes_.count(key + ".name")) {
                            kind_str += attributes_.at(key+".name").string.c_str();
                            kind_str += "=";
                        }
                        kind_str += attr.to_string();
                        if ((nm_index_t)i<(nm_index_t)n-1) {
                            kind_str += ",";
                        }
                    }
                    kind_str += "}";
                }
                return kind_str;
            };

            if (is_buffer() || is_compute()) {
                auto kind_str = nmtools_string();
                switch (kind()) {
                    case Kind::UNKNOWN:
                    kind_str += "UNKNOWN";
                    break;
                    case Kind::INDEXING:
                    kind_str += "INDEXING";
                    if (attributes_.count("indexer")) {
                        kind_str += "{";
                        kind_str += ".indexer=";
                        kind_str += attributes_.at("indexer").string.c_str();
                        kind_str += indexer_args_to_string(attributes_);
                        kind_str += "}";
                    }
                    break;
                    case Kind::UNARY_UFUNC:
                    kind_str += "UNARY_UFUNC";
                    if (attributes_.count("op"))
                    {
                        kind_str += "{";
                        kind_str += ".op=";
                        kind_str += attributes_.at("op").to_string();
                        kind_str += "}";
                    }
                    break;
                    case Kind::BINARY_UFUNC:
                    kind_str += "BINARY_UFUNC";
                    if (attributes_.count("op"))
                    {
                        kind_str += "{";
                        kind_str += ".op=";
                        kind_str += attributes_.at("op").to_string();
                        kind_str += "}";
                    }
                    break;
                    case Kind::REDUCE:
                    kind_str += "REDUCE";
                    if (attributes_.count("op"))
                    {
                        kind_str += "{";
                        kind_str += ".op=";
                        kind_str += attributes_.at("op").string.c_str();
                        if (attributes_.count("axis")) {
                            kind_str += ",axis=";
                            kind_str += attributes_.at("axis").to_string();
                        }
                        if (attributes_.count("dtype")) {
                            kind_str += ",dtype=";
                            kind_str += attributes_.at("dtype").to_string();
                        }
                        if (attributes_.count("initital")) {
                            kind_str += ",initial=";
                            kind_str += attributes_.at("initial").to_string();
                        }
                        if (attributes_.count("keepdims")) {
                            kind_str += ",keepdims=";
                            kind_str += attributes_.at("keepdims").to_string();
                        }
                        kind_str += "}";
                    }
                    break;
                    case Kind::BUFFERED:
                    kind_str += "BUFFERED";
                    if (attributes_.count("layout")) {
                        kind_str += "{";
                        kind_str += "layout=";
                        kind_str += attributes_.at("layout").string.c_str();
                        kind_str += "}";
                    }
                    break;
                    case Kind::COMPOSITION:
                    kind_str += "COMPOSITION";
                    default:
                    break;
                };
                strs.push_back(kind_str);

                if constexpr (!is_none_v<attributes_t>) {
                    
                }

                auto dtype_str = nmtools_string();
                dtype_str += "dtype: ";
                switch (dtype()) {
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

                if (!is_num()) {
                    dtype_str += " | ";
                    dtype_str += "dim: ";
                    if (max_dim() > 0) {
                        dtype_str += utils::to_string(max_dim());
                    } else {
                        dtype_str += "?";
                    }
                }

                dtype_str += " | ";
                dtype_str += "shape: ";
                if (is_num()) {
                    dtype_str += "None";
                } else {
                    auto n = len(shape());
                    if (n > 0) {
                        dtype_str += "{";
                        for (nm_size_t i=0; i<(nm_size_t)n; i++) {
                            auto shape_i = at(shape(),i);
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
                switch (combinator_type()) {
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
                if (combinator_args() > 0) {
                    str += "(";
                    str += utils::to_string(combinator_args());
                    str += ")";
                }
                strs.push_back(str);
            } else if (is_composition()) {
                // composition_type maybe none, to avoid blowing up the recursion
                if constexpr (!is_none_v<composition_type>) {
                    for (nm_index_t i=1; i<(nm_index_t)composition().size(); i++) {
                        strs.push_back(at(composition(),-i).to_string().front());
                    }
                    strs.push_back(composition().at(0).to_string().front());
                }
            }

            return strs;
        }
        #endif
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

        shape_type   shape_;
        dim_type     dim_;
        max_dim_type max_dim_;
        is_num_type  is_num_;
        Kind         kind_  = Kind::UNKNOWN;
        Type         dtype_ = Type::UNKNOWN;

        // no is_composition but can check if this node is composition by checking the size
        composition_type composition_ = {};
        Layout           layout_      = Layout::UNKNOWN;
        // when INVALID, assume this node is not combinator
        // combinator args is simply an int
        Combinator combinator_type_ = Combinator::INVALID;
        nm_index_t combinator_args_ = -1;

        /*************************************************/

        constexpr decltype(auto) shape() const
        {
            return shape_;
        }

        constexpr decltype(auto) dim() const
        {
            return dim_;
        }

        constexpr decltype(auto) max_dim() const
        {
            return max_dim_;
        }

        constexpr decltype(auto) is_num() const
        {
            return is_num_;
        }

        constexpr decltype(auto) kind() const
        {
            return kind_;
        }

        constexpr decltype(auto) dtype() const
        {
            return dtype_;
        }

        constexpr decltype(auto) composition() const
        {
            return composition_;
        }

        constexpr decltype(auto) layout() const
        {
            return layout_;
        }

        constexpr decltype(auto) combinator_type() const
        {
            return combinator_type_;
        }

        constexpr decltype(auto) combinator_args() const
        {
            return combinator_args_;
        }

        /*************************************************/

        constexpr decltype(auto) shape()
        {
            return (shape_);
        }

        constexpr decltype(auto) dim()
        {
            return (dim_);
        }

        constexpr decltype(auto) max_dim()
        {
            return (max_dim_);
        }

        constexpr decltype(auto) is_num()
        {
            return (is_num_);
        }

        constexpr decltype(auto) kind()
        {
            return (kind_);
        }

        constexpr decltype(auto) dtype()
        {
            return (dtype_);
        }

        constexpr decltype(auto) composition()
        {
            return (composition_);
        }

        constexpr decltype(auto) layout()
        {
            return (layout_);
        }

        constexpr decltype(auto) combinator_type()
        {
            return (combinator_type_);
        }

        constexpr decltype(auto) combinator_args()
        {
            return (combinator_args_);
        }

        /*************************************************/

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

        static constexpr auto indexing(const shape_type& shape
            , Type dtype
            , Layout layout=Layout::UNKNOWN)
        {
            return compute(Kind::INDEXING,shape,dtype,layout);
        }

        static constexpr auto reduce(const shape_type& shape
            , Type dtype
            , Layout layout=Layout::UNKNOWN)
        {
            return compute(Kind::REDUCE,shape,dtype,layout);
        }

        constexpr auto is_combinator() const noexcept
        {
            return (combinator_type() != Combinator::INVALID);
        }

        constexpr auto is_composition() const noexcept
        {
            if constexpr (is_none_v<composition_type>) {
                return false;
            } else {
                return static_cast<bool>(composition().size());
            }
        }

        constexpr auto is_buffer() const noexcept
        {
            return ((kind() == Kind::BUFFERED) && !is_combinator() && !is_composition());
        }

        constexpr auto is_compute() const noexcept
        {
            return (!is_buffer() && !is_combinator() && !is_composition());
        }

        template <
            auto RHS_MAX_DIM
            , auto RHS_MAX_COMPOSITION>
        constexpr auto operator=(const Node<RHS_MAX_DIM,RHS_MAX_COMPOSITION,attributes_t>& other)
        {
            this->shape()   = other.shape();
            this->dim()     = other.dim();
            this->max_dim() = other.max_dim();
            this->is_num()  = other.is_num();
            this->kind()    = other.kind();
            this->dtype()   = other.dtype();
            this->layout()  = other.layout();
            this->combinator_type() = other.combinator_type();
            this->combinator_args() = other.combinator_args();

            if constexpr (meta::is_same_v<decltype(composition_),decltype(other.composition_)>) {
                this->composition() = other.composition();
            }
            return *this;
        }

        constexpr auto operator*(const Node& other) const
        {
            // compose
            auto result = Node{};

            // TODO: assert/throw
            // assume not buffer, only comput/combinator/composition
            
            auto dst_size = 2;
            dst_size += (is_composition() ? composition().size()-1 : 0);
            dst_size += (other.is_composition() ? other.composition().size()-1 : 0);
            result.composition().resize(dst_size);

            auto idx = 0ul;
            if (is_composition()) {
                for (nm_size_t i=0; i<composition().size(); i++) {
                    at(result.composition(),idx++) = at(composition(),i);
                }
            } else {
                at(result.composition(),idx++) = *this;
            }
            if (other.is_composition()) {
                for (nm_size_t i=0; i<other.composition().size(); i++) {
                    at(result.composition(),idx++) = at(other.composition(),i);
                }
            } else {
                at(result.composition(),idx++) = other;
            }
        
            return result;
        }

        constexpr auto operator|(const Node& other) const
        {
            return other * *this;
        }

        #if NMTOOLS_HAS_STRING
        inline auto to_string() const
        {
            auto strs = nmtools_list<nmtools_string>{};

            if (is_buffer() || is_compute()) {
                auto kind_str = nmtools_string();
                switch (kind()) {
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

                if (kind() == Kind::BUFFERED && !is_num()) {
                    auto layout_str = nmtools_string();
                    layout_str += "layout: ";

                    switch (layout()) {
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
                switch (dtype()) {
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

                if (!is_num()) {
                    dtype_str += " | ";
                    dtype_str += "dim: ";
                    if (max_dim() > 0) {
                        dtype_str += utils::to_string(max_dim());
                    } else {
                        dtype_str += "?";
                    }
                }

                dtype_str += " | ";
                dtype_str += "shape: ";
                if (is_num()) {
                    dtype_str += "None";
                } else {
                    auto n = len(shape());
                    if (n > 0) {
                        dtype_str += "{";
                        for (nm_size_t i=0; i<(nm_size_t)n; i++) {
                            auto shape_i = at(shape(),i);
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
                switch (combinator_type()) {
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
                if (combinator_args() > 0) {
                    str += "(";
                    str += utils::to_string(combinator_args());
                    str += ")";
                }
                strs.push_back(str);
            } else if (is_composition()) {
                // composition_type maybe none, to avoid blowing up the recursion
                if constexpr (!is_none_v<composition_type>) {
                    for (nm_index_t i=1; i<(nm_index_t)composition().size(); i++) {
                        strs.push_back(at(composition(),-i).to_string().front());
                    }
                    strs.push_back(composition().at(0).to_string().front());
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
    // temporary
    // TODO: remove
    template <
        auto MAX_DIM
        , auto MAX_COMPOSITION
        , typename attributes_t
        , typename integer_t
        , typename float_t
        , auto max_len
        , auto max_str_len>
    struct is_nodev2<functional::NodeV2<MAX_DIM,MAX_COMPOSITION,attributes_t,integer_t,float_t,max_len,max_str_len>> : true_type {};

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

    template <typename input_t, typename shape_t, typename element_t, typename node_t>
    struct to_value<
        functional::buffer_node_t<input_t,shape_t,element_t>
        , node_t
    > {
        static constexpr auto value = [](){
            using Node = conditional_t<is_void_v<node_t>,functional::Node<>,node_t>;
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

            using shape_type = typename Node::shape_type;
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

    template <typename functor_t, typename operands_t, typename output_shape_t, typename output_element_t, typename node_t>
    struct to_value<
        functional::compute_node_t<functor_t,operands_t,output_shape_t,output_element_t>
        , node_t
    > {
        static constexpr auto value = [](){
            using Node = conditional_t<is_void_v<node_t>,functional::Node<>,node_t>;

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

            using shape_type = typename Node::shape_type;
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

            using composition_type = typename Node::composition_type;
            auto composition = composition_type{};

            using attributes_type = functional::Attributes<>;
            [[maybe_unused]]
            auto attributes = attributes_type{};

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

                if constexpr (is_same_functor_v<functional::unary_fmap_t<functional::fun::indexing>,functor_type>) {
                    using attributes_t = remove_cvref_t<typename functor_type::attributes_type>;
                    using attribute_t  = remove_cvref_t<at_t<attributes_t,0>>;
                    using indexer_type = typename attribute_t::indexer_type;

                    auto indexer_name = type_name_v<indexer_type>;
                    attributes["indexer"] = indexer_name;
                }

                if constexpr (
                    (is_binary_ufunc_functor_v<functor_type>)
                    || (is_same_functor_v<functional::unary_fmap_t<functional::fun::unary_ufunc<>>,functor_type>)
                ) {
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
                    attributes["op"] = str;
                }

                if constexpr (is_same_functor_v<functional::unary_fmap_t<functional::fun::reduce<>>,functor_type>)
                {
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
                    attributes["op"] = str;
                    constexpr auto make_value = [](auto vtype){
                        using type = type_t<decltype(vtype)>;
                        [[maybe_unused]]
                        constexpr auto DIM = len_v<type>;
                        if constexpr (is_constant_index_v<type>
                            || is_constant_index_array_v<type>
                        ) {
                            return to_value_v<type>;
                        } else if constexpr (DIM > 0) {
                            using result_t = nmtools_array<nm_index_t,DIM>;
                            auto result = result_t {};
                            for (nm_size_t i=0; i<(nm_size_t)DIM; i++) {
                                // only known at runtime
                                at(result,i) = -1;
                            }
                            return result;
                        } else if constexpr (is_none_v<type>) {
                            return None;
                        } else {
                            return type_name_v<type>;
                        }
                    };
                    using axis_type     = typename attribute_t::axis_type;
                    using initial_type  = typename attribute_t::initial_type;
                    using keepdims_type = typename attribute_t::keepdims_type;
                    attributes["axis"]     = make_value(as_value_v<axis_type>);
                    attributes["initial"]  = make_value(as_value_v<initial_type>);
                    attributes["keepdims"] = make_value(as_value_v<keepdims_type>);
                }
            }

            auto node = Node{shape,dim,max_dim,is_num,kind,dtype,composition};
            if constexpr (is_void_v<node_t>) {
                return node;
            } else {
                if (attributes.count("indexer")) {
                    node.attributes()["indexer"] = attributes["indexer"];
                }
                if (attributes.count("op")) {
                    node.attributes()["op"] = attributes["op"];
                }
                if (attributes.count("axis")) {
                    node.attributes()["axis"] = attributes["axis"];
                }
                if (attributes.count("initial")) {
                    node.attributes()["initial"] = attributes["initial"];
                }
                if (attributes.count("keepdims")) {
                    node.attributes()["keepdims"] = attributes["keepdims"];
                }
                return node;
            }
        }();
    };
}

#endif // NMTOOLS_CORE_NODE_HPP