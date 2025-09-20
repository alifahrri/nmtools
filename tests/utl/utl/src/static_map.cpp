#include "nmtools/utl/static_map.hpp"
#include "nmtools/utl/static_string.hpp"
#include "nmtools/testing/doctest.hpp"

namespace utl = nmtools::utl;

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
        CHECK( kv[99] == "hello" );
    }
    {
        utl::static_map<nm_index_t,utl::static_string> kv;
        kv[99] = "hello";
        NMTOOLS_ASSERT_EQUAL( kv.size(), 1 );
        CHECK( kv[99] == "hello" );
        kv.erase(99);
        NMTOOLS_ASSERT_EQUAL( kv.count(99), 0 );
    }
    {
        utl::static_map<nm_index_t,utl::static_string> kv;
        kv[99] = "hello";
        NMTOOLS_ASSERT_EQUAL( kv.size(), 1 );
        CHECK( kv[99] == "hello" );
        kv.at(99) += " world";
        CHECK( kv.at(99) == "hello world" );
    }
    {
        utl::static_map<utl::static_string,utl::static_string> kv;
        kv["hello"] = "world";
        NMTOOLS_ASSERT_EQUAL( kv.size(), 1 );
        CHECK( kv.at("hello") == "world" );
    }
    {
        utl::static_map<utl::static_string,utl::static_string> kv;
        kv["hello"] = "world";
        kv.at("hello") += "!";
        NMTOOLS_ASSERT_EQUAL( kv.size(), 1 );
        CHECK( kv.at("hello") == "world!" );
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
        CHECK( kv[99] == "hello" );
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
        CHECK( kv.at(99) == "hello world" );
    }
}