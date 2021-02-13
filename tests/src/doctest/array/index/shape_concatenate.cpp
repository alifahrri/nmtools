#include "nmtools/array/index/shape_concatenate.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/array/index/as_tuple.hpp"

#include "nmtools/constants.hpp"
#include "testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;
namespace idx  = nm::index;
using namespace nm::literals;

NMTOOLS_TESTING_DECLARE_CASE(shape_concatenate)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int axis = 0;
        int ashape[2] = {2,2};
        int bshape[2] = {1,2};
        auto ashape_a = cast<int>(ashape);
        auto ashape_v = cast(ashape,kind::nested_vec);
        auto ashape_d = cast(ashape,kind::dynamic);
        auto ashape_f = cast(ashape,kind::fixed);
        auto ashape_h = cast(ashape,kind::hybrid);
        auto ashape_t = idx::as_tuple(ashape_a);
        auto bshape_a = cast<int>(bshape);
        auto bshape_v = cast(bshape,kind::nested_vec);
        auto bshape_d = cast(bshape,kind::dynamic);
        auto bshape_f = cast(bshape,kind::fixed);
        auto bshape_h = cast(bshape,kind::hybrid);
        auto bshape_t = idx::as_tuple(bshape_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        bool success = true;
        int shape[2] = {3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int axis = 1;
        int ashape[2] = {2,2};
        int bshape[2] = {1,2};
        auto ashape_a = cast<int>(ashape);
        auto ashape_v = cast(ashape,kind::nested_vec);
        auto ashape_d = cast(ashape,kind::dynamic);
        auto ashape_f = cast(ashape,kind::fixed);
        auto ashape_h = cast(ashape,kind::hybrid);
        auto ashape_t = idx::as_tuple(ashape_a);
        auto bshape_a = cast<int>(bshape);
        auto bshape_v = cast(bshape,kind::nested_vec);
        auto bshape_d = cast(bshape,kind::dynamic);
        auto bshape_f = cast(bshape,kind::fixed);
        auto bshape_h = cast(bshape,kind::hybrid);
        auto bshape_t = idx::as_tuple(bshape_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        bool success = false;
        int shape[2] = {0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        int axis = 1;
        int ashape[2] = {2,2};
        int bshape[2] = {2,1};
        auto ashape_a = cast<int>(ashape);
        auto ashape_v = cast(ashape,kind::nested_vec);
        auto ashape_d = cast(ashape,kind::dynamic);
        auto ashape_f = cast(ashape,kind::fixed);
        auto ashape_h = cast(ashape,kind::hybrid);
        auto ashape_t = idx::as_tuple(ashape_a);
        auto bshape_a = cast<int>(bshape);
        auto bshape_v = cast(bshape,kind::nested_vec);
        auto bshape_d = cast(bshape,kind::dynamic);
        auto bshape_f = cast(bshape,kind::fixed);
        auto bshape_h = cast(bshape,kind::hybrid);
        auto bshape_t = idx::as_tuple(bshape_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        bool success = true;
        int shape[2] = {2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        auto axis = None;
        int ashape[2] = {2,2};
        int bshape[2] = {2,1};
        auto ashape_a = cast<int>(ashape);
        auto ashape_v = cast(ashape,kind::nested_vec);
        auto ashape_d = cast(ashape,kind::dynamic);
        auto ashape_f = cast(ashape,kind::fixed);
        auto ashape_h = cast(ashape,kind::hybrid);
        auto ashape_t = idx::as_tuple(ashape_a);
        auto bshape_a = cast<int>(bshape);
        auto bshape_v = cast(bshape,kind::nested_vec);
        auto bshape_d = cast(bshape,kind::dynamic);
        auto bshape_f = cast(bshape,kind::fixed);
        auto bshape_h = cast(bshape,kind::hybrid);
        auto bshape_t = idx::as_tuple(bshape_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        bool success = true;
        int shape[1] = {6};
    }
}

#define RUN_impl(...) \
nm::index::shape_concatenate(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs shape_concatenate fn to callable lambda
#define RUN_shape_concatenate(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("shape_concatenate-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_shape_concatenate(case_name, ...) \
RUN_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#ifdef __clang__
#define SHAPE_CONCATENATE_SUBCASE(case_name, ashape, bshape, axis) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(shape_concatenate, case_name) \
    auto result = RUN_shape_concatenate(case_name, args::ashape, args::bshape, args::axis); \
    auto success = std::get<0>(result); \
    auto shape = std::get<1>(result); \
    NMTOOLS_ASSERT_EQUAL( success, expect::success ); \
    if (expect::success) \
        NMTOOLS_ASSERT_EQUAL( shape, expect::shape ); \
}
#else
#define SHAPE_CONCATENATE_SUBCASE(case_name, ashape, bshape, axis) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(shape_concatenate, case_name) \
    auto [success, shape] = RUN_shape_concatenate(case_name, args::ashape, args::bshape, args::axis); \
    NMTOOLS_ASSERT_EQUAL( success, expect::success ); \
    if (expect::success) \
        NMTOOLS_ASSERT_EQUAL( shape, expect::shape ); \
}
#endif // __clang__

TEST_CASE("shape_concatenate(case1)" * doctest::test_suite("index::shape_concatenate"))
{
    SHAPE_CONCATENATE_SUBCASE( case1, ashape_a, bshape_a, axis );
    SHAPE_CONCATENATE_SUBCASE( case1, ashape_v, bshape_v, axis );
    SHAPE_CONCATENATE_SUBCASE( case1, ashape_h, bshape_h, axis );
}

TEST_CASE("shape_concatenate(case2)" * doctest::test_suite("index::shape_concatenate"))
{
    SHAPE_CONCATENATE_SUBCASE( case2, ashape_a, bshape_a, axis );
    SHAPE_CONCATENATE_SUBCASE( case2, ashape_v, bshape_v, axis );
    SHAPE_CONCATENATE_SUBCASE( case2, ashape_h, bshape_h, axis );
}

TEST_CASE("shape_concatenate(case3)" * doctest::test_suite("index::shape_concatenate"))
{
    SHAPE_CONCATENATE_SUBCASE( case3, ashape_a, bshape_a, axis );
    SHAPE_CONCATENATE_SUBCASE( case3, ashape_v, bshape_v, axis );
    SHAPE_CONCATENATE_SUBCASE( case3, ashape_h, bshape_h, axis );
}

TEST_CASE("shape_concatenate(case4)" * doctest::test_suite("index::shape_concatenate"))
{
    SHAPE_CONCATENATE_SUBCASE( case4, ashape_a, bshape_a, axis );
    SHAPE_CONCATENATE_SUBCASE( case4, ashape_v, bshape_v, axis );
    SHAPE_CONCATENATE_SUBCASE( case4, ashape_h, bshape_h, axis );
}