#ifndef NMTOOLS_UTL_TUPLE_HPP
#define NMTOOLS_UTL_TUPLE_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/expr.hpp"
#include "nmtools/meta/bits/transform/remove_address_space.hpp"

// poor man's tuple

// NOTE: base class acess is assumed to be unsuppoted when compiling to spirv
// TODO: revisit this cases
// #define NMTOOLS_TUPLE_NO_BASE_ACCESS

namespace nmtools::utl
{
    #define DECLARE_TUPLE_VAL_TYPE(index) \
    using arg##index##_type = meta::remove_address_space_t<arg##index>;

    #define DEFINE_TUPLE_VAL(index) \
    arg##index##_type value##index;

    #define DEFINE_TUPLE_CTOR(index) \
    constexpr tuple##index() : base(), value##index{} {}

    #define DEFINE_TUPLE_COPY_CTOR(index) \
    constexpr tuple##index(const tuple##index& tp) \
        : base(static_cast<base>(tp)), value##index{tp.value##index} {}

    template <class arg1>
    struct tuple1
    { 
        DECLARE_TUPLE_VAL_TYPE(1)
        DEFINE_TUPLE_VAL(1)

        constexpr tuple1() : value1{} {}
        constexpr tuple1(const arg1& arg)
            : value1(arg) {}
        template <typename var1>
        constexpr tuple1(const tuple1<var1>& tp)
            : value1(tp.value1) {};
    };

    template <class arg1, class arg2>
    struct tuple2
    #ifndef NMTOOLS_TUPLE_NO_BASE_ACCESS
        : tuple1<arg1>
    #endif
    { 
        #ifndef NMTOOLS_TUPLE_NO_BASE_ACCESS
        using base = tuple1<arg1>;
        DECLARE_TUPLE_VAL_TYPE(2)
        DEFINE_TUPLE_VAL(2)
        DEFINE_TUPLE_CTOR(2)

        constexpr tuple2(const arg1& val1, const arg2& val2) 
            : base(val1), value2{val2} {}
        
        template <typename var1, typename var2>
        constexpr tuple2(const tuple2<var1,var2>& tp)
            : base(tp.value1), value2(tp.value2) {}
        #else
        DECLARE_TUPLE_VAL_TYPE(1)
        DEFINE_TUPLE_VAL(1)
        DECLARE_TUPLE_VAL_TYPE(2)
        DEFINE_TUPLE_VAL(2)

        constexpr tuple2()
            : value1{}
            , value2{}
        {}
        constexpr tuple2(const arg1& val1, const arg2& val2)
            : value1(val1)
            , value2(val2)
        {}
        template <typename var1, typename var2>
        constexpr tuple2(const tuple2<var1,var2>& tp)
            : value1(tp.value1)
            , value2(tp.value2)
        {};
        #endif
    };

    template <class arg1, class arg2, class arg3>
    struct tuple3
    #ifndef NMTOOLS_TUPLE_NO_BASE_ACCESS
        : tuple2<arg1,arg2>
    #endif
    { 
        #ifndef NMTOOLS_TUPLE_NO_BASE_ACCESS
        using base = tuple2<arg1,arg2>;
        DECLARE_TUPLE_VAL_TYPE(3)
        DEFINE_TUPLE_VAL(3)
        DEFINE_TUPLE_CTOR(3)

        constexpr tuple3(const arg1& val1, const arg2& val2, const arg3& val3)
            : base(val1,val2), value3{val3} {}
        
        template <typename var1, typename var2, typename var3>
        constexpr tuple3(const tuple3<var1,var2,var3>& tp)
            : base(tp.value1,tp.value2), value3{tp.value3} {}
        #else

        DECLARE_TUPLE_VAL_TYPE(1)
        DEFINE_TUPLE_VAL(1)
        DECLARE_TUPLE_VAL_TYPE(2)
        DEFINE_TUPLE_VAL(2)
        DECLARE_TUPLE_VAL_TYPE(3)
        DEFINE_TUPLE_VAL(3)

        constexpr tuple3()
            : value1{}
            , value2{}
            , value3{}
        {}

        constexpr tuple3(const arg1& val1, const arg2& val2, const arg3& val3)
            : value1{val1}
            , value2{val2}
            , value3{val3}
        {}
        
        template <typename var1, typename var2, typename var3>
        constexpr tuple3(const tuple3<var1,var2,var3>& tp)
            : value1{tp.value1}
            , value2{tp.value2}
            , value3{tp.value3}
        {}
        #endif // NMTOOLS_NO_BASE_ACCESS
    };

    template <class arg1, class arg2, class arg3, class arg4>
    struct tuple4
    #ifndef NMTOOLS_TUPLE_NO_BASE_ACCESS
        : tuple3<arg1,arg2,arg3>
    #endif
    { 
        #ifndef NMTOOLS_TUPLE_NO_BASE_ACCESS
        using base = tuple3<arg1,arg2,arg3>;
        DECLARE_TUPLE_VAL_TYPE(4)
        DEFINE_TUPLE_VAL(4)
        DEFINE_TUPLE_CTOR(4)

        constexpr tuple4(const arg1& val1, const arg2& val2, const arg3& val3, const arg4& val4)
            : base(val1,val2,val3), value4{val4} {}
        
        template <typename var1, typename var2, typename var3, typename var4>
        constexpr tuple4(const tuple4<var1,var2,var3,var4>& tp)
            : base(tp.value1,tp.value2,tp.value3), value4{tp.value4} {}
        
        // constexpr tuple4(tuple4&&) = default;
        // constexpr tuple4(const tuple4&) = default;
        #else

        DECLARE_TUPLE_VAL_TYPE(1)
        DEFINE_TUPLE_VAL(1)
        DECLARE_TUPLE_VAL_TYPE(2)
        DEFINE_TUPLE_VAL(2)
        DECLARE_TUPLE_VAL_TYPE(3)
        DEFINE_TUPLE_VAL(3)
        DECLARE_TUPLE_VAL_TYPE(4)
        DEFINE_TUPLE_VAL(4)

        constexpr tuple4()
            : value1{}
            , value2{}
            , value3{}
            , value4{}
        {}

        constexpr tuple4(const arg1& val1, const arg2& val2, const arg3& val3, const arg4& val4)
            : value1{val1}
            , value2{val2}
            , value3{val3}
            , value4{val4}
        {}

        template <typename var1, typename var2, typename var3, typename var4>
        constexpr tuple4(const tuple4<var1,var2,var3,var4>& tp)
            : value1{tp.value1}
            , value2{tp.value2}
            , value3{tp.value3}
            , value4{tp.value4}
        {}

        #endif // NMTOOLS_NO_BASE_ACCESS
    };

    template <class arg1, class arg2, class arg3, class arg4, class arg5>
    struct tuple5 : tuple4<arg1,arg2,arg3,arg4>
    { 
        using base = tuple4<arg1,arg2,arg3,arg4>;
        DECLARE_TUPLE_VAL_TYPE(5)
        DEFINE_TUPLE_VAL(5)
        DEFINE_TUPLE_CTOR(5)

        constexpr tuple5(const arg1& val1, const arg2& val2, const arg3& val3, const arg4& val4, const arg5& val5)
            : base(val1,val2,val3,val4), value5{val5} {}

        template <typename var1, typename var2, typename var3, typename var4, typename var5>
        constexpr tuple5(const tuple5<var1,var2,var3,var4,var5>& tp)
            : base(tp.value1,tp.value2,tp.value3,tp.value4), value5{tp.value5} {}

        // constexpr tuple5(tuple5&&) = default;
        // constexpr tuple5(const tuple5&) = default;
    };

    template <class arg1, class arg2, class arg3, class arg4, class arg5, class arg6>
    struct tuple6 : tuple5<arg1,arg2,arg3,arg4,arg5>
    { 
        using base = tuple5<arg1,arg2,arg3,arg4,arg5>;
        DECLARE_TUPLE_VAL_TYPE(6)
        DEFINE_TUPLE_VAL(6)
        DEFINE_TUPLE_CTOR(6)

        constexpr tuple6(const arg1& val1, const arg2& val2, const arg3& val3, const arg4& val4, const arg5& val5, const arg6& val6)
            : base(val1,val2,val3,val4,val5), value6{val6} {}
        
        template <typename var1, typename var2, typename var3, typename var4, typename var5, typename var6>
        constexpr tuple6(const tuple6<var1,var2,var3,var4,var5,var6>& tp)
            : base(tp.value1,tp.value2,tp.value3,tp.value4,tp.value5), value6{tp.value6} {}
        
        // constexpr tuple6(tuple6&&) = default;
        // constexpr tuple6(const tuple6&) = default;
    };

    template <class arg1, class arg2, class arg3, class arg4, class arg5, class arg6, class arg7>
    struct tuple7 : tuple6<arg1,arg2,arg3,arg4,arg5,arg6>
    { 
        using base = tuple6<arg1,arg2,arg3,arg4,arg5,arg6>;
        DECLARE_TUPLE_VAL_TYPE(7)
        DEFINE_TUPLE_VAL(7)
        DEFINE_TUPLE_CTOR(7)

        constexpr tuple7(const arg1& val1, const arg2& val2, const arg3& val3, const arg4& val4, const arg5& val5, const arg6& val6, const arg7& val7)
            : base(val1,val2,val3,val4,val5,val6), value7{val7} {}
        
        template <typename var1, typename var2, typename var3, typename var4, typename var5, typename var6, typename var7>
        constexpr tuple7(const tuple7<var1,var2,var3,var4,var5,var6,var7>& tp)
            : base(tp.value1,tp.value2,tp.value3,tp.value4,tp.value5,tp.value6), value7{tp.value7} {}
    };

    template <class arg1, class arg2, class arg3, class arg4, class arg5, class arg6, class arg7, class arg8>
    struct tuple8 : tuple7<arg1,arg2,arg3,arg4,arg5,arg6,arg7>
    { 
        using base = tuple7<arg1,arg2,arg3,arg4,arg5,arg6,arg7>;
        DECLARE_TUPLE_VAL_TYPE(8)
        DEFINE_TUPLE_VAL(8)
        DEFINE_TUPLE_CTOR(8)

        constexpr tuple8(const arg1& val1, const arg2& val2, const arg3& val3, const arg4& val4, const arg5& val5, const arg6& val6, const arg7& val7, const arg8& val8)
            : base(val1,val2,val3,val4,val5,val6,val7), value8{val8} {}
        
        template <typename var1, typename var2, typename var3, typename var4, typename var5, typename var6, typename var7, typename var8>
        constexpr tuple8(const tuple8<var1,var2,var3,var4,var5,var6,var7,var8>& tp)
            : base(tp.value1,tp.value2,tp.value3,tp.value4,tp.value5,tp.value6,tp.value7), value8{tp.value8} {}
    };

    template <class arg1, class arg2, class arg3, class arg4, class arg5, class arg6, class arg7, class arg8, class arg9>
    struct tuple9 : tuple8<arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8>
    { 
        using base = tuple8<arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8>;
        DECLARE_TUPLE_VAL_TYPE(9)
        DEFINE_TUPLE_VAL(9)
        DEFINE_TUPLE_CTOR(9)

        constexpr tuple9(const arg1& val1, const arg2& val2, const arg3& val3, const arg4& val4, const arg5& val5, const arg6& val6, const arg7& val7, const arg8& val8, const arg9& val9)
            : base(val1,val2,val3,val4,val5,val6,val7,val8), value9{val9} {}
        
        template <typename var1, typename var2, typename var3, typename var4, typename var5, typename var6, typename var7, typename var8, typename var9>
        constexpr tuple9(const tuple9<var1,var2,var3,var4,var5,var6,var7,var8,var9>& tp)
            : base(tp.value1,tp.value2,tp.value3,tp.value4,tp.value5,tp.value6,tp.value7,tp.value8), value9{tp.value9} {}
    };

    #define RETURN_TUPLE_BASE_TYPE_IF(numel) \
    if constexpr (N==numel) { \
        using type = tuple##numel<Args...>; \
        return meta::as_value_v<type>; \
    }

    template <typename...Args>
    struct tuple_base
    {
        static constexpr auto vtype = [](){
            constexpr auto N = sizeof...(Args);
            RETURN_TUPLE_BASE_TYPE_IF(1)
            else RETURN_TUPLE_BASE_TYPE_IF(2)
            else RETURN_TUPLE_BASE_TYPE_IF(3)
            else RETURN_TUPLE_BASE_TYPE_IF(4)
            else RETURN_TUPLE_BASE_TYPE_IF(5)
            else RETURN_TUPLE_BASE_TYPE_IF(6)
            else RETURN_TUPLE_BASE_TYPE_IF(7)
            else RETURN_TUPLE_BASE_TYPE_IF(8)
            else RETURN_TUPLE_BASE_TYPE_IF(9)
            // TODO: add error type
        }();
        using type = meta::type_t<decltype(vtype)>;
    };

    template <typename...Args>
    using tuple_base_t = typename tuple_base<Args...>::type;

    /**
     * @brief Poor man's tuple.
     * 
     * This structure doesn't aim to be fully STL-compatible,
     * only subset of that is used in nmtools.
     * 
     * @tparam Args 
     */
    template <typename...Args>
    struct tuple : tuple_base_t<Args...>
    {
        static_assert( sizeof...(Args) <= 9 );
        using base = tuple_base_t<Args...>;
        constexpr tuple() : base() {};

        constexpr tuple(const Args&...args) : base(args...) {}

        template <typename...args_t>
        constexpr tuple(const tuple<args_t...>& tp) : base(static_cast<tuple_base_t<args_t...>>(tp)) {}

        // constexpr tuple(const tuple&) = default;
        // constexpr tuple(tuple&&) = default;
    };

    template <>
    struct tuple<>
    {
        constexpr tuple() {};
    };

    template <typename...args_t>
    constexpr auto make_tuple(const args_t&...args)
    {
        constexpr auto N = sizeof...(args_t);
        if constexpr (N == 1) {
            return tuple1<args_t...>(args...);
        } else if constexpr (N == 2) {
            return tuple2<args_t...>(args...);
        } else if constexpr (N == 3) {
            return tuple3<args_t...>(args...);
        } else if constexpr (N == 4) {
            return tuple4<args_t...>(args...);
        }
    }

    #define HAS_VALUE_N(index) \
    template <typename T> \
    using has_value##index = decltype(meta::declval<T>().value##index);

    HAS_VALUE_N(1)
    HAS_VALUE_N(2)
    HAS_VALUE_N(3)
    HAS_VALUE_N(4)
    HAS_VALUE_N(5)
    HAS_VALUE_N(6)
    HAS_VALUE_N(7)
    HAS_VALUE_N(8)
    HAS_VALUE_N(9)

    #define RETURN_TUPLE_ELEM_IF(index) \
    if constexpr (((I+1)==index) && (meta::detail::expression_check<void,has_value##index,tuple_t>::value)) { \
        return (tp.value##index); \
    }

    template <auto I, typename...Args>
    constexpr decltype(auto) get(const tuple<Args...>& tp)
    {
        using tuple_t = tuple<Args...>;
        RETURN_TUPLE_ELEM_IF(1)
        else RETURN_TUPLE_ELEM_IF(2)
        else RETURN_TUPLE_ELEM_IF(3)
        else RETURN_TUPLE_ELEM_IF(4)
        else RETURN_TUPLE_ELEM_IF(5)
        else RETURN_TUPLE_ELEM_IF(6)
        else RETURN_TUPLE_ELEM_IF(7)
        else RETURN_TUPLE_ELEM_IF(8)
        else RETURN_TUPLE_ELEM_IF(9)
    }

    template <auto I, typename...Args>
    constexpr decltype(auto) get(tuple<Args...>& tp)
    {
        using tuple_t = tuple<Args...>;
        RETURN_TUPLE_ELEM_IF(1)
        else RETURN_TUPLE_ELEM_IF(2)
        else RETURN_TUPLE_ELEM_IF(3)
        else RETURN_TUPLE_ELEM_IF(4)
        else RETURN_TUPLE_ELEM_IF(5)
        else RETURN_TUPLE_ELEM_IF(6)
        else RETURN_TUPLE_ELEM_IF(7)
        else RETURN_TUPLE_ELEM_IF(8)
        else RETURN_TUPLE_ELEM_IF(9)
    }

    template <typename T>
    struct tuple_size;

    template <typename...Args>
    struct tuple_size<tuple<Args...>>
    {
        static constexpr auto value = sizeof...(Args);
    };

    template <typename T>
    inline constexpr auto tuple_size_v = tuple_size<T>::value;

    template <size_t I, typename T>
    struct tuple_element;

    #define RETURN_TUPLE_ARG_TYPE_IF(index) \
    if constexpr (((I+1)==index) && (meta::detail::expression_check<void,has_value##index,tuple_type>::value)) { \
        using type = decltype(meta::declval<tuple_type>().value##index); \
        return meta::as_value_v<type>; \
    }

    template <size_t I, typename...Args>
    struct tuple_element<I,tuple<Args...>>
    {
        using tuple_type = tuple<Args...>;
        nmtools_meta_variable_attribute
        static constexpr auto vtype = [](){
            RETURN_TUPLE_ARG_TYPE_IF(1)
            else RETURN_TUPLE_ARG_TYPE_IF(2)
            else RETURN_TUPLE_ARG_TYPE_IF(3)
            else RETURN_TUPLE_ARG_TYPE_IF(4)
            else RETURN_TUPLE_ARG_TYPE_IF(5)
            else RETURN_TUPLE_ARG_TYPE_IF(6)
            else RETURN_TUPLE_ARG_TYPE_IF(7)
            else RETURN_TUPLE_ARG_TYPE_IF(8)
            else RETURN_TUPLE_ARG_TYPE_IF(9)
        }();
        using type = meta::type_t<decltype(vtype)>;
    };

    template <size_t I, typename T>
    using tuple_element_t = meta::type_t<tuple_element<I,T>>;

    #undef DEFINE_TUPLE_VAL
    #undef DEFINE_TUPLE_CTOR
    #undef RETURN_TUPLE_BASE_TYPE_IF
    #undef RETURN_TUPLE_ARG_TYPE_IF
    #undef RETURN_TUPLE_ELEM_IF
    #undef HAS_VALUE_N

} // namespace nmtools::utl

// folowing https://en.cppreference.com/w/cpp/language/structured_binding
// and based on current implementation of utl::tuple,
// must expose some of metafunction to std namespace 🤦

// NOTE: to avoid ambiguous on clang with libc++,
// apparently on android NDK, the struct is located at std::__ndk1::tuple_size 🤦,
// on emscripten it is 'std::__2::tuple_size' 🤦,
// which triggers ambiguous reference when trying to specialize

// make sure to follow stl tuple, if has stl
#if __has_include(<tuple>)
#include <tuple>
#else
namespace std
{
    template <typename T>
    struct tuple_size;

    template <size_t I, typename T>
    struct tuple_element;
} // namespace std
#endif // <tuple>

#define NMTOOLS_UTL_STD_TUPLE_SIZE(tuple) \
    template <typename...Args> \
    struct std::tuple_size<nmtools::utl::tuple<Args...>> \
    { \
        using tuple_type = nmtools::utl::tuple<Args...>; \
        static constexpr auto value = nmtools::utl::tuple_size_v<tuple_type>; \
    }; \
    template <typename...Args> \
    struct std::tuple_size<const nmtools::utl::tuple<Args...>> : std::tuple_size<nmtools::utl::tuple<Args...>>{}; \

#define NMTOOLS_UTL_STD_TUPLE_ELEMENT(tuple) \
    template <size_t I, typename...Args> \
    struct std::tuple_element<I,nmtools::utl::tuple<Args...>> \
    { \
        using tuple_type = nmtools::utl::tuple<Args...>; \
        using type = nmtools::utl::tuple_element_t<I,tuple_type>; \
    }; \
    template <size_t I, typename...Args> \
    struct std::tuple_element<I,const nmtools::utl::tuple<Args...>> \
    { \
        using tuple_type = nmtools::utl::tuple<Args...>; \
        using type = const nmtools::utl::tuple_element_t<I,tuple_type>; \
    };

// NOTE: to allow avr-gcc, the base class must be defined as well

NMTOOLS_UTL_STD_TUPLE_SIZE(tuple)
NMTOOLS_UTL_STD_TUPLE_ELEMENT(tuple)

NMTOOLS_UTL_STD_TUPLE_SIZE(tuple1)
NMTOOLS_UTL_STD_TUPLE_ELEMENT(tuple1)

NMTOOLS_UTL_STD_TUPLE_SIZE(tuple2)
NMTOOLS_UTL_STD_TUPLE_ELEMENT(tuple2)

NMTOOLS_UTL_STD_TUPLE_SIZE(tuple3)
NMTOOLS_UTL_STD_TUPLE_ELEMENT(tuple3)

NMTOOLS_UTL_STD_TUPLE_SIZE(tuple4)
NMTOOLS_UTL_STD_TUPLE_ELEMENT(tuple4)

NMTOOLS_UTL_STD_TUPLE_SIZE(tuple5)
NMTOOLS_UTL_STD_TUPLE_ELEMENT(tuple5)

NMTOOLS_UTL_STD_TUPLE_SIZE(tuple6)
NMTOOLS_UTL_STD_TUPLE_ELEMENT(tuple6)

NMTOOLS_UTL_STD_TUPLE_SIZE(tuple7)
NMTOOLS_UTL_STD_TUPLE_ELEMENT(tuple7)

NMTOOLS_UTL_STD_TUPLE_SIZE(tuple8)
NMTOOLS_UTL_STD_TUPLE_ELEMENT(tuple8)

NMTOOLS_UTL_STD_TUPLE_SIZE(tuple9)
NMTOOLS_UTL_STD_TUPLE_ELEMENT(tuple9)

#undef NMTOOLS_UTL_STD_TUPLE_SIZE
#undef NMTOOLS_UTL_STD_TUPLE_ELEMENT

#endif // NMTOOLS_UTL_TUPLE_HPP