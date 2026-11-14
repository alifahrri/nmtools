#include <map>
#include "nmtools/index/invert_map.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm  = nmtools;
namespace utl = nmtools::utl;
namespace ix  = nmtools::index;

using namespace nm::literals;
using nmtools_tuple;
using nm::ct;

TEST_CASE("invert_map(case1)" * doctest::test_suite("index"))
{
    using map_t = utl::flat_map<int,int>;

    auto map = map_t{};

    map[1] = 10;
    map[2] = 100;
    map[3] = 1000;

    auto inv_map = ix::invert_map(map);

    using inv_t = nm::remove_cvref_t<decltype(inv_map)>;
    static_assert( nm::is_same_v<inv_t,nmtools_default_map<int,int>> );

    NMTOOLS_ASSERT_EQUAL( inv_map.size(), 3 );

    // values become keys, keys become values
    NMTOOLS_ASSERT_EQUAL( inv_map[10], 1 );
    NMTOOLS_ASSERT_EQUAL( inv_map[100], 2 );
    NMTOOLS_ASSERT_EQUAL( inv_map[1000], 3 );

    NMTOOLS_ASSERT_EQUAL( inv_map.count(7), 0 );

    // empty map
    auto empty_inv = ix::invert_map(map_t{});
    NMTOOLS_ASSERT_EQUAL( empty_inv.size(), 0 );
}

TEST_CASE("invert_map(case2)" * doctest::test_suite("index"))
{
    // static_map has a hard capacity, inverted to a static_map
    // with the same capacity
    using map_t = utl::static_map<int,int,4>;

    auto map = map_t{};

    map[1] = 10;
    map[2] = 100;
    map[3] = 1000;

    auto inv_map = ix::invert_map(map);

    using inv_t = nm::remove_cvref_t<decltype(inv_map)>;
    static_assert( nm::is_same_v<inv_t,utl::static_map<int,int,4>> );

    NMTOOLS_ASSERT_EQUAL( inv_map.size(), 3 );

    NMTOOLS_ASSERT_EQUAL( inv_map[10], 1 );
    NMTOOLS_ASSERT_EQUAL( inv_map[100], 2 );
    NMTOOLS_ASSERT_EQUAL( inv_map[1000], 3 );

    NMTOOLS_ASSERT_EQUAL( inv_map.count(7), 0 );

    // collision: two keys sharing a value collapse, the last one
    // (in iteration order) wins since the inversion uses operator[]
    auto dup = map_t{};
    dup[1] = 10;
    dup[2] = 10;
    auto dup_inv = ix::invert_map(dup);
    NMTOOLS_ASSERT_EQUAL( dup_inv.size(), 1 );
    NMTOOLS_ASSERT_EQUAL( dup_inv[10], 2 );
}

TEST_CASE("invert_map(case3)" * doctest::test_suite("index"))
{
    // std::map is unbounded: inverted to the default (unordered) map
    using map_t = std::map<int,int>;

    auto map = map_t{};

    map[1] = 10;
    map[2] = 100;
    map[3] = 1000;

    auto inv_map = ix::invert_map(map);

    using inv_t = nm::remove_cvref_t<decltype(inv_map)>;
    static_assert( nm::is_same_v<inv_t,nmtools_default_map<int,int>> );

    NMTOOLS_ASSERT_EQUAL( inv_map.size(), 3 );

    NMTOOLS_ASSERT_EQUAL( inv_map[10], 1 );
    NMTOOLS_ASSERT_EQUAL( inv_map[100], 2 );
    NMTOOLS_ASSERT_EQUAL( inv_map[1000], 3 );

    NMTOOLS_ASSERT_EQUAL( inv_map.count(7), 0 );

    // collision: std::map iterates in key order, so the larger key
    // (2) wins over the smaller (1)
    auto dup = map_t{};
    dup[1] = 10;
    dup[2] = 10;
    auto dup_inv = ix::invert_map(dup);
    NMTOOLS_ASSERT_EQUAL( dup_inv.size(), 1 );
    NMTOOLS_ASSERT_EQUAL( dup_inv[10], 2 );
}

TEST_CASE("invert_map(case4)" * doctest::test_suite("index"))
{
    using keys_t   = tuple<ct<2>,ct<3>,ct<5>>;
    using values_t = tuple<ct<1>,ct<6>,ct<4>>;
    using ct_map_t = utl::constant_map<keys_t,values_t>;

    auto map = ct_map_t{};

    auto inv_map = ix::invert_map(map);

    static_assert( nm::is_constant_map_v<decltype(inv_map)> );
    NMTOOLS_ASSERT_EQUAL( inv_map.size(), 3 );

    NMTOOLS_ASSERT_EQUAL( inv_map.count(1_ct), 1 );
    NMTOOLS_ASSERT_EQUAL( inv_map.count(6_ct), 1 );
    NMTOOLS_ASSERT_EQUAL( inv_map.count(4_ct), 1 );

    NMTOOLS_ASSERT_EQUAL( inv_map.count(2_ct), 0 );
    NMTOOLS_ASSERT_EQUAL( inv_map.count(3_ct), 0 );
    NMTOOLS_ASSERT_EQUAL( inv_map.count(5_ct), 0 );

    NMTOOLS_ASSERT_EQUAL( inv_map.at(1_ct), 2_ct );
    NMTOOLS_ASSERT_EQUAL( inv_map.at(6_ct), 3_ct );
    NMTOOLS_ASSERT_EQUAL( inv_map.at(4_ct), 5_ct );
}

TEST_CASE("invert_map(case5)" * doctest::test_suite("index"))
{
    using keys_t   = tuple<ct<2>,ct<3>,ct<5>>;
    using values_t = tuple<ct<1>,int,ct<4>>;
    using ct_map_t = utl::constant_map<keys_t,values_t>;

    auto map = ct_map_t{};

    auto inv_map = ix::invert_map(map);

    static_assert( nm::is_constant_map_v<decltype(inv_map)> );

    // currently reject runtime value, ct map can't handle mixed keys
    NMTOOLS_ASSERT_EQUAL( inv_map.size(), 2 );


    NMTOOLS_ASSERT_EQUAL( inv_map.count(1_ct), 1 );
    NMTOOLS_ASSERT_EQUAL( inv_map.count(4_ct), 1 );

    NMTOOLS_ASSERT_EQUAL( inv_map.count(2_ct), 0 );
    NMTOOLS_ASSERT_EQUAL( inv_map.count(3_ct), 0 );
    NMTOOLS_ASSERT_EQUAL( inv_map.count(5_ct), 0 );
    NMTOOLS_ASSERT_EQUAL( inv_map.count(6_ct), 0 );

    NMTOOLS_ASSERT_EQUAL( inv_map.at(1_ct), 2_ct );
    NMTOOLS_ASSERT_EQUAL( inv_map.at(4_ct), 5_ct );
}