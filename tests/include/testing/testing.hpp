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
    template <auto...Args>
    auto make_func_args(std::string func, const auto&...args)
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
        auto tparams = std::array<std::string,m>{
            {std::to_string(Args)...}
        };
        ss << func;
        if constexpr (m>=1) {
            ss << '<';
            for (size_t i=0; i<m; i++) {
                ss << tparams[i];
                if (i!=(m-1))
                    ss << ",";
            }
            ss << '>';
        }
        ss << '(';
        for (size_t i=0; i<n; i++) {
            ss << typenames[i];
            if (i!=(n-1))
                ss << ",";
        }
        ss << ')';
        return ss.str();
    } // auto make_func_args

    template <auto...Args>
    auto make_func_args(std::string func, std::string result_type, const auto&...args)
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
        auto tparams = std::array<std::string,m>{
            {std::to_string(Args)...}
        };
        ss << func;
        if constexpr (m>=1) {
            ss << '<';
            for (size_t i=0; i<m; i++) {
                ss << tparams[i];
                if (i!=(m-1))
                    ss << ",";
            }
            ss << '>';
        }
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

    inline constexpr auto nested_vec = nested_vector_t {};
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

/**
 * @brief implementation of doctest assert macro with message
 * 
 */
#define NMTOOLS_ASSERT_CLOSE_DOCTEST(result,expect) \
CHECK_MESSAGE(isclose(result,expect,NMTOOLS_TESTING_OUTPUT_PRECISION), \
    (   \
        std::string{} \
        + "\n\tActual  : " + STRINGIFY(result) \
        + "\n\tExpected: " + STRINGIFY(expect) \
    )   \
);

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

#define NMTOOLS_TESTING_DECLARE_NS_MACRO(_1,_2,NAME,...) NAME
#define NMTOOLS_TESTING_DECLARE_NS(...) NMTOOLS_TESTING_DECLARE_NS_MACRO(__VA_ARGS__, NMTOOLS_TESTING_DECLARE_NS2, NMTOOLS_TESTING_DECLARE_NS1)(__VA_ARGS__)

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
#define LOG_TYPEINFO(type) \
{ \
    MESSAGE(std::string(#type) + " = " + NMTOOLS_TESTING_GET_TYPENAME(type)); \
} \

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
    CHECK_MESSAGE(is_same, std::string(#type1) + " (" + NMTOOLS_TESTING_GET_TYPENAME(type1) + ")" + ", " + std::string(#type2) + " (" + NMTOOLS_TESTING_GET_TYPENAME(type2) + ")" ); \
} \

#define STATIC_CHECK_TRAIT_FALSE(trait, type) \
{ \
    constexpr auto value = !trait<type>::value; \
    NMTOOLS_STATIC_ASSERT(value); \
    CHECK_MESSAGE(value, std::string("trait") + " (" + std::string(#trait) + "), " + std::string(#type) + " (" + NMTOOLS_TESTING_GET_TYPENAME(type) + "); false;" ); \
} \

#define STATIC_CHECK_TRAIT_TRUE(trait, type) \
{ \
    constexpr auto value = trait<type>::value; \
    NMTOOLS_STATIC_ASSERT(value); \
    CHECK_MESSAGE(value, std::string("trait") + " (" + std::string(#trait) + "), " + std::string(#type) + " (" + NMTOOLS_TESTING_GET_TYPENAME(type) + "); true;" ); \
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

namespace nmtools::testing::data::common
{
    /**
     * @brief first row of magic matrix 5x5
     * 
     * @tparam T 
     */
    template <typename T>
    constexpr T v5[5] = {17,   24,    1,    8,   15};

    /**
     * @brief first row of magic matrix 10x10
     * 
     * @tparam T 
     */
    template <typename T>
    constexpr T v10[10] = {92,    99,     1,     8,    15,    67,    74,    51,    58,    40};

    /**
     * @brief first row of magic matrix 15x15
     * 
     * @tparam T 
     */
    template <typename T>
    constexpr T v15[15] = {122,   139,   156,   173,   190,   207,   224,     1,    18,    35,    52,    69,    86,   103,   120};

    /**
     * @brief first row of magic matrix 20x20
     * 
     * @tparam T 
     */
    template <typename T>
    constexpr T v20[20] = {400,     2,     3,   397,   396,     6,     7,   393,   392,    10,    11,   389,   388,    14,    15,   385,   384,    18,    19,   381};

    /**
     * @brief first row of magic matrix 25x25
     * 
     * @tparam T 
     */
    template <typename T>
    constexpr T v25[25] = {327,   354,   381,   408,   435,   462,   489,   516,   543,   570,   597,   624,     1,    28,    55,    82,   109,   136,   163,   190,   217,   244,   271,   298,   325};

    /**
     * @brief a range vector of size 5, similar to 1:N in octave wher N is the size of the vector
     * 
     * @tparam T 
     */
    template <typename T>
    constexpr T r5[5] = {1,    2,    3,    4,    5};

    /**
     * @brief a range vector of size 10, similar to 1:N in octave wher N is the size of the vector
     * 
     * @tparam T 
     */
    template <typename T>
    constexpr T r10[10] = {1,    2,    3,    4,    5,    6,    7,    8,    9,   10};
    
    /**
     * @brief a range vector of size 15, similar to 1:N in octave wher N is the size of the vector
     * 
     * @tparam T 
     */
    template <typename T>
    constexpr T r15[15] = {1,    2,    3,    4,    5,    6,    7,    8,    9,   10,   11,   12,   13,   14,   15};
    
    /**
     * @brief a range vector of size 20, similar to 1:N in octave wher N is the size of the vector
     * 
     * @tparam T 
     */
    template <typename T>
    constexpr T r20[20] = {1,    2,    3,    4,    5,    6,    7,    8,    9,   10,   11,   12,   13,   14,   15,   16,   17,   18,   19,   20};

    /**
     * @brief a range vector of size 25, similar to 1:N in octave wher N is the size of the vector
     * 
     * @tparam T 
     */
    template <typename T>
    constexpr T r25[25] = {1,    2,    3,    4,    5,    6,    7,    8,    9,   10,   11,   12,   13,   14,   15,   16,   17,   18,   19,   20,   21,   22,   23,   24,   25};
} // namespace nmtools::testing::data::common

namespace nmtools::testing::data::common_matrix
{
    /**
     * @brief zeros of 3x3 matrix
     * 
     * @note that array cannot returned from functions by value
     * and cannot be targets of most cast expressions.
     * @tparam T desired element type
     */
    template <typename T>
    constexpr T z3x3[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
    };

    template <typename T>
    constexpr T z5x5[5][5] = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
    };

    template <typename T>
    constexpr T z10x10[10][10] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    template <typename T>
    constexpr T z15x15[15][15] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    template <typename T>
    constexpr T z20x20[20][20] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    template <typename T>
    constexpr T z25x25[25][25] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    template <typename T>
    constexpr T o3x3[3][3] = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1},
    };

    template <typename T>
    constexpr T o5x5[5][5] = {
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
    };

    template <typename T>
    constexpr T o10x10[10][10] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };

    template <typename T>
    constexpr T o15x15[15][15] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };

    template <typename T>
    constexpr T o20x20[20][20] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };

    template <typename T>
    constexpr T o25x25[25][25] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };

    template <typename T>
    constexpr T e3x3[3][3] = {
        {1,   0,   0},
        {0,   1,   0},
        {0,   0,   1},
    };

    template <typename T>
    constexpr T e5x5[5][5] = {
        {1,   0,   0,   0,   0},
        {0,   1,   0,   0,   0},
        {0,   0,   1,   0,   0},
        {0,   0,   0,   1,   0},
        {0,   0,   0,   0,   1},
    };

    template <typename T>
    constexpr T e10x10[10][10] = {
        {1,   0,   0,   0,   0,   0,   0,   0,   0,   0},
        {0,   1,   0,   0,   0,   0,   0,   0,   0,   0},
        {0,   0,   1,   0,   0,   0,   0,   0,   0,   0},
        {0,   0,   0,   1,   0,   0,   0,   0,   0,   0},
        {0,   0,   0,   0,   1,   0,   0,   0,   0,   0},
        {0,   0,   0,   0,   0,   1,   0,   0,   0,   0},
        {0,   0,   0,   0,   0,   0,   1,   0,   0,   0},
        {0,   0,   0,   0,   0,   0,   0,   1,   0,   0},
        {0,   0,   0,   0,   0,   0,   0,   0,   1,   0},
        {0,   0,   0,   0,   0,   0,   0,   0,   0,   1},
    };

    template <typename T>
    constexpr T e15x15[15][15] = {
        {1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
        {0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
        {0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
        {0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
        {0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
        {0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0},
        {0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0},
        {0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0},
        {0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0},
        {0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0},
        {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0},
        {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0},
        {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0},
        {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0},
        {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1},
    };

    template <typename T>
    constexpr T e20x20[20][20] = {
        {1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
        {0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
        {0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
        {0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
        {0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
        {0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
        {0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
        {0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
        {0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
        {0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
        {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0},
        {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0},
        {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0},
        {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0},
        {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0},
        {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0},
        {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0},
        {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0},
        {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0},
        {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1},
    };

    template <typename T>
    constexpr T e25x25[25][25] = {
        {1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
        {0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
        {0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
        {0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
        {0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
        {0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
        {0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
        {0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
        {0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
        {0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
        {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
        {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
        {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
        {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
        {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
        {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0},
        {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0},
        {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0},
        {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0},
        {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0},
        {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0},
        {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0},
        {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0},
        {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0},
        {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1},
    };

    /**
     * @brief 
     * 
     */
    namespace magic
    {
        /**
         * @brief 5x5 magic matrix template
         * 
         * @tparam T desired element type.
         * @note that c++ array is lvalue,
         * doing `auto var = m5x5<double>;`
         * will deduce the value of var 
         * to be `const double (* const&)[5])`
         */
        template <typename T>
        constexpr T m5x5[5][5] = {
            {17,   24,    1,    8,   15},
            {23,    5,    7,   14,   16},
            { 4,    6,   13,   20,   22},
            {10,   12,   19,   21,    3},
            {11,   18,   25,    2,    9},
        };
        /**
         * @brief 5x5 magic matrix with std::array storage and double dtype
         * 
         */
        // inline auto mad5x5 = cast(m5x5<double>);
        // inline auto maf5x5 = cast(m5x5<float>);
        /**
         * @brief 5x5 magic matrix with std::array storage and double dtype
         * 
         */
        // inline auto mvd5x5 = cast<nested_vec_t<double>>(mad5x5);
        // inline auto mvf5x5 = cast<nested_vec_t<float>>(maf5x5);
        /**
         * @brief 5x5 magic matrix with array::fixed_matrix as storage
         * 
         */
        /* TODO: find-out how to left-out specifying size of array */
        // inline auto mfd5x5 = cast<fdmat_t<5,5>>(mad5x5);
        // inline auto mff5x5 = cast<ffmat_t<5,5>>(maf5x5);

        /**
         * @brief 10x10 magic matrix
         * `octave> magic(10)`
         * 
         * @tparam T 
         */
        template <typename T>
        constexpr T m10x10[10][10] = {
            {92,    99,     1,     8,    15,    67,    74,    51,    58,    40},
            {98,    80,     7,    14,    16,    73,    55,    57,    64,    41},
            { 4,    81,    88,    20,    22,    54,    56,    63,    70,    47},
            {85,    87,    19,    21,     3,    60,    62,    69,    71,    28},
            {86,    93,    25,     2,     9,    61,    68,    75,    52,    34},
            {17,    24,    76,    83,    90,    42,    49,    26,    33,    65},
            {23,     5,    82,    89,    91,    48,    30,    32,    39,    66},
            {79,     6,    13,    95,    97,    29,    31,    38,    45,    72},
            {10,    12,    94,    96,    78,    35,    37,    44,    46,    53},
            {11,    18,   100,    77,    84,    36,    43,    50,    27,    59},
        };
        /**
         * @brief 5x5 magic matrix with std::array storage and double dtype
         * 
         */
        // inline auto mad10x10 = cast(m10x10<double>);
        // inline auto maf10x10 = cast(m10x10<float>);
        /**
         * @brief 5x5 magic matrix with std::array storage and double dtype
         * 
         */
        // inline auto mvd10x10 = cast<nested_vec_t<double>>(mad10x10);
        // inline auto mvf10x10 = cast<nested_vec_t<float>>(maf10x10);
        /**
         * @brief 5x5 magic matrix with array::fixed_matrix as storage
         * 
         */
        /* TODO: find-out how to left-out specifying size of array */
        // inline auto mfd10x10 = cast<fdmat_t<10,10>>(mad10x10);
        // inline auto mff10x10 = cast<ffmat_t<10,10>>(maf10x10);

        /**
         * @brief 15x15 magic matrix
         * `octave> magic(15)`
         * 
         * @tparam T 
         */
        template <typename T>
        constexpr T m15x15[15][15] = {
            {122,   139,   156,   173,   190,   207,   224,     1,    18,    35,    52,    69,    86,   103,   120},
            {138,   155,   172,   189,   206,   223,    15,    17,    34,    51,    68,    85,   102,   119,   121},
            {154,   171,   188,   205,   222,    14,    16,    33,    50,    67,    84,   101,   118,   135,   137},
            {170,   187,   204,   221,    13,    30,    32,    49,    66,    83,   100,   117,   134,   136,   153},
            {186,   203,   220,    12,    29,    31,    48,    65,    82,    99,   116,   133,   150,   152,   169},
            {202,   219,    11,    28,    45,    47,    64,    81,    98,   115,   132,   149,   151,   168,   185},
            {218,    10,    27,    44,    46,    63,    80,    97,   114,   131,   148,   165,   167,   184,   201},
            {  9,    26,    43,    60,    62,    79,    96,   113,   130,   147,   164,   166,   183,   200,   217},
            { 25,    42,    59,    61,    78,    95,   112,   129,   146,   163,   180,   182,   199,   216,     8},
            { 41,    58,    75,    77,    94,   111,   128,   145,   162,   179,   181,   198,   215,     7,    24},
            { 57,    74,    76,    93,   110,   127,   144,   161,   178,   195,   197,   214,     6,    23,    40},
            { 73,    90,    92,   109,   126,   143,   160,   177,   194,   196,   213,     5,    22,    39,    56},
            { 89,    91,   108,   125,   142,   159,   176,   193,   210,   212,     4,    21,    38,    55,    72},
            {105,   107,   124,   141,   158,   175,   192,   209,   211,     3,    20,    37,    54,    71,    88},
            {106,   123,   140,   157,   174,   191,   208,   225,     2,    19,    36,    53,    70,    87,   104},
        };
        /**
         * @brief 5x5 magic matrix with std::array storage and double dtype
         * 
         */
        // inline auto mad15x15 = cast(m15x15<double>);
        // inline auto maf15x15 = cast(m15x15<float>);
        /**
         * @brief 5x5 magic matrix with std::array storage and double dtype
         * 
         */
        // inline auto mvd15x15 = cast<nested_vec_t<double>>(mad15x15);
        // inline auto mvf15x15 = cast<nested_vec_t<float>>(maf15x15);
        /**
         * @brief 5x5 magic matrix with array::fixed_matrix as storage
         * 
         */
        /* TODO: find-out how to left-out specifying size of array */
        // inline auto mfd15x15 = cast<fdmat_t<15,15>>(mad15x15);
        // inline auto mff15x15 = cast<ffmat_t<15,15>>(maf15x15);

        template <typename T>
        constexpr T m20x20[20][20] = {
            {400,     2,     3,   397,   396,     6,     7,   393,   392,    10,    11,   389,   388,    14,    15,   385,   384,    18,    19,   381},
            { 21,   379,   378,    24,    25,   375,   374,    28,    29,   371,   370,    32,    33,   367,   366,    36,    37,   363,   362,    40},
            { 41,   359,   358,    44,    45,   355,   354,    48,    49,   351,   350,    52,    53,   347,   346,    56,    57,   343,   342,    60},
            {340,    62,    63,   337,   336,    66,    67,   333,   332,    70,    71,   329,   328,    74,    75,   325,   324,    78,    79,   321},
            {320,    82,    83,   317,   316,    86,    87,   313,   312,    90,    91,   309,   308,    94,    95,   305,   304,    98,    99,   301},
            {101,   299,   298,   104,   105,   295,   294,   108,   109,   291,   290,   112,   113,   287,   286,   116,   117,   283,   282,   120},
            {121,   279,   278,   124,   125,   275,   274,   128,   129,   271,   270,   132,   133,   267,   266,   136,   137,   263,   262,   140},
            {260,   142,   143,   257,   256,   146,   147,   253,   252,   150,   151,   249,   248,   154,   155,   245,   244,   158,   159,   241},
            {240,   162,   163,   237,   236,   166,   167,   233,   232,   170,   171,   229,   228,   174,   175,   225,   224,   178,   179,   221},
            {181,   219,   218,   184,   185,   215,   214,   188,   189,   211,   210,   192,   193,   207,   206,   196,   197,   203,   202,   200},
            {201,   199,   198,   204,   205,   195,   194,   208,   209,   191,   190,   212,   213,   187,   186,   216,   217,   183,   182,   220},
            {180,   222,   223,   177,   176,   226,   227,   173,   172,   230,   231,   169,   168,   234,   235,   165,   164,   238,   239,   161},
            {160,   242,   243,   157,   156,   246,   247,   153,   152,   250,   251,   149,   148,   254,   255,   145,   144,   258,   259,   141},
            {261,   139,   138,   264,   265,   135,   134,   268,   269,   131,   130,   272,   273,   127,   126,   276,   277,   123,   122,   280},
            {281,   119,   118,   284,   285,   115,   114,   288,   289,   111,   110,   292,   293,   107,   106,   296,   297,   103,   102,   300},
            {100,   302,   303,    97,    96,   306,   307,    93,    92,   310,   311,    89,    88,   314,   315,    85,    84,   318,   319,    81},
            { 80,   322,   323,    77,    76,   326,   327,    73,    72,   330,   331,    69,    68,   334,   335,    65,    64,   338,   339,    61},
            {341,    59,    58,   344,   345,    55,    54,   348,   349,    51,    50,   352,   353,    47,    46,   356,   357,    43,    42,   360},
            {361,    39,    38,   364,   365,    35,    34,   368,   369,    31,    30,   372,   373,    27,    26,   376,   377,    23,    22,   380},
            { 20,   382,   383,    17,    16,   386,   387,    13,    12,   390,   391,     9,     8,   394,   395,     5,     4,   398,   399,     1},
        };

        template <typename T>
        constexpr T m25x25[25][25] = {
            {327,   354,   381,   408,   435,   462,   489,   516,   543,   570,   597,   624,     1,    28,    55,    82,   109,   136,   163,   190,   217,   244,   271,   298,   325},
            {353,   380,   407,   434,   461,   488,   515,   542,   569,   596,   623,    25,    27,    54,    81,   108,   135,   162,   189,   216,   243,   270,   297,   324,   326},
            {379,   406,   433,   460,   487,   514,   541,   568,   595,   622,    24,    26,    53,    80,   107,   134,   161,   188,   215,   242,   269,   296,   323,   350,   352},
            {405,   432,   459,   486,   513,   540,   567,   594,   621,    23,    50,    52,    79,   106,   133,   160,   187,   214,   241,   268,   295,   322,   349,   351,   378},
            {431,   458,   485,   512,   539,   566,   593,   620,    22,    49,    51,    78,   105,   132,   159,   186,   213,   240,   267,   294,   321,   348,   375,   377,   404},
            {457,   484,   511,   538,   565,   592,   619,    21,    48,    75,    77,   104,   131,   158,   185,   212,   239,   266,   293,   320,   347,   374,   376,   403,   430},
            {483,   510,   537,   564,   591,   618,    20,    47,    74,    76,   103,   130,   157,   184,   211,   238,   265,   292,   319,   346,   373,   400,   402,   429,   456},
            {509,   536,   563,   590,   617,    19,    46,    73,   100,   102,   129,   156,   183,   210,   237,   264,   291,   318,   345,   372,   399,   401,   428,   455,   482},
            {535,   562,   589,   616,    18,    45,    72,    99,   101,   128,   155,   182,   209,   236,   263,   290,   317,   344,   371,   398,   425,   427,   454,   481,   508},
            {561,   588,   615,    17,    44,    71,    98,   125,   127,   154,   181,   208,   235,   262,   289,   316,   343,   370,   397,   424,   426,   453,   480,   507,   534},
            {587,   614,    16,    43,    70,    97,   124,   126,   153,   180,   207,   234,   261,   288,   315,   342,   369,   396,   423,   450,   452,   479,   506,   533,   560},
            {613,    15,    42,    69,    96,   123,   150,   152,   179,   206,   233,   260,   287,   314,   341,   368,   395,   422,   449,   451,   478,   505,   532,   559,   586},
            { 14,    41,    68,    95,   122,   149,   151,   178,   205,   232,   259,   286,   313,   340,   367,   394,   421,   448,   475,   477,   504,   531,   558,   585,   612},
            { 40,    67,    94,   121,   148,   175,   177,   204,   231,   258,   285,   312,   339,   366,   393,   420,   447,   474,   476,   503,   530,   557,   584,   611,    13},
            { 66,    93,   120,   147,   174,   176,   203,   230,   257,   284,   311,   338,   365,   392,   419,   446,   473,   500,   502,   529,   556,   583,   610,    12,    39},
            { 92,   119,   146,   173,   200,   202,   229,   256,   283,   310,   337,   364,   391,   418,   445,   472,   499,   501,   528,   555,   582,   609,    11,    38,    65},
            {118,   145,   172,   199,   201,   228,   255,   282,   309,   336,   363,   390,   417,   444,   471,   498,   525,   527,   554,   581,   608,    10,    37,    64,    91},
            {144,   171,   198,   225,   227,   254,   281,   308,   335,   362,   389,   416,   443,   470,   497,   524,   526,   553,   580,   607,     9,    36,    63,    90,   117},
            {170,   197,   224,   226,   253,   280,   307,   334,   361,   388,   415,   442,   469,   496,   523,   550,   552,   579,   606,     8,    35,    62,    89,   116,   143},
            {196,   223,   250,   252,   279,   306,   333,   360,   387,   414,   441,   468,   495,   522,   549,   551,   578,   605,     7,    34,    61,    88,   115,   142,   169},
            {222,   249,   251,   278,   305,   332,   359,   386,   413,   440,   467,   494,   521,   548,   575,   577,   604,     6,    33,    60,    87,   114,   141,   168,   195},
            {248,   275,   277,   304,   331,   358,   385,   412,   439,   466,   493,   520,   547,   574,   576,   603,     5,    32,    59,    86,   113,   140,   167,   194,   221},
            {274,   276,   303,   330,   357,   384,   411,   438,   465,   492,   519,   546,   573,   600,   602,     4,    31,    58,    85,   112,   139,   166,   193,   220,   247},
            {300,   302,   329,   356,   383,   410,   437,   464,   491,   518,   545,   572,   599,   601,     3,    30,    57,    84,   111,   138,   165,   192,   219,   246,   273},
            {301,   328,   355,   382,   409,   436,   463,   490,   517,   544,   571,   598,   625,     2,    29,    56,    83,   110,   137,   164,   191,   218,   245,   272,   299},
        };
    } // namespace magic
} // namespace nmtools::testing::data::common_matrix

/** @} */ // end groupt testing

#endif // NMTOOLS_TESTING_HPP