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
        {
            auto isequal = ( kv[99] == "hello" );
            CHECK( isequal );
        }
    }
    {
        utl::static_map<nm_index_t,utl::static_string> kv;
        kv[99] = "hello";
        NMTOOLS_ASSERT_EQUAL( kv.size(), 1 );
        {
            auto isequal = ( kv[99] == "hello" );
            CHECK( isequal );
        }
        kv.erase(99);
        NMTOOLS_ASSERT_EQUAL( kv.count(99), 0 );
    }
    {
        utl::static_map<nm_index_t,utl::static_string> kv;
        kv[99] = "hello";
        NMTOOLS_ASSERT_EQUAL( kv.size(), 1 );
        {
            auto isequal = ( kv[99] == "hello" );
            CHECK( isequal );
        }
        kv.at(99) += " world";
        {
            auto isequal = ( kv.at(99) == "hello world" );
            CHECK( isequal );
        }
    }
    {
        utl::static_map<utl::static_string,utl::static_string> kv;
        kv["hello"] = "world";
        NMTOOLS_ASSERT_EQUAL( kv.size(), 1 );
        {
            auto isequal = ( kv.at("hello") == "world" );
            CHECK( isequal );
        }
    }
    {
        utl::static_map<utl::static_string,utl::static_string> kv;
        kv["hello"] = "world";
        kv.at("hello") += "!";
        NMTOOLS_ASSERT_EQUAL( kv.size(), 1 );
        {
            auto isequal = ( kv.at("hello") == "world!" );
            CHECK( isequal );
        }
        kv.erase("hello");
        NMTOOLS_ASSERT_EQUAL( kv.count("hello"), 0 );
    }
    {
        utl::static_map<int,int> map;
        map[1] = 10;
        map[2] = 20;
        map[3] = 20;

        auto inv_map = utl::static_map<int,int>();
        for (const auto& [k,v] : map) {
            inv_map[v] = k;
        }

        NMTOOLS_ASSERT_EQUAL( inv_map.size(), 2 );
        NMTOOLS_ASSERT_EQUAL( inv_map.count(10), 1 );
        NMTOOLS_ASSERT_EQUAL( inv_map.count(20), 1 );
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
        {
            auto isequal = ( kv[99] == "hello" );
            CHECK( isequal );
        }
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
        {
            auto isequal = ( kv.at(99) == "hello world" );
            CHECK( isequal );
        }
    }
}