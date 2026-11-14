#include "nmtools/utl/constant_map.hpp"
#include "nmtools/utl/string.hpp"
#include "nmtools/utility/has_value.hpp"
#include "nmtools/utility/unwrap.hpp"
#include "nmtools/testing/doctest.hpp"

namespace utl = nmtools::utl;
using nmtools_tuple, nmtools::ct, nmtools::ct_v;
using namespace nmtools::literals;

TEST_CASE("constant_map" * doctest::test_suite("utl"))
{
    using keys_t   = tuple<ct<2>,ct<3>,ct<5>>;
    using values_t = tuple<ct<1>,int,ct<4>>;
    using ct_map_t = utl::constant_map<keys_t,values_t>;
    {
        auto map = ct_map_t{};

        NMTOOLS_ASSERT_EQUAL( map.size(), 3 );
        NMTOOLS_ASSERT_EQUAL( map[2_ct], 1_ct );
        NMTOOLS_ASSERT_EQUAL( map[3_ct], 0 );
        NMTOOLS_ASSERT_EQUAL( map[5_ct], 4_ct );

        map[3_ct] = 99;
        NMTOOLS_ASSERT_EQUAL( map[3_ct], 99 );
    }
    {
        auto map = ct_map_t{};

        NMTOOLS_ASSERT_EQUAL( map.at(2_ct), 1_ct );
        NMTOOLS_ASSERT_EQUAL( map.at(3_ct), 0 );
        NMTOOLS_ASSERT_EQUAL( map.at(5_ct), 4_ct );

        map.at(3_ct) = 77;
        NMTOOLS_ASSERT_EQUAL( map.at(3_ct), 77 );

        auto const& cmap = map;
        NMTOOLS_ASSERT_EQUAL( cmap.at(2_ct), 1_ct );
        NMTOOLS_ASSERT_EQUAL( cmap.at(3_ct), 77 );
    }
    {
        // count is keyed by value, not by key type (unlike at/operator[])
        auto map = ct_map_t{};

        NMTOOLS_ASSERT_EQUAL( map.count(2), 1 );
        NMTOOLS_ASSERT_EQUAL( map.count(3), 1 );
        NMTOOLS_ASSERT_EQUAL( map.count(5), 1 );

        // missing key
        NMTOOLS_ASSERT_EQUAL( map.count(4), 0 );
        NMTOOLS_ASSERT_EQUAL( map.count(0), 0 );

        // count is unaffected by value mutation
        map[3_ct] = 99;
        NMTOOLS_ASSERT_EQUAL( map.count(3), 1 );
    }
}

TEST_CASE("constant_map.keys" * doctest::test_suite("utl"))
{
    using keys_t   = tuple<ct<2>,ct<3>,ct<5>>;
    using values_t = tuple<ct<1>,int,ct<4>>;
    using ct_map_t = utl::constant_map<keys_t,values_t>;
    {
        constexpr auto keys = ct_map_t::keys();

        // keys come back as the same constant index tuple type
        static_assert( nmtools::meta::is_same_v<nmtools::meta::remove_cvref_t<decltype(keys)>,keys_t> );

        NMTOOLS_ASSERT_EQUAL( nmtools::at(keys,0), 2 );
        NMTOOLS_ASSERT_EQUAL( nmtools::at(keys,1), 3 );
        NMTOOLS_ASSERT_EQUAL( nmtools::at(keys,2), 5 );
    }
}

TEST_CASE("constant_map.insert" * doctest::test_suite("utl"))
{
    using keys_t   = tuple<ct<2>,ct<3>,ct<5>>;
    using values_t = tuple<ct<1>,int,ct<4>>;
    using ct_map_t = utl::constant_map<keys_t,values_t>;

    {
        auto map = ct_map_t{};

        auto map1 = map.insert(7_ct,utl::string("hello"));
        NMTOOLS_ASSERT_EQUAL( map1.size(), 4 );
        NMTOOLS_ASSERT_EQUAL( map1.count(7_ct), 1 );
        CHECK( (map1.at(7_ct) == "hello") );
        
        auto map2 = map.insert(7_ct,utl::string("world"));
        NMTOOLS_ASSERT_EQUAL( map2.size(), 4 );
        NMTOOLS_ASSERT_EQUAL( map2.count(7_ct), 1 );
        CHECK( (map2.at(7_ct) == "world") );
    }
}

TEST_CASE("constant_map" * doctest::test_suite("utl"))
{
    // all values are runtime ints (by-value storage)
    using keys_t   = tuple<ct<2>,ct<3>,ct<5>>;
    using values_t = tuple<int,int,int>;
    using rt_values_map_t = utl::constant_map<keys_t,values_t>;
    {
        auto map = rt_values_map_t{};

        NMTOOLS_ASSERT_EQUAL( map.size(), 3 );
        NMTOOLS_ASSERT_EQUAL( map[2_ct], 0 );
        NMTOOLS_ASSERT_EQUAL( map[3_ct], 0 );
        NMTOOLS_ASSERT_EQUAL( map[5_ct], 0 );

        map[2_ct] = 1;
        map[3_ct] = 3;
        map.at(5_ct) = 5;
        NMTOOLS_ASSERT_EQUAL( map[2_ct], 1 );
        NMTOOLS_ASSERT_EQUAL( map[3_ct], 3 );
        NMTOOLS_ASSERT_EQUAL( map[5_ct], 5 );

        auto const& cmap = map;
        NMTOOLS_ASSERT_EQUAL( cmap.at(2_ct), 1 );
        NMTOOLS_ASSERT_EQUAL( cmap.at(5_ct), 5 );

        NMTOOLS_ASSERT_EQUAL( map.count(4), 0 );
        NMTOOLS_ASSERT_EQUAL( map.count(5), 1 );
    }
}

TEST_CASE("constant_map" * doctest::test_suite("utl"))
{
    // mixed values: constant, runtime int, and utl::string
    using keys_t   = tuple<ct<2>,ct<3>,ct<5>>;
    using values_t = tuple<ct<1>,int,utl::string>;
    using mixed_map_t = utl::constant_map<keys_t,values_t>;
    auto map = mixed_map_t{};
    {
        NMTOOLS_ASSERT_EQUAL( map.size(), 3 );
        NMTOOLS_ASSERT_EQUAL( map[2_ct], 1_ct );
        NMTOOLS_ASSERT_EQUAL( map[3_ct], 0 );
        // isequal() has no utfl::string mapping yet (see the TODO in the header),
        // compare through the string's own operator==
        CHECK_MESSAGE( (map[5_ct] == utl::string{}), "expect empty string" );

        map[3_ct] = 7;
        map[5_ct] = "hello";
        NMTOOLS_ASSERT_EQUAL( map[2_ct], 1_ct );
        NMTOOLS_ASSERT_EQUAL( map[3_ct], 7 );
        CHECK_MESSAGE( (map[5_ct] == "hello"), "expect string value" );

        auto const& cmap = map;
        NMTOOLS_ASSERT_EQUAL( cmap.at(2_ct), 1_ct );
        NMTOOLS_ASSERT_EQUAL( cmap.at(3_ct), 7 );
        CHECK_MESSAGE( (cmap.at(5_ct) == "hello"), "const access of string value" );

        NMTOOLS_ASSERT_EQUAL( map.count(4), 0 );
        NMTOOLS_ASSERT_EQUAL( map.count(5), 1 );
    }
}

TEST_CASE("constant_map.to_value" * doctest::test_suite("utl"))
{
    using keys_t   = tuple<ct<2>,ct<3>,ct<5>>;
    using values_t = tuple<ct<1>,ct<6>,ct<4>>;
    using ct_map_t = utl::constant_map<keys_t,values_t>;

    {
        // all values are compile-time: to_value demotes both keys and
        // values to runtime ints, producing a fully constexpr-evaluable
        // runtime static_map (no longer a constant_map)
        constexpr auto map = nmtools::to_value_v<ct_map_t>;

        using map_t = nmtools::meta::remove_cvref_t<decltype(map)>;
        // NOTE: static_map's capacity is an `auto` NTTP, so its underlying
        // type is part of the type identity. Derive it from the same
        // expression to_value() uses instead of hardcoding 3ul, which only
        // matches on platforms where size_t is unsigned long.
        static_assert( nmtools::meta::is_same_v<map_t,utl::static_map<int,int,nmtools::meta::len_v<keys_t>>> );
        static_assert( nmtools::meta::is_map_v<map_t> );
        static_assert( !nmtools::meta::is_constant_map_v<map_t> );

        NMTOOLS_ASSERT_EQUAL( map.size(), 3 );
        NMTOOLS_ASSERT_EQUAL( map.count(2), 1 );
        NMTOOLS_ASSERT_EQUAL( map.count(3), 1 );
        NMTOOLS_ASSERT_EQUAL( map.count(5), 1 );

        // values are carried over per key
        NMTOOLS_ASSERT_EQUAL( map[2], 1 );
        NMTOOLS_ASSERT_EQUAL( map[3], 6 );
        NMTOOLS_ASSERT_EQUAL( map[5], 4 );

        // missing key
        NMTOOLS_ASSERT_EQUAL( map.count(4), 0 );
    }
    {
        // runtime mutation on a copy: the constexpr original is unaffected
        constexpr auto map = nmtools::to_value_v<ct_map_t>;
        auto copy = map;
        copy[3] = 99;
        NMTOOLS_ASSERT_EQUAL( copy[3], 99 );
        NMTOOLS_ASSERT_EQUAL( map[3], 6 );
    }
    {
        // mixed values: compile-time slots carry their values, runtime
        // slots become NONE
        using mixed_values_t = tuple<ct<1>,int,ct<4>>;
        using mixed_map_t = utl::constant_map<keys_t,mixed_values_t>;

        constexpr auto map = nmtools::to_value_v<mixed_map_t>;

        using map_t = nmtools::meta::remove_cvref_t<decltype(map)>;
        static_assert( nmtools::meta::is_same_v<map_t,utl::static_map<int,nmtools::nullable_num<int>,nmtools::meta::len_v<keys_t>>> );

        NMTOOLS_ASSERT_EQUAL( map.size(), 3 );
        NMTOOLS_ASSERT_EQUAL( map.count(2), 1 );
        NMTOOLS_ASSERT_EQUAL( map.count(3), 1 );
        NMTOOLS_ASSERT_EQUAL( map.count(5), 1 );

        CHECK( nmtools::has_value(map[2]) );
        CHECK( !nmtools::has_value(map[3]) );
        CHECK( nmtools::has_value(map[5]) );
        NMTOOLS_ASSERT_EQUAL( nmtools::unwrap(map[2]), 1 );
        NMTOOLS_ASSERT_EQUAL( nmtools::unwrap(map[5]), 4 );
    }
}
TEST_CASE("constant_map.len" * doctest::test_suite("utl"))
{
    using keys_t   = tuple<ct<2>,ct<3>,ct<5>>;
    using values_t = tuple<ct<1>,int,ct<4>>;
    using ct_map_t = utl::constant_map<keys_t,values_t>;

    // len == number of keys == number of values
    static_assert( nmtools::len_v<ct_map_t> == 3 );

    // max_len falls back to len: also a hard bound
    static_assert( nmtools::max_len_v<ct_map_t> == 3 );
}
