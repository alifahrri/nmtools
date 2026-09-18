#include "nmtools/utl/flat_map.hpp"
#include "nmtools/utl/static_string.hpp"
#include "nmtools/testing/doctest.hpp"

namespace utl = nmtools::utl;

TEST_CASE("flat_map" * doctest::test_suite("utl"))
{
    {
        utl::flat_map<nm_index_t,utl::static_string> kv;
        NMTOOLS_ASSERT_EQUAL( kv.size(), 0 );
    }
    {
        utl::flat_map<nm_index_t,utl::static_string> kv;
        kv[99] = "hello";
        NMTOOLS_ASSERT_EQUAL( kv.size(), 1 );
        {
            auto isequal = ( kv[99] == "hello" );
            CHECK( isequal );
        }
    }
    {
        utl::flat_map<nm_index_t,utl::static_string> kv;
        kv[99] = "hello";
        NMTOOLS_ASSERT_EQUAL( kv.size(), 1 );
        {
            auto isequal = ( kv[99] == "hello" );
            CHECK( isequal );
        }
        kv.erase(99);
        NMTOOLS_ASSERT_EQUAL( kv.size(), 0 );
        NMTOOLS_ASSERT_EQUAL( kv.count(99), 0 );
    }
    {
        utl::flat_map<nm_index_t,utl::static_string> kv;
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
        utl::flat_map<utl::static_string,utl::static_string> kv;
        kv["hello"] = "world";
        NMTOOLS_ASSERT_EQUAL( kv.size(), 1 );
        {
            auto isequal = ( kv.at("hello") == "world" );
            CHECK( isequal );
        }
    }
    {
        utl::flat_map<utl::static_string,utl::static_string> kv;
        kv["hello"] = "world";
        kv.at("hello") += "!";
        NMTOOLS_ASSERT_EQUAL( kv.size(), 1 );
        {
            auto isequal = ( kv.at("hello") == "world!" );
            CHECK( isequal );
        }
        kv.erase("hello");
        NMTOOLS_ASSERT_EQUAL( kv.size(), 0 );
        NMTOOLS_ASSERT_EQUAL( kv.count("hello"), 0 );
    }
    {
        // emplace: insert new key, re-initialize existing key
        utl::flat_map<int,int> map;
        map.emplace(1,10);
        NMTOOLS_ASSERT_EQUAL( map.size(), 1 );
        NMTOOLS_ASSERT_EQUAL( map.at(1), 10 );
        map.emplace(1,11);
        NMTOOLS_ASSERT_EQUAL( map.size(), 1 );
        NMTOOLS_ASSERT_EQUAL( map.at(1), 11 );
        map.emplace(2,20);
        NMTOOLS_ASSERT_EQUAL( map.size(), 2 );
        NMTOOLS_ASSERT_EQUAL( map.at(2), 20 );
    }
    {
        // grow beyond DIM: small_vector storage falls back to dynamic buffer
        utl::flat_map<int,int,4> map;
        for (int i=0; i<16; i++) {
            map[i] = i*10;
        }
        NMTOOLS_ASSERT_EQUAL( map.size(), 16 );
        for (int i=0; i<16; i++) {
            NMTOOLS_ASSERT_EQUAL( map.at(i), i*10 );
        }
        map.erase(7);
        NMTOOLS_ASSERT_EQUAL( map.size(), 15 );
        NMTOOLS_ASSERT_EQUAL( map.count(7), 0 );
        NMTOOLS_ASSERT_EQUAL( map.at(6), 60 );
        NMTOOLS_ASSERT_EQUAL( map.at(8), 80 );
    }
    {
        // erase from middle and tail of dynamic buffer
        utl::flat_map<int,int,4> map;
        for (int i=0; i<10; i++) {
            map[i] = i;
        }
        map.erase(0);
        map.erase(9);
        NMTOOLS_ASSERT_EQUAL( map.size(), 8 );
        NMTOOLS_ASSERT_EQUAL( map.count(0), 0 );
        NMTOOLS_ASSERT_EQUAL( map.count(9), 0 );
        auto i = 1;
        for (const auto& [k,v] : map) {
            NMTOOLS_ASSERT_EQUAL( k, i );
            NMTOOLS_ASSERT_EQUAL( v, i );
            i++;
        }
    }
    {
        // iteration and inverse map
        utl::flat_map<int,int> map;
        map[1] = 10;
        map[2] = 20;
        map[3] = 20;

        auto inv_map = utl::flat_map<int,int>();
        for (const auto& [k,v] : map) {
            inv_map[v] = k;
        }

        NMTOOLS_ASSERT_EQUAL( inv_map.size(), 2 );
        NMTOOLS_ASSERT_EQUAL( inv_map.count(10), 1 );
        NMTOOLS_ASSERT_EQUAL( inv_map.count(20), 1 );
        NMTOOLS_ASSERT_EQUAL( inv_map.at(10), 1 );
        NMTOOLS_ASSERT_EQUAL( inv_map.at(20), 3 );
    }
    {
        // const access
        utl::flat_map<int,int> map;
        map[2] = 42;
        const auto& cmap = map;
        NMTOOLS_ASSERT_EQUAL( cmap.at(2), 42 );
        NMTOOLS_ASSERT_EQUAL( cmap[2], 42 );
        NMTOOLS_ASSERT_EQUAL( cmap.count(2), 1 );
        NMTOOLS_ASSERT_EQUAL( cmap.size(), 1 );
    }
}
