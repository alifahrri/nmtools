#if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
#define NMTOOLS_CAST_ARRAYS_EXTRA(name) \
inline auto name##_cs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_fb); \
inline auto name##_cs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_hb); \
inline auto name##_cs_db = nmtools::cast(name, nmtools::array::kind::ndarray_cs_db); \
inline auto name##_fs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_fs_fb); \
inline auto name##_fs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_fs_hb); \
inline auto name##_fs_db = nmtools::cast(name, nmtools::array::kind::ndarray_fs_db); \
inline auto name##_hs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_hs_fb); \
inline auto name##_hs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_hs_hb); \
inline auto name##_hs_db = nmtools::cast(name, nmtools::array::kind::ndarray_hs_db); \
inline auto name##_ds_fb = nmtools::cast(name, nmtools::array::kind::ndarray_ds_fb); \
inline auto name##_ds_hb = nmtools::cast(name, nmtools::array::kind::ndarray_ds_hb); \
inline auto name##_ds_db = nmtools::cast(name, nmtools::array::kind::ndarray_ds_db);
#endif

#include "nmtools/array/view/var.hpp"
#include "nmtools/testing/data/array/var.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#define RUN_var_impl(...) \
nmtools::view::var(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs var fn to callable lambda
#define RUN_var(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("view::var-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_var_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_var(case_name, ...) \
RUN_var_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define VAR_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, var, case_name); \
    using namespace args; \
    auto result = RUN_var(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("var(case1)" * doctest::test_suite("view::var"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    VAR_SUBCASE( case1, array, axis );
    VAR_SUBCASE( case1, array_a, axis_a );
    VAR_SUBCASE( case1, array_f, axis_f );
    VAR_SUBCASE( case1, array_h, axis );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case1, array_d, axis );

    #else
    VAR_SUBCASE( case1, array_cs_fb, axis );
    VAR_SUBCASE( case1, array_cs_hb, axis );
    VAR_SUBCASE( case1, array_cs_db, axis );
    
    VAR_SUBCASE( case1, array_fs_fb, axis );
    VAR_SUBCASE( case1, array_fs_hb, axis );
    VAR_SUBCASE( case1, array_fs_db, axis );

    // TODO: fix compile
    // VAR_SUBCASE( case1, array_hs_fb, axis );
    // VAR_SUBCASE( case1, array_hs_hb, axis );
    // VAR_SUBCASE( case1, array_hs_db, axis );

    VAR_SUBCASE( case1, array_ds_fb, axis );
    VAR_SUBCASE( case1, array_ds_hb, axis );
    VAR_SUBCASE( case1, array_ds_db, axis );
    #endif
}

TEST_CASE("var(case2)" * doctest::test_suite("view::var"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    VAR_SUBCASE( case2, array, axis );
    VAR_SUBCASE( case2, array_a, axis_a );
    VAR_SUBCASE( case2, array_f, axis_f );
    VAR_SUBCASE( case2, array_h, axis );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case2, array_d, axis );

    #else
    VAR_SUBCASE( case2, array_cs_fb, axis );
    VAR_SUBCASE( case2, array_cs_hb, axis );
    VAR_SUBCASE( case2, array_cs_db, axis );
    
    VAR_SUBCASE( case2, array_fs_fb, axis );
    VAR_SUBCASE( case2, array_fs_hb, axis );
    VAR_SUBCASE( case2, array_fs_db, axis );

    // VAR_SUBCASE( case2, array_hs_fb, axis );
    // VAR_SUBCASE( case2, array_hs_hb, axis );
    // VAR_SUBCASE( case2, array_hs_db, axis );

    VAR_SUBCASE( case2, array_ds_fb, axis );
    VAR_SUBCASE( case2, array_ds_hb, axis );
    VAR_SUBCASE( case2, array_ds_db, axis );
    #endif
}

TEST_CASE("var(case3)" * doctest::test_suite("view::var"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    VAR_SUBCASE( case3, array, axis );
    VAR_SUBCASE( case3, array_a, axis );
    VAR_SUBCASE( case3, array_f, axis );
    VAR_SUBCASE( case3, array_h, axis );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case3, array_d, axis );

    #else
    VAR_SUBCASE( case3, array_cs_fb, axis );
    VAR_SUBCASE( case3, array_cs_hb, axis );
    VAR_SUBCASE( case3, array_cs_db, axis );
    
    VAR_SUBCASE( case3, array_fs_fb, axis );
    VAR_SUBCASE( case3, array_fs_hb, axis );
    VAR_SUBCASE( case3, array_fs_db, axis );

    // VAR_SUBCASE( case3, array_hs_fb, axis );
    // VAR_SUBCASE( case3, array_hs_hb, axis );
    // VAR_SUBCASE( case3, array_hs_db, axis );

    VAR_SUBCASE( case3, array_ds_fb, axis );
    VAR_SUBCASE( case3, array_ds_hb, axis );
    VAR_SUBCASE( case3, array_ds_db, axis );
    #endif
}

TEST_CASE("var(case4)" * doctest::test_suite("view::var"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    VAR_SUBCASE( case4, array, axis );
    VAR_SUBCASE( case4, array_a, axis );
    VAR_SUBCASE( case4, array_f, axis );
    VAR_SUBCASE( case4, array_h, axis );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case4, array_d, axis );

    #else
    VAR_SUBCASE( case4, array_cs_fb, axis );
    VAR_SUBCASE( case4, array_cs_hb, axis );
    VAR_SUBCASE( case4, array_cs_db, axis );
    
    VAR_SUBCASE( case4, array_fs_fb, axis );
    VAR_SUBCASE( case4, array_fs_hb, axis );
    VAR_SUBCASE( case4, array_fs_db, axis );

    // VAR_SUBCASE( case4, array_hs_fb, axis );
    // VAR_SUBCASE( case4, array_hs_hb, axis );
    // VAR_SUBCASE( case4, array_hs_db, axis );

    VAR_SUBCASE( case4, array_ds_fb, axis );
    VAR_SUBCASE( case4, array_ds_hb, axis );
    VAR_SUBCASE( case4, array_ds_db, axis );
    #endif
}

TEST_CASE("var(case5)" * doctest::test_suite("view::var"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    VAR_SUBCASE( case5, array, axis );
    VAR_SUBCASE( case5, array_a, axis );
    VAR_SUBCASE( case5, array_f, axis );
    VAR_SUBCASE( case5, array_h, axis );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case5, array_d, axis );

    #else
    VAR_SUBCASE( case5, array_cs_fb, axis );
    VAR_SUBCASE( case5, array_cs_hb, axis );
    VAR_SUBCASE( case5, array_cs_db, axis );
    
    VAR_SUBCASE( case5, array_fs_fb, axis );
    VAR_SUBCASE( case5, array_fs_hb, axis );
    VAR_SUBCASE( case5, array_fs_db, axis );

    // VAR_SUBCASE( case5, array_hs_fb, axis );
    // VAR_SUBCASE( case5, array_hs_hb, axis );
    // VAR_SUBCASE( case5, array_hs_db, axis );

    VAR_SUBCASE( case5, array_ds_fb, axis );
    VAR_SUBCASE( case5, array_ds_hb, axis );
    VAR_SUBCASE( case5, array_ds_db, axis );
    #endif
}

TEST_CASE("var(case6)" * doctest::test_suite("view::var"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    VAR_SUBCASE( case6,   array, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case6, array_a, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case6, array_f, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case6, array_h, axis, nm::None, ddof, keepdims );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case6, array_d, axis, nm::None, ddof, keepdims );

    #else
    VAR_SUBCASE( case6, array_cs_fb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case6, array_cs_hb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case6, array_cs_db, axis, nm::None, ddof, keepdims );
    
    VAR_SUBCASE( case6, array_fs_fb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case6, array_fs_hb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case6, array_fs_db, axis, nm::None, ddof, keepdims );

    // VAR_SUBCASE( case6, array_hs_fb, axis, nm::None, ddof, keepdims );
    // VAR_SUBCASE( case6, array_hs_hb, axis, nm::None, ddof, keepdims );
    // VAR_SUBCASE( case6, array_hs_db, axis, nm::None, ddof, keepdims );

    VAR_SUBCASE( case6, array_ds_fb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case6, array_ds_hb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case6, array_ds_db, axis, nm::None, ddof, keepdims );
    #endif
}

TEST_CASE("var(case7)" * doctest::test_suite("view::var"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    VAR_SUBCASE( case7,   array, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case7, array_a, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case7, array_f, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case7, array_h, axis, nm::None, ddof, keepdims );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case7, array_d, axis, nm::None, ddof, keepdims );

    #else
    VAR_SUBCASE( case7, array_cs_fb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case7, array_cs_hb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case7, array_cs_db, axis, nm::None, ddof, keepdims );
    
    VAR_SUBCASE( case7, array_fs_fb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case7, array_fs_hb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case7, array_fs_db, axis, nm::None, ddof, keepdims );

    // VAR_SUBCASE( case7, array_hs_fb, axis, nm::None, ddof, keepdims );
    // VAR_SUBCASE( case7, array_hs_hb, axis, nm::None, ddof, keepdims );
    // VAR_SUBCASE( case7, array_hs_db, axis, nm::None, ddof, keepdims );

    VAR_SUBCASE( case7, array_ds_fb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case7, array_ds_hb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case7, array_ds_db, axis, nm::None, ddof, keepdims );
    #endif
}

TEST_CASE("var(case8)" * doctest::test_suite("view::var"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    VAR_SUBCASE( case8,   array, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case8, array_a, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case8, array_f, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case8, array_h, axis, nm::None, ddof, keepdims );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case7, array_d, axis, nm::None, ddof, keepdims );

    #else
    VAR_SUBCASE( case8, array_cs_fb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case8, array_cs_hb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case8, array_cs_db, axis, nm::None, ddof, keepdims );
    
    VAR_SUBCASE( case8, array_fs_fb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case8, array_fs_hb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case8, array_fs_db, axis, nm::None, ddof, keepdims );

    // VAR_SUBCASE( case8, array_hs_fb, axis, nm::None, ddof, keepdims );
    // VAR_SUBCASE( case8, array_hs_hb, axis, nm::None, ddof, keepdims );
    // VAR_SUBCASE( case8, array_hs_db, axis, nm::None, ddof, keepdims );

    VAR_SUBCASE( case8, array_ds_fb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case8, array_ds_hb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case8, array_ds_db, axis, nm::None, ddof, keepdims );
    #endif
}

TEST_CASE("var(case9)" * doctest::test_suite("view::var"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    VAR_SUBCASE( case9,   array, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case9, array_a, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case9, array_f, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case9, array_h, axis, nm::None, ddof, keepdims );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case9, array_d, axis, nm::None, ddof, keepdims );

    #else
    VAR_SUBCASE( case9, array_cs_fb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case9, array_cs_hb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case9, array_cs_db, axis, nm::None, ddof, keepdims );
    
    VAR_SUBCASE( case9, array_fs_fb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case9, array_fs_hb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case9, array_fs_db, axis, nm::None, ddof, keepdims );

    // VAR_SUBCASE( case9, array_hs_fb, axis, nm::None, ddof, keepdims );
    // VAR_SUBCASE( case9, array_hs_hb, axis, nm::None, ddof, keepdims );
    // VAR_SUBCASE( case9, array_hs_db, axis, nm::None, ddof, keepdims );

    VAR_SUBCASE( case9, array_ds_fb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case9, array_ds_hb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case9, array_ds_db, axis, nm::None, ddof, keepdims );
    #endif
}

namespace view = nm::view;
namespace meta = nm::meta;

TEST_CASE("var(case10)" * doctest::test_suite("view::var"))
{
    {
        NMTOOLS_TESTING_DECLARE_NS(array, var, case10);
        using namespace args;

        auto var = view::var(array, axis, nm::None, ddof, keepdims );
        using var_t = decltype(var);
        static_assert( meta::is_either_v<var_t> );

        using left_t  = meta::get_either_left_t<var_t>;
        using right_t = meta::get_either_right_t<var_t>;
        static_assert( meta::is_num_v<left_t> );
        static_assert( meta::is_ndarray_v<right_t> );

        auto value = nmtools::get_if<left_t>(&var);
        NMTOOLS_ASSERT_CLOSE( *value, expect::result );
    }

    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    VAR_SUBCASE( case10,   array, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case10, array_a, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case10, array_f, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case10, array_h, axis, nm::None, ddof, keepdims );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case10, array_d, axis, nm::None, ddof, keepdims );

    #else
    VAR_SUBCASE( case10, array_cs_fb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case10, array_cs_hb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case10, array_cs_db, axis, nm::None, ddof, keepdims );
    
    VAR_SUBCASE( case10, array_fs_fb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case10, array_fs_hb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case10, array_fs_db, axis, nm::None, ddof, keepdims );

    // VAR_SUBCASE( case10, array_hs_fb, axis, nm::None, ddof, keepdims );
    // VAR_SUBCASE( case10, array_hs_hb, axis, nm::None, ddof, keepdims );
    // VAR_SUBCASE( case10, array_hs_db, axis, nm::None, ddof, keepdims );

    VAR_SUBCASE( case10, array_ds_fb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case10, array_ds_hb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case10, array_ds_db, axis, nm::None, ddof, keepdims );
    #endif
}

TEST_CASE("var(case11)" * doctest::test_suite("view::var"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    VAR_SUBCASE( case11,   array, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case11, array_a, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case11, array_f, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case11, array_h, axis, nm::None, ddof, keepdims );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case11, array_d, axis, nm::None, ddof, keepdims );

    #else
    VAR_SUBCASE( case11, array_cs_fb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case11, array_cs_hb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case11, array_cs_db, axis, nm::None, ddof, keepdims );
    
    VAR_SUBCASE( case11, array_fs_fb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case11, array_fs_hb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case11, array_fs_db, axis, nm::None, ddof, keepdims );

    // VAR_SUBCASE( case11, array_hs_fb, axis, nm::None, ddof, keepdims );
    // VAR_SUBCASE( case11, array_hs_hb, axis, nm::None, ddof, keepdims );
    // VAR_SUBCASE( case11, array_hs_db, axis, nm::None, ddof, keepdims );

    VAR_SUBCASE( case11, array_ds_fb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case11, array_ds_hb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case11, array_ds_db, axis, nm::None, ddof, keepdims );
    #endif
}

TEST_CASE("var(case12)" * doctest::test_suite("view::var"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    VAR_SUBCASE( case12,   array, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case12, array_a, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case12, array_f, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case12, array_h, axis, nm::None, ddof, keepdims );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case12, array_d, axis, nm::None, ddof, keepdims );

    #else
    VAR_SUBCASE( case12, array_cs_fb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case12, array_cs_hb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case12, array_cs_db, axis, nm::None, ddof, keepdims );
    
    VAR_SUBCASE( case12, array_fs_fb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case12, array_fs_hb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case12, array_fs_db, axis, nm::None, ddof, keepdims );

    // VAR_SUBCASE( case12, array_hs_fb, axis, nm::None, ddof, keepdims );
    // VAR_SUBCASE( case12, array_hs_hb, axis, nm::None, ddof, keepdims );
    // VAR_SUBCASE( case12, array_hs_db, axis, nm::None, ddof, keepdims );

    VAR_SUBCASE( case12, array_ds_fb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case12, array_ds_hb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case12, array_ds_db, axis, nm::None, ddof, keepdims );
    #endif
}

TEST_CASE("var(case13)" * doctest::test_suite("view::var"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    VAR_SUBCASE( case13,   array, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case13, array_a, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case13, array_f, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case13, array_h, axis, nm::None, ddof, keepdims );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case13, array_d, axis, nm::None, ddof, keepdims );

    #else
    VAR_SUBCASE( case13, array_cs_fb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case13, array_cs_hb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case13, array_cs_db, axis, nm::None, ddof, keepdims );
    
    VAR_SUBCASE( case13, array_fs_fb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case13, array_fs_hb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case13, array_fs_db, axis, nm::None, ddof, keepdims );

    // VAR_SUBCASE( case13, array_hs_fb, axis, nm::None, ddof, keepdims );
    // VAR_SUBCASE( case13, array_hs_hb, axis, nm::None, ddof, keepdims );
    // VAR_SUBCASE( case13, array_hs_db, axis, nm::None, ddof, keepdims );

    VAR_SUBCASE( case13, array_ds_fb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case13, array_ds_hb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case13, array_ds_db, axis, nm::None, ddof, keepdims );
    #endif
}

TEST_CASE("var(case14)" * doctest::test_suite("view::var"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    VAR_SUBCASE( case14,   array, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case14, array_a, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case14, array_f, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case14, array_h, axis, nm::None, ddof, keepdims );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case14, array_d, axis, nm::None, ddof, keepdims );

    #else
    VAR_SUBCASE( case14, array_cs_fb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case14, array_cs_hb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case14, array_cs_db, axis, nm::None, ddof, keepdims );
    
    VAR_SUBCASE( case14, array_fs_fb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case14, array_fs_hb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case14, array_fs_db, axis, nm::None, ddof, keepdims );

    // VAR_SUBCASE( case14, array_hs_fb, axis, nm::None, ddof, keepdims );
    // VAR_SUBCASE( case14, array_hs_hb, axis, nm::None, ddof, keepdims );
    // VAR_SUBCASE( case14, array_hs_db, axis, nm::None, ddof, keepdims );

    VAR_SUBCASE( case14, array_ds_fb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case14, array_ds_hb, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case14, array_ds_db, axis, nm::None, ddof, keepdims );
    #endif
}