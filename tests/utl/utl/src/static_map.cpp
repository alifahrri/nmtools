#include "nmtools/utl/static_map.hpp"
#include "nmtools/utl/static_string.hpp"
#include "nmtools/testing/doctest.hpp"

namespace utl = nmtools::utl;

#if defined(__arm__) || defined(__thumb__)
    /* We are on an ARM architecture */

    #if __ARM_ARCH == 5 || __ARM_ARCH == 7
        #define DISABLE_CHECK 1
    #else
        #define DISABLE_CHECK 0
    #endif

#else
    /* Not ARM */
    #define DISABLE_CHECK 0
#endif

TEST_CASE("static_map" * doctest::test_suite("utl"))
{
    {
        utl::static_map<nm_index_t,utl::static_string> kv;
        NMTOOLS_ASSERT_EQUAL( kv.size(), 0 );
    }
    {
        utl::static_map<nm_index_t,utl::static_string> kv;
        kv[99] = "hello";
        NMTOOLS_ASSERT_EQUAL( kv.size(), 1 );
        #if !DISABLE_CHECK
        CHECK( kv[99] == "hello" );
        #endif
    }
    {
        utl::static_map<nm_index_t,utl::static_string> kv;
        kv[99] = "hello";
        NMTOOLS_ASSERT_EQUAL( kv.size(), 1 );
        #if !DISABLE_CHECK
        CHECK( kv[99] == "hello" );
        #endif
        kv.erase(99);
        NMTOOLS_ASSERT_EQUAL( kv.count(99), 0 );
    }
    {
        utl::static_map<nm_index_t,utl::static_string> kv;
        kv[99] = "hello";
        NMTOOLS_ASSERT_EQUAL( kv.size(), 1 );
        #if !DISABLE_CHECK
        CHECK( kv[99] == "hello" );
        #endif
        kv.at(99) += " world";
        #if !DISABLE_CHECK
        CHECK( kv.at(99) == "hello world" );
        #endif
    }
    {
        utl::static_map<utl::static_string,utl::static_string> kv;
        kv["hello"] = "world";
        NMTOOLS_ASSERT_EQUAL( kv.size(), 1 );
        #if !DISABLE_CHECK
        CHECK( kv.at("hello") == "world" );
        #endif
    }
    {
        utl::static_map<utl::static_string,utl::static_string> kv;
        kv["hello"] = "world";
        kv.at("hello") += "!";
        NMTOOLS_ASSERT_EQUAL( kv.size(), 1 );
        #if !DISABLE_CHECK
        CHECK( kv.at("hello") == "world!" );
        #endif
        kv.erase("hello");
        NMTOOLS_ASSERT_EQUAL( kv.count("hello"), 0 );
    }
}

TEST_CASE("constexpr_static_map" * doctest::test_suite("utl"))
{
    {
        constexpr utl::static_map<nm_index_t,utl::static_string> kv;
        NMTOOLS_ASSERT_EQUAL( kv.size(), 0 );
    }
    {
        constexpr auto kv = [](){
            utl::static_map<nm_index_t,utl::static_string> kv;
            kv[99] = "hello";
            return kv;
        }();
        NMTOOLS_ASSERT_EQUAL( kv.size(), 1 );
        #if !DISABLE_CHECK
        CHECK( kv[99] == "hello" );
        #endif
    }
    {
        constexpr auto kv = [](){
            utl::static_map<nm_index_t,utl::static_string> kv;
            kv[99] = "hello";
            kv.erase(99);
            return kv;
        }();
        NMTOOLS_ASSERT_EQUAL( kv.count(99), 0 );
    }
    {
        constexpr auto kv = [](){
            utl::static_map<nm_index_t,utl::static_string> kv;
            kv[99] = "hello";
            kv.at(99) += " world";
            return kv;
        }();
        #if !DISABLE_CHECK
        CHECK( kv.at(99) == "hello world" );
        #endif
    }
}