#ifndef NMTOOLS_TESTING_DOCTEST_HPP
#define NMTOOLS_TESTING_DOCTEST_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/utility/fwd.hpp"
#include "nmtools/utils/to_string.hpp"

namespace meta = nmtools::meta;
namespace utils = nmtools::utils;

#define NMTOOLS_ASSERT_EQUAL_MSG_OPERANDS_DOCTEST(result,expect,...) \
{ \
    auto args_pack = nmtools::pack_operands(__VA_ARGS__); \
    auto arguments_string = std::string{}; \
    constexpr auto n_args = meta::len_v<decltype(args_pack)>; \
    meta::template_for<n_args>([&](auto I){ \
        arguments_string += "\t(#"; \
        arguments_string += utils::to_string(I); \
        arguments_string += "): "; \
        arguments_string += utils::to_string(nmtools::at(args_pack,I)); \
        arguments_string += "\n"; \
    }); \
    CHECK_MESSAGE(isequal(result,expect), \
        (   \
            std::string{} \
            + "\n\tActual   :\n" + STRINGIFY(result) \
            + "\n\tExpected :\n" + STRINGIFY(expect) \
            + "\n\tArguments:\n" + arguments_string \
        )   \
    ); \
}

#define NMTOOLS_ASSERT_EQUAL_MSG_ATTRIBUTES_DOCTEST(result,expect,...) \
{ \
    auto args_pack = nmtools::pack_attributes(__VA_ARGS__); \
    auto arguments_string = std::string{}; \
    constexpr auto n_args = meta::len_v<decltype(args_pack)>; \
    meta::template_for<n_args>([&](auto I){ \
        auto arg_typename = nmtools_string(NMTOOLS_TESTING_GET_TYPENAME(decltype(nmtools::at(args_pack,I)))); \
        arguments_string += "\t(#"; arguments_string += utils::to_string(I); arguments_string += "): "; \
        arguments_string += nmtools_string("\033[0;90m(") + arg_typename + nmtools_string(")\033[0m:\n\t\t"); \
        arguments_string += utils::to_string(nmtools::at(args_pack,I)); \
        arguments_string += "\n"; \
    }); \
    auto result_typename = nmtools_string(NMTOOLS_TESTING_GET_TYPENAME(decltype(result))); \
    auto expect_typename = nmtools_string(NMTOOLS_TESTING_GET_TYPENAME(decltype(expect))); \
    CHECK_MESSAGE(isequal(result,expect), \
        (   \
            std::string{} \
            + "\n\tActual " + nmtools_string("\033[0;90m(") + result_typename + nmtools_string(")\033[0m:\n") \
            + STRINGIFY(result) \
            + "\n\tExpected " + nmtools_string("\033[0;90m(") + expect_typename + nmtools_string(")\033[0m:\n") \
            + STRINGIFY(expect) \
            + "\n\tArguments:\n" + arguments_string \
        )   \
    ); \
}

#define NMTOOLS_ASSERT_CLOSE_MSG_OPERANDS_DOCTEST(result,expect,...) \
{ \
    auto args_pack = nmtools_tuple{__VA_ARGS__}; \
    auto arguments_string = std::string{}; \
    constexpr auto n_args = meta::len_v<decltype(args_pack)>; \
    meta::template_for<n_args>([&](auto I){ \
        auto arg_typename = nmtools_string(NMTOOLS_TESTING_GET_TYPENAME(decltype(nmtools::at(args_pack,I)))); \
        arguments_string += "\t(#"; arguments_string += utils::to_string(I); arguments_string += "): "; \
        arguments_string += nmtools_string("\033[0;90m(") + arg_typename + nmtools_string(")\033[0m:\n\t\t"); \
        arguments_string += utils::to_string(nmtools::at(args_pack,I)); \
        arguments_string += "\n"; \
    }); \
    auto result_typename = NMTOOLS_TESTING_GET_TYPENAME(decltype(result)); \
    auto expect_typename = NMTOOLS_TESTING_GET_TYPENAME(decltype(expect)); \
    CHECK_MESSAGE(isclose(result,expect), \
        (   \
            std::string{} \
            + "\n\tActual " + "\033[0;90m<" + result_typename + ">\033[0m:\n" \
            + STRINGIFY(result) \
            + "\n\tExpected " + "\033[0;90m<" + expect_typename + ">\033[0m:\n" \
            + STRINGIFY(expect) \
            + "\n\tArguments:\n" + arguments_string \
        )   \
    ); \
}

#define NMTOOLS_ASSERT_APPLY_EQUAL_DOCTEST(result,expect) \
{ \
    auto result_typename = nmtools_string(NMTOOLS_TESTING_GET_TYPENAME(decltype(result))); \
    auto expect_typename = nmtools_string(NMTOOLS_TESTING_GET_TYPENAME(decltype(expect))); \
    auto message = std::string{} \
        + "\n\tActual " + nmtools_string("\033[0;90m<") + result_typename + nmtools_string(">\033[0m:\n") \
        + STRINGIFY(result) \
        + "\n\tExpected " + nmtools_string("\033[0;90m<") + expect_typename + nmtools_string(">\033[0m:\n") \
        + STRINGIFY(expect) \
    ; \
    CHECK_MESSAGE(nmtools::utils::apply_isequal(result,expect), \
        message \
    ); \
}

#define NMTOOLS_ASSERT_APPLY_CLOSE_DOCTEST(result,expect) \
{ \
    auto result_typename = nmtools_string(NMTOOLS_TESTING_GET_TYPENAME(decltype(result))); \
    auto expect_typename = nmtools_string(NMTOOLS_TESTING_GET_TYPENAME(decltype(expect))); \
    auto message = std::string{} \
        + "\n\tActual " + nmtools_string("\033[0;90m<") + result_typename + nmtools_string(">\033[0m:\n") \
        + STRINGIFY(result) \
        + "\n\tExpected " + nmtools_string("\033[0;90m<") + expect_typename + nmtools_string(">\033[0m:\n") \
        + STRINGIFY(expect) \
    ; \
    CHECK_MESSAGE(nmtools::utils::apply_isclose(result,expect), \
        message \
    ); \
}

namespace nmtools::testing
{
    // TODO: remove
    template <typename T>
    constexpr auto maybe_shape(const T& t)
    {
        if constexpr (meta::is_maybe_v<T>) {
            using result_type = decltype(shape(*t));
            using return_type = nmtools_maybe<result_type>;
            if (static_cast<bool>(t)) {
                return return_type{shape(*t)};
            } else {
                return return_type{meta::Nothing};
            }
        } else {
            return shape(t);
        }
    }
}

#undef NMTOOLS_ASSERT_CLOSE
#define NMTOOLS_ASSERT_CLOSE NMTOOLS_ASSERT_CLOSE_DOCTEST

#undef NMTOOLS_ASSERT_EQUAL
#define NMTOOLS_ASSERT_EQUAL NMTOOLS_ASSERT_EQUAL_DOCTEST

#undef NMTOOLS_ASSERT_APPLY_EQUAL
#define NMTOOLS_ASSERT_APPLY_EQUAL NMTOOLS_ASSERT_APPLY_EQUAL_DOCTEST

#undef NMTOOLS_ASSERT_APPLY_CLOSE
#define NMTOOLS_ASSERT_APPLY_CLOSE NMTOOLS_ASSERT_APPLY_CLOSE_DOCTEST

// TODO: remove
#define NMTOOLS_ASSERT_SHAPE(result,expect) \
{ \
    NMTOOLS_ASSERT_EQUAL( nmtools::testing::maybe_shape(result), nmtools::testing::maybe_shape(expect) ); \
}

#undef NMTOOLS_ASSERT_EQUAL_MSG_OPERANDS
#define NMTOOLS_ASSERT_EQUAL_MSG_OPERANDS NMTOOLS_ASSERT_EQUAL_MSG_OPERANDS_DOCTEST

#undef NMTOOLS_ASSERT_EQUAL_MSG_ATTRIBUTES
#define NMTOOLS_ASSERT_EQUAL_MSG_ATTRIBUTES NMTOOLS_ASSERT_EQUAL_MSG_ATTRIBUTES_DOCTEST

#undef NMTOOLS_ASSERT_CLOSE_MSG_OPERANDS
#define NMTOOLS_ASSERT_CLOSE_MSG_OPERANDS NMTOOLS_ASSERT_CLOSE_MSG_OPERANDS_DOCTEST

#undef NMTOOLS_ASSERT_NOT_EQUAL
#define NMTOOLS_ASSERT_NOT_EQUAL NMTOOLS_ASSERT_NOT_EQUAL_DOCTEST

#define NMTOOLS_REQUIRE_EQUAL(lhs, rhs) \
{ \
    auto lhs_str = nmtools::utils::to_string(lhs); \
    auto rhs_str = nmtools::utils::to_string(rhs); \
    auto msg_str = nmtools_string("\nActual:\n") + lhs_str + nmtools_string("\nExpected:\n") + rhs_str; \
    REQUIRE_MESSAGE( (nmtools::utils::isequal(lhs, rhs)), msg_str ); \
}

#undef NMTOOLS_STATIC_ASSERT_CLOSE
#define NMTOOLS_STATIC_ASSERT_CLOSE NMTOOLS_STATIC_ASSERT_CLOSE_DOCTEST

#undef NMTOOLS_STATIC_ASSERT_EQUAL
#define NMTOOLS_STATIC_ASSERT_EQUAL NMTOOLS_STATIC_ASSERT_EQUAL_DOCTEST

#if __has_include("doctest/doctest.h")
    #include "doctest/doctest.h"
#else
    #include "doctest.h"
#endif

#if __has_include(<ciso646>)
    #include <ciso646>
#else
    #error "nmtools internal error: can't detect stdlib vendor. TODO: include <version>"
#endif

// at the moment, only libstdc++ that has good constexpr support
#if __GLIBCXX__ && !defined(__EMSCRIPTEN__) && !defined(__ANDROID__) && !defined(__arm__) && !defined(__MINGW32__)
    #define NMTOOLS_TESTING_HAS_CONSTEXPR_MATH true
#else
    #define NMTOOLS_TESTING_HAS_CONSTEXPR_MATH false
#endif

#endif // NMTOOLS_TESTING_DOCTEST_HPP