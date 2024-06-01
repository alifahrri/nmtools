#include "nmtools/array/functional/compress.hpp"
#include "nmtools/testing/data/array/compress.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nm::functional;

#define FUNCTIONAL_SUBCASE(subcase_name, function, ...) \
SUBCASE(subcase_name) \
{ \
    auto result = function (__VA_ARGS__); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("compress(case1)" * doctest::test_suite("functional::compress"))
{
    NMTOOLS_TESTING_USE_CASE(array, compress, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::compress[condition][axis], array );
    FUNCTIONAL_SUBCASE( "case1", fn::compress[condition_a][axis], array_a );
    FUNCTIONAL_SUBCASE( "case1", fn::compress[condition_f][axis], array_f );
    FUNCTIONAL_SUBCASE( "case1", fn::compress[condition_h][axis], array_h );
    FUNCTIONAL_SUBCASE( "case1", fn::compress[condition_v][axis], array_d );
}

#if 1
TEST_CASE("compress(case3)" * doctest::test_suite("functional::compress"))
{
    NMTOOLS_TESTING_USE_CASE(array, compress, case3);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case3", fn::compress[condition][axis], array );
    FUNCTIONAL_SUBCASE( "case3", fn::compress[condition_a][axis], array_a );
    FUNCTIONAL_SUBCASE( "case3", fn::compress[condition_f][axis], array_f );
    FUNCTIONAL_SUBCASE( "case3", fn::compress[condition_h][axis], array_h );
    FUNCTIONAL_SUBCASE( "case3", fn::compress[condition_v][axis], array_d );
}
#endif

// NOTE: unsupported from tuple_append
// TODO: fix
#if 0
TEST_CASE("compress(case5)" * doctest::test_suite("functional::compress"))
{
    NMTOOLS_TESTING_USE_CASE(array, compress, case5);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case5", fn::compress[condition][axis], array );
    FUNCTIONAL_SUBCASE( "case5", fn::compress[condition][axis], array_a );
    FUNCTIONAL_SUBCASE( "case5", fn::compress[condition][axis], array_f );
    FUNCTIONAL_SUBCASE( "case5", fn::compress[condition][axis], array_h );
    FUNCTIONAL_SUBCASE( "case5", fn::compress[condition][axis], array_d );
}
#endif