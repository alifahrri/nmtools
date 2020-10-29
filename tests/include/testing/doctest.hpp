#ifndef NMTOOLS_TESTING_DOCTEST_HPP
#define NMTOOLS_TESTING_DOCTEST_HPP

#include "testing/testing.hpp"

#undef NMTOOLS_ASSERT_CLOSE
#define NMTOOLS_ASSERT_CLOSE NMTOOLS_ASSERT_CLOSE_DOCTEST

#if __has_include("doctest/doctest.h")
    #include "doctest/doctest.h"
#else
    #include "doctest.h"
#endif

#endif // NMTOOLS_TESTING_DOCTEST_HPP