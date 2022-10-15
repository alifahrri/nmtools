#define NMTOOLS_TESTING_CONSTEXPR
#define NMTOOLS_CONSTEXPR_CAST_ARRAYS_EXTRA(name) \
constexpr inline auto name##_cs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_fb); \
constexpr inline auto name##_cs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_hb); \
constexpr inline auto name##_fs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_fs_fb); \
constexpr inline auto name##_fs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_fs_hb); \
constexpr inline auto name##_hs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_hs_fb); \
constexpr inline auto name##_hs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_hs_hb);

#include "nmtools/array/array/atleast_1d.hpp"
#include "nmtools/testing/data/array/atleast_1d.hpp"

#include "nmtools/array/array/atleast_2d.hpp"
#include "nmtools/testing/data/array/atleast_2d.hpp"

#include "nmtools/array/array/atleast_3d.hpp"
#include "nmtools/testing/data/array/atleast_3d.hpp"

#include "nmtools/testing/arduino.hpp"

using nmtools::array::atleast_1d;
using nmtools::array::atleast_2d;
using nmtools::array::atleast_3d;

NM_TEST_SUBCASE(constexpr_atleast_1d, case1)
{
    NMTOOLS_TESTING_DECLARE_NS( array, constexpr_atleast_1d, case1);
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, result, atleast_1d, a );
}

NM_TEST_SUBCASE(constexpr_atleast_1d, case2)
{
    NMTOOLS_TESTING_DECLARE_NS( array, constexpr_atleast_1d, case2);
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, atleast_1d, a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, atleast_1d, a_a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, atleast_1d, a_f );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, atleast_1d, a_h );

    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, atleast_1d, a_cs_fb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, atleast_1d, a_cs_hb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, atleast_1d, a_fs_fb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, atleast_1d, a_fs_hb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, atleast_1d, a_hs_fb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, atleast_1d, a_hs_hb );
}

NM_TEST_SUBCASE(constexpr_atleast_1d, case3)
{
    NMTOOLS_TESTING_DECLARE_NS( array, constexpr_atleast_1d, case3);
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, result, atleast_1d, a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, result, atleast_1d, a_a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, result, atleast_1d, a_f );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, result, atleast_1d, a_h );

    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, result, atleast_1d, a_cs_fb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, result, atleast_1d, a_cs_hb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, result, atleast_1d, a_fs_fb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, result, atleast_1d, a_fs_hb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, result, atleast_1d, a_hs_fb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, result, atleast_1d, a_hs_hb );
}

NM_TEST_SUBCASE(constexpr_atleast_1d, case4)
{
    NMTOOLS_TESTING_DECLARE_NS( array, constexpr_atleast_1d, case4);
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, atleast_1d, a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, atleast_1d, a_a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, atleast_1d, a_f );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, atleast_1d, a_h );

    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, atleast_1d, a_cs_fb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, atleast_1d, a_cs_hb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, atleast_1d, a_fs_fb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, atleast_1d, a_fs_hb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, atleast_1d, a_hs_fb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, atleast_1d, a_hs_hb );
}

/* --------------------- atleast_2d ------------------------------ */

NM_TEST_SUBCASE(constexpr_atleast_2d, case1)
{
    NMTOOLS_TESTING_DECLARE_NS( array, constexpr_atleast_2d, case1);
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, result, atleast_2d, a );
}

NM_TEST_SUBCASE(constexpr_atleast_2d, case2)
{
    NMTOOLS_TESTING_DECLARE_NS( array, constexpr_atleast_2d, case2);
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, atleast_2d, a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, atleast_2d, a_a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, atleast_2d, a_f );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, atleast_2d, a_h );

    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, atleast_2d, a_cs_fb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, atleast_2d, a_cs_hb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, atleast_2d, a_fs_fb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, atleast_2d, a_fs_hb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, atleast_2d, a_hs_fb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, atleast_2d, a_hs_hb );
}

NM_TEST_SUBCASE(constexpr_atleast_2d, case3)
{
    NMTOOLS_TESTING_DECLARE_NS( array, constexpr_atleast_2d, case3);
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, result, atleast_2d, a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, result, atleast_2d, a_a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, result, atleast_2d, a_f );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, result, atleast_2d, a_h );

    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, result, atleast_2d, a_cs_fb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, result, atleast_2d, a_cs_hb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, result, atleast_2d, a_fs_fb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, result, atleast_2d, a_fs_hb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, result, atleast_2d, a_hs_fb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, result, atleast_2d, a_hs_hb );
}

NM_TEST_SUBCASE(constexpr_atleast_2d, case4)
{
    NMTOOLS_TESTING_DECLARE_NS( array, constexpr_atleast_2d, case4);
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, atleast_2d, a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, atleast_2d, a_a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, atleast_2d, a_f );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, atleast_2d, a_h );

    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, atleast_2d, a_cs_fb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, atleast_2d, a_cs_hb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, atleast_2d, a_fs_fb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, atleast_2d, a_fs_hb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, atleast_2d, a_hs_fb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, atleast_2d, a_hs_hb );
}

/* --------------------- atleast_3d ------------------------------ */

NM_TEST_SUBCASE(constexpr_atleast_3d, case1)
{
    NMTOOLS_TESTING_DECLARE_NS( array, constexpr_atleast_3d, case1);
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, result, atleast_3d, a );
}

NM_TEST_SUBCASE(constexpr_atleast_3d, case2)
{
    NMTOOLS_TESTING_DECLARE_NS( array, constexpr_atleast_3d, case2);
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, atleast_3d, a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, atleast_3d, a_a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, atleast_3d, a_f );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, atleast_3d, a_h );

    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, atleast_3d, a_cs_fb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, atleast_3d, a_cs_hb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, atleast_3d, a_fs_fb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, atleast_3d, a_fs_hb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, atleast_3d, a_hs_fb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, atleast_3d, a_hs_hb );
}

NM_TEST_SUBCASE(constexpr_atleast_3d, case3)
{
    NMTOOLS_TESTING_DECLARE_NS( array, constexpr_atleast_3d, case3);
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, result, atleast_3d, a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, result, atleast_3d, a_a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, result, atleast_3d, a_f );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, result, atleast_3d, a_h );

    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, result, atleast_3d, a_cs_fb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, result, atleast_3d, a_cs_hb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, result, atleast_3d, a_fs_fb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, result, atleast_3d, a_fs_hb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, result, atleast_3d, a_hs_fb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, result, atleast_3d, a_hs_hb );
}

NM_TEST_SUBCASE(constexpr_atleast_3d, case4)
{
    NMTOOLS_TESTING_DECLARE_NS( array, constexpr_atleast_3d, case4);
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, atleast_3d, a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, atleast_3d, a_a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, atleast_3d, a_f );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, atleast_3d, a_h );

    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, atleast_3d, a_cs_fb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, atleast_3d, a_cs_hb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, atleast_3d, a_fs_fb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, atleast_3d, a_fs_hb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, atleast_3d, a_hs_fb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, atleast_3d, a_hs_hb );
}

NM_TEST_SUBCASE(constexpr_atleast_3d, case5)
{
    NMTOOLS_TESTING_DECLARE_NS( array, constexpr_atleast_3d, case5);
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case5, result, atleast_3d, a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case5, result, atleast_3d, a_a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case5, result, atleast_3d, a_f );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case5, result, atleast_3d, a_h );

    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case5, result, atleast_3d, a_cs_fb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case5, result, atleast_3d, a_cs_hb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case5, result, atleast_3d, a_fs_fb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case5, result, atleast_3d, a_fs_hb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case5, result, atleast_3d, a_hs_fb );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case5, result, atleast_3d, a_hs_hb );
}

/* --------------------- runtime ------------------------------ */

#ifndef LED_BUILTIN
#define LED_BUILTIN PC13
#endif

void setup()
{
    // initialize LED digital pin as an output.
    pinMode(LED_BUILTIN, OUTPUT);

    delay(1000);

    UNITY_BEGIN();

    NMTOOLS_PIO_RUN(constexpr_atleast_1d, case1)
    NMTOOLS_PIO_RUN(constexpr_atleast_1d, case2)
    NMTOOLS_PIO_RUN(constexpr_atleast_1d, case3)
    NMTOOLS_PIO_RUN(constexpr_atleast_1d, case4)

    NMTOOLS_PIO_RUN(constexpr_atleast_2d, case1)
    NMTOOLS_PIO_RUN(constexpr_atleast_2d, case2)
    NMTOOLS_PIO_RUN(constexpr_atleast_2d, case3)
    NMTOOLS_PIO_RUN(constexpr_atleast_2d, case4)

    NMTOOLS_PIO_RUN(constexpr_atleast_3d, case1)
    NMTOOLS_PIO_RUN(constexpr_atleast_3d, case2)
    NMTOOLS_PIO_RUN(constexpr_atleast_3d, case3)
    NMTOOLS_PIO_RUN(constexpr_atleast_3d, case4)
    NMTOOLS_PIO_RUN(constexpr_atleast_3d, case5)

    UNITY_END();
}

void loop()
{
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
}