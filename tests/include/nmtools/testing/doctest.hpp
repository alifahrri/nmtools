#ifndef NMTOOLS_TESTING_DOCTEST_HPP
#define NMTOOLS_TESTING_DOCTEST_HPP

#include "nmtools/testing/testing.hpp"

#undef NMTOOLS_ASSERT_CLOSE
#define NMTOOLS_ASSERT_CLOSE NMTOOLS_ASSERT_CLOSE_DOCTEST

#undef NMTOOLS_ASSERT_EQUAL
#define NMTOOLS_ASSERT_EQUAL NMTOOLS_ASSERT_EQUAL_DOCTEST

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