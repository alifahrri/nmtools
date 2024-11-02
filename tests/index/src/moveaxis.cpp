#include "nmtools/array/index/moveaxis.hpp"
#include "nmtools/testing/doctest.hpp"

using namespace nmtools::literals;

NMTOOLS_TESTING_DECLARE_CASE(index, moveaxis_to_transpose)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int shape[3] = {1,2,3};
        inline int source = 0;
        inline int destination = 1;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        inline auto shape_ct  = nmtools_tuple{1_ct,2_ct,3_ct};
        inline auto source_ct = 0_ct;
        inline auto destination_ct = 1_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[3] = {1,0,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int shape[3] = {1,2,3};
        inline int source = 1;
        inline int destination = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        inline auto shape_ct  = nmtools_tuple{1_ct,2_ct,3_ct};
        inline auto source_ct = 1_ct;
        inline auto destination_ct = 0_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[3] = {1,0,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int shape[3] = {1,2,3};
        inline int source = 0;
        inline int destination = -2;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        inline auto shape_ct  = nmtools_tuple{1_ct,2_ct,3_ct};
        inline auto source_ct = 0_ct;
        inline auto destination_ct = "-2"_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[3] = {1,0,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int shape[3] = {1,2,3};
        inline int source = 0;
        inline int destination = 2;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        inline auto shape_ct  = nmtools_tuple{1_ct,2_ct,3_ct};
        inline auto source_ct = 0_ct;
        inline auto destination_ct = 2_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[3] = {1,2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int shape[3] = {1,2,3};
        inline int source = 0;
        inline int destination = -1;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        inline auto shape_ct  = nmtools_tuple{1_ct,2_ct,3_ct};
        inline auto source_ct = 0_ct;
        inline auto destination_ct = "-1"_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[3] = {1,2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int shape[3] = {1,2,3};
        inline int source = -1;
        inline int destination = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result[3] = {2,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int shape[3] = {1,2,3};
        inline int source[1] = {-1};
        inline int destination[1] = {0};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(source);
        NMTOOLS_CAST_INDEX_ARRAYS(destination);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int result[3] = {2,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int shape[4] = {1,2,3,4};
        inline int source[1] = {0};
        inline int destination[1] = {-1};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(source);
        NMTOOLS_CAST_INDEX_ARRAYS(destination);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int result[4] = {1,2,3,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int shape[4] = {1,2,3,4};
        inline int source[2] = {0,1};
        inline int destination[2] = {-1,2};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(source);
        NMTOOLS_CAST_INDEX_ARRAYS(destination);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int result[4] = {2,3,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline int shape[4] = {1,2,3,4};
        inline int source[2] = {0,1};
        inline int destination[2] = {3,2};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(source);
        NMTOOLS_CAST_INDEX_ARRAYS(destination);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline int result[4] = {2,3,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline int shape[4] = {1,2,3,4};
        inline int source = 0;
        inline int destination = -1;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline int result[4] = {1,2,3,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        inline int shape[4] = {1,2,3,4};
        inline int source = 0;
        inline int destination = -2;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline int result[4] = {1,2,0,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        inline int shape[4] = {1,2,3,4};
        inline int source = 2;
        inline int destination = 3;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        inline int result[4] = {0,1,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        inline int shape[4] = {1,2,3,4};
        inline int source[1] = {2};
        inline int destination[1] = {1};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(source);
        NMTOOLS_CAST_INDEX_ARRAYS(destination);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        inline int result[4] = {0,2,1,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case15)
    {
        inline int shape[4] = {1,2,3,4};
        // inline int source[2] = {2,0};
        // inline int destination[2] = {1,2};
        inline int source[2] = {2,1};
        inline int destination[2] = {1,0};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(source);
        NMTOOLS_CAST_INDEX_ARRAYS(destination);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        inline int result[4] = {1,2,0,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case16)
    {
        inline int shape[4] = {1,2,3,4};
        inline int source[2] = {2,0};
        inline int destination[2] = {1,2};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(source);
        NMTOOLS_CAST_INDEX_ARRAYS(destination);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case16)
    {
        inline int result[4] = {1,2,0,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case17)
    {
        inline int shape[3] = {1,2,6};
        inline int source = 0;
        inline int destination = 1;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case17)
    {
        inline int result[3] = {1,0,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case18)
    {
        inline int shape[3]       = {1,2,6};
        inline int source[1]      = {0};
        inline int destination[1] = {1};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(source);
        NMTOOLS_CAST_INDEX_ARRAYS(destination);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case18)
    {
        inline int result[3] = {1,0,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case19)
    {
        inline auto shape = nmtools_tuple{1_ct,2_ct,6_ct};
        inline auto source = nmtools_tuple{0_ct};
        inline auto destination = nmtools_tuple{1_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case19)
    {
        inline auto result = nmtools_tuple{1_ct,0_ct,2_ct};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(index, constexpr_moveaxis_to_transpose)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline int shape[3] = {1,2,3};
        constexpr inline int source = 0;
        constexpr inline int destination = 1;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline int result[3] = {1,0,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline int shape[3] = {1,2,3};
        constexpr inline int source = 1;
        constexpr inline int destination = 0;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline int result[3] = {1,0,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline int shape[3] = {1,2,3};
        constexpr inline int source = 0;
        constexpr inline int destination = -2;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline int result[3] = {1,0,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline int shape[3] = {1,2,3};
        constexpr inline int source = 0;
        constexpr inline int destination = 2;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline int result[3] = {1,2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        constexpr inline int shape[3] = {1,2,3};
        constexpr inline int source = 0;
        constexpr inline int destination = -1;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline int result[3] = {1,2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        constexpr inline int shape[3] = {1,2,3};
        constexpr inline int source = -1;
        constexpr inline int destination = 0;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        constexpr inline int result[3] = {2,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        constexpr inline int shape[3] = {1,2,3};
        constexpr inline int source[1] = {-1};
        constexpr inline int destination[1] = {0};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(source);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(destination);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        constexpr inline int result[3] = {2,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        constexpr inline int shape[4] = {1,2,3,4};
        constexpr inline int source[1] = {0};
        constexpr inline int destination[1] = {-1};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(source);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(destination);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        constexpr inline int result[4] = {1,2,3,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        constexpr inline int shape[4] = {1,2,3,4};
        constexpr inline int source[2] = {0,1};
        constexpr inline int destination[2] = {-1,2};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(source);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(destination);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        constexpr inline int result[4] = {2,3,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        constexpr inline int shape[4] = {1,2,3,4};
        constexpr inline int source[2] = {0,1};
        constexpr inline int destination[2] = {3,2};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(source);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(destination);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        constexpr inline int result[4] = {2,3,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        constexpr inline int shape[4] = {1,2,3,4};
        constexpr inline int source = 0;
        constexpr inline int destination = -1;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        constexpr inline int result[4] = {1,2,3,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        constexpr inline int shape[4] = {1,2,3,4};
        constexpr inline int source = 0;
        constexpr inline int destination = -2;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        constexpr inline int result[4] = {1,2,0,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        constexpr inline int shape[4] = {1,2,3,4};
        constexpr inline int source = 2;
        constexpr inline int destination = 3;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        constexpr inline int result[4] = {0,1,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        constexpr inline int shape[4] = {1,2,3,4};
        constexpr inline int source[1] = {2};
        constexpr inline int destination[1] = {1};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(source);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(destination);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        constexpr inline int result[4] = {0,2,1,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case15)
    {
        constexpr inline int shape[4] = {1,2,3,4};
        // inline int source[2] = {2,0};
        // inline int destination[2] = {1,2};
        constexpr inline int source[2] = {2,1};
        constexpr inline int destination[2] = {1,0};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(source);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(destination);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        constexpr inline int result[4] = {1,2,0,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case16)
    {
        constexpr inline int shape[4] = {1,2,3,4};
        constexpr inline int source[2] = {2,0};
        constexpr inline int destination[2] = {1,2};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(source);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(destination);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case16)
    {
        constexpr inline int result[4] = {1,2,0,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case17)
    {
        constexpr inline int shape[3] = {1,2,6};
        constexpr inline int source = 0;
        constexpr inline int destination = 1;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case17)
    {
        constexpr inline int result[3] = {1,0,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case18)
    {
        constexpr inline int shape[3]       = {1,2,6};
        constexpr inline int source[1]      = {0};
        constexpr inline int destination[1] = {1};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(source);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(destination);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case18)
    {
        constexpr inline int result[3] = {1,0,2};
    }
}

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_moveaxis_to_transpose_impl(...) \
nm::index::moveaxis_to_transpose(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs moveaxis_to_transpose fn to callable lambda
#define RUN_moveaxis_to_transpose(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("index::moveaxis_to_transpose-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_moveaxis_to_transpose_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_moveaxis_to_transpose(case_name, ...) \
RUN_moveaxis_to_transpose_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define MOVEAXIS_TO_TRANSPOSE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, moveaxis_to_transpose, case_name); \
    using namespace args; \
    auto result = RUN_moveaxis_to_transpose(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

#define CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, constexpr_moveaxis_to_transpose, case_name); \
    using namespace args; \
    constexpr auto result = RUN_moveaxis_to_transpose_impl(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("moveaxis_to_transpose(case1)" * doctest::test_suite("index::moveaxis_to_transpose"))
{
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case1, shape, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case1, shape_a, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case1, shape_v, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case1, shape_f, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case1, shape_h, source, destination );

    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case1, shape, source_ct, destination_ct );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case1, shape_a, source_ct, destination_ct );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case1, shape_v, source_ct, destination_ct );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case1, shape_f, source_ct, destination_ct );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case1, shape_h, source_ct, destination_ct );

    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case1, shape_ct, source_ct, destination_ct );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case1, shape_ct, source, destination );
}

TEST_CASE("moveaxis_to_transpose(case2)" * doctest::test_suite("index::moveaxis_to_transpose"))
{
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case2, shape, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case2, shape_a, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case2, shape_v, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case2, shape_f, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case2, shape_h, source, destination );

    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case2, shape, source_ct, destination_ct );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case2, shape_a, source_ct, destination_ct );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case2, shape_v, source_ct, destination_ct );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case2, shape_f, source_ct, destination_ct );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case2, shape_h, source_ct, destination_ct );

    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case2, shape_ct, source_ct, destination_ct );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case2, shape_ct, source, destination );
}

TEST_CASE("moveaxis_to_transpose(case3)" * doctest::test_suite("index::moveaxis_to_transpose"))
{
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case3, shape, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case3, shape_a, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case3, shape_v, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case3, shape_f, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case3, shape_h, source, destination );

    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case3, shape, source_ct, destination_ct );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case3, shape_a, source_ct, destination_ct );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case3, shape_v, source_ct, destination_ct );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case3, shape_f, source_ct, destination_ct );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case3, shape_h, source_ct, destination_ct );

    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case3, shape_ct, source_ct, destination_ct );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case3, shape_ct, source, destination );
}

TEST_CASE("moveaxis_to_transpose(case4)" * doctest::test_suite("index::moveaxis_to_transpose"))
{
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case4, shape, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case4, shape_a, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case4, shape_v, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case4, shape_f, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case4, shape_h, source, destination );

    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case4, shape, source_ct, destination_ct );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case4, shape_a, source_ct, destination_ct );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case4, shape_v, source_ct, destination_ct );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case4, shape_f, source_ct, destination_ct );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case4, shape_h, source_ct, destination_ct );

    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case4, shape_ct, source_ct, destination_ct );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case4, shape_ct, source, destination );
}

TEST_CASE("moveaxis_to_transpose(case5)" * doctest::test_suite("index::moveaxis_to_transpose"))
{
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case5, shape, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case5, shape_a, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case5, shape_v, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case5, shape_f, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case5, shape_h, source, destination );

    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case5, shape, source_ct, destination_ct );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case5, shape_a, source_ct, destination_ct );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case5, shape_v, source_ct, destination_ct );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case5, shape_f, source_ct, destination_ct );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case5, shape_h, source_ct, destination_ct );

    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case5, shape_ct, source_ct, destination_ct );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case5, shape_ct, source, destination );
}

TEST_CASE("moveaxis_to_transpose(case6)" * doctest::test_suite("index::moveaxis_to_transpose"))
{
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case6, shape, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case6, shape_a, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case6, shape_v, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case6, shape_f, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case6, shape_h, source, destination );
}

TEST_CASE("moveaxis_to_transpose(case7)" * doctest::test_suite("index::moveaxis_to_transpose"))
{
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case7, shape, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case7, shape_a, source_a, destination_a );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case7, shape_v, source_v, destination_v );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case7, shape_f, source_f, destination_f );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case7, shape_h, source_h, destination_h );
}

TEST_CASE("moveaxis_to_transpose(case8)" * doctest::test_suite("index::moveaxis_to_transpose"))
{
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case8, shape, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case8, shape_a, source_a, destination_a );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case8, shape_v, source_v, destination_v );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case8, shape_f, source_f, destination_f );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case8, shape_h, source_h, destination_h );
}

TEST_CASE("moveaxis_to_transpose(case9)" * doctest::test_suite("index::moveaxis_to_transpose"))
{
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case9, shape, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case9, shape_a, source_a, destination_a );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case9, shape_v, source_v, destination_v );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case9, shape_f, source_f, destination_f );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case9, shape_h, source_h, destination_h );
}

TEST_CASE("moveaxis_to_transpose(case10)" * doctest::test_suite("index::moveaxis_to_transpose"))
{
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case10, shape, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case10, shape_a, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case10, shape_v, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case10, shape_f, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case10, shape_h, source, destination );
}

TEST_CASE("moveaxis_to_transpose(case11)" * doctest::test_suite("index::moveaxis_to_transpose"))
{
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case11, shape, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case11, shape_a, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case11, shape_v, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case11, shape_f, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case11, shape_h, source, destination );
}

TEST_CASE("moveaxis_to_transpose(case12)" * doctest::test_suite("index::moveaxis_to_transpose"))
{
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case12, shape, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case12, shape_a, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case12, shape_v, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case12, shape_f, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case12, shape_h, source, destination );
}

TEST_CASE("moveaxis_to_transpose(case13)" * doctest::test_suite("index::moveaxis_to_transpose"))
{
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case13, shape, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case13, shape_a, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case13, shape_v, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case13, shape_f, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case13, shape_h, source, destination );
}

TEST_CASE("moveaxis_to_transpose(case14)" * doctest::test_suite("index::moveaxis_to_transpose"))
{
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case14, shape, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case14, shape_a, source_a, destination_a );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case14, shape_v, source_v, destination_v );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case14, shape_f, source_f, destination_f );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case14, shape_h, source_h, destination_h );
}

TEST_CASE("moveaxis_to_transpose(case15)" * doctest::test_suite("index::moveaxis_to_transpose"))
{
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case15, shape, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case15, shape_a, source_a, destination_a );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case15, shape_v, source_v, destination_v );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case15, shape_f, source_f, destination_f );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case15, shape_h, source_h, destination_h );
}

TEST_CASE("moveaxis_to_transpose(case16)" * doctest::test_suite("index::moveaxis_to_transpose"))
{
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case16, shape, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case16, shape_a, source_a, destination_a );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case16, shape_v, source_v, destination_v );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case16, shape_f, source_f, destination_f );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case16, shape_h, source_h, destination_h );
}

TEST_CASE("moveaxis_to_transpose(case17)" * doctest::test_suite("index::moveaxis_to_transpose"))
{
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case17, shape, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case17, shape_a, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case17, shape_v, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case17, shape_f, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case17, shape_h, source, destination );
}

TEST_CASE("moveaxis_to_transpose(case18)" * doctest::test_suite("index::moveaxis_to_transpose"))
{
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case18, shape, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case18, shape_a, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case18, shape_v, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case18, shape_f, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case18, shape_h, source, destination );
}

#if defined(__clang__) && (__clang_major__ <= 10)
#define NMTOOLS_NO_CONSTEXPR_MOVEAXIS
#endif // clang 10

TEST_CASE("moveaxis_to_transpose(case1)" * doctest::test_suite("index::constexpr_moveaxis_to_transpose"))
{
    // somehow doesn't work on clang 🤷, works fine on gcc
    // note: non-constexpr function 'operator()<int const (&)[3], const int &>' cannot be used in a constant expression
    // TODO: fix constexpr clang, seems like something to do with at customization point
    #ifndef NMTOOLS_NO_CONSTEXPR_MOVEAXIS
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case1, shape, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case1, shape_a, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case1, shape_f, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case1, shape_h, source, destination );
    #endif // NMTOOLS_NO_CONSTEXPR_MOVEAXIS
}

TEST_CASE("moveaxis_to_transpose(case2)" * doctest::test_suite("index::constexpr_moveaxis_to_transpose"))
{
    #ifndef NMTOOLS_NO_CONSTEXPR_MOVEAXIS
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case2, shape, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case2, shape_a, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case2, shape_f, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case2, shape_h, source, destination );
    #endif // NMTOOLS_NO_CONSTEXPR_MOVEAXIS
}

TEST_CASE("moveaxis_to_transpose(case3)" * doctest::test_suite("index::constexpr_moveaxis_to_transpose"))
{
    #ifndef NMTOOLS_NO_CONSTEXPR_MOVEAXIS
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case3, shape, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case3, shape_a, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case3, shape_f, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case3, shape_h, source, destination );
    #endif // NMTOOLS_NO_CONSTEXPR_MOVEAXIS
}

TEST_CASE("moveaxis_to_transpose(case4)" * doctest::test_suite("index::constexpr_moveaxis_to_transpose"))
{
    #ifndef NMTOOLS_NO_CONSTEXPR_MOVEAXIS
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case4, shape, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case4, shape_a, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case4, shape_f, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case4, shape_h, source, destination );
    #endif // NMTOOLS_NO_CONSTEXPR_MOVEAXIS
}

TEST_CASE("moveaxis_to_transpose(case5)" * doctest::test_suite("index::constexpr_moveaxis_to_transpose"))
{
    #ifndef NMTOOLS_NO_CONSTEXPR_MOVEAXIS
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case5, shape, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case5, shape_a, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case5, shape_f, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case5, shape_h, source, destination );
    #endif // NMTOOLS_NO_CONSTEXPR_MOVEAXIS
}

TEST_CASE("moveaxis_to_transpose(case6)" * doctest::test_suite("index::constexpr_moveaxis_to_transpose"))
{
    #ifndef NMTOOLS_NO_CONSTEXPR_MOVEAXIS
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case6, shape, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case6, shape_a, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case6, shape_f, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case6, shape_h, source, destination );
    #endif // NMTOOLS_NO_CONSTEXPR_MOVEAXIS
}

TEST_CASE("moveaxis_to_transpose(case7)" * doctest::test_suite("index::constexpr_moveaxis_to_transpose"))
{
    #ifndef NMTOOLS_NO_CONSTEXPR_MOVEAXIS
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case7, shape, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case7, shape_a, source_a, destination_a );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case7, shape_f, source_f, destination_f );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case7, shape_h, source_h, destination_h );
    #endif // NMTOOLS_NO_CONSTEXPR_MOVEAXIS
}

TEST_CASE("moveaxis_to_transpose(case8)" * doctest::test_suite("index::constexpr_moveaxis_to_transpose"))
{
    #ifndef NMTOOLS_NO_CONSTEXPR_MOVEAXIS
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case8, shape, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case8, shape_a, source_a, destination_a );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case8, shape_f, source_f, destination_f );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case8, shape_h, source_h, destination_h );
    #endif // NMTOOLS_NO_CONSTEXPR_MOVEAXIS
}

TEST_CASE("moveaxis_to_transpose(case9)" * doctest::test_suite("index::constexpr_moveaxis_to_transpose"))
{
    #ifndef NMTOOLS_NO_CONSTEXPR_MOVEAXIS
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case9, shape, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case9, shape_a, source_a, destination_a );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case9, shape_f, source_f, destination_f );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case9, shape_h, source_h, destination_h );
    #endif // NMTOOLS_NO_CONSTEXPR_MOVEAXIS
}

TEST_CASE("moveaxis_to_transpose(case10)" * doctest::test_suite("index::constexpr_moveaxis_to_transpose"))
{
    #ifndef NMTOOLS_NO_CONSTEXPR_MOVEAXIS
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case10, shape, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case10, shape_a, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case10, shape_f, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case10, shape_h, source, destination );
    #endif // NMTOOLS_NO_CONSTEXPR_MOVEAXIS
}

TEST_CASE("moveaxis_to_transpose(case11)" * doctest::test_suite("index::constexpr_moveaxis_to_transpose"))
{
    #ifndef NMTOOLS_NO_CONSTEXPR_MOVEAXIS
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case11, shape, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case11, shape_a, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case11, shape_f, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case11, shape_h, source, destination );
    #endif // NMTOOLS_NO_CONSTEXPR_MOVEAXIS
}

TEST_CASE("moveaxis_to_transpose(case12)" * doctest::test_suite("index::constexpr_moveaxis_to_transpose"))
{
    #ifndef NMTOOLS_NO_CONSTEXPR_MOVEAXIS
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case12, shape, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case12, shape_a, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case12, shape_f, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case12, shape_h, source, destination );
    #endif // NMTOOLS_NO_CONSTEXPR_MOVEAXIS
}

TEST_CASE("moveaxis_to_transpose(case13)" * doctest::test_suite("index::constexpr_moveaxis_to_transpose"))
{
    #ifndef NMTOOLS_NO_CONSTEXPR_MOVEAXIS
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case13, shape, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case13, shape_a, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case13, shape_f, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case13, shape_h, source, destination );
    #endif // NMTOOLS_NO_CONSTEXPR_MOVEAXIS
}

TEST_CASE("moveaxis_to_transpose(case14)" * doctest::test_suite("index::constexpr_moveaxis_to_transpose"))
{
    #ifndef NMTOOLS_NO_CONSTEXPR_MOVEAXIS
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case14, shape, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case14, shape_a, source_a, destination_a );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case14, shape_f, source_f, destination_f );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case14, shape_h, source_h, destination_h );
    #endif // NMTOOLS_NO_CONSTEXPR_MOVEAXIS
}

TEST_CASE("moveaxis_to_transpose(case15)" * doctest::test_suite("index::constexpr_moveaxis_to_transpose"))
{
    #ifndef NMTOOLS_NO_CONSTEXPR_MOVEAXIS
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case15, shape, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case15, shape_a, source_a, destination_a );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case15, shape_f, source_f, destination_f );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case15, shape_h, source_h, destination_h );
    #endif // NMTOOLS_NO_CONSTEXPR_MOVEAXIS
}

TEST_CASE("moveaxis_to_transpose(case16)" * doctest::test_suite("index::constexpr_moveaxis_to_transpose"))
{
    #ifndef NMTOOLS_NO_CONSTEXPR_MOVEAXIS
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case16, shape, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case16, shape_a, source_a, destination_a );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case16, shape_f, source_f, destination_f );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case16, shape_h, source_h, destination_h );
    #endif // NMTOOLS_NO_CONSTEXPR_MOVEAXIS
}

TEST_CASE("moveaxis_to_transpose(case17)" * doctest::test_suite("index::constexpr_moveaxis_to_transpose"))
{
    #ifndef NMTOOLS_NO_CONSTEXPR_MOVEAXIS
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case17, shape, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case17, shape_a, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case17, shape_f, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case17, shape_h, source, destination );
    #endif // NMTOOLS_NO_CONSTEXPR_MOVEAXIS
}

TEST_CASE("moveaxis_to_transpose(case18)" * doctest::test_suite("index::constexpr_moveaxis_to_transpose"))
{
    // broken on clang 10
    #ifndef NMTOOLS_NO_CONSTEXPR_MOVEAXIS
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case18, shape, source, destination );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case18, shape_a, source_a, destination_a );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case18, shape_f, source_f, destination_f );
    CONSTEXPR_MOVEAXIS_TO_TRANSPOSE_SUBCASE( case18, shape_h, source_h, destination_h );
    #endif // NMTOOLS_NO_CONSTEXPR_MOVEAXIS
}

namespace meta = nmtools::meta;
namespace ix   = nm::index;

// ¯\_(ツ)_/¯
// error: redefinition of 'index' as different kind of symbol
// namespace index = nm::index;

TEST_CASE("moveaxis_to_transpose(case19)" * doctest::test_suite("index::moveaxis_to_transpose"))
{
    #if 1
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case19, shape, source, destination );
    #endif
    {
        NMTOOLS_TESTING_USE_CASE(index, moveaxis_to_transpose, case19);
        // using namespace args;
        constexpr auto shape       = meta::to_value_v<decltype(args::shape)>;
        constexpr auto source      = meta::to_value_v<decltype(args::source)>;
        constexpr auto destination = meta::to_value_v<decltype(args::destination)>;
        NMTOOLS_ASSERT_EQUAL( shape, args::shape );
        NMTOOLS_ASSERT_EQUAL( source, args::source );
        NMTOOLS_ASSERT_EQUAL( destination, args::destination );
        constexpr auto result = ix::moveaxis_to_transpose(shape,source,destination);
        NMTOOLS_ASSERT_EQUAL( result, expect::result );
    }
}