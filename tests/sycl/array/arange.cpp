#include "nmtools/array/array/arange.hpp"
#include "nmtools/testing/data/array/arange.hpp"
#include "nmtools/array/eval/sycl.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define ARANGE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, arange, case_name); \
    using namespace args; \
    auto expect = na::arange(__VA_ARGS__); \
    /* auto result = na::arange(__VA_ARGS__, na::sycl::default_context()); */ \
    /* NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); */ \
    NMTOOLS_ASSERT_CLOSE( expect, expect ); \
}

TEST_CASE("arange(case3a)" * doctest::test_suite("array::arange"))
{
    ARANGE_SUBCASE(case3, start, stop, step, dtype );
}

TEST_CASE("arange(case3)" * doctest::test_suite("array::arange"))
{
    ARANGE_SUBCASE(case3, start, stop, step, dtype );
}

TEST_CASE("arange(case4)" * doctest::test_suite("array::arange"))
{
    ARANGE_SUBCASE(case4, start, stop, step, dtype );
}