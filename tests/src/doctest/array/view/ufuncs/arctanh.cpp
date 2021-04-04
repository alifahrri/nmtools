#include "nmtools/array/view/ufuncs/arctanh.hpp"
#include "nmtools/testing/data/array/arctanh.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define RUN_arctanh_impl(...) \
nm::view::arctanh(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs arctanh fn to callable lambda
#define RUN_arctanh(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("arctanh-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_arctanh_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_arctanh(case_name, ...) \
RUN_arctanh_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ARCTANH_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, arctanh, case_name); \
    using namespace args; \
    auto result = RUN_arctanh(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("arctanh(case1)" * doctest::test_suite("view::arctanh"))
{
    ARCTANH_SUBCASE( case1,   a);
    ARCTANH_SUBCASE( case1, a_a);
    ARCTANH_SUBCASE( case1, a_v);
    ARCTANH_SUBCASE( case1, a_f);
    ARCTANH_SUBCASE( case1, a_d);
    ARCTANH_SUBCASE( case1, a_h);
}