#ifndef NMTOOLS_TESTING_HPP
#define NMTOOLS_TESTING_HPP

#include "nmtools/platform.hpp"
#include "nmtools/utils/isclose.hpp"
#include "nmtools/utils/isequal.hpp"
#include "nmtools/testing/string.hpp"
#include "nmtools/testing/array_cast.hpp"

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
 * @brief implementation of typeinfo logging for doctest,
 * may be used by `NMTOOLS_TESTING_LOG_TYPEINFO` macro
 * 
 */
#define NMTOOLS_TESTING_LOG_TYPEINFO_IMPL_DOCTEST INFO

#ifndef NMTOOLS_CHECK_MESSAGE
#if !defined(__EMSCRIPTEN__) && !defined(__ANDROID__) && !defined(__arm__) && !defined(__MINGW32__)
#define NMTOOLS_CHECK_MESSAGE(result, message) \
{ \
    CHECK_MESSAGE(result, message); \
}
#else
#define NMTOOLS_CHECK_MESSAGE(result, message) \
{ \
    CHECK(result); \
}
#endif // (__EMSCRIPTEN__ || __ANDROID__ || __arm__ || __MINGW32__)
#endif // NMTOOLS_CHECK_MESSAGE

/**
 * @brief implementation of doctest assert macro with message
 * 
 */
#define NMTOOLS_ASSERT_CLOSE_DOCTEST(result,expect) \
{ \
    auto result_ = isclose(result,expect,NMTOOLS_TESTING_OUTPUT_PRECISION); \
    std::string message {}; \
    message = message + \
        + "\n\tActual  :\n" + STRINGIFY(result)  \
        + "\n\tExpected:\n" + STRINGIFY(expect); \
    NMTOOLS_CHECK_MESSAGE( result_, message ); \
}

#define NMTOOLS_STATIC_ASSERT_CLOSE_DOCTEST(result,expect) \
{ \
    constexpr auto result_ = isclose(result,expect,NMTOOLS_TESTING_OUTPUT_PRECISION); \
    std::string message {}; \
    message = message + \
        + "\n\tActual  : " + STRINGIFY(result)  \
        + "\n\tExpected: " + STRINGIFY(expect); \
    NMTOOLS_STATIC_ASSERT( result_); \
    NMTOOLS_CHECK_MESSAGE( result_, message ); \
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

#define NMTOOLS_STATIC_ASSERT_EQUAL_DOCTEST(result,expect) \
{ \
    [[maybe_unused]] constexpr auto result_ = isequal(result,expect); \
    std::string message {}; \
    message = message + \
        + "\n\tActual  : " + STRINGIFY(result)  \
        + "\n\tExpected: " + STRINGIFY(expect); \
    NMTOOLS_STATIC_ASSERT( result_ ); \
    NMTOOLS_CHECK_MESSAGE( result_, message ); \
}

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
    static_assert(nmtools::meta::is_same_v<decltype(result),type>); \
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
    static_assert(nmtools::meta::is_same_v<decltype(result),type>); \
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

#define NMTOOLS_TEST_SUBCASE_NOOP(...) {}

/**
 * @brief log given type to doctest as message
 * 
 * @warn only available for doctest
 */
#if 0
    #define LOG_TYPEINFO(type) {}
#else
#define LOG_TYPEINFO(type) \
{ \
    std::string msg = std::string(#type) + std::string(" = ") + NMTOOLS_TESTING_GET_TYPENAME(type); \
    MESSAGE(msg); \
}
#endif

/**
 * @brief no operation used for static asssertion
 *
 * @see DEFER_STATIC_CHECK
 * @see STATIC_CHECK
 * @see STATIC_CHECK_IS_SAME
 */
#define NMTOOLS_DEFERRED_STATIC_ASSERT(value) {}

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

#define NMTOOLS_STATIC_CHECK_IS_SAME STATIC_CHECK_IS_SAME

#define NMTOOLS_STATIC_CHECK( expr ) \
{ \
    NMTOOLS_STATIC_ASSERT( expr ); \
    NMTOOLS_CHECK_MESSAGE( expr, #expr ); \
}

#define NMTOOLS_STATIC_CHECK_TRAIT_TRUE  STATIC_CHECK_TRAIT_TRUE
#define NMTOOLS_STATIC_CHECK_TRAIT_FALSE STATIC_CHECK_TRAIT_FALSE
#define NMTOOLS_STATIC_CHECK_TRAIT       STATIC_CHECK_TRAIT_TRUE

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

// NOTE: use IILE to avoid checking discarded if constexpr branch
#define NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(result, expect) \
[](const auto& result_, const auto& expect_) \
{ \
    using result_t = nmtools::meta::remove_cvref_t<decltype(result_)>; \
    if constexpr (!nmtools::meta::is_fail_v<result_t>) { \
        NMTOOLS_ASSERT_EQUAL( result_, expect_ ); \
    } \
}(result, expect);

#define NMTOOLS_STATIC_CHECK_SAME_INDEX_TRAIT( result_t, expect_t ) \
{ \
    constexpr auto pass_is_index = meta::is_index_array_v<result_t>; \
    constexpr auto pass_is_constant = meta::is_constant_index_array_v<result_t> == meta::is_constant_index_array_v<expect_t>; \
    constexpr auto pass_len = meta::len_v<result_t> == meta::len_v<expect_t>; \
    constexpr auto pass_bounded_size = [](){ \
        constexpr auto b_size_result = meta::bounded_size_v<result_t>; \
        constexpr auto b_size_expect = meta::bounded_size_v<expect_t>; \
        constexpr auto is_same_kind  = meta::is_fail_v<decltype(b_size_result)> == meta::is_fail_v<decltype(b_size_expect)>; \
        if constexpr (meta::is_fail_v<decltype(b_size_result)>) { \
            return is_same_kind; \
        } else if constexpr (meta::is_fail_v<decltype(b_size_expect)>) { \
            return is_same_kind; \
        } else if constexpr (is_same_kind) { \
            return (b_size_result == b_size_expect); \
        } else { \
            return false; \
        } \
    }(); \
    constexpr auto passed = (pass_is_index && pass_is_constant && pass_len && pass_bounded_size); \
    NMTOOLS_STATIC_ASSERT( passed ); \
    std::string message = std::string(#result_t) + "(" + NMTOOLS_TESTING_GET_TYPENAME(result_t) + "), " + std::string(#expect_t) + "(" + NMTOOLS_TESTING_GET_TYPENAME(expect_t) + ")"; \
    NMTOOLS_CHECK_MESSAGE( passed, message ); \
}

/** @} */ // end groupt testing

#endif // NMTOOLS_TESTING_HPP