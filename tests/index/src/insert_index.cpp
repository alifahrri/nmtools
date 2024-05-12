#include "nmtools/array/index/insert_index.hpp"
#include "nmtools/utility/flatten_either.hpp"
#include "nmtools/utils/apply_isequal.hpp"
#include "nmtools/utils/apply_to_string.hpp"
#include "nmtools/testing/doctest.hpp"

NMTOOLS_TESTING_DECLARE_CASE(index, insert_index)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int indices[3] = {1,2,3};
        inline int idx  = 4;
        inline int axis = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[4] = {4,1,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int indices[3] = {1,2,3};
        inline int idx  = 4;
        inline int axis = 3;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[4] = {1,2,3,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int indices[3] = {1,2,3};
        inline int idx  = 4;
        inline int axis = 2;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[4] = {1,2,4,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int indices[3] = {1,2,3};
        inline auto idx = Ellipsis;
        inline int axis = 2;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        using slice_t  = nmtools_either<int,ellipsis_t>;
        using slices_t = nmtools_array<slice_t,4>;
        using maybe_slices_t   = nmtools_maybe<slices_t>;
        #if 0
        inline slices_t slices = {1,2,Ellipsis,3};
        #else
        inline slices_t slices = {(slice_t)1,(slice_t)2,(slice_t)Ellipsis,(slice_t)3};
        #endif
        inline auto result = maybe_slices_t{slices};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int indices[3] = {1,2,3};
        inline auto idx = Ellipsis;
        inline int axis = 3;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        using slice_t  = nmtools_either<int,ellipsis_t>;
        using slices_t = nmtools_array<slice_t,4>;
        using maybe_slices_t   = nmtools_maybe<slices_t>;
        #if 0
        inline slices_t slices = {1,2,3,Ellipsis};
        #else
        inline slices_t slices = {(slice_t)1,(slice_t)2,(slice_t)3,(slice_t)Ellipsis};
        #endif
        inline auto result = maybe_slices_t{slices};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int indices[3] = {1,2,3};
        inline auto idx = Ellipsis;
        inline int axis = 4;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline auto result = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int indices[3] = {1,2,3};
        inline int other[2] = {4,5};
        inline int axis = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(other)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int result[5] = {4,5,1,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int indices[3] = {1,2,3};
        inline int other[2] = {4,5};
        inline int axis = 1;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(other)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int result[5] = {1,4,5,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int indices[3] = {1,2,3};
        inline int other[2] = {4,5};
        inline int axis = 2;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(other)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int result[5] = {1,2,4,5,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline int indices[3] = {1,2,3};
        inline int other[2] = {4,5};
        inline int axis = 3;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(other)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline int result[5] = {1,2,3,4,5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline int indices[1] = {1};
        inline auto other = Ellipsis;
        inline auto axis = -1;
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        using slice_t  = nmtools_either<int,ellipsis_t>;
        using slices_t = nmtools_array<slice_t,2>;
        #if 0
        inline auto result = slices_t{1,Ellipsis};
        #else
        inline auto result = slices_t{(slice_t)1,(slice_t)Ellipsis};
        #endif
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        using slice_t  = nmtools_either<int,ellipsis_t>;
        using slices_t = nmtools_array<slice_t,2>;
        #if 0
        inline auto indices = slices_t{1,Ellipsis};
        #else
        inline auto indices = slices_t{(slice_t)1,(slice_t)Ellipsis};
        #endif
        inline int other[1] = {0};
        inline auto axis = -1;
        NMTOOLS_CAST_INDEX_ARRAYS(other)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        using slice_t  = nmtools_either<int,ellipsis_t>;
        using slices_t = nmtools_array<slice_t,3>;
        #if 0
        inline auto result = slices_t{1,Ellipsis,0};
        #else
        inline auto result = slices_t{(slice_t)1,(slice_t)Ellipsis,(slice_t)0};
        #endif
    }
}

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_insert_index_impl(...) \
nm::index::insert_index(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs insert_index fn to callable lambda
#define RUN_insert_index(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("insert_index-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_insert_index_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_insert_index(case_name, ...) \
RUN_insert_index_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define INSERT_INDEX_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(index, insert_index, case_name); \
    using namespace args; \
    auto result = RUN_insert_index(case_name, __VA_ARGS__); \
    auto isequal = nm::utils::apply_isequal( result, expect::result ); \
    CHECK_MESSAGE( isequal, nm::utils::apply_to_string(result )); \
}

TEST_CASE("insert_index(case1)" * doctest::test_suite("index::insert_index"))
{
    INSERT_INDEX_SUBCASE( case1, indices, idx, axis );
    INSERT_INDEX_SUBCASE( case1, indices_a, idx, axis );
    INSERT_INDEX_SUBCASE( case1, indices_v, idx, axis );
    // TODO: implement replace_value_type for ndarray
    // INSERT_INDEX_SUBCASE( case1, indices_f, idx, axis );
    // INSERT_INDEX_SUBCASE( case1, indices_h, idx, axis );
}

TEST_CASE("insert_index(case2)" * doctest::test_suite("index::insert_index"))
{
    INSERT_INDEX_SUBCASE( case2, indices, idx, axis );
    INSERT_INDEX_SUBCASE( case2, indices_a, idx, axis );
    INSERT_INDEX_SUBCASE( case2, indices_v, idx, axis );
}

TEST_CASE("insert_index(case3)" * doctest::test_suite("index::insert_index"))
{
    INSERT_INDEX_SUBCASE( case3, indices, idx, axis );
    INSERT_INDEX_SUBCASE( case3, indices_a, idx, axis );
    INSERT_INDEX_SUBCASE( case3, indices_v, idx, axis );
}

// TODO: fix to_string
#if 0
TEST_CASE("insert_index(case4)" * doctest::test_suite("index::insert_index"))
{
    INSERT_INDEX_SUBCASE( case4, indices, idx, axis );
    INSERT_INDEX_SUBCASE( case4, indices_a, idx, axis );
    INSERT_INDEX_SUBCASE( case4, indices_v, idx, axis );
}

TEST_CASE("insert_index(case5)" * doctest::test_suite("index::insert_index"))
{
    INSERT_INDEX_SUBCASE( case5, indices, idx, axis );
    INSERT_INDEX_SUBCASE( case5, indices_a, idx, axis );
    INSERT_INDEX_SUBCASE( case5, indices_v, idx, axis );
}

TEST_CASE("insert_index(case6)" * doctest::test_suite("index::insert_index"))
{
    INSERT_INDEX_SUBCASE( case6, indices, idx, axis );
    INSERT_INDEX_SUBCASE( case6, indices_a, idx, axis );
    INSERT_INDEX_SUBCASE( case6, indices_v, idx, axis );
}
#endif

TEST_CASE("insert_index(case7)" * doctest::test_suite("index::insert_index"))
{
    INSERT_INDEX_SUBCASE( case7, indices, other, axis );
    INSERT_INDEX_SUBCASE( case7, indices_a, other, axis );
    INSERT_INDEX_SUBCASE( case7, indices_v, other, axis );
}

TEST_CASE("insert_index(case8)" * doctest::test_suite("index::insert_index"))
{
    INSERT_INDEX_SUBCASE( case8, indices, other, axis );
    INSERT_INDEX_SUBCASE( case8, indices_a, other_a, axis );
    INSERT_INDEX_SUBCASE( case8, indices_v, other_v, axis );
}

TEST_CASE("insert_index(case9)" * doctest::test_suite("index::insert_index"))
{
    INSERT_INDEX_SUBCASE( case9, indices, other, axis );
    INSERT_INDEX_SUBCASE( case9, indices_a, other_a, axis );
    INSERT_INDEX_SUBCASE( case9, indices_v, other_v, axis );
}

TEST_CASE("insert_index(case10)" * doctest::test_suite("index::insert_index"))
{
    INSERT_INDEX_SUBCASE( case10, indices, other, axis );
    INSERT_INDEX_SUBCASE( case10, indices_a, other_a, axis );
    INSERT_INDEX_SUBCASE( case10, indices_v, other_v, axis );
}

// TODO: fix to_string
#if 0
TEST_CASE("insert_index(case11)" * doctest::test_suite("index::insert_index"))
{
    INSERT_INDEX_SUBCASE( case11, indices, other, axis );
    INSERT_INDEX_SUBCASE( case11, indices_a, other, axis );
    INSERT_INDEX_SUBCASE( case11, indices_v, other, axis );
}

TEST_CASE("insert_index(case12)" * doctest::test_suite("index::insert_index"))
{
    INSERT_INDEX_SUBCASE( case12, indices, other, axis );
    INSERT_INDEX_SUBCASE( case12, indices, other_a, axis );
    INSERT_INDEX_SUBCASE( case12, indices, other_v, axis );
}
#endif