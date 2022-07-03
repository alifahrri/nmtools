#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;

struct deleted_destructor
{
   deleted_destructor();
   ~deleted_destructor() = delete;
};

TEST_CASE("is_destructible(case1)" * doctest::test_suite("meta::is_destructible"))
{
    {
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, bool );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, const bool );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, volatile bool );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, const volatile bool );
    }
    {
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, signed char );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, const signed char );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, volatile signed char );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, const volatile signed char );
    }
    {
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, unsigned char );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, const unsigned char );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, volatile unsigned char );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, const volatile unsigned char );
    }
    {
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, char );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, const char );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, volatile char );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, const volatile char );
    }
    {
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, unsigned short );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, const unsigned short );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, volatile unsigned short );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, const volatile unsigned short );
    }
    {
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, short );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, const short );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, volatile short );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, const volatile short );
    }
    {
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, unsigned int );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, const unsigned int );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, volatile unsigned int );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, const volatile unsigned int );
    }
    {
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, int );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, const int );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, volatile int );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, const volatile int );
    }
    {
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, long );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, const long );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, volatile long );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, const volatile long );
    }
    {
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, float );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, const float );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, volatile float );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, const volatile float );
    }
    {
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, double );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, const double );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, volatile double );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, const volatile double );
    }
    {
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, void* );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, int*const );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_destructible, void );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_destructible, deleted_destructor );
    }
    {
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, int[2] );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, int[2][3] );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_destructible, int[2][3][2] );
    }
}