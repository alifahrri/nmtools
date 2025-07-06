#include "nmtools/array/hardtanh.hpp"
#include "nmtools/testing/data/array/hardtanh.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace view = nmtools::view;

#define RUN_hardtanh_impl(...) \
nm::view::hardtanh(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs hardtanh fn to callable lambda
#define RUN_hardtanh(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("hardtanh-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_hardtanh_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_hardtanh(case_name, ...) \
RUN_hardtanh_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define HARDTANH_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(activations, hardtanh, case_name); \
    using namespace args; \
    auto result = RUN_hardtanh(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("hardtanh(case1)" * doctest::test_suite("view::hardtanh"))
{
    HARDTANH_SUBCASE(case1, a);
    HARDTANH_SUBCASE(case1, a_a);
    HARDTANH_SUBCASE(case1, a_f);
    HARDTANH_SUBCASE(case1, a_h);
    HARDTANH_SUBCASE(case1, a_d);
}