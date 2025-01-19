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

#include "nmtools/array/ufuncs/cos.hpp"
#include "nmtools/testing/data/array/cos.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define COS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, cos, case_name); \
    using namespace args; \
    auto result = view::cos(__VA_ARGS__); \
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