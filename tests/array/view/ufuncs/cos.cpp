#if 1
#define NMTOOLS_CAST_ARRAYS_EXTRA(name) \
inline auto name##_cs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_fb); \
inline auto name##_cs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_hb); \
inline auto name##_cs_db = nmtools::cast(name, nmtools::array::kind::ndarray_cs_db); \
inline auto name##_fs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_fb); \
inline auto name##_fs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_hb); \
inline auto name##_fs_db = nmtools::cast(name, nmtools::array::kind::ndarray_cs_db); \
inline auto name##_hs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_fb); \
inline auto name##_hs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_hb); \
inline auto name##_hs_db = nmtools::cast(name, nmtools::array::kind::ndarray_cs_db); \
inline auto name##_ds_fb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_fb); \
inline auto name##_ds_hb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_hb); \
inline auto name##_ds_db = nmtools::cast(name, nmtools::array::kind::ndarray_cs_db);
#endif

#include "nmtools/array/view/ufuncs/cos.hpp"
#include "nmtools/testing/data/array/cos.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define RUN_cos_impl(...) \
nm::view::cos(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs cos fn to callable lambda
#define RUN_cos(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("cos-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_cos_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_cos(case_name, ...) \
RUN_cos_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define COS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, cos, case_name); \
    using namespace args; \
    auto result = RUN_cos(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("cos(case1)" * doctest::test_suite("view::cos"))
{
    COS_SUBCASE( case1,   a);
    COS_SUBCASE( case1, a_a);
    COS_SUBCASE( case1, a_f);
    COS_SUBCASE( case1, a_d);
    COS_SUBCASE( case1, a_h);

    COS_SUBCASE( case1, a_cs_fb );
    COS_SUBCASE( case1, a_cs_hb );
    COS_SUBCASE( case1, a_cs_db );

    COS_SUBCASE( case1, a_fs_fb );
    COS_SUBCASE( case1, a_fs_hb );
    COS_SUBCASE( case1, a_fs_db );

    COS_SUBCASE( case1, a_hs_fb );
    COS_SUBCASE( case1, a_hs_hb );
    COS_SUBCASE( case1, a_hs_db );

    COS_SUBCASE( case1, a_ds_fb );
    COS_SUBCASE( case1, a_ds_hb );
    COS_SUBCASE( case1, a_ds_db );
}

#define COS_FIXED_SHAPE_SUBCASE(subcase_name, expected_shape, ...) \
SUBCASE(#subcase_name) \
{ \
    auto result = RUN_cos(subcase_name, __VA_ARGS__); \
    using result_t = decltype(result); \
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, result_t ); \
    NMTOOLS_STATIC_ASSERT_EQUAL( meta::fixed_ndarray_shape_v<result_t>, expected_shape ); \
}

TEST_CASE("cos(fixed_shape)" * doctest::test_suite("view::cos"))
{
    namespace meta = nmtools::meta;
    {
        constexpr auto expected_shape = std::array{3};
        int A[3] = {1,2,3};
        COS_FIXED_SHAPE_SUBCASE( raw, expected_shape, A );
    }
    {
        constexpr auto expected_shape = std::array{3};
        auto A = std::array{1,2,3};
        COS_FIXED_SHAPE_SUBCASE( array, expected_shape, A );
    }
    {
        constexpr auto expected_shape = std::array{3};
        auto A = na::fixed_ndarray{{1,2,3}};
        COS_FIXED_SHAPE_SUBCASE( fixed_ndarray, expected_shape, A );
    }
}