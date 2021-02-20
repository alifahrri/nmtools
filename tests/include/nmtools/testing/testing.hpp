#ifndef NMTOOLS_TESTING_HPP
#define NMTOOLS_TESTING_HPP

#include "nmtools/utils/isclose.hpp"
#include "nmtools/utils/isequal.hpp"
#include "nmtools/utils/to_string.hpp"
#include "nmtools/array/kind.hpp"
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/utility/cast.hpp"
#include "nmtools/array/index/product.hpp"
#include <type_traits>
#include <array>
// when using emscripten, compiler complains about 'boost/type_index.hpp' file not found
// while cmake find boost is success, for now fallback to typeid
#if __has_include(<boost/type_index.hpp>)
    #include <boost/type_index.hpp>
    #define _NMTOOLS_TESTING_HAS_TYPE_INDEX
#endif

#ifdef _NMTOOLS_TESTING_HAS_TYPE_INDEX
#define NMTOOLS_TESTING_GET_TYPENAME(type) \
boost::typeindex::type_id<type>().pretty_name()
#else
#define NMTOOLS_TESTING_GET_TYPENAME(type) \
typeid(type).name()
#endif

/**
 * @defgroup testing
 * collections of helper functions and macros for testing purpose.
 * 
 */

namespace nmtools::testing
{
    using std::integer_sequence;
    template <size_t...I>
    using index_sequence = integer_sequence<size_t,I...>;

    /**
     * @ingroup testing
     * @{
     */

    /**
     * @brief overloaded version of make_func_args
     * 
     * @tparam Args non-type template parameters passed that should be passed to func
     * @param func function name
     * @param args arguments that should be passed to func
     * @return auto string formated with `func<tparams(s)...>(typename(s)...)`
     */
    template <typename...Args>
    auto make_func_args(std::string func, const Args&...args)
    {
        std::stringstream ss;
        constexpr auto n = (sizeof...(args));
        constexpr auto m = (sizeof...(Args));
        #ifdef _NMTOOLS_TESTING_HAS_TYPE_INDEX
        auto typenames = std::array<std::string,n>{
            {boost::typeindex::type_id<decltype(args)>().pretty_name()...}
        };
        #else
        auto typenames = std::array<std::string,n>{
            {typeid(decltype(args)).name()...}
        };
        #endif
        /* non-type template parameters, assuming can be converted to string*/
        // auto tparams = std::array<std::string,m>{
        //     {std::to_string(Args)...}
        // };
        ss << func;
        // if constexpr (m>=1) {
        //     ss << '<';
        //     for (size_t i=0; i<m; i++) {
        //         ss << tparams[i];
        //         if (i!=(m-1))
        //             ss << ",";
        //     }
        //     ss << '>';
        // }
        ss << '(';
        for (size_t i=0; i<n; i++) {
            ss << typenames[i];
            if (i!=(n-1))
                ss << ",";
        }
        ss << ')';
        return ss.str();
    } // auto make_func_args

    template <typename...Args>
    auto make_func_args(std::string func, std::string result_type, const Args&...args)
    {
        std::stringstream ss;
        constexpr auto n = (sizeof...(args));
        constexpr auto m = (sizeof...(Args));
        #ifdef _NMTOOLS_TESTING_HAS_TYPE_INDEX
        auto typenames = std::array<std::string,n>{
            {boost::typeindex::type_id<decltype(args)>().pretty_name()...}
        };
        #else
        auto typenames = std::array<std::string,n>{
            {typeid(decltype(args)).name()...}
        };
        #endif
        /* non-type template parameters, assuming can be converted to string*/
        // auto tparams = std::array<std::string,m>{
        //     {std::to_string(Args)...}
        // };
        ss << func;
        // if constexpr (m>=1) {
        //     ss << '<';
        //     for (size_t i=0; i<m; i++) {
        //         ss << tparams[i];
        //         if (i!=(m-1))
        //             ss << ",";
        //     }
        //     ss << '>';
        // }
        ss << '(';
        for (size_t i=0; i<n; i++) {
            ss << typenames[i];
            if (i!=(n-1))
                ss << ",";
        }
        ss << ") -> " << result_type;
        return ss.str();
    } // auto make_func_args

    /** @} */ // end groupt testing
} // nmtools::testing

namespace nmtools::array::kind
{
    // for testing purpose only
    struct nested_vector_t {};

    struct fixed_vec_t {};
    struct dynamic_vec_t {};

    inline constexpr auto nested_vec  = nested_vector_t {};
    inline constexpr auto fixed_vec   = fixed_vec_t {};
    inline constexpr auto dynamic_vec = dynamic_vec_t {};
} // namespace nmtools::array::kind

namespace nmtools
{
    struct cast_kind_t {};

    template <typename src_t>
    struct meta::resolve_optype<
        std::enable_if_t<meta::is_fixed_size_ndarray_v<src_t>>,
        cast_kind_t, src_t, array::kind::fixed_t
    >
    {
        using element_t = get_element_type_t<src_t>;
        // start with arbitrary shaped fixed_ndarray, then resize with src
        using fixed_kind_t = array::fixed_ndarray<element_t,1>;
        using type = resize_fixed_ndarray_t<fixed_kind_t,src_t>;
    }; // resolve_optype

    template <typename src_t>
    struct meta::resolve_optype<
        void, cast_kind_t, src_t, array::kind::dynamic_t
    >
    {
        using element_t = get_element_type_t<src_t>;
        using type = array::dynamic_ndarray<element_t>;
    }; // resolve_optype

    template <typename src_t>
    struct meta::resolve_optype<
        std::enable_if_t<meta::is_fixed_size_ndarray_v<src_t>>,
        cast_kind_t, src_t, array::kind::hybrid_t
    >
    {
        using element_t = get_element_type_t<src_t>;
        static constexpr auto shape = fixed_ndarray_shape_v<src_t>;
        static constexpr auto numel = index::product(shape);
        static constexpr auto dim = fixed_ndarray_dim_v<src_t>;
        using type = array::hybrid_ndarray<element_t,numel,dim>;
    }; // resolve_optype

    template <typename src_t>
    struct meta::resolve_optype<
        std::enable_if_t<meta::is_fixed_size_ndarray_v<src_t>>,
        cast_kind_t, src_t, array::kind::nested_vector_t
    >
    {
        using element_t = get_element_type_t<src_t>;
        static constexpr auto dim = fixed_ndarray_dim_v<src_t>;
        using type = meta::make_nested_dynamic_array_t<std::vector,element_t,dim>;
    }; // resolve_optype

    template <typename src_t>
    struct meta::resolve_optype<
        std::enable_if_t<meta::is_fixed_size_ndarray_v<src_t>>,
        cast_kind_t, src_t, array::kind::fixed_vec_t
    >
    {
        using element_t = get_element_type_t<src_t>;
        static constexpr auto shape = fixed_ndarray_shape_v<src_t>;
        static constexpr auto dim   = fixed_ndarray_dim_v<src_t>;
        using type = std::conditional_t<dim==1,
            array::fixed_vector<element_t,std::get<0>(shape)>, void
        >;
    }; // resolve_optype

    template <typename src_t>
    struct meta::resolve_optype<
        std::enable_if_t<meta::is_fixed_size_ndarray_v<src_t>>,
        cast_kind_t, src_t, array::kind::dynamic_vec_t
    >
    {
        using element_t = get_element_type_t<src_t>;
        static constexpr auto shape = fixed_ndarray_shape_v<src_t>;
        static constexpr auto dim   = fixed_ndarray_dim_v<src_t>;
        using type = std::conditional_t<dim==1,
            array::dynamic_vector<element_t>, void
        >;
    }; // resolve_optype

    template <typename src_t, typename kind_t>
    constexpr auto cast(const src_t& src, const kind_t& kind)
    {
        using ret_t = meta::resolve_optype_t<cast_kind_t,src_t,kind_t>;
        return cast<ret_t>(src);
    } // cast
} // namespace nmtools

using nmtools::utils::isclose;
using nmtools::utils::isequal;

/**
 * @ingroup testing
 * @{
 */

/**
 * @brief copy variable for testing while casting to desired type T
 * Expect to be called from limited scope (to avoid naming conflict).
 * Used by `NMTOOLS_TESTING_ISCLOSE_TEST_CAST` macro.
 * 
 * @todo remove
 */
#define NMTOOLS_TESTING_VAR_CAST(T, var, var_name) \
using value_type_##var_name = nmtools::meta::get_element_type_t<T>; \
auto var_name = nmtools::testing::cast<T>(var<value_type_##var_name>);

/**
 * @brief call stringify helper with std::stringstream as tparam.
 * 
 */
#define STRINGIFY(array) \
nmtools::utils::to_string(array)

#define NMTOOLS_TESTING_OUTPUT_PRECISION 1e-6

/**
 * @brief implementation of gtest assert macro
 * 
 */
#define NMTOOLS_ASSERT_CLOSE_GTEST(result,expect) \
EXPECT_TRUE(isclose(result,expect,NMTOOLS_TESTING_OUTPUT_PRECISION)) \
        <<   "Actual  :\n" \
        << STRINGIFY(result) \
        << "\nExpected:\n" \
        << STRINGIFY(expect) \

/**
 * @brief implementation of gtest assert macro
 * 
 */
#define NMTOOLS_ASSERT_EQUAL_GTEST(result,expect) \
EXPECT_TRUE(isequal(result,expect)) \
        <<   "Actual  :\n" \
        << STRINGIFY(result) \
        << "\nExpected:\n" \
        << STRINGIFY(expect) \

/**
 * @brief implementation of typeinfo logging for doctest,
 * may be used by `NMTOOLS_TESTING_LOG_TYPEINFO` macro
 * 
 */
#define NMTOOLS_TESTING_LOG_TYPEINFO_IMPL_DOCTEST INFO

#ifndef __EMSCRIPTEN__
#define NMTOOLS_CHECK_MESSAGE(result, message) \
{ \
    CHECK_MESSAGE(result, message); \
}
#else
#define NMTOOLS_CHECK_MESSAGE(result, message) \
{ \
    CHECK(result); \
}
#endif // __EMSCRIPTEN__

/**
 * @brief implementation of doctest assert macro with message
 * 
 */
#define NMTOOLS_ASSERT_CLOSE_DOCTEST(result,expect) \
{ \
    auto __result = isclose(result,expect,NMTOOLS_TESTING_OUTPUT_PRECISION); \
    std::string message {}; \
    message = message + \
        + "\n\tActual  : " + STRINGIFY(result)  \
        + "\n\tExpected: " + STRINGIFY(expect); \
    NMTOOLS_CHECK_MESSAGE( __result, message ); \
}

/**
 * @brief implementation of doctest assert macro with message
 * 
 */
#define NMTOOLS_ASSERT_EQUAL_DOCTEST(result,expect) \
CHECK_MESSAGE(isequal(result,expect), \
    (   \
        std::string{} \
        + "\n\tActual  : " + STRINGIFY(result) \
        + "\n\tExpected: " + STRINGIFY(expect) \
    )   \
);

/**
 * @brief default implementation of typeinfo logging macro,
 * used by `NMTOOLS_TESTING_LOG_TYPEINFO` macro by default,
 * can be overriden.
 * 
 */
#define NMTOOLS_TESTING_LOG_TYPEINFO_IMPL(x)

/**
 * @brief log information about possibly generic function call given
 * args, format func and the type of args to string, e.g. "func(typeinfo(args))".
 * Pass the formatted function-args info to logging typeinfo implementation,
 * a.k.a. `NMTOOLS_TESTING_LOG_TYPEINFO_IMPL` macro.
 * May be called by `NMTOOLS_TESTING_ISCLOSE_TEST` 
 * and `NMTOOLS_TESTING_ISCLOSE_TEST_CAST` macros.
 * 
 */
#define NMTOOLS_TESTING_LOG_TYPEINFO(func,...) \
NMTOOLS_TESTING_LOG_TYPEINFO_IMPL( \
    nmtools::testing::make_func_args(#func,__VA_ARGS__) \
) \

/**
 * @brief check if return value of `func(arg)` is close with `expect`.
 * May log information about typeinfo of `func(arg)`.
 * Requires a macro function `NMTOOLS_ASSERT_CLOSE`
 * that takes two arguments to be defined.
 * 
 */
#define NMTOOLS_TESTING_ISCLOSE_TEST(func, expect, ...) \
{  \
    auto result = func(__VA_ARGS__); \
    NMTOOLS_TESTING_LOG_TYPEINFO(func,__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE(result,expect); \
    /* TODO: check return type! */ \
} \

#define NMTOOLS_TESTING_TYPECHECK_ISCLOSE_TEST(func, expect, type, ...) \
{  \
    auto result = func(__VA_ARGS__); \
    static_assert(std::is_same_v<decltype(result),type>); \
    NMTOOLS_TESTING_LOG_TYPEINFO(func,__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE(result,expect); \
    /* TODO: check return type! */ \
} \

/**
 * @brief check if return value of `func(arg)` is close with `expect` at compile-time.
 * Requires `func`, `arg`, and `expect` to be constexpr.
 * 
 */
#define NMTOOLS_TESTING_CONSTEXPR_ISCLOSE_TEST(func, expect, ...) \
{ \
    constexpr auto result = func(__VA_ARGS__); \
    static_assert(isclose(result,expect,NMTOOLS_TESTING_OUTPUT_PRECISION)); \
    /* TODO: check return type! */ \
} \

/**
 * @brief check if return value of `func(arg)` is close with `expect`.
 * May log information about typeinfo of `func(arg)`.
 * Requires a macro function `NMTOOLS_ASSERT_CLOSE`
 * that takes two arguments to be defined.
 * 
 */
#define NMTOOLS_TESTING_ISEQUAL_TEST(func, expect, ...) \
{  \
    auto result = func(__VA_ARGS__); \
    NMTOOLS_TESTING_LOG_TYPEINFO(func,__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL(result,expect); \
    /* TODO: check return type! */ \
} \

#define NMTOOLS_TESTING_TYPECHECK_ISEQUAL_TEST(func, expect, type, ...) \
{  \
    auto result = func(__VA_ARGS__); \
    static_assert(std::is_same_v<decltype(result),type>); \
    NMTOOLS_TESTING_LOG_TYPEINFO(func,__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL(result,expect); \
    /* TODO: check return type! */ \
} \

/**
 * @brief check if return value of `func(arg)` is close with `expect` at compile-time.
 * Requires `func`, `arg`, and `expect` to be constexpr.
 * 
 */
#define NMTOOLS_TESTING_CONSTEXPR_ISEQUAL_TEST(func, expect, ...) \
{ \
    constexpr auto result = func(__VA_ARGS__); \
    static_assert(isequal(result,expect)); \
    /* TODO: check return type! */ \
} \

/**
 * @brief check if return type of `func`, given casted `arg` to type T, is close with `expect`.
 * Requires `arg` to be class template. Type cast is done by `NMTOOLS_TESTING_VAR_CAST` macro.
 * Requires a macro function `NMTOOLS_ASSERT_CLOSE` that takes two arguments to be defined.
 * May log information about typeinfo of `func` and casted `arg`
 * using `NMTOOLS_TESTING_LOG_TYPEINFO` macro.
 * 
 * @todo remove
 */
#define NMTOOLS_TESTING_ISCLOSE_TEST_CAST(T, func, expect, arg) \
{   \
    NMTOOLS_TESTING_VAR_CAST(T, arg, test_variable) \
    auto result = func(test_variable); \
    NMTOOLS_TESTING_LOG_TYPEINFO(func,test_variable); \
    NMTOOLS_ASSERT_CLOSE(result,expect); \
    /* TODO: check return type! */ \
} \

#define NMTOOLS_TESTING_RESULT_TYPE(func,...) \
NMTOOLS_TESTING_GET_TYPENAME(decltype(func(__VA_ARGS__)))

#define NMTOOLS_TESTING_FUNCTION_SIGNATURE(func,...) \
nmtools::testing::make_func_args(#func,NMTOOLS_TESTING_RESULT_TYPE(func,__VA_ARGS__),__VA_ARGS__).c_str()

/**
 * @brief define `doctest`'s `SUBCASE` with pretty-name of `func(args...)` as case name,
 * run and check if `func(args...)` match `expect`.
 * 
 */
#define NMTOOLS_TESTING_DOCTEST_SUBCASE(func, expect, ...) \
{   \
    SUBCASE(NMTOOLS_TESTING_FUNCTION_SIGNATURE(func,__VA_ARGS__))   \
    {   \
        NMTOOLS_TESTING_ISCLOSE_TEST(func, expect, __VA_ARGS__); \
    }   \
}   \

// @todo add subcase for isequal

/**
 * @brief like `NMTOOLS_TESTING_DOCTEST_SUBCASE` but at compile-time
 * 
 */
#define NMTOOLS_TESTING_DOCTEST_CONSTEXPR_SUBCASE(func, expect, ...) \
{   \
    SUBCASE(NMTOOLS_TESTING_FUNCTION_SIGNATURE(func,__VA_ARGS__))   \
    {   \
        NMTOOLS_TESTING_CONSTEXPR_ISCLOSE_TEST(func, expect, __VA_ARGS__); \
    }   \
}   \

#define NMTOOLS_TESTING_DOCTEST_TYPECHECK_SUBCASE(func, expect, type, ...) \
{   \
    SUBCASE(NMTOOLS_TESTING_FUNCTION_SIGNATURE(func,__VA_ARGS__))   \
    {   \
        NMTOOLS_TESTING_TYPECHECK_ISCLOSE_TEST(func, expect, type, __VA_ARGS__); \
    }   \
}   \

/**
 * @brief alias template for 1D dynamic array using std::vector
 * 
 * @tparam T value_type
 */
template <typename T>
using vec_t = std::vector<T>;

/**
 * @brief alias template for 2D dynamic array using nested std::vector
 * 
 * @tparam T value_type
 */
template <typename T>
using nested_vec_t = std::vector<std::vector<T>>;

/**
 * @brief alias template for 1D fixed array using nmtools::array::fixed_vector
 * 
 * @tparam N desired number of elements
 */
template <size_t N>
using fdvec_t = nmtools::array::fixed_vector<double,N>;
template <size_t N>
using ffvec_t = nmtools::array::fixed_vector<float,N>;

/**
 * @brief alias template for 2D fixed array using nmtools::array::fixed_matrix
 * 
 * @tparam Rows desired number of rows
 * @tparam Cols desired number of columns
 */
template <size_t Rows, size_t Cols>
using fdmat_t = nmtools::array::fixed_matrix<double,Rows,Cols>;
template <size_t Rows, size_t Cols>
using ffmat_t = nmtools::array::fixed_matrix<float,Rows,Cols>;

/**
 * @brief alias template for 1D dynamic array using nmtools::array::dynamic_vector
 * 
 * @tparam T value_type
 */
template <typename T>
using dvec_t = nmtools::array::dynamic_vector<T>;

/**
 * @brief alias template for 2D dynamic array using nmtools::array::dynamic_matrix
 * 
 * @tparam T value_type
 */
template <typename T>
using dmat_t = nmtools::array::dynamic_matrix<T>;

/**
 * @brief helper macro to declare inline std::array
 * with element type of double and float given template
 * variable `x` as macro parameter.
 * The variable are declared with name of `{prefix}ad` and `{prefix}af`
 * for double and float, respectively.
 * Expected to be used for declaring testing data variable.
 * Note that `{prefix}` is performed using  token-pasting operator, 
 * aka `##`, see https://godbolt.org/z/8TPrsq for simple demo.
 * 
 */
#define NMTOOLS_TESTING_DATA_DECLARE_ARRAY(prefix,x) \
inline auto prefix##ad = ::nmtools::cast<double>(x<double>); \
inline auto prefix##af = ::nmtools::cast<float>(x<float>);  \

/**
 * @brief helper macro to declare inline matrix with type of
 * `nested_vec_t<double>`, `nested_vec_t<float>`, `fdmat_t<...>`, `ffmat_t<...>`.
 * The variable are declared with name of `{prefix}vd`, `{prefix}vf`, `{prefix}fd`, `{prefix}ff`,
 * for the corresponding types above, respectively.
 * Those variables are casted from `{prefix}ad` and `{prefix}af` for corresponding double and float type.
 * Expected to be used for declaring testing data variable.
 * Note that `{prefix}` is performed using  token-pasting operator, 
 * aka `##`, see https://godbolt.org/z/8TPrsq for simple demo.
 * 
 */
#define NMTOOLS_TESTING_DATA_DECLARE_MAT(prefix,Rows,Cols)          \
inline auto prefix##vd = ::nmtools::cast<nested_vec_t<double>>(prefix##ad);    \
inline auto prefix##vf = ::nmtools::cast<nested_vec_t<float>>(prefix##af);     \
inline auto prefix##fd = ::nmtools::cast<fdmat_t<Rows,Cols>>(prefix##ad);      \
inline auto prefix##ff = ::nmtools::cast<ffmat_t<Rows,Cols>>(prefix##af);      \
inline auto prefix##dd = ::nmtools::cast<dmat_t<double>>(prefix##ad);          \
inline auto prefix##df = ::nmtools::cast<dmat_t<float>>(prefix##ad);           \

/**
 * @brief helper macro to declare inline vector with type of
 * `vec_t<double>`, `vec_t<float>`, `fdvec_t<...>`, `ffvec_t<...>`.
 * The variable are declared with name of `{prefix}vd`, `{prefix}vf`, `{prefix}fd`, `{prefix}ff`,
 * for the corresponding types above, respectively.
 * Those variables are casted from `{prefix}ad` and `{prefix}af` for corresponding double and float type.
 * Expected to be used for declaring testing data variable.
 * Note that `{prefix}` is performed using  token-pasting operator, 
 * aka `##`, see https://godbolt.org/z/8TPrsq for simple demo.
 * 
 */
#define NMTOOLS_TESTING_DATA_DECLARE_VEC(prefix,N)          \
inline auto prefix##vd = ::nmtools::cast<vec_t<double>>(prefix##ad);   \
inline auto prefix##vf = ::nmtools::cast<vec_t<float>>(prefix##af);    \
inline auto prefix##fd = ::nmtools::cast<fdvec_t<N>>(prefix##ad);      \
inline auto prefix##ff = ::nmtools::cast<ffvec_t<N>>(prefix##af);      \
inline auto prefix##dd = ::nmtools::cast<dvec_t<double>>(prefix##ad);  \
inline auto prefix##df = ::nmtools::cast<dvec_t<float>>(prefix##af);   \

/**
 * @brief helper macro to declare inline scalar variable with type of double and float.
 * The variable are declared with name of `{prefix}vd`, `{prefix}vf`, `{prefix}fd`, `{prefix}ff`,
 * for the corresponding types above, respectively.
 * Those variables are casted from `{prefix}ad` and `{prefix}af` for corresponding double and float type.
 * Expected to be used for declaring testing data variable.
 * 
 */
#define NMTOOLS_TESTING_DATA_DECLARE_SCALAR(prefix,x) \
inline auto prefix##ad = ::nmtools::cast<double>(x<double>); \
inline auto prefix##vd = ::nmtools::cast<double>(x<double>); \
inline auto prefix##fd = ::nmtools::cast<double>(x<double>); \
inline auto prefix##dd = ::nmtools::cast<double>(x<double>); \
inline auto prefix##af = ::nmtools::cast<float>(x<float>); \
inline auto prefix##vf = ::nmtools::cast<float>(x<float>); \
inline auto prefix##ff = ::nmtools::cast<float>(x<float>); \
inline auto prefix##df = ::nmtools::cast<float>(x<float>); \

#define NMTOOLS_TESTING_DATA_DECLARE_INTEGER(x) \
inline auto x##ad = x; \
inline auto x##vd = x; \
inline auto x##fd = x; \
inline auto x##dd = x; \
inline auto x##af = x; \
inline auto x##vf = x; \
inline auto x##ff = x; \
inline auto x##df = x; \

/**
 * @brief helper macro to declare test data for given function for testing,
 * simply create namespace under `nmtools::testing::data::{module}::{function}`
 * 
 */
#define NMTOOLS_TESTING_DECLARE_CASE2(module, function) \
namespace nmtools::testing::data::module::function

/**
 * @brief helper macro to declare test data for given function for testing,
 * simply create namespace under `nmtools::testing::data::{module}::{function}`
 * 
 */
#define NMTOOLS_TESTING_DECLARE_CASE1(function) \
namespace nmtools::testing::data::function

/**
 * @brief helper macro to overload NMTOOLS_TESTING_DECLARE_CASE macro
 * 
 */
#define NMTOOLS_GET_TESTING_DECLARE_CASE_MACRO(_1,_2,NAME,...) NAME
#define NMTOOLS_TESTING_DECLARE_CASE(...) NMTOOLS_GET_TESTING_DECLARE_CASE_MACRO(__VA_ARGS__, NMTOOLS_TESTING_DECLARE_CASE2, NMTOOLS_TESTING_DECLARE_CASE1)(__VA_ARGS__)

#define NMTOOLS_TESTING_DECLARE_NS1(ns) \
using namespace nmtools::testing::data::ns;

#define NMTOOLS_TESTING_DECLARE_NS2(ns1, ns2) \
using namespace nmtools::testing::data::ns1::ns2;

#define NMTOOLS_TESTING_DECLARE_NS3(ns1, ns2, ns3) \
using namespace nmtools::testing::data::ns1::ns2::ns3;

#define NMTOOLS_TESTING_DECLARE_NS_MACRO(_1,_2,_3,NAME,...) NAME
#define NMTOOLS_TESTING_DECLARE_NS(...) NMTOOLS_TESTING_DECLARE_NS_MACRO(__VA_ARGS__, NMTOOLS_TESTING_DECLARE_NS3, NMTOOLS_TESTING_DECLARE_NS2, NMTOOLS_TESTING_DECLARE_NS1)(__VA_ARGS__)

/**
 * @brief helper macro to declare actual test data,
 * simply create new namespace under `{subcase}::args`
 * 
 */
#define NMTOOLS_TESTING_DECLARE_ARGS(subcase)   \
namespace subcase::args

/**
 * @brief helper macro to declare expected result of test case,
 * simply create new namespace under `{subcase}::expect`
 * 
 */
#define NMTOOLS_TESTING_DECLARE_EXPECT(subcase)   \
namespace subcase::expect

/**
 * @brief define test case for given func that takes single argument, using std::array as param.
 * Assuming a variable with name of {prefix}ad has already declared and visible within the scope.
 * 
 * @see NMTOOLS_TESTING_DECLARE_SUBCASES
 * @see NMTOOLS_TESTING_DATA_DECLARE_ARRAY
 * @see NMTOOLS_TESTING_DECLARE_TPARAM_SUBCASES
 */
#define NMTOOLS_TEST_SUBCASE_ARRAY_IMPL(func, result, prefix) \
NMTOOLS_TEST_SUBCASE( func, result, prefix##ad ); \
NMTOOLS_TEST_SUBCASE( func, result, prefix##af );

/**
 * @brief define test case for given func that takes two argument, using std::array as param.
 * Assuming a variable with name of {prefix}ad has already declared and visible within the scope.
 * 
 * @see NMTOOLS_TESTING_DECLARE_SUBCASES2
 * @see NMTOOLS_TESTING_DATA_DECLARE_ARRAY
 */
#define NMTOOLS_TEST_SUBCASE_ARRAY2_IMPL(func, result, xprefix, yprefix) \
NMTOOLS_TEST_SUBCASE( func, result, xprefix##ad, yprefix##ad ); \
NMTOOLS_TEST_SUBCASE( func, result, xprefix##af, yprefix##af );

/**
 * @brief define test case for given func that takes three argument, using std::array as param.
 * Assuming a variable with name of {prefix}ad has already declared and visible within the scope.
 * 
 * @see NMTOOLS_TESTING_DECLARE_SUBCASES3
 * @see NMTOOLS_TESTING_DATA_DECLARE_ARRAY
 */
#define NMTOOLS_TEST_SUBCASE_ARRAY3_IMPL(func, result, xprefix, yprefix, zprefix) \
NMTOOLS_TEST_SUBCASE( func, result, xprefix##ad, yprefix##ad, zprefix##ad ); \
NMTOOLS_TEST_SUBCASE( func, result, xprefix##af, yprefix##af, zprefix##af );

/*
 * @brief define test case for given func that takes single argument, using nmtools::array::fixed_* as param.
 * Assuming a variable with name of {prefix}fd has already declared and visible within the scope.
 * 
 * @see NMTOOLS_TESTING_DECLARE_SUBCASES
 * @see NMTOOLS_TESTING_DATA_DECLARE_MAT
 * @see NMTOOLS_TESTING_DECLARE_TPARAM_SUBCASES
 * @see nmtools::array::fixed_vector
 * @see nmtools::array::fixed_matrix
 */
#define NMTOOLS_TEST_SUBCASE_FIXED_ARRAY_IMPL(func, result, prefix) \
NMTOOLS_TEST_SUBCASE( func, result, prefix##fd ); \
NMTOOLS_TEST_SUBCASE( func, result, prefix##ff );

/*
 * @brief define test case for given func that takes two argument, using nmtools::array::fixed_* as param.
 * Assuming a variable with name of {prefix}fd has already declared and visible within the scope.
 * 
 * @see NMTOOLS_TESTING_DECLARE_SUBCASES2
 * @see NMTOOLS_TESTING_DATA_DECLARE_MAT
 * @see nmtools::array::fixed_vector
 * @see nmtools::array::fixed_matrix
 */
#define NMTOOLS_TEST_SUBCASE_FIXED_ARRAY2_IMPL(func, result, xprefix, yprefix) \
NMTOOLS_TEST_SUBCASE( func, result, xprefix##fd, yprefix##fd ); \
NMTOOLS_TEST_SUBCASE( func, result, xprefix##ff, yprefix##ff );

/*
 * @brief define test case for given func that takes three argument, using nmtools::array::fixed_* as param.
 * Assuming a variable with name of {prefix}fd has already declared and visible within the scope.
 * 
 * @see NMTOOLS_TESTING_DECLARE_SUBCASES2
 * @see NMTOOLS_TESTING_DATA_DECLARE_MAT
 * @see nmtools::array::fixed_vector
 * @see nmtools::array::fixed_matrix
 */
#define NMTOOLS_TEST_SUBCASE_FIXED_ARRAY3_IMPL(func, result, xprefix, yprefix, zprefix) \
NMTOOLS_TEST_SUBCASE( func, result, xprefix##fd, yprefix##fd, zprefix##fd ); \
NMTOOLS_TEST_SUBCASE( func, result, xprefix##ff, yprefix##ff, zprefix##ff );

/**
 * @brief define test case for given func that take single argument, using std::vector as param.
 * Assuming a variable with name of {prefix}vd has already declared and visible within the scope.
 * 
 * @see NMTOOLS_TESTING_DECLARE_SUBCASES
 * @see NMTOOLS_TESTING_DATA_DECLARE_MAT
 * 
 */
#define NMTOOLS_TEST_SUBCASE_VECTOR_IMPL(func, result, prefix) \
NMTOOLS_TEST_SUBCASE( func, result, prefix##vd ); \
NMTOOLS_TEST_SUBCASE( func, result, prefix##vf );

/**
 * @brief define test case for given func that take two arguments, using std::vector as param.
 * Assuming a variable with name of {prefix}vd has already declared and visible within the scope.
 * 
 * @see NMTOOLS_TESTING_DECLARE_SUBCASES2
 * @see NMTOOLS_TESTING_DATA_DECLARE_MAT
 * 
 */
#define NMTOOLS_TEST_SUBCASE_VECTOR2_IMPL(func, result, xprefix, yprefix) \
NMTOOLS_TEST_SUBCASE( func, result, xprefix##vd, yprefix##vd ); \
NMTOOLS_TEST_SUBCASE( func, result, xprefix##vf, yprefix##vf );

/**
 * @brief define test case for given func that take three arguments, using std::vector as param.
 * Assuming a variable with name of {prefix}vd has already declared and visible within the scope.
 * 
 * @see NMTOOLS_TESTING_DECLARE_SUBCASES3
 * @see NMTOOLS_TESTING_DATA_DECLARE_MAT
 * 
 */
#define NMTOOLS_TEST_SUBCASE_VECTOR3_IMPL(func, result, xprefix, yprefix, zprefix) \
NMTOOLS_TEST_SUBCASE( func, result, xprefix##vd, yprefix##vd, zprefix##vd ); \
NMTOOLS_TEST_SUBCASE( func, result, xprefix##vf, yprefix##vf, zprefix##vf );

/**
 * @brief define test case for given func that take single argument, using nmtools::array::dynamic_* as param.
 * Assuming a variable with name of {prefix}vd has already declared and visible within the scope.
 * 
 * @see NMTOOLS_TESTING_DECLARE_SUBCASES
 * @see NMTOOLS_TESTING_DATA_DECLARE_MAT
 * @see nmtools::array::dynamic_vector
 * @see nmtools::array::dynamic_matrix
 * 
 */
#define NMTOOLS_TEST_SUBCASE_DYNAMIC_ARRAY_IMPL(func, result, prefix) \
NMTOOLS_TEST_SUBCASE( func, result, prefix##dd ); \
NMTOOLS_TEST_SUBCASE( func, result, prefix##df );

/**
 * @brief define test case for given func that take two arguments, using nmtools::array::dynamic_* as param.
 * Assuming a variable with name of {prefix}vd has already declared and visible within the scope.
 * 
 * @see NMTOOLS_TESTING_DECLARE_SUBCASES2
 * @see NMTOOLS_TESTING_DATA_DECLARE_MAT
 * @see nmtools::array::dynamic_vector
 * @see nmtools::array::dynamic_matrix
 * 
 */
#define NMTOOLS_TEST_SUBCASE_DYNAMIC_ARRAY2_IMPL(func, result, xprefix, yprefix) \
NMTOOLS_TEST_SUBCASE( func, result, xprefix##dd, yprefix##dd ); \
NMTOOLS_TEST_SUBCASE( func, result, xprefix##df, yprefix##df );

/**
 * @brief define test case for given func that take three arguments, using nmtools::array::dynamic_* as param.
 * Assuming a variable with name of {prefix}vd has already declared and visible within the scope.
 * 
 * @see NMTOOLS_TESTING_DECLARE_SUBCASES3
 * @see NMTOOLS_TESTING_DATA_DECLARE_MAT
 * @see nmtools::array::dynamic_vector
 * @see nmtools::array::dynamic_matrix
 * 
 */
#define NMTOOLS_TEST_SUBCASE_DYNAMIC_ARRAY3_IMPL(func, result, xprefix, yprefix, zprefix) \
NMTOOLS_TEST_SUBCASE( func, result, xprefix##dd, yprefix##dd, zprefix##dd ); \
NMTOOLS_TEST_SUBCASE( func, result, xprefix##df, yprefix##df, zprefix##df );

#define NMTOOLS_TEST_SUBCASE_NOOP(...) {}

/**
 * @brief allow to skip testing with fixed size array
 * (std::array, nmtools::array::fixed_vector, nmtools::array::fixed_matrix)
 * 
 */
#ifndef NMTOOLS_TEST_SKIP_FIXED_SIZE_ARRAY
#define NMTOOLS_TEST_SUBCASE_ARRAY NMTOOLS_TEST_SUBCASE_ARRAY_IMPL
#define NMTOOLS_TEST_SUBCASE_ARRAY2 NMTOOLS_TEST_SUBCASE_ARRAY2_IMPL
#define NMTOOLS_TEST_SUBCASE_ARRAY3 NMTOOLS_TEST_SUBCASE_ARRAY3_IMPL
#define NMTOOLS_TEST_SUBCASE_FIXED_ARRAY NMTOOLS_TEST_SUBCASE_FIXED_ARRAY_IMPL
#define NMTOOLS_TEST_SUBCASE_FIXED_ARRAY2 NMTOOLS_TEST_SUBCASE_FIXED_ARRAY2_IMPL
#define NMTOOLS_TEST_SUBCASE_FIXED_ARRAY3 NMTOOLS_TEST_SUBCASE_FIXED_ARRAY3_IMPL
#else // NMTOOLS_TEST_SKIP_FIXED_SIZE_ARRAY
/**
 * @brief actually skip testing with std::array
 * 
 */
#define NMTOOLS_TEST_SUBCASE_ARRAY  NMTOOLS_TEST_SUBCASE_NOOP
#define NMTOOLS_TEST_SUBCASE_ARRAY2 NMTOOLS_TEST_SUBCASE_NOOP
#define NMTOOLS_TEST_SUBCASE_ARRAY3 NMTOOLS_TEST_SUBCASE_NOOP
/**
 * @brief actually skip testing with nmtools::array::fixed_*
 * 
 */
#define NMTOOLS_TEST_SUBCASE_FIXED_ARRAY  NMTOOLS_TEST_SUBCASE_NOOP
#define NMTOOLS_TEST_SUBCASE_FIXED_ARRAY2 NMTOOLS_TEST_SUBCASE_NOOP
#define NMTOOLS_TEST_SUBCASE_FIXED_ARRAY3 NMTOOLS_TEST_SUBCASE_NOOP
#endif // NMTOOLS_TEST_SKIP_FIXED_SIZE_ARRAY

#ifndef NMTOOLS_TEST_SKIP_DYNAMIC_SIZE_ARRAY
#define NMTOOLS_TEST_SUBCASE_VECTOR NMTOOLS_TEST_SUBCASE_VECTOR_IMPL
#define NMTOOLS_TEST_SUBCASE_VECTOR2 NMTOOLS_TEST_SUBCASE_VECTOR2_IMPL
#define NMTOOLS_TEST_SUBCASE_VECTOR3 NMTOOLS_TEST_SUBCASE_VECTOR3_IMPL
#define NMTOOLS_TEST_SUBCASE_DYNAMIC_ARRAY NMTOOLS_TEST_SUBCASE_DYNAMIC_ARRAY_IMPL
#define NMTOOLS_TEST_SUBCASE_DYNAMIC_ARRAY2 NMTOOLS_TEST_SUBCASE_DYNAMIC_ARRAY2_IMPL
#define NMTOOLS_TEST_SUBCASE_DYNAMIC_ARRAY3 NMTOOLS_TEST_SUBCASE_DYNAMIC_ARRAY3_IMPL
#else // NMTOOLS_TEST_SKIP_DYNAMIC_SIZE_ARRAY
/**
 * @brief actually skip testing with std::vector
 * 
 */
#define NMTOOLS_TEST_SUBCASE_VECTOR  NMTOOLS_TEST_SUBCASE_NOOP
#define NMTOOLS_TEST_SUBCASE_VECTOR2 NMTOOLS_TEST_SUBCASE_NOOP
#define NMTOOLS_TEST_SUBCASE_VECTOR3 NMTOOLS_TEST_SUBCASE_NOOP
/**
 * @brief actually skip with nmtools::array::dynamic_*
 * 
 */
#define NMTOOLS_TEST_SUBCASE_DYNAMIC_ARRAY  NMTOOLS_TEST_SUBCASE_NOOP
#define NMTOOLS_TEST_SUBCASE_DYNAMIC_ARRAY2 NMTOOLS_TEST_SUBCASE_NOOP
#define NMTOOLS_TEST_SUBCASE_DYNAMIC_ARRAY3 NMTOOLS_TEST_SUBCASE_NOOP
#endif // NMTOOLS_TEST_SKIP_DYNAMIC_SIZE_ARRAY

/**
 * @brief declare subcase for testing for function that takes single arguments.
 * @note that the testing namespace is strictly `nmtools::testing::data::{func}::{case_name}`,
 * and the arguments suffixes should be matched with NMTOOLS_TESTING_DATA_DECLARE_ARRAY,
 * NMTOOLS_TESTING_DATA_DECLARE_MAT, and NMTOOLS_TESTING_DATA_DECLARE_VEC macros
 * @see NMTOOLS_TESTING_DATA_DECLARE_ARRAY
 * @see NMTOOLS_TESTING_DATA_DECLARE_MAT
 * @see NMTOOLS_TESTING_DATA_DECLARE_VEC
 * @todo also add multiprecision whenever possible
 * 
 */
#define NMTOOLS_TESTING_DECLARE_SUBCASES(case_name, func, result, prefix) \
{   \
    using namespace nmtools::testing::data::func::case_name;    \
    NMTOOLS_TEST_SUBCASE_ARRAY( func, result, prefix );         \
    NMTOOLS_TEST_SUBCASE_VECTOR( func, result, prefix );        \
    NMTOOLS_TEST_SUBCASE_FIXED_ARRAY( func, result, prefix );   \
    NMTOOLS_TEST_SUBCASE_DYNAMIC_ARRAY( func, result, prefix ); \
}   \


/**
 * @brief declare subcase for testing for functions that takes single argument and single template parameters.
 * @note that the testing namespace is strictly `nmtools::testing::data::{func}::{case_name}`,
 * and the arguments suffixes should be matched with NMTOOLS_TESTING_DATA_DECLARE_ARRAY,
 * NMTOOLS_TESTING_DATA_DECLARE_MAT, and NMTOOLS_TESTING_DATA_DECLARE_VEC macros.
 * Also note that tparam is not prefixed.
 * @see NMTOOLS_TESTING_DATA_DECLARE_ARRAY
 * @see NMTOOLS_TESTING_DATA_DECLARE_MAT
 * @see NMTOOLS_TESTING_DATA_DECLARE_VEC
 * @todo also add multiprecision whenever possible
 * 
 */
#define NMTOOLS_TESTING_DECLARE_TPARAM_SUBCASES(case_name, func, tparam, result, prefix) \
{   \
    using namespace nmtools::testing::data::func::case_name;  \
    NMTOOLS_TEST_SUBCASE_ARRAY( func<tparam>, result, prefix );         \
    NMTOOLS_TEST_SUBCASE_VECTOR( func<tparam>, result, prefix );        \
    NMTOOLS_TEST_SUBCASE_FIXED_ARRAY( func<tparam>, result, prefix );   \
    NMTOOLS_TEST_SUBCASE_DYNAMIC_ARRAY( func<tparam>, result, prefix ); \
}   \

/**
 * @brief declare subcase for testing for functions that takes single argument and two template parameters.
 * @note that the testing namespace is strictly `nmtools::testing::data::{func}::{case_name}`,
 * and the arguments suffixes should be matched with NMTOOLS_TESTING_DATA_DECLARE_ARRAY,
 * NMTOOLS_TESTING_DATA_DECLARE_MAT, and NMTOOLS_TESTING_DATA_DECLARE_VEC macros.
 * Also note that tparam is not prefixed.
 * @see NMTOOLS_TESTING_DATA_DECLARE_ARRAY
 * @see NMTOOLS_TESTING_DATA_DECLARE_MAT
 * @see NMTOOLS_TESTING_DATA_DECLARE_VEC
 * @todo also add multiprecision whenever possible
 * 
 */
#define NMTOOLS_TESTING_DECLARE_TPARAM2_SUBCASES(case_name, func, tparam1, tparam2, result, prefix) \
{   \
    using namespace nmtools::testing::data::func::case_name;  \
    NMTOOLS_TEST_SUBCASE_ARRAY( (func<tparam1,tparam2>), result, prefix );         \
    NMTOOLS_TEST_SUBCASE_VECTOR( (func<tparam1,tparam2>), result, prefix );        \
    NMTOOLS_TEST_SUBCASE_FIXED_ARRAY( (func<tparam1,tparam2>), result, prefix );   \
    NMTOOLS_TEST_SUBCASE_DYNAMIC_ARRAY( (func<tparam1,tparam2>), result, prefix ); \
}   \

/**
 * @brief declare subcase for testing for functions that takes single argument and three template parameters.
 * @note that the testing namespace is strictly `nmtools::testing::data::{func}::{case_name}`,
 * and the arguments suffixes should be matched with NMTOOLS_TESTING_DATA_DECLARE_ARRAY,
 * NMTOOLS_TESTING_DATA_DECLARE_MAT, and NMTOOLS_TESTING_DATA_DECLARE_VEC macros.
 * Also note that tparam is not prefixed.
 * @see NMTOOLS_TESTING_DATA_DECLARE_ARRAY
 * @see NMTOOLS_TESTING_DATA_DECLARE_MAT
 * @see NMTOOLS_TESTING_DATA_DECLARE_VEC
 * @todo also add multiprecision whenever possible
 * 
 */
#define NMTOOLS_TESTING_DECLARE_TPARAM3_SUBCASES(case_name, func, tparam1, tparam2, tparam3, result, prefix) \
{   \
    using namespace nmtools::testing::data::func::case_name;  \
    NMTOOLS_TEST_SUBCASE_ARRAY( (func<tparam1,tparam2,tparam3>), result, prefix );         \
    NMTOOLS_TEST_SUBCASE_VECTOR( (func<tparam1,tparam2,tparam3>), result, prefix );        \
    NMTOOLS_TEST_SUBCASE_FIXED_ARRAY( (func<tparam1,tparam2,tparam3>), result, prefix );   \
    NMTOOLS_TEST_SUBCASE_DYNAMIC_ARRAY( (func<tparam1,tparam2,tparam3>), result, prefix ); \
}   \

/**
 * @brief declare subcase for testing for functions that takes single argument and four template parameters.
 * @note that the testing namespace is strictly `nmtools::testing::data::{func}::{case_name}`,
 * and the arguments suffixes should be matched with NMTOOLS_TESTING_DATA_DECLARE_ARRAY,
 * NMTOOLS_TESTING_DATA_DECLARE_MAT, and NMTOOLS_TESTING_DATA_DECLARE_VEC macros.
 * Also note that tparam is not prefixed.
 * @see NMTOOLS_TESTING_DATA_DECLARE_ARRAY
 * @see NMTOOLS_TESTING_DATA_DECLARE_MAT
 * @see NMTOOLS_TESTING_DATA_DECLARE_VEC
 * @todo also add multiprecision whenever possible
 * 
 */
#define NMTOOLS_TESTING_DECLARE_TPARAM4_SUBCASES(case_name, func, tparam1, tparam2, tparam3, tparam4, result, prefix) \
{   \
    using namespace nmtools::testing::data::func::case_name;  \
    NMTOOLS_TEST_SUBCASE_ARRAY( (func<tparam1,tparam2,tparam3,tparam4>), result, prefix );         \
    NMTOOLS_TEST_SUBCASE_VECTOR( (func<tparam1,tparam2,tparam3,tparam4>), result, prefix );        \
    NMTOOLS_TEST_SUBCASE_FIXED_ARRAY( (func<tparam1,tparam2,tparam3,tparam4>), result, prefix );   \
    NMTOOLS_TEST_SUBCASE_DYNAMIC_ARRAY( (func<tparam1,tparam2,tparam3,tparam4>), result, prefix ); \
}   \

/**
 * @brief declare subcase for testing with raw array.
 * @note that the raw array is assumend to be templated.
 * 
 */
#define NMTOOLS_TESTING_DEC_RAW_SUBCASES(case_name, func, result, arg) \
{   \
    using namespace nmtools::testing::data::func::case_name; \
    NMTOOLS_TEST_SUBCASE( func, result, arg<double> ); \
    NMTOOLS_TEST_SUBCASE( func, result, arg<float> ); \
}   \

/**
 * @brief declare subcase for testing for functions that takes templated single argument and single template parameters.
 * @note that the testing namespace is strictly `nmtools::testing::data::{func}::{case_name}`,
 * and the arguments suffixes should be matched with NMTOOLS_TESTING_DATA_DECLARE_ARRAY,
 * NMTOOLS_TESTING_DATA_DECLARE_MAT, and NMTOOLS_TESTING_DATA_DECLARE_VEC macros.
 * Also note that tparam is not prefixed.
 * @see NMTOOLS_TESTING_DATA_DECLARE_ARRAY
 * @see NMTOOLS_TESTING_DATA_DECLARE_MAT
 * @see NMTOOLS_TESTING_DATA_DECLARE_VEC
 * @todo also add multiprecision whenever possible
 * 
 */
#define NMTOOLS_TESTING_DEC_TPARAM_RAW_SUBCASES(case_name, func, tparam, result, arg) \
{   \
    using namespace nmtools::testing::data::func::case_name;   \
    NMTOOLS_TEST_SUBCASE( func<tparam>, result, arg<double> ); \
    NMTOOLS_TEST_SUBCASE( func<tparam>, result, arg<float> );  \
}   \

/**
 * @brief declare subcase for testing for function that takes two arguments.
 * @note that the testing namespace is strictly `nmtools::testing::data::{func}::{case_name}`,
 * and the arguments suffixes should be matched with NMTOOLS_TESTING_DATA_DECLARE_ARRAY,
 * NMTOOLS_TESTING_DATA_DECLARE_MAT, and NMTOOLS_TESTING_DATA_DECLARE_VEC macros
 * @note do not use variadic for param, since I don't know how to do token-pasting with __VA_ARGS__
 * @todo find out if can use token-pasting with __VA_ARGS__
 * @see NMTOOLS_TESTING_DATA_DECLARE_ARRAY
 * @see NMTOOLS_TESTING_DATA_DECLARE_MAT
 * @see NMTOOLS_TESTING_DATA_DECLARE_VEC
 * 
 */
#define NMTOOLS_TESTING_DECLARE_SUBCASES2(case_name, func, result, xprefix, yprefix) \
{   \
    using namespace nmtools::testing::data::func::case_name;               \
    NMTOOLS_TEST_SUBCASE_ARRAY2( func, result, xprefix, yprefix );         \
    NMTOOLS_TEST_SUBCASE_VECTOR2( func, result, xprefix, yprefix );        \
    NMTOOLS_TEST_SUBCASE_FIXED_ARRAY2( func, result, xprefix, yprefix );   \
    NMTOOLS_TEST_SUBCASE_DYNAMIC_ARRAY2( func, result, xprefix, yprefix ); \
}   \

/**
 * @brief declare subcase for testing with raw array.
 * @note that the raw array is assumend to be templated.
 * 
 */
#define NMTOOLS_TESTING_DEC_RAW_SUBCASES2(case_name, func, result, arg1, arg2) \
{   \
    using namespace nmtools::testing::data::func::case_name; \
    NMTOOLS_TEST_SUBCASE( func, result, arg1<double>, arg2<double> ); \
    NMTOOLS_TEST_SUBCASE( func, result, arg1<float>, arg2<float> ); \
}   \

/**
 * @brief declare subcase for testing for function that takes three arguments.
 * @note that the testing namespace is strictly `nmtools::testing::data::{func}::{case_name}`,
 * and the arguments suffixes should be matched with NMTOOLS_TESTING_DATA_DECLARE_ARRAY,
 * NMTOOLS_TESTING_DATA_DECLARE_MAT, and NMTOOLS_TESTING_DATA_DECLARE_VEC macros
 * @note do not use variadic for param, since I don't know how to do token-pasting with __VA_ARGS__
 * @todo find out if can use token-pasting with __VA_ARGS__
 * @see NMTOOLS_TESTING_DATA_DECLARE_ARRAY
 * @see NMTOOLS_TESTING_DATA_DECLARE_MAT
 * @see NMTOOLS_TESTING_DATA_DECLARE_VEC
 * 
 */
#define NMTOOLS_TESTING_DECLARE_SUBCASES3(case_name, func, result, xprefix, yprefix, zprefix) \
{   \
    using namespace nmtools::testing::data::func::case_name; \
    NMTOOLS_TEST_SUBCASE_ARRAY3( func, result, xprefix, yprefix, zprefix );         \
    NMTOOLS_TEST_SUBCASE_VECTOR3( func, result, xprefix, yprefix, zprefix );        \
    NMTOOLS_TEST_SUBCASE_FIXED_ARRAY3( func, result, xprefix, yprefix, zprefix );   \
    NMTOOLS_TEST_SUBCASE_DYNAMIC_ARRAY3( func, result, xprefix, yprefix, zprefix ); \
}   \

/**
 * @brief declare subcase for testing with raw array.
 * @note that the raw array is assumend to be templated.
 * 
 */
#define NMTOOLS_TESTING_DEC_RAW_SUBCASES3(case_name, func, result, arg1, arg2, arg3) \
{   \
    using namespace nmtools::testing::data::func::case_name; \
    NMTOOLS_TEST_SUBCASE( func, result, arg1<double>, arg2<double>, arg3<double> ); \
    NMTOOLS_TEST_SUBCASE( func, result, arg1<float>,  arg2<float>, arg3<float> );   \
}   \

/**
 * @brief log given type to doctest as message
 * 
 * @warn only available for doctest
 */
#ifdef __EMSCRIPTEN__
    // somehow doctest MESSAGE macro doesnt work well with emscripten
    #define LOG_TYPEINFO(type) {}
#else
#define LOG_TYPEINFO(type) \
{ \
    MESSAGE(std::string(#type) + " = " + NMTOOLS_TESTING_GET_TYPENAME(type)); \
}
#endif

/**
 * @brief no operation used for static asssertion
 *
 * @see DEFER_STATIC_CHECK
 * @see STATIC_CHECK
 * @see STATIC_CHECK_IS_SAME
 */
#define NMTOOLS_DEFERRED_STATIC_ASSERT {}

#ifndef DEFER_STATIC_CHECK
#define NMTOOLS_STATIC_ASSERT static_assert
#else
#define NMTOOLS_STATIC_ASSERT NMTOOLS_DEFERRED_STATIC_ASSERT
#endif

/**
 * @brief perform static assertion on `expr` and also run assertion at runtime for message and sanity check
 *
 * Compile-time assertion can be deferred to runtime
 * by defining DEFER_STATIC_CHECK before include, or redefine NMTOOLS_STATIC_ASSERT.
 * 
 * @warn only available for doctest
 * @see DEFER_STATIC_CHECK
 * @see NMTOOLS_DEFERRED_STATIC_ASSERT
 */
#define STATIC_CHECK(expr) \
{ \
  NMTOOLS_STATIC_ASSERT(expr); \
  CHECK_MESSAGE(expr, #expr); \
} \

/**
 * @brief perform static assertion std::is_same on type1 and type1.
 *
 * Also run assertion at runtime for message and sanity check.
 * Compile-time assertion can be deferred to runtime
 * by defining DEFER_STATIC_CHECK before include, or redefine NMTOOLS_STATIC_ASSERT.
 * 
 * @warn only available for doctest
 * @see DEFER_STATIC_CHECK
 * @see NMTOOLS_DEFERRED_STATIC_ASSERT
 */
#define STATIC_CHECK_IS_SAME(type1, type2) \
{ \
    constexpr auto is_same = std::is_same_v<type1,type2>; \
    NMTOOLS_STATIC_ASSERT(is_same); \
    std::string message = std::string(#type1) + " (" + NMTOOLS_TESTING_GET_TYPENAME(type1) + ")" + ", " + std::string(#type2) + " (" + NMTOOLS_TESTING_GET_TYPENAME(type2) + ")"; \
    NMTOOLS_CHECK_MESSAGE(is_same, message); \
} \

#define STATIC_CHECK_TRAIT_FALSE(trait, type) \
{ \
    constexpr auto value = !trait<type>::value; \
    NMTOOLS_STATIC_ASSERT(value); \
    std::string message = std::string("trait") + " (" + std::string(#trait) + "), " + std::string(#type) + " (" + NMTOOLS_TESTING_GET_TYPENAME(type) + "); false;"; \
    NMTOOLS_CHECK_MESSAGE(value, message); \
} \

#define STATIC_CHECK_TRAIT_TRUE(trait, type) \
{ \
    constexpr auto value = trait<type>::value; \
    NMTOOLS_STATIC_ASSERT(value); \
    std::string message = std::string("trait") + " (" + std::string(#trait) + "), " + std::string(#type) + " (" + NMTOOLS_TESTING_GET_TYPENAME(type) + "); true;"; \
    NMTOOLS_CHECK_MESSAGE(value, message); \
} \

/**
 * @brief perform static assertion given trait and type
 *
 * Assuming given trait has static member variable `value`.
 * Also run assertion at runtime for message and sanity check.
 * Compile-time assertion can be deferred to runtime
 * by defining DEFER_STATIC_CHECK before include, or redefine NMTOOLS_STATIC_ASSERT.
 * 
 * @warn only available for doctest
 * @see DEFER_STATIC_CHECK
 * @see NMTOOLS_DEFERRED_STATIC_ASSERT
 */
#define STATIC_CHECK_TRAIT STATIC_CHECK_TRAIT_TRUE

// @todo: maybe unnecessary, do not include here
#include "nmtools/testing/data/common.hpp"

/** @} */ // end groupt testing

#endif // NMTOOLS_TESTING_HPP