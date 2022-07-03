#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;

// adapted from boost/type_traits tests suite

struct trivial_except_construct
{
   trivial_except_construct();
   int i;
};

struct trivial_except_destroy
{
   ~trivial_except_destroy();
   int i;
};

struct trivial_except_copy
{
   trivial_except_copy(trivial_except_copy const&);
   int i;
};

struct trivial_except_assign
{
   trivial_except_assign& operator=(trivial_except_assign const&);
   int i;
};

// adapted from en.cppreference example
struct A {
    int m;
};
 
struct B {
    int m1;
private:
    #ifdef __clang__
    [[maybe_unused]]
    #endif
    int m2;
};
 
struct C {
    virtual void foo();
};

TEST_CASE("is_pod(case1)" * doctest::test_suite("meta::is_pod"))
{
    {
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, bool );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, const bool );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, volatile bool );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, const volatile bool );
    }
    {
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, signed char );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, const signed char );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, volatile signed char );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, const volatile signed char );
    }
    {
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, unsigned char );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, const unsigned char );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, volatile unsigned char );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, const volatile unsigned char );
    }
    {
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, unsigned short );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, const unsigned short );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, volatile unsigned short );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, const volatile unsigned short );
    }
    {
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, short );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, const short );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, volatile short );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, const volatile short );
    }
    {
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, unsigned int );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, const unsigned int );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, volatile unsigned int );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, const volatile unsigned int );
    }
    {
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, int );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, const int );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, volatile int );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, const volatile int );
    }
    {
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, unsigned long );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, const unsigned long );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, volatile unsigned long );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, const volatile unsigned long );
    }
    {
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, long );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, const long );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, volatile long );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, const volatile long );
    }
    {
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, float );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, const float );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, volatile float );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, const volatile float );
    }
    {
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, double );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, const double );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, volatile double );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, const volatile double );
    }
    {
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, int );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, void* );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, int*const );
    }
    {
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_pod, int& );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_pod, int&& );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_pod, const int& );
    }
    {
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_pod, trivial_except_copy );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_pod, trivial_except_construct );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_pod, trivial_except_assign );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_pod, trivial_except_destroy );
    }
    {
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_pod, A );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_pod, B );
        NMTOOLS_STATIC_CHECK( !meta::is_pod_v<C> );
    }
}